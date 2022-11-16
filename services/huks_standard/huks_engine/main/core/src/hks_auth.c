/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "hks_auth.h"

#include <stddef.h>

#include "hks_log.h"
#include "hks_param.h"
#include "hks_template.h"

struct HksAuthPolicy {
    uint32_t authId;
    uint32_t policyCnt;
    uint32_t *policyTag;
};

#ifndef _CUT_AUTHENTICATE_
static uint32_t g_symCipherPolicyTag[] = { HKS_TAG_ALGORITHM, HKS_TAG_BLOCK_MODE, HKS_TAG_PADDING, HKS_TAG_PURPOSE };
static uint32_t g_asymCipherPolicyTag[] = { HKS_TAG_ALGORITHM, HKS_TAG_DIGEST, HKS_TAG_PADDING, HKS_TAG_PURPOSE };
static uint32_t g_signVerifyRsaPolicyTag[] = { HKS_TAG_ALGORITHM, HKS_TAG_DIGEST, HKS_TAG_PADDING, HKS_TAG_PURPOSE };
static uint32_t g_signVerifyEccPolicyTag[] = { HKS_TAG_ALGORITHM, HKS_TAG_DIGEST, HKS_TAG_PURPOSE };
static uint32_t g_signVerifyEd25519PolicyTag[] = { HKS_TAG_PURPOSE };
static uint32_t g_macPolicyTag[] = { HKS_TAG_DIGEST, HKS_TAG_PURPOSE };
static uint32_t g_macSm3PolicyTag[] = { HKS_TAG_ALGORITHM, HKS_TAG_DIGEST, HKS_TAG_PURPOSE };
static uint32_t g_derivePolicyTag[] = { HKS_TAG_DIGEST, HKS_TAG_PURPOSE };
static uint32_t g_agreePolicyTag[] = { HKS_TAG_PURPOSE };

struct HksAuthPolicy g_authPolicyList[] = {
    { HKS_AUTH_ID_SYM_CIPHER, HKS_ARRAY_SIZE(g_symCipherPolicyTag), g_symCipherPolicyTag },
    { HKS_AUTH_ID_ASYM_CIPHER, HKS_ARRAY_SIZE(g_asymCipherPolicyTag), g_asymCipherPolicyTag },
    { HKS_AUTH_ID_SIGN_VERIFY_RSA, HKS_ARRAY_SIZE(g_signVerifyRsaPolicyTag), g_signVerifyRsaPolicyTag },
    { HKS_AUTH_ID_SIGN_VERIFY_ECC, HKS_ARRAY_SIZE(g_signVerifyEccPolicyTag), g_signVerifyEccPolicyTag },
    { HKS_AUTH_ID_SIGN_VERIFY_ED25519, HKS_ARRAY_SIZE(g_signVerifyEd25519PolicyTag), g_signVerifyEd25519PolicyTag },
    { HKS_AUTH_ID_MAC_HMAC, HKS_ARRAY_SIZE(g_macPolicyTag), g_macPolicyTag },
    { HKS_AUTH_ID_MAC_SM3, HKS_ARRAY_SIZE(g_macSm3PolicyTag), g_macSm3PolicyTag },
    { HKS_AUTH_ID_DERIVE, HKS_ARRAY_SIZE(g_derivePolicyTag), g_derivePolicyTag },
    { HKS_AUTH_ID_AGREE, HKS_ARRAY_SIZE(g_agreePolicyTag), g_agreePolicyTag }
};

static int32_t CheckPurpose(const struct HksParam *authParam, const struct HksParam *requestParam)
{
    if (requestParam->uint32Param == 0) {
        return HKS_ERROR_INVALID_ARGUMENT;
    }
    if ((requestParam->uint32Param & authParam->uint32Param) != requestParam->uint32Param) {
        return HKS_ERROR_INVALID_ARGUMENT;
    }
    return HKS_SUCCESS;
}

static int32_t AuthPolicy(const struct HksAuthPolicy *policy, const struct HksParamSet *keyBlobParamSet,
    const struct HksParamSet *paramSet)
{
    int32_t ret;
    uint32_t authTag;
    struct HksParam *authParam = NULL;
    struct HksParam *requestParam = NULL;

    for (uint32_t i = 0; i < policy->policyCnt; i++) {
        authTag = policy->policyTag[i];
        ret = HksGetParam(keyBlobParamSet, authTag, &authParam);
        HKS_IF_NOT_SUCC_LOGE_RETURN(ret, ret, "get auth param[0x%" LOG_PUBLIC "x] failed!", authTag)

        ret = HksGetParam(paramSet, authTag, &requestParam);
        HKS_IF_NOT_SUCC_LOGE_RETURN(ret, ret, "get request param[0x%" LOG_PUBLIC "x] failed!", authTag)

        if (authTag != HKS_TAG_PURPOSE) {
            ret = HksCheckParamMatch((const struct HksParam *)authParam, (const struct HksParam *)requestParam);
        } else {
            ret = CheckPurpose((const struct HksParam *)authParam, (const struct HksParam *)requestParam);
        }
        HKS_IF_NOT_SUCC_LOGE_RETURN(ret, ret,
            "unmatch policy[0x%" LOG_PUBLIC "x], [0x%" LOG_PUBLIC "x] != [0x%" LOG_PUBLIC "x]!",
            authTag, requestParam->uint32Param, authParam->uint32Param)
    }
    return HKS_SUCCESS;
}

int32_t HksAuth(uint32_t authId, const struct HksKeyNode *keyNode, const struct HksParamSet *paramSet)
{
    for (uint32_t i = 0; i < HKS_ARRAY_SIZE(g_authPolicyList); i++) {
        if (authId == g_authPolicyList[i].authId) {
            return AuthPolicy(&g_authPolicyList[i], keyNode->paramSet, paramSet);
        }
    }
    return HKS_ERROR_BAD_STATE;
}

int32_t HksThreeStageAuth(uint32_t authId, const struct HuksKeyNode *keyNode)
{
    for (uint32_t i = 0; i < HKS_ARRAY_SIZE(g_authPolicyList); i++) {
        if (authId == g_authPolicyList[i].authId) {
            return AuthPolicy(&g_authPolicyList[i], keyNode->keyBlobParamSet, keyNode->runtimeParamSet);
        }
    }
    return HKS_ERROR_BAD_STATE;
}
#endif /* _CUT_AUTHENTICATE_ */
