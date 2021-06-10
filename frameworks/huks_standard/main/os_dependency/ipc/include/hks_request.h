/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef HKS_REQUEST_H
#define HKS_REQUEST_H

#include "hks_type.h"

enum HksMessage {
    HKS_MSG_BASE = 0x3a400, /* range of message value defined by router. globally unique */

    HKS_MSG_GEN_KEY = HKS_MSG_BASE,
    HKS_MSG_IMPORT_KEY,
    HKS_MSG_EXPORT_PUBLIC_KEY,
    HKS_MSG_DELETE_KEY,
    HKS_MSG_GET_KEY_PARAMSET,
    HKS_MSG_KEY_EXIST,
    HKS_MSG_GENERATE_RANDOM,
    HKS_MSG_SIGN,
    HKS_MSG_SIGN_INIT,
    HKS_MSG_SIGN_UPDATE,
    HKS_MSG_SIGN_FINAL,
    HKS_MSG_VERIFY,
    HKS_MSG_VERIFY_INIT,
    HKS_MSG_VERIFY_UPDATE,
    HKS_MSG_VERIFY_FINAL,
    HKS_MSG_ENCRYPT,
    HKS_MSG_ENCRYPT_INIT,
    HKS_MSG_ENCRYPT_UPDATE,
    HKS_MSG_ENCRYPT_FINAL,
    HKS_MSG_DECRYPT,
    HKS_MSG_DECRYPT_INIT,
    HKS_MSG_DECRYPT_UPDATE,
    HKS_MSG_DECRYPT_FINAL,
    HKS_MSG_AGREE_KEY,
    HKS_MSG_DERIVE_KEY,
    HKS_MSG_MAC,
    HKS_MSG_MAC_INIT,
    HKS_MSG_MAC_UPDATE,
    HKS_MSG_MAC_FINAL,
    HKS_MSG_GET_KEY_INFO_LIST,
    HKS_MSG_ATTEST_KEY,
    HKS_MSG_GET_CERTIFICATE_CHAIN,
    HKS_MSG_WRAP_KEY,
    HKS_MSG_UNWRAP_KEY,
    HKS_MSG_SIGN_WITH_DEVICE_KEY,
    HKS_MSG_PROVISION,
    HKS_MSG_PROVISION_VERIFY,
    HKS_MSG_EXPORT_TRUST_CERTS,
    HKS_MSG_MAX, /* new cmd type must be added before HKS_MSG_MAX */
};

#ifdef __cplusplus
extern "C" {
#endif

/*
 * SendRequest - Send the request message to target module by function call or ipc or other ways.
 * @type:        the request message type.
 * @inBlob:      the input serialized data blob.
 * @outBlob:     the output serialized data blob, can be null.
 */
int32_t HksSendRequest(enum HksMessage type, const struct HksBlob *inBlob, struct HksBlob *outBlob,
    const struct HksParamSet *paramSet);

#ifdef __cplusplus
}
#endif

#endif /* HKS_REQUEST_H */