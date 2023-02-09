/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hks_upgrade_key.h"

#ifdef HKS_CONFIG_FILE
#include HKS_CONFIG_FILE
#else
#include "hks_config.h"
#endif

#include "hks_keyblob.h"
#include "hks_log.h"
#include "hks_mandatory_params.h"
#include "hks_mem.h"
#include "hks_template.h"
#include "hks_type.h"

#include "securec.h"

#ifdef HKS_ENABLE_UPGRADE_KEY
static const struct HksMandatoryParams* GetMandatoryParams(uint32_t keyVersion)
{
    if (HKS_ARRAY_SIZE(HKS_MANDATORY_PARAMS) < keyVersion ||
        HKS_MANDATORY_PARAMS[keyVersion - 1].keyVersion != keyVersion) {
        HKS_LOG_E("get mandatory params for version %" LOG_PUBLIC "u failed!", keyVersion);
        return NULL;
    }
    return &HKS_MANDATORY_PARAMS[keyVersion - 1];
}

static bool IsTagInMandatoryArray(uint32_t tag, uint32_t keyVersion)
{
    uint32_t i = 0;
    const struct HksMandatoryParams* mandatoryParams = GetMandatoryParams(keyVersion);
    if (mandatoryParams == NULL) {
        return false;
    }
    for (;i < mandatoryParams->paramsLen; ++i) {
        if (tag == mandatoryParams->params[i]) {
            return true;
        }
    }
    return false;
}

static int32_t AddParamsWithoutMandatory(uint32_t keyVersion, const struct HksParamSet *srcParamSet,
    const struct HksParamSet *paramSet, struct HksParamSet *targetParamSet)
{
    (void)paramSet;
    int32_t ret = HKS_SUCCESS;

    uint32_t i = 0;
    for (; i < srcParamSet->paramsCnt; ++i) {
        if (!IsTagInMandatoryArray(srcParamSet->params[i].tag, keyVersion)) {
            ret = HksAddParams(targetParamSet, &(srcParamSet->params[i]), 1);
            if (ret != HKS_SUCCESS) {
                HKS_LOG_E("append param %" LOG_PUBLIC "u failed", srcParamSet->params[i].tag);
                break;
            }
        }
    }
    return ret;
}

#ifdef HKS_ENABLE_MARK_CLEARED_FOR_SMALL_TO_SERVICE
static int32_t HksChangeProcessNameParam(const struct HksParamSet *srcParamSet, const struct HksParamSet *paramSet,
    struct HksParamSet *targetParamSet)
{
    (void)srcParamSet;
    struct HksParam *processName = NULL;
    int32_t ret = HksGetParam(paramSet, &processName);
    if (ret == HKS_ERROR_PARAM_NOT_EXIST) {
        return HKS_SUCCESS;
    }

    struct HksParam *newProcessName = NULL;
    ret = HksGetParam(targetParamSet, &newProcessName);
    HKS_IF_NOT_SUCC_LOGE_RETURN(ret, ret, "get process name failed!")

    // no need to free old blob for it's mem is same as in srcParamSet
    newProcessName->blob.data = processName->blob.data;
    newProcessName->blob.size = processName->blob.size;
    return ret;
}
#endif

static int32_t AddMandatoryParams(const struct HksParamSet *srcParamSet, const struct HksParamSet *paramSet,
    struct HksParamSet *targetParamSet)
{
    int32_t ret = HKS_SUCCESS;
    uint32_t i = 0;
    const struct HksMandatoryParams* mandatoryParams = GetMandatoryParams(HKS_KEY_VERSION);
    for (; i < mandatoryParams->paramsLen; ++i) {
        struct HksParam *param = NULL;
        ret = HksGetParam(paramSet, mandatoryParams->params[i], &param);
        if (ret != HKS_SUCCESS) {
            ret = HksGetParam(srcParamSet, mandatoryParams->params[i], &param);
        }
        HKS_IF_NOT_SUCC_LOGE_RETURN(ret, ret, "get param %" LOG_PUBLIC "u from srcParamSet and paramSet failed!",
            mandatoryParams->params[i])
        ret = HksAddParams(targetParamSet, param, 1);
        HKS_IF_NOT_SUCC_LOGE_RETURN(ret, ret, "add param %" LOG_PUBLIC "u into targetParamSet failed!",
            mandatoryParams->params[i])
    }
    return ret;
}

static int32_t AddMandatoryeParamsInCore(const struct HksParamSet *keyBlobParamSet,
    const struct HksParamSet *srcParamSet, struct HksParamSet **targetParamSet)
{
    (void)keyBlobParamSet;
    (void)srcParamSet;
    struct HksParamSet *outParamSet = NULL;
    int32_t ret;
    do {
        ret = HksInitParamSet(&outParamSet);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "init paramset failed!")

        ret = HksAddParams(outParamSet, srcParamSet->params, srcParamSet->paramsCnt);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "add params from srcParamSet to targetParamSet failed!")

        struct HksParam HksParamKeyVerison = { .tag = HKS_TAG_KEY_VERSION, .uint32Param = HKS_KEY_VERSION };
        ret = HksAddParams(outParamSet, &HksParamKeyVerison, 1);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "add param HksParamKeyVerison failed!")

        struct HksParam HksParamOsLevel = { .tag = HKS_TAG_OS_VERSION, .uint32Param = HKS_KEY_BLOB_DUMMY_OS_VERSION };
        ret = HksAddParams(outParamSet, &HksParamOsLevel, 1);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "add param HksParamOsLevel failed!")

        struct HksParam HksOsPatchLevel = { .tag = HKS_TAG_OS_PATCHLEVEL,
            .uint32Param = HKS_KEY_BLOB_DUMMY_OS_PATCHLEVEL };
        ret = HksAddParams(outParamSet, &HksOsPatchLevel, 1);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "add param HksOsPatchLevel failed!")
        *targetParamSet = outParamSet;
        return ret;
    } while (0);
    HksFreeParamSet(&outParamSet);
    return ret;
}

int32_t HksUpgradeKey(const struct HksBlob *oldKey, const struct HksParamSet *paramSet, struct HksBlob *newKey)
{
    HKS_LOG_I("enter HksUpgradeKey");
    int32_t ret;
    struct HksParamSet *oldKeyBlobParamSet = NULL;
    struct HksParamSet *newKeyBlobParamSet = NULL;
    struct HksKeyNode *keyNode = NULL;
    struct HksParamSet *newParamSet = NULL;
    do {
        keyNode = HksGenerateKeyNode(oldKey);
        if (keyNode == NULL) {
            ret = HKS_ERROR_BAD_STATE;
            HKS_LOG_E("generate key node failed!");
            break;
        }
        
        ret = HksInitParamSet(&newKeyBlobParamSet);
        if (ret != HKS_SUCCESS) {
            break;
        }

        ret = HksGetParamSet(keyNode->paramSet, keyNode->paramSet->paramSetSize, &oldKeyBlobParamSet);
        if (ret != HKS_SUCCESS) {
            break;
        }

        struct HksParam *keyVersion = NULL;
        ret = HksGetParam(oldKeyBlobParamSet, HKS_TAG_KEY_VERSION, &keyVersion);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "get key version failed!")

        ret = AddMandatoryeParamsInCore(oldKeyBlobParamSet, paramSet, &newParamSet);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "AddMandatoryeParamsInCore failed!")

        // the key param must be the last one added
        ret = AddMandatoryParams(oldKeyBlobParamSet, newParamSet, newKeyBlobParamSet);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "AddMandatoryParams failed!")

        ret = AddParamsWithoutMandatory(keyVersion->uint32Param, oldKeyBlobParamSet, newParamSet, newKeyBlobParamSet);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "AddParamsWithoutMandatory failed!")

#ifdef HKS_ENABLE_MARK_CLEARED_FOR_SMALL_TO_SERVICE
        ret = HksChangeProcessNameParam(oldKeyBlobParamSet, newParamSet, newKeyBlobParamSet);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "HksChangeProcessNameParam failed!")
#endif
        ret = HksBuildParamSet(&newKeyBlobParamSet);
        HKS_IF_NOT_SUCC_LOGE_BREAK(ret, "build newKeyBlobParamSet failed!")

        ret = HksBuildKeyBlobWithOutAdd(newKeyBlobParamSet, newKey);
    } while (0);
    
    HksFreeParamSet(&newKeyBlobParamSet);
    HksFreeParamSet(&oldKeyBlobParamSet);
    HksFreeParamSet(&newParamSet);
    HksFreeKeyNode(&keyNode);

    return ret;
}

#else /* HKS_ENABLE_UPGRADE_KEY */
int32_t HksUpgradeKey(const struct HksBlob *oldKey, const struct HksParamSet *paramSet, struct HksBlob *newKey)
{
    (void)oldKey;
    (void)paramSet;
    (void)newKey;
    return HKS_SUCCESS;
}
#endif