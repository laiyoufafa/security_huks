/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "hksupdate_fuzzer.h"

#include <securec.h>

#include "hks_api.h"
#include "hks_mem.h"
#include "hks_param.h"
#include "hks_type.h"

const int BLOB_SIZE = 10;
const int DOUBLE_BLOB_SIZE = 20;
const int TRIPLE_BLOB_SIZE = 30;

namespace OHOS {
    bool DoSomethingInterestingWithMyAPI(const uint8_t *data, size_t size)
    {
        if (data == nullptr || size <= (sizeof(struct HksParamSet) + TRIPLE_BLOB_SIZE)) {
            return false;
        }

        uint8_t *myData = (uint8_t *)HksMalloc(sizeof(uint8_t) * size);
        if (myData == nullptr) {
            return false;
        }

        (void)memcpy_s(myData, size, data, size);

        struct HksBlob handle = { BLOB_SIZE, (uint8_t *)myData };
        struct HksBlob inData = { BLOB_SIZE, (uint8_t *)(myData + BLOB_SIZE) };
        struct HksBlob outData = { BLOB_SIZE, (uint8_t *)(myData + DOUBLE_BLOB_SIZE) };

        struct HksParamSet *paramSet = (struct HksParamSet *)(myData + TRIPLE_BLOB_SIZE);
        paramSet->paramSetSize = size - DOUBLE_BLOB_SIZE;

        (void)HksUpdate(&handle, paramSet, &inData, &outData);

        if (myData != nullptr) {
            HksFree(myData);
        }

        return true;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}