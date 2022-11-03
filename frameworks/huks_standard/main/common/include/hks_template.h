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

#ifndef HKS_TEMPLATE_H
#define HKS_TEMPLATE_H

#define HKS_EXCEPRTION_HALDER_LOGE_RETURN(ERROR_CODE, LOG_MESSAGE, ...) \
if (ret != HKS_SUCCESS) { \
    HKS_LOG_E(LOG_MESSAGE, ##__VA_ARGS__); \
    return ERROR_CODE; \
}

#define HKS_EXCEPRTION_HALDER_LOGE_BREAK(LOG_MESSAGE, ...) \
if (ret != HKS_SUCCESS) { \
    HKS_LOG_E(LOG_MESSAGE, ##__VA_ARGS__); \
    break; \
}

#define HKS_EXCEPRTION_HALDER_LOGE(LOG_MESSAGE, ...) \
if (ret != HKS_SUCCESS) { \
    HKS_LOG_E(LOG_MESSAGE, ##__VA_ARGS__); \
}

#define HKS_EXCEPRTION_HALDER_RETURN(ERROR_CODE) \
if (ret != HKS_SUCCESS) { \
    return ERROR_CODE; \
}

#endif /* HKS_TEMPLATE_H */
