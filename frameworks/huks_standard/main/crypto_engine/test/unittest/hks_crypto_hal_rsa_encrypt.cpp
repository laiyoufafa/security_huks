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

#include <gtest/gtest.h>
#include <iostream>

#include "hks_config.h"
#include "hks_crypto_hal.h"
#include "hks_crypto_hal_common.h"
#include "hks_mem.h"

using namespace testing::ext;
namespace {
namespace {
const char RSA_1024_NOPADDING_KEY[] =
    "0100000000040000800000008000000080000000a51514cb129c6e19e50eaf764e08067e5720ba300a9031a5a40509d210b0e5a072b7dc"
    "6e0b9da82b59bb5c41b0baabbd4b534eb6a8fd50c25a7d9b7b1c7d9e808c5de65a0658fbb353b635dce78ab6d09478257b7e8b5b508cd7"
    "5a735ca3944aba2bc8f443cd9ed6b0096cfda268e2fda1462182b313b25f27ecdc4510fc87770000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100"
    "016671c4ab98eb16b05f2353e3d8dcc61ad53aec10301df791514e0720235783c8a4285154c1449f3df7bb7baf105b67845b2061b29d00"
    "4683b5e049028755b56c15879f4b5dc76e57fd0296c1286b347f7387b2f9e8cee0fbd6cf034cd16dffa6cc2f5c1101c1f430c265ea0d5b"
    "c27a01672405d4f670baf194ccb4ba87a3c5b1";
const char RSA_2048_NOPADDING_KEY[] =
    "0100000000080000000100000001000000010000a0286e22fea334e1ec2f48a955d91d44992e2fda06d23ff00bbfdd70f0f961bed02781"
    "e345ad866f63c217ae82f84db6f3ef2d5937fe9684f2c1e1ac091e81eb7dc1da7bb4a2ad7e3bb2911cfbfa8c0244527b91259b5b7ac1e4"
    "32701ac4e5c87186b59340ae0b67e4d2805ad01431121d907181aaac1d7a26e4703b1812c711fa3d056a8f4709a923193895f2657e66b0"
    "b109dbc65c9703bc08d79696f35f63e790aff9cf4323320288d5bc9360f08dc9576d7cba0792bc56864a844b72c49041340b8b3487dba1"
    "f724bac429e7d40c99d752d4be9cca352b59a7594ddae02784c3b8e137f141e2a77e098524aec3b96d989fe09e28578fabeb6e6976bba3"
    "77000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "000000000000000000000000000000000000000000000000000000000000000000000100010490024b36ebd956d24eaa88406cd5fb9d4d"
    "868974864ad200d3af70473d237eb7195906eb763d0d314f57335e81ca5cfae80667b343aa7011265ad276d40aa975c4aeffb52ea9389e"
    "64c0e38d7e1ebcf5cb4fbfdbcd6836c00d4b2e8c64ad931f40d22d66bb4e91e01feb0e2b3d580487191552b754fde5fbf3a80ad6edba04"
    "0a8d0c30fa413ce7cb7d1bdd5960cb6d9c68285cf7ca8abde4c2a5aa2f7ef875e66094b9a263e529f38651f405ee9410ae45f3f272effb"
    "d318c23eb112bb295b79cfff9f5df4ed2a91c590c03fdb304e74dd7758916b91e4716a6b4f5703516aaad8a8cb9f2b603f11ac90b0e941"
    "ffdf7059c7ba1a74c5bf6435a8040f175ae1";
const char RSA_3072_NOPADDING_KEY[] =
    "01000000000c0000800100008001000080010000b3c325e9339d6cc17db61da704dc05364320f4ca208467ddbf3d44a625a5dc3a6cd134"
    "27cce14a3f0a2f7a50a6e377b52f73bb824254d8bed785b91303f30211c20d1bef9ddd5e4ee88b7425ef2846f41e791d5a9670682553be"
    "ce2dbf41d88abbfde7dc3f450572290daabb55a1a56b28b282de9576249de95d0075d47914943f52d9a559ddcec9b5f610eeee9bf10cd3"
    "d807d00abdf94e7f63a50d01ddb8cff95e0452e56e614115031fe5ddb91d46c13358c1f42685fc19e09a2cf3170fa0bf0e0a380400fc8c"
    "c3e2f287c68d48ae04ecd3448273198744f37187eee774cc2dcc28fd3b037af7f4c54e30dd254c12b6f482c32e2de7014fb48f5badfea3"
    "91531b6a58c1c95f84ded943cc8fe113ff21e3c5f5625d88c77ee24ecad6b22e0013831af764c2a87c7db71062b922c136402a102391c4"
    "911bb286e8d96efa8e1c629d8818fd02de45bcdb8352cf16af7f282e5676a4b07c74a7e52b94726963fb79f433991114415474f90b10e3"
    "fea5d24043ce964298a938aa79014ae98da4b3000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "000000000000000000000000000000010001546d4714ebc4f81b382b9c69a102a500032f2b48f354bc638d39fd4ffb4696d469df279bb9"
    "c1e5d90db396c2e25edb0e21a73d5dc4418d3ab4867d91ccbd092fc5efda3b03edc029575687ca7934757e9a015024079beb8dfc7314ea"
    "af75017ac7284d09483de67ce38323b8b0532719d9175e17a422c4b7d5ae7454e2e1ab24a54908277cb98c317860853b729d92ecef61fa"
    "e95ee23281079b891d3ecf1fc9add8d63708c27ab2d2679147a8871494f290671350d3f7019c35bcb377c850f1e87dcc174873ecd98d0c"
    "f6ed9dd83118142d9f9cef1301b221a047440609ac3be88bf69e8e50843f75c855f974dc00e18168c8000a9a4ca65247560a5187ffed04"
    "4eb4da9e4e517870ab2dcbf6574c63676f8a3620852940c6b185186d21a53bdb20e7bf7d16288a3d9e0d47844d2b605f8ba879e87ce348"
    "033667577d6c91645f30f2720e9f9229ccc7a270215b124677650e94e5c181cdac04e2b2dfb8c3165f3a4a556c78684f60e602fb79f911"
    "68a938c5f0c4254265ae72f54938268021";
const char RSA_4096_NOPADDING_KEY[] =
    "0100000000100000000200000002000000020000e5a087382ce37175f66f6e4ebc00c0cb7d9b0486425eed1bf831cb43566031894221a1"
    "f1b0c7275318d82b186640256c3f1325f32a740e2c9ab3f7ca866d02b982f9caaa59eb49d7e3268f6b902e589ec65c91164d1e370ec407"
    "b06f9687b059835574ce9a541607b08e18a33fc74ec9ae0bb7e2a3c1fd73eeffb493e2e939b9ab7501dd0692ac63d262cb4130fae6be54"
    "42964a80f3e7474c0fee48dce2940e7fae7a8a8aec30a8d71dab54b1d42b1a364fc60a837f2533ca79dec02796cc00202db34dfb674641"
    "d20aa00c1d748aae18f5219ff5232a479e4e61a653c54b84ec1fbbd16624d595af1bb831508af96f02494312e46bcccca9e8c6f471c082"
    "c7a2e742a239cb908279b63f29385d53172ece4a85272acca9e52b9599c244a6ee786b7ddb599c198362bd5697c522f667457c11503286"
    "4e4364325873652f9e69b27aae8b1c8c385164c8edcdf401dc306ade1907449bd1c58593681b5f8e8cb536c9e60390152ce648ada0f091"
    "d3b11ca660f44421257434b69f4f60a6159cb86c8911559319e765550d142d58e844896259f0e8eb471a2150a79221c31d0b2032b3d716"
    "b3c00255eb300fbb2fba4bec0d4041d7b010939fd339e8080d52c7ded936af229358a580ac87518bbd785fb103534b9ad3f19501125b5a"
    "9467d4b76e5e571d2b1393454e92711be52d1f9482f7997f4e65102995874febc087792b77000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000198"
    "f34d3e40c01ac22d2cd9f7bdc86ea2dc7e560c2bc758fe695a997eb7d90905d933d7cfca254d6f4f3c25b071e3464a0cd56f50c2355d7f"
    "9e6843a3f5d8449956c19599d49d21a9985705eeeab1c43bb5fad0755f56c1eba6ed4c3b77b3d7e637d1c3251eace5a3a7996e95c694b6"
    "4926120e20fb5ceababf36398ccbf6f78951c8753e48f387ba51d796754cefc2a482317c341222e4299c637c1fb269859f06b32c527de8"
    "871cdf7496bbaa5b9d7e2f3101c3dd04e2bdd59f499d0a81aa4e6720a9af46c6ea884b24e2a84f3262714694791a37c97d8f08c642caec"
    "3f9d66e374dbc0c5ddc11a9bf1c5c5ab557681d7aefeeb6594dc6c72bc67514937a6a399d80094486382538c330569a3a944375751d9eb"
    "ed82c39bf81cf27f88c211070960d781719fb64d3c7a507c955e015cd3c4e968fea4d999d57245b30bcffae2c44ab6bfe4d2c3d7457a68"
    "3f0580cdc0d4910e071ef624888db604f110eb6aa2a454cd9b74d4b9b857994452c092c20df2a0110ed81c8275aa745971e900c9485f67"
    "82fbf666215762f2f971e4d213be05cb1760e4c7bfc3fb17ae1409039568ba3d9e2d34e282cc43c9db4ed8286a0a504022cbd23cd68cc7"
    "94685dd6daddf1054673cb9b517495e0c39569e0627e4b8ef80bb196f58f53627af0a4142fb2b469cc767a348ce74ea8dbdc647386e485"
    "62a124488021988f9d71ff68f2028a19";
const char RSA_3072_PKCS1PADDING_KEY[] =
    "01000000000c0000800100008001000080010000b6267a0a854bc91d6a7f469ea9212dc3fb2a5a2e6626ec1f41e3f6436361b0c8141bcc"
    "77e3e568dfee0068e0c863681ba0383b22046e6ef166274cbe19893e8a0ad4fdf86475998b0b00af04ccb0d1e1b42f89a20f56dccbfe14"
    "45e794a8123434a252eab9e386a35d663669d219b34ad92f7a64a90a91f25ffa002ccc589843fde8cb3111d566b4a665c51d801f290ceb"
    "be980ae71fad125e851c426d240fa361414c34a037d2a0840a25e4af4355931a6efc7c9faf11a5e8d225387965ea51f81f910786b9dfa9"
    "8459678db6a0670b14b64a2be05ebd2db0f25fcab225f719b5cd97a0f38c490d38a710d594d50ba75ab0ebc04456fe12514f96351cdc9a"
    "8a868389c932b3572726ce2303ab1e7f85c43c18e52ae14efcad4e0f65bffbf3254e10ad616ce169594373dcf1d44016c4fd77023bb0a8"
    "302ce72de9ce1aba9d885c05aefa935492592afaae543c8c99e997dff2c1125a3931f5897b5ce2c6217d69be0d74612dea66347c076c44"
    "5849c786e36a0c285e0f3b838d630b3347a96b000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000100013f242b5e0642f51e6b525f6a947a59e0fbe9fc84e5084d05b0d393045d28fa1d014b799f7d"
    "b2829e4d647af6a0c044d07ec3bf4bd5796a9fe7a76be4e1f93f629ecaa2973e4bbdc40336637528778ae9d08a420d997fa4de59df3134"
    "4bc5cf39a59d375d02bf2a66eaf3899d39258b8f40a642a92e27e9dbb905729614e80930588e20118c7b0b35481133393cb69086581a23"
    "9e73ebf914cb0b1d76b15ab4c90fe790c1156104747c11007dbb7b7de8965b2ecf0c93a56c7bbe8d047ca0a58edaa75649497e7a4c1b69"
    "90a9d6fda6dcbf9732d517a01a3818287c8717949fa4820d88f3a5918bc0d629d88ae63e1b9ba0a52bd8cefdf30e4b273e9ead163dad87"
    "bafb456b7af8b8e5dc353eda84195190b994e447758f082c1d9700d83655f1956f1c75dd5cde9880169b7f7720cc39761411a3c98cb25d"
    "ce939c5c1724c07f31a1bfb59771d06cee3c6057e04489ceec6a122866d67d19923c7c5cbf598e48ab4fede639807b9d3d6f83aa821411"
    "94019bc2c4fd028ccca7dc4e56e657f931";
const char RSA_4096_PKCS1PADDING_KEY[] =
    "0100000000100000000200000002000000020000c214a594a87457faccdfa9e466160af3a292f93003783fa46feeae2d84c0c41704d01a"
    "2eb9874b59fcd217d7394e01e20a9fd162ef4de6c87adc11d423bc13c1f2b609e73c5ff20251a7e9e940fdb2fed3e8d04a2dc5fd33708e"
    "aeea6b85ea021487daa0d8cc52b1ee0299915a5dc5b469792908aa05bad12d4c1af13c5ab552849c480ac6bec9fd4256d2b2b8f4f48583"
    "f471c8f9e3c099c170e4863f5935ae11475d45bf4a1c5022937c31cdb23379f3bdbbfc8f59cce6dff3b02f201f660640605c9cf9f489da"
    "74d378f9a97cc1284662346fd78f621c7b36b15b60cc5d645b5217a5aaee9f4c5f0cd1a3ba6d4fcfc49e472951e300af124106f38fc10f"
    "3e40812997b93c35e44e8267e5d88bb0fba1e941801ee360317d1b4be71e40332d2a44c8727f7ae36eefe83906b4bc44214f126882f03a"
    "9856e08268784c39fa351a7a00fbe916c2279ca679d7fa39a386e7ad50a08511031a480ffb449928b8e6b729921671f882f85dffbea3b6"
    "93c362c311cba5ab909f06c7e2e333d11ca9ed0a821f4029101788071471236bd7af5a6e84ee6f5b7010a35ecd4abc894db5e5283322e7"
    "5ef6f539d8a1524f155a7d2da825f42b11b80358d806d28934ef73014e863eeca74156d4b1b066ae11a875b746164095ed815b10478a37"
    "cae6fa96fe16e9833397270fd531f7c1a9cfae0caad254e3b659e37e3fa9a1dcf07b48e101000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100012f"
    "99f4cab34e65cdc3b60feb4f0695051098cfb971006b4b9f9080f3f51d7a7ad2d95fb29a1a8ee6b155ae37417cda856069b667779e39be"
    "6e33cfc3a2481ce872e92720a9f4365d4f3dc9e745e373a580c017663a37d7546884f66dd49571c1b4db654a12227b1ddcec9251ce4235"
    "9d7c49154164c22701eb04418f6d682a14e525979ddd052a718d75d213b7bd8cc3ba8b97e4dd357925bd063d6697deff85840366e31679"
    "ccdbf2bf0db5016875abb19695a6ea59f221a64814ac5a4a99316b54b722614413139b97ca922179d1be5914f91b7d59538cfcc37b5898"
    "3347acb7a138df8f3f1b9f15a9053a0d1d8677c517b508736723e1ccae5a501eb011569bd1d1dc71f75681c5871497a149bdd4c0cfe7ca"
    "acca439faba11526aee5f280345555c81f09213e6d6699511cece3dcb1ef47694c3d2eada01653d565dd0f85a56b9bf35ed63f1dcffdec"
    "73939a2bd962f67feb49aeca0395214d7d2430b6a9c43a93f49386ee99579a46ad9848138ca08c0c02c4036f538f41b708bd1ce3be00c6"
    "4caff64bfbeafe65d19b245f3547b999d84163e51c200b91b762728e43d5eace6ebec90119be092ae6f131ea7b5d5901eda3b8cbca01f0"
    "df7f98dc3aab37712c3b223d03510ce241cb81e5719fb8ee161a1346d8323397d2ab673695d5d08816f1c0fc61073eb33471d29d7ecdcd"
    "083678709efd4b63e5f0a699ec19e949";
}  // namespace
class HksCryptoHalRsaEncrypt : public HksCryptoHalCommon, public testing::Test {};

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_001
 * @tc.name      : HksCryptoHalRsaEncrypt_001
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-512-NOPADDING key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_001, Function | SmallTest | Level1)
{
    int32_t ret;

    const char *keyData =
        "0100000000020000400000004000000040000000ba5395c32972cdd04061fc45ac6d501555110a32300d44f57d6d7d9b478888361d815b"
        "45c30aedce3674cf440c455552ba05ea9ef4659f37077c9498541f79d10000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000010001355e09702ba801411b9fb514f3ad1f99ec"
        "9283dc1a1d42da1981c9cf36eee92c3154e0b65cd6653c01a0568dec5f969bf6581ca2aa3c572138cfc9a0b2b3535d";
    uint32_t keyLen = strlen(keyData) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&keyData[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_NONE,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff000000000000000000000000000"
                          "0000000000000000000000000000000000000";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = dataLen;

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
#if defined(_USE_OPENSSL_)
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
#if defined(_USE_MBEDTLS_)
    ASSERT_EQ(HKS_ERROR_NOT_SUPPORTED, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_002
 * @tc.name      : HksCryptoHalRsaEncrypt_002
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-768-NOPADDING key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_002, Function | SmallTest | Level1)
{
    int32_t ret;

    const char *keyData =
        "0100000000030000600000006000000060000000eadcc37762c4a0c4cd358de290f2efedf39503a1833e4082aef44cb564ff47d4feaee5"
        "f145b3711cd9abf944e0586bc083dd2c7dde4fc8f7d9a69d4fc5a8aef527c82d02fd30eb33a1791db30011733d60ef3110bd769f385f10"
        "b071ae552dbd00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010001158f2e62472ec593"
        "4b431f432d0b1ffb37e0f5f45d97d95425bb474f5f760fa1fdbf105c95896358c2a286bf4bd8d20b2d0b0880ff0193bcf0e625a9dbe330"
        "6ea4534c0d7e83b657684194501574a554f76cbe29ce5953e1d92b479b4d1f8201";
    uint32_t keyLen = strlen(keyData) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&keyData[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_NONE,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData =
        "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff0000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = dataLen;

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
#if defined(_USE_OPENSSL_)
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
#if defined(_USE_MBEDTLS_)
    ASSERT_EQ(HKS_ERROR_NOT_SUPPORTED, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_003
 * @tc.name      : HksCryptoHalRsaEncrypt_003
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-1024-NOPADDING key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_003, Function | SmallTest | Level1)
{
    int32_t ret;

    uint32_t keyLen = strlen(RSA_1024_NOPADDING_KEY) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&RSA_1024_NOPADDING_KEY[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_NONE,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff000000000000000000000000000"
                          "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                          "00000000000000000000000000000000000000000000000000000000000000000000000000";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = dataLen;

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
#if defined(_USE_OPENSSL_)
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
#if defined(_USE_MBEDTLS_)
    ASSERT_EQ(HKS_ERROR_NOT_SUPPORTED, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_004
 * @tc.name      : HksCryptoHalRsaEncrypt_004
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-2048-NOPADDING key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_004, Function | SmallTest | Level1)
{
    int32_t ret;

    uint32_t keyLen = strlen(RSA_2048_NOPADDING_KEY) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&RSA_2048_NOPADDING_KEY[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_NONE,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData =
        "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff0000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000000";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = dataLen;

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
#if defined(_USE_OPENSSL_)
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
#if defined(_USE_MBEDTLS_)
    ASSERT_EQ(HKS_ERROR_NOT_SUPPORTED, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_005
 * @tc.name      : HksCryptoHalRsaEncrypt_005
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-3072-NOPADDING key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_005, Function | SmallTest | Level1)
{
    int32_t ret;

    uint32_t keyLen = strlen(RSA_3072_NOPADDING_KEY) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&RSA_3072_NOPADDING_KEY[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_NONE,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData =
        "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff0000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = dataLen;

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
#if defined(_USE_OPENSSL_)
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
#if defined(_USE_MBEDTLS_)
    ASSERT_EQ(HKS_ERROR_NOT_SUPPORTED, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_006
 * @tc.name      : HksCryptoHalRsaEncrypt_006
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-4096-NOPADDING key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_006, Function | SmallTest | Level1)
{
    int32_t ret;

    uint32_t keyLen = strlen(RSA_4096_NOPADDING_KEY) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&RSA_4096_NOPADDING_KEY[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_NONE,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData =
        "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff0000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = dataLen;

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
#if defined(_USE_OPENSSL_)
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
#if defined(_USE_MBEDTLS_)
    ASSERT_EQ(HKS_ERROR_NOT_SUPPORTED, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
#endif
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_007
 * @tc.name      : HksCryptoHalRsaEncrypt_007
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-512-PKCS1Padding key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_007, Function | SmallTest | Level1)
{
    int32_t ret;

    const char *keyData =
        "0100000000020000400000004000000040000000a6a29490a5a6b309192f7571daa7cacce05dc5a5af6e4c0648ffc3dd72704651c806ee"
        "0cb61afc2f118bb24075a2f303cc548bfd9fea2c3dc945d5d976457ae10000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000100012a295cb9b4901720a834afdc9cdc739d9e"
        "ef5b00ef0053500bcc5afc7ee6158457279c58942bafa28d436be509cd30b841e40cb769efffe8723b70c6f464f599";
    uint32_t keyLen = strlen(keyData) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&keyData[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_PKCS1_V1_5,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = HKS_KEY_BYTES(HKS_RSA_KEY_SIZE_512);

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_008
 * @tc.name      : HksCryptoHalRsaEncrypt_008
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-768-PKCS1Padding key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_008, Function | SmallTest | Level1)
{
    int32_t ret;

    const char *keyData =
        "0100000000030000600000006000000060000000d056e8b387700c781feb01097ecd9868c32af0cea33292634b2b0027117b75af0ebdb9"
        "6172c776ef95bb7c3dcfa6126858e6fe69c87e0ed69dcf81e15ebef50f03fbaffaee527c291f3740e521730271eb3b63f4057cba780c6a"
        "c8520816d79300000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010001acbf7361f12a5a5c"
        "7c72bac069d105cfd00c59f1ace630f57e0d60aa0457ef63c10055a754a9c997acfaf170bb2dc3d21b8e26541ba01ff0b99788b13a553b"
        "f97c8c71cd149dcb421fb96affc55a6588adb642251bd991ef7d54890950e5b719";
    uint32_t keyLen = strlen(keyData) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&keyData[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_PKCS1_V1_5,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = HKS_KEY_BYTES(HKS_RSA_KEY_SIZE_768);

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_009
 * @tc.name      : HksCryptoHalRsaEncrypt_009
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-1024-PKCS1Padding key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_009, Function | SmallTest | Level1)
{
    int32_t ret;

    const char *keyData =
        "0100000000040000800000008000000080000000bc294482ddb7abe39a04a31b8410e9115691e8cdedc7aa060a63977d55a6f924f8387d"
        "93bba101ad7351ad244baf25d19a840dc975409801fe634a603cce8fec3f2c40db3d2b6f0053e4ae0c073f5d21c9632e4d3a61f4afac89"
        "5367e58eb6fc9a723e75f14a8dcd7dd210644427d9d26da3cb88aa085e9d3fb74bdeb16d4d250000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000100"
        "014fc97801be1eba46a2f2c06f548b0f2988fa0a2bf85e281cb39f1387d4201f99ab9fd8b02269dd9a3d422f172af8b422b350b7bfeb76"
        "5e7ec9ee3485a68338c78cc6cd9ceb514aa6b7cce5811306d6d256b3a1d6f6e1a2c309b0d721a0a32566c8e030794c90d984af31685a99"
        "70960dc0698a51f3e03211fa43b3a4f9336141";
    uint32_t keyLen = strlen(keyData) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&keyData[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_PKCS1_V1_5,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = HKS_KEY_BYTES(HKS_RSA_KEY_SIZE_1024);

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_010
 * @tc.name      : HksCryptoHalRsaEncrypt_010
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-2048-PKCS1Padding key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_010, Function | SmallTest | Level1)
{
    int32_t ret;

    const char *keyData =
        "0100000000080000000100000001000000010000ddf3e9c6589658e5c124a49d473db529e8eb08b99c351cf7c5d502f64def9752d4ee88"
        "d942cbdbc7fb46eac9d9b9f9b309fbffa99c9fe05363b2d5e71c2d132bc83d74f0b8441266fc2f6f0462b54fa0ffaef92bb93cec2d1805"
        "9db40ff9d579f7980c08cb9a30d076d6ebf50f4166514bd00cdf20ca042ddf13581feddd32b15e8508f2b185f4e6c77217c5096a9dfecd"
        "5132ee4ce41bccd3faa75abcf1014e5e27328d3a1b08e56c33d5f5f2fe8b8f232db6953a337bca29e2726165732c8d1aae10a6e9c60ce5"
        "4b2423868e6d024dfdfab45fbb3d589d06fb8f55564bdc2bb07c1c84cf8c076045706b36e6715c4dc8cd1f4fe751de77b031b5bcf7cde7"
        "41000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000001000151ac53b5fd1b361335837a5fb5bb6b52c4b6"
        "d83b14d42698b65faffb5aaa7390b37223416f66fcb5162dfe6fd082b2f3c314cbfb69fb1add14aed62f791acd172b54121812765a1f33"
        "657100b821e7ef62a6cc61de842094676689a59ccb5e56c75957f45497a4a6d1543cf7ac69707131e89913f248e448ccf19d58027b870f"
        "361c57bc60e75da62e75d94b7e42c544e7ef183fd1935f0ca8d637e18cc4acae0e99f8aabbf83c968460b5237eac3271f214fd10580166"
        "c836e067948438f8a3c5edded4871baf6acab762e501db5fde6f2ec201072532c109d0a55cdf0e275322ccf326c9a2a6b235d5742067b6"
        "f7912bf772c9039385ab0a81c0186bf91001";
    uint32_t keyLen = strlen(keyData) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&keyData[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_PKCS1_V1_5,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = HKS_KEY_BYTES(HKS_RSA_KEY_SIZE_2048);

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_011
 * @tc.name      : HksCryptoHalRsaEncrypt_011
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-3072-PKCS1Padding key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_011, Function | SmallTest | Level1)
{
    int32_t ret;

    uint32_t keyLen = strlen(RSA_3072_PKCS1PADDING_KEY) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&RSA_3072_PKCS1PADDING_KEY[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_PKCS1_V1_5,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = HKS_KEY_BYTES(HKS_RSA_KEY_SIZE_3072);

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
}

/**
 * @tc.number    : HksCryptoHalRsaEncrypt_012
 * @tc.name      : HksCryptoHalRsaEncrypt_012
 * @tc.desc      : Using HksCryptoHalEncrypt Encrypt RSA-4096-PKCS1Padding key.
 */
HWTEST_F(HksCryptoHalRsaEncrypt, HksCryptoHalRsaEncrypt_012, Function | SmallTest | Level1)
{
    int32_t ret;

    uint32_t keyLen = strlen(RSA_4096_PKCS1PADDING_KEY) / 2;
    HksBlob key = {.size = keyLen, .data = (uint8_t *)HksMalloc(keyLen)};
    for (uint32_t ii = 0; ii < keyLen; ii++) {
        key.data[ii] = ReadHex((const uint8_t *)&RSA_4096_PKCS1PADDING_KEY[2 * ii]);
    }

    HksUsageSpec usageSpec = {
        .algType = HKS_ALG_RSA,
        .mode = HKS_MODE_ECB,
        .padding = HKS_PADDING_PKCS1_V1_5,
        .digest = HKS_DIGEST_NONE,
        .purpose = HKS_KEY_PURPOSE_ENCRYPT | HKS_KEY_PURPOSE_DECRYPT,
        .algParam = nullptr,
    };

    const char *hexData = "00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff";
    uint32_t dataLen = strlen(hexData) / 2;

    uint32_t inLen = dataLen;
    uint32_t outLen = HKS_KEY_BYTES(HKS_RSA_KEY_SIZE_4096);

    HksBlob message = {.size = inLen, .data = (uint8_t *)HksMalloc(inLen)};
    for (uint32_t ii = 0; ii < dataLen; ii++) {
        message.data[ii] = ReadHex((const uint8_t *)&hexData[2 * ii]);
    }

    HksBlob cipherText = {.size = outLen, .data = (uint8_t *)HksMalloc(outLen)};

    HksBlob tagAead = {.size = 0, .data = nullptr};

    ret = HksCryptoHalEncrypt(&key, &usageSpec, &message, &cipherText, &tagAead);
    EXPECT_EQ(HKS_SUCCESS, ret);
    HksFree(key.data);
    HksFree(message.data);
    HksFree(cipherText.data);
}
}  // namespace