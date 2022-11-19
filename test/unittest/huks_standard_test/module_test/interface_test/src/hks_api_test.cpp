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

#include "hks_api_test.h"

#include <gtest/gtest.h>
#include <thread>
#include <unistd.h>

#include "hks_api.h"
#include "hks_log.h"
#include "hks_mem.h"
#include "hks_param.h"
#include "hks_type.h"

#include "securec.h"

using namespace testing::ext;
namespace Unittest::HksAPITest {
class HksAPITest : public testing::Test {
public:
    static void SetUpTestCase(void);

    static void TearDownTestCase(void);

    void SetUp();

    void TearDown();
};

void HksAPITest::SetUpTestCase(void)
{
}

void HksAPITest::TearDownTestCase(void)
{
}

void HksAPITest::SetUp()
{
    EXPECT_EQ(HksInitialize(), 0);
}

void HksAPITest::TearDown()
{
}

/**
 * @tc.name: HksAPITest.HksAPITest001
 * @tc.desc: tdd HksGetSdkVersion,  expecting HKS_SUCCESS
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest001, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest001");
    const uint32_t sdkSize = 32;
    struct HksBlob sdkVer = { .size = sdkSize, .data = (uint8_t *)HksMalloc(sdkSize)};
    int32_t ret = HksGetSdkVersion(&sdkVer);
    EXPECT_EQ(ret, HKS_SUCCESS) << "HksGetSdkVersion failed, ret = " << ret;
    HksFree(sdkVer.data);
}

/**
 * @tc.name: HksAPITest.HksAPITest002
 * @tc.desc: tdd HksAbort with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest002, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest002");
    int32_t ret = HksAbort(nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksAbort failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest003
 * @tc.desc: tdd HksFinish with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest003, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest003");
    int32_t ret = HksFinish(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksFinish failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest004
 * @tc.desc: tdd HksUpdate with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest004, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest004");
    int32_t ret = HksUpdate(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksFinish failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest005
 * @tc.desc: tdd HksValidateCertChain with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest005, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest005");
    int32_t ret = HksValidateCertChain(nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksValidateCertChain failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest006
 * @tc.desc: tdd HcmIsDeviceKeyExist with nullptr input, expecting HKS_SUCCESS
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest006, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest006");
    int32_t ret = HcmIsDeviceKeyExist(nullptr);
    EXPECT_EQ(ret, HKS_SUCCESS) << "HcmIsDeviceKeyExist failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest007
 * @tc.desc: tdd HksBnExpMod with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest007, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest007");
    int32_t ret = HksBnExpMod(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksBnExpMod failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest008
 * @tc.desc: tdd HksHash with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest008, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest008");
    int32_t ret = HksHash(nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksHash failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest009
 * @tc.desc: tdd HksMac with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest009, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest009");
    int32_t ret = HksMac(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksMac failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest010
 * @tc.desc: tdd HksDeriveKey with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest010, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest010");
    int32_t ret = HksDeriveKey(nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksDeriveKey failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest011
 * @tc.desc: tdd HksAgreeKey with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest011, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest011");
    int32_t ret = HksAgreeKey(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksAgreeKey failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest012
 * @tc.desc: tdd HksDecrypt with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest012, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest012");
    int32_t ret = HksDecrypt(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksDecrypt failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest013
 * @tc.desc: tdd HksEncrypt with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest013, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest013");
    int32_t ret = HksEncrypt(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksEncrypt failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest014
 * @tc.desc: tdd HksVerify with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest014, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest014");
    int32_t ret = HksVerify(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksVerify failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest015
 * @tc.desc: tdd HksSign with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest015, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest015");
    int32_t ret = HksSign(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksSign failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest016
 * @tc.desc: tdd HksGenerateRandom with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest016, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest016");
    int32_t ret = HksGenerateRandom(nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksGenerateRandom failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest017
 * @tc.desc: tdd HksGenerateRandom with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest017, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest017");
    int32_t ret = HksKeyExist(nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksKeyExist failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest018
 * @tc.desc: tdd HksDeleteKey with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest018, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest018");
    int32_t ret = HksDeleteKey(nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksDeleteKey failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest019
 * @tc.desc: tdd HksImportWrappedKey with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest019, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest019");
    int32_t ret = HksImportWrappedKey(nullptr, nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksImportWrappedKey failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest020
 * @tc.desc: tdd HksImportKey with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest020, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest020");
    int32_t ret = HksImportKey(nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksImportKey failed, ret = " << ret;
}

/**
 * @tc.name: HksAPITest.HksAPITest021
 * @tc.desc: tdd HksGenerateKey with nullptr input, expecting HKS_ERROR_NULL_POINTER
 * @tc.type: FUNC
 */
HWTEST_F(HksAPITest, HksAPITest021, TestSize.Level0)
{
    HKS_LOG_I("enter HksAPITest021");
    int32_t ret = HksGenerateKey(nullptr, nullptr, nullptr);
    EXPECT_EQ(ret, HKS_ERROR_NULL_POINTER) << "HksGenerateKey failed, ret = " << ret;
}
}
