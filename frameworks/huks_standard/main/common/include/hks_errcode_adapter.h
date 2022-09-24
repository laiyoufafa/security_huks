/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef HKS_ERRCODE_ADAPTER_H
#define HKS_ERRCODE_ADAPTER_H

#include "hks_type.h"

struct HksResult {
    int32_t errorCode;
    const char *errorMsg;
    uint8_t *data;
};

struct HksError {
    int32_t oldErrCode;
    struct HksResult hksResult;
};

#ifdef __cplusplus
extern "C" {
#endif

HKS_API_EXPORT struct HksResult ConvertErrCode(int32_t result);
#ifdef __cplusplus
}
#endif

#endif /* HKS_ERRCODE_ADAPTER_H */
