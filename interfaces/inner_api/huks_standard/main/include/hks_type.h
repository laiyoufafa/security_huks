/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

/**
 * @file hks_param.h
 *
 * @brief Declares huks struct and enum.
 *
 * @since 8
 */

#ifndef HKS_TYPE_H
#define HKS_TYPE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HKS_API_PUBLIC
    #if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) || defined(__ICCARM__) /* __ICCARM__ for iar */
        #define HKS_API_EXPORT
    #else
        #define HKS_API_EXPORT __attribute__ ((visibility("default")))
    #endif
#else
    #define HKS_API_EXPORT __attribute__ ((visibility("default")))
#endif

#define HKS_SDK_VERSION "2.0.0.4"

/*
 * Align to 4-tuple
 * Before calling this function, ensure that the size does not overflow after 3 is added.
 */
#define ALIGN_SIZE(size) ((((uint32_t)(size) + 3) >> 2) << 2)
#define DEFAULT_ALIGN_MASK_SIZE 3

#define HKS_AE_TAG_LEN 16
#define HKS_BITS_PER_BYTE 8
#define MAX_KEY_SIZE 2048
#define HKS_AE_TAG_LEN 16
#define HKS_AE_NONCE_LEN 12
#define HKS_MAX_KEY_ALIAS_LEN 64
#define HKS_MAX_PROCESS_NAME_LEN 50
#define HKS_MAX_RANDOM_LEN 1024
#define HKS_KEY_BYTES(keySize) (((keySize) + HKS_BITS_PER_BYTE - 1) / HKS_BITS_PER_BYTE)
#define HKS_SIGNATURE_MIN_SIZE 64
#define HKS_ARRAY_SIZE(arr) ((sizeof(arr)) / (sizeof((arr)[0])))
#define MAX_OUT_BLOB_SIZE (5 * 1024 * 1024)
#define HKS_WRAPPED_FORMAT_MAX_SIZE (1024 * 1024)
#define HKS_IMPORT_WRAPPED_KEY_TOTAL_BLOBS 10

#define TOKEN_CHALLENGE_LEN 32
#define SHA256_SIGN_LEN 32
#define TOKEN_SIZE 32
#define MAX_AUTH_TIMEOUT_SECOND 60
#define SECURE_SIGN_VERSION 0x01000001

#define HKS_CERT_COUNT 4
#define HKS_CERT_ROOT_SIZE 2048
#define HKS_CERT_CA_SIZE 2048
#define HKS_CERT_DEVICE_SIZE 2048
#define HKS_CERT_APP_SIZE 4096

#define HKS_KEY_BLOB_AT_KEY_SIZE 256
#define HKS_KEY_BLOB_AT_KEY_BYTES 32

/**
 * @brief hks key type
 */
enum HksKeyType {
    HKS_KEY_TYPE_RSA_PUBLIC_KEY = 0x01001000,
    HKS_KEY_TYPE_RSA_KEYPAIR = 0x01002000,

    HKS_KEY_TYPE_ECC_P256_PUBLIC_KEY = 0x02021000,
    HKS_KEY_TYPE_ECC_P256_KEYPAIR = 0x02022000,
    HKS_KEY_TYPE_ECC_P384_PUBLIC_KEY = 0x02031000,
    HKS_KEY_TYPE_ECC_P384_KEYPAIR = 0x02032000,
    HKS_KEY_TYPE_ECC_P521_PUBLIC_KEY = 0x02051000,
    HKS_KEY_TYPE_ECC_P521_KEYPAIR = 0x02052000,

    HKS_KEY_TYPE_ED25519_PUBLIC_KEY = 0x02101000,
    HKS_KEY_TYPE_ED25519_KEYPAIR = 0x02102000,
    HKS_KEY_TYPE_X25519_PUBLIC_KEY = 0x02111000,
    HKS_KEY_TYPE_X25519_KEYPAIR = 0x02112000,

    HKS_KEY_TYPE_AES = 0x03000000,
    HKS_KEY_TYPE_CHACHA20 = 0x04010000,
    HKS_KEY_TYPE_CHACHA20_POLY1305 = 0x04020000,

    HKS_KEY_TYPE_HMAC = 0x05000000,
    HKS_KEY_TYPE_HKDF = 0x06000000,
    HKS_KEY_TYPE_PBKDF2 = 0x07000000,
};

/**
 * @brief hks key purpose
 */
enum HksKeyPurpose {
    HKS_KEY_PURPOSE_ENCRYPT = 1,                   /* Usable with RSA, EC, AES, and SM4 keys. */
    HKS_KEY_PURPOSE_DECRYPT = 2,                   /* Usable with RSA, EC, AES, and SM4 keys. */
    HKS_KEY_PURPOSE_SIGN = 4,                      /* Usable with RSA, EC keys. */
    HKS_KEY_PURPOSE_VERIFY = 8,                    /* Usable with RSA, EC keys. */
    HKS_KEY_PURPOSE_DERIVE = 16,                   /* Usable with EC keys. */
    HKS_KEY_PURPOSE_WRAP = 32,                     /* Usable with wrap key. */
    HKS_KEY_PURPOSE_UNWRAP = 64,                   /* Usable with unwrap key. */
    HKS_KEY_PURPOSE_MAC = 128,                     /* Usable with mac. */
    HKS_KEY_PURPOSE_AGREE = 256,                   /* Usable with agree. */
};

/**
 * @brief hks key digest
 */
enum HksKeyDigest {
    HKS_DIGEST_NONE = 0,
    HKS_DIGEST_MD5 = 1,
    HKS_DIGEST_SM3 = 2,
    HKS_DIGEST_SHA1 = 10,
    HKS_DIGEST_SHA224 = 11,
    HKS_DIGEST_SHA256 = 12,
    HKS_DIGEST_SHA384 = 13,
    HKS_DIGEST_SHA512 = 14,
};

/**
 * @brief hks key padding
 */
enum HksKeyPadding {
    HKS_PADDING_NONE = 0,
    HKS_PADDING_OAEP = 1,
    HKS_PADDING_PSS = 2,
    HKS_PADDING_PKCS1_V1_5 = 3,
    HKS_PADDING_PKCS5 = 4,
    HKS_PADDING_PKCS7 = 5,
};

/**
 * @brief hks cipher mode
 */
enum HksCipherMode {
    HKS_MODE_ECB = 1,
    HKS_MODE_CBC = 2,
    HKS_MODE_CTR = 3,
    HKS_MODE_OFB = 4,
    HKS_MODE_CCM = 31,
    HKS_MODE_GCM = 32,
};

/**
 * @brief hks key size
 */
enum HksKeySize {
    HKS_RSA_KEY_SIZE_512 = 512,
    HKS_RSA_KEY_SIZE_768 = 768,
    HKS_RSA_KEY_SIZE_1024 = 1024,
    HKS_RSA_KEY_SIZE_2048 = 2048,
    HKS_RSA_KEY_SIZE_3072 = 3072,
    HKS_RSA_KEY_SIZE_4096 = 4096,

    HKS_ECC_KEY_SIZE_224 = 224,
    HKS_ECC_KEY_SIZE_256 = 256,
    HKS_ECC_KEY_SIZE_384 = 384,
    HKS_ECC_KEY_SIZE_521 = 521,

    HKS_AES_KEY_SIZE_128 = 128,
    HKS_AES_KEY_SIZE_192 = 192,
    HKS_AES_KEY_SIZE_256 = 256,
    HKS_AES_KEY_SIZE_512 = 512,

    HKS_CURVE25519_KEY_SIZE_256 = 256,

    HKS_DH_KEY_SIZE_2048 = 2048,
    HKS_DH_KEY_SIZE_3072 = 3072,
    HKS_DH_KEY_SIZE_4096 = 4096,

    HKS_SM2_KEY_SIZE_256 = 256,
    HKS_SM4_KEY_SIZE_128 = 128,
};

/**
 * @brief hks key algorithm
 */
enum HksKeyAlg {
    HKS_ALG_RSA = 1,
    HKS_ALG_ECC = 2,
    HKS_ALG_DSA = 3,

    HKS_ALG_AES = 20,
    HKS_ALG_HMAC = 50,
    HKS_ALG_HKDF = 51,
    HKS_ALG_PBKDF2 = 52,
    HKS_ALG_GMKDF = 53,

    HKS_ALG_ECDH = 100,
    HKS_ALG_X25519 = 101,
    HKS_ALG_ED25519 = 102,
    HKS_ALG_DH = 103,

    HKS_ALG_SM2 = 150,
    HKS_ALG_SM3 = 151,
    HKS_ALG_SM4 = 152,
};

/**
 * @brief hks algorithm suite
 */
enum HuksAlgSuite {
    /* Algorithm suites of unwrapping wrapped-key by huks */
    /* Unwrap suite of key agreement type */
    /* WrappedData format(Bytes Array):
     *  | x25519_plain_pubkey_length  (4 Byte) | x25519_plain_pubkey |  agreekey_aad_length (4 Byte) | agreekey_aad
     *  |   agreekey_nonce_length     (4 Byte) |   agreekey_nonce    | agreekey_aead_tag_len(4 Byte) | agreekey_aead_tag
     *  |    kek_enc_data_length      (4 Byte) |    kek_enc_data     |    kek_aad_length    (4 Byte) | kek_aad
     *  |      kek_nonce_length       (4 Byte) |      kek_nonce      |   kek_aead_tag_len   (4 Byte) | kek_aead_tag
     *  |   key_material_size_len     (4 Byte) |  key_material_size  |   key_mat_enc_length (4 Byte) | key_mat_enc_data
     */
    HKS_UNWRAP_SUITE_X25519_AES_256_GCM_NOPADDING = 1,

    /* WrappedData format(Bytes Array):
     *  |  ECC_plain_pubkey_length    (4 Byte) |  ECC_plain_pubkey   |  agreekey_aad_length (4 Byte) | agreekey_aad
     *  |   agreekey_nonce_length     (4 Byte) |   agreekey_nonce    | agreekey_aead_tag_len(4 Byte) | agreekey_aead_tag
     *  |    kek_enc_data_length      (4 Byte) |    kek_enc_data     |    kek_aad_length    (4 Byte) | kek_aad
     *  |      kek_nonce_length       (4 Byte) |      kek_nonce      |   kek_aead_tag_len   (4 Byte) | kek_aead_tag
     *  |   key_material_size_len     (4 Byte) |  key_material_size  |   key_mat_enc_length (4 Byte) | key_mat_enc_data
     */
    HKS_UNWRAP_SUITE_ECDH_AES_256_GCM_NOPADDING = 2,

    /* WrappedData format(Bytes Array):
     *  |  SM2_plain_pubkey_length    (4 Byte) |  SM2_plain_pubkey   | signData_size_length (4 Byte) | signData_size
     *  |     kek_enc_data_length     (4 Byte) |     kek_enc_data    | kek_material_size_len(4 Byte) | kek_material_size
     *  |       factor1_data_len      (4 Byte) |    factor1_data     |  factor2_data_len    (4 Byte) | factor2_data
     *  |       mac_data_length       (4 Byte) |       mac_data      | key_mat_enc_length   (4 Byte) | key_mat_enc_data
     *  |          iv_data_length     (4 Byte) |            iv_data  |key_material_size_len (4 Byte) | key_material_size
     */
    HKS_UNWRAP_SUITE_SM2_SM4_128_CBC_PKCS7_WITH_VERIFY_DIG_SM3 = 3,

    /* WrappedData format(Bytes Array):
     *  |     kek_enc_data_length     (4 Byte) |     kek_enc_data    | kek_material_size_len(4 Byte) | kek_material_size
     *  |       factor1_data_len      (4 Byte) |    factor1_data     |  factor2_data_len    (4 Byte) | factor2_data
     *  |       mac_data_length       (4 Byte) |       mac_data      | key_mat_enc_length   (4 Byte) | key_mat_enc_data
     *  |          iv_data_length     (4 Byte) |            iv_data  |key_material_size_len (4 Byte) | key_material_size
     */
    HKS_UNWRAP_SUITE_SM2_SM4_128_CBC_PKCS7 = 4,
};

/**
 * @brief hks key generate type
 */
enum HksKeyGenerateType {
    HKS_KEY_GENERATE_TYPE_DEFAULT = 0,
    HKS_KEY_GENERATE_TYPE_DERIVE = 1,
    HKS_KEY_GENERATE_TYPE_AGREE = 2,
};

/**
 * @brief hks key flag
 */
enum HksKeyFlag {
    HKS_KEY_FLAG_IMPORT_KEY = 1,
    HKS_KEY_FLAG_GENERATE_KEY = 2,
    HKS_KEY_FLAG_AGREE_KEY = 3,
    HKS_KEY_FLAG_DERIVE_KEY = 4,
};

/**
 * @brief hks key storage type
 */
enum HksKeyStorageType {
    HKS_STORAGE_TEMP = 0,
    HKS_STORAGE_PERSISTENT = 1,
    HKS_STORAGE_ONLY_USED_IN_HUKS = 2,
    HKS_STORAGE_ALLOW_KEY_EXPORTED = 3,
};

/**
 * @brief hks import key type
 */
enum HksImportKeyType {
    HKS_KEY_TYPE_PUBLIC_KEY = 0,
    HKS_KEY_TYPE_PRIVATE_KEY = 1,
    HKS_KEY_TYPE_KEY_PAIR = 2,
};

/**
 * @brief hks rsa pss salt len type
 */
enum HksRsaPssSaltLenType {
    HKS_RSA_PSS_SALTLEN_DIGEST = 0,  /* Salt length matches digest */
    HKS_RSA_PSS_SALTLEN_MAX = 1,  /* Set salt length to maximum possible, default type */
};

/**
 * @brief hks error code
 */
enum HksErrorCode {
    HKS_SUCCESS = 0,
    HKS_FAILURE = -1,
    HKS_ERROR_BAD_STATE = -2,
    HKS_ERROR_INVALID_ARGUMENT = -3,
    HKS_ERROR_NOT_SUPPORTED = -4,
    HKS_ERROR_NO_PERMISSION = -5,
    HKS_ERROR_INSUFFICIENT_DATA = -6,
    HKS_ERROR_BUFFER_TOO_SMALL = -7,
    HKS_ERROR_INSUFFICIENT_MEMORY = -8,
    HKS_ERROR_COMMUNICATION_FAILURE = -9,
    HKS_ERROR_STORAGE_FAILURE = -10,
    HKS_ERROR_HARDWARE_FAILURE = -11,
    HKS_ERROR_ALREADY_EXISTS = -12,
    HKS_ERROR_NOT_EXIST = -13,
    HKS_ERROR_NULL_POINTER = -14,
    HKS_ERROR_FILE_SIZE_FAIL = -15,
    HKS_ERROR_READ_FILE_FAIL = -16,
    HKS_ERROR_INVALID_PUBLIC_KEY = -17,
    HKS_ERROR_INVALID_PRIVATE_KEY = -18,
    HKS_ERROR_INVALID_KEY_INFO = -19,
    HKS_ERROR_HASH_NOT_EQUAL = -20,
    HKS_ERROR_MALLOC_FAIL = -21,
    HKS_ERROR_WRITE_FILE_FAIL = -22,
    HKS_ERROR_REMOVE_FILE_FAIL = -23,
    HKS_ERROR_OPEN_FILE_FAIL = -24,
    HKS_ERROR_CLOSE_FILE_FAIL = -25,
    HKS_ERROR_MAKE_DIR_FAIL = -26,
    HKS_ERROR_INVALID_KEY_FILE = -27,
    HKS_ERROR_IPC_MSG_FAIL = -28,
    HKS_ERROR_REQUEST_OVERFLOWS = -29,
    HKS_ERROR_PARAM_NOT_EXIST = -30,
    HKS_ERROR_CRYPTO_ENGINE_ERROR = -31,
    HKS_ERROR_COMMUNICATION_TIMEOUT = -32,
    HKS_ERROR_IPC_INIT_FAIL = -33,
    HKS_ERROR_IPC_DLOPEN_FAIL = -34,
    HKS_ERROR_EFUSE_READ_FAIL = -35,
    HKS_ERROR_NEW_ROOT_KEY_MATERIAL_EXIST = -36,
    HKS_ERROR_UPDATE_ROOT_KEY_MATERIAL_FAIL = -37,
    HKS_ERROR_VERIFICATION_FAILED = -38,
    HKS_ERROR_SESSION_REACHED_LIMIT = -39,

    HKS_ERROR_GET_USERIAM_SECINFO_FAILED = -40,
    HKS_ERROR_GET_USERIAM_AUTHINFO_FAILED = -41,
    HKS_ERROR_USER_AUTH_TYPE_NOT_SUPPORT = -42,
    HKS_ERROR_KEY_AUTH_FAILED = -43,
    HKS_ERROR_DEVICE_NO_CREDENTIAL = -44,
    HKS_ERROR_API_NOT_SUPPORTED = -45,
    HKS_ERROR_KEY_AUTH_PERMANENTLY_INVALIDATED = -46,
    HKS_ERROR_KEY_AUTH_VERIFY_FAILED = -47,
    HKS_ERROR_KEY_AUTH_TIME_OUT = -48,

    HKS_ERROR_CREDENTIAL_NOT_EXIST = -49,

    HKS_ERROR_CHECK_GET_ALG_FAIL = -100,
    HKS_ERROR_CHECK_GET_KEY_SIZE_FAIL = -101,
    HKS_ERROR_CHECK_GET_PADDING_FAIL = -102,
    HKS_ERROR_CHECK_GET_PURPOSE_FAIL = -103,
    HKS_ERROR_CHECK_GET_DIGEST_FAIL = -104,
    HKS_ERROR_CHECK_GET_MODE_FAIL = -105,
    HKS_ERROR_CHECK_GET_NONCE_FAIL = -106,
    HKS_ERROR_CHECK_GET_AAD_FAIL = -107,
    HKS_ERROR_CHECK_GET_IV_FAIL = -108,
    HKS_ERROR_CHECK_GET_AE_TAG_FAIL = -109,
    HKS_ERROR_CHECK_GET_SALT_FAIL = -110,
    HKS_ERROR_CHECK_GET_ITERATION_FAIL = -111,
    HKS_ERROR_INVALID_ALGORITHM = -112,
    HKS_ERROR_INVALID_KEY_SIZE = -113,
    HKS_ERROR_INVALID_PADDING = -114,
    HKS_ERROR_INVALID_PURPOSE = -115,
    HKS_ERROR_INVALID_MODE = -116,
    HKS_ERROR_INVALID_DIGEST =  -117,
    HKS_ERROR_INVALID_SIGNATURE_SIZE = -118,
    HKS_ERROR_INVALID_IV = -119,
    HKS_ERROR_INVALID_AAD = -120,
    HKS_ERROR_INVALID_NONCE = -121,
    HKS_ERROR_INVALID_AE_TAG = -122,
    HKS_ERROR_INVALID_SALT = -123,
    HKS_ERROR_INVALID_ITERATION = -124,
    HKS_ERROR_INVALID_OPERATION = -125,
    HKS_ERROR_INVALID_WRAPPED_FORMAT = -126,
    HKS_ERROR_INVALID_USAGE_OF_KEY = -127,
    HKS_ERROR_CHECK_GET_AUTH_TYP_FAILED = -128,
    HKS_ERROR_CHECK_GET_CHALLENGE_TYPE_FAILED = -129,
    HKS_ERROR_CHECK_GET_ACCESS_TYPE_FAILED = -130,
    HKS_ERROR_CHECK_GET_AUTH_TOKEN_FAILED = -131,
    HKS_ERROR_INVALID_TIME_OUT = -132,
    HKS_ERROR_INVALID_AUTH_TYPE = -133,
    HKS_ERROR_INVALID_CHALLENGE_TYPE = -134,
    HKS_ERROR_INVALID_ACCESS_TYPE = -135,
    HKS_ERROR_INVALID_AUTH_TOKEN = -136,
    HKS_ERROR_INVALID_SECURE_SIGN_TYPE = -137,

    HKS_ERROR_NEED_SKIP_ACCESS_CONTROL = -138,

    HKS_ERROR_INTERNAL_ERROR = -999,
    HKS_ERROR_UNKNOWN_ERROR = -1000,
};

/**
 * @brief hks err code
 */
enum HksErrCode {
    HUKS_ERR_CODE_PERMISSION_FAIL = 201,
    HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401,
    HUKS_ERR_CODE_NOT_SUPPORTED_API = 801,

    HUKS_ERR_CODE_FEATURE_NOT_SUPPORTED = 12000001,
    HUKS_ERR_CODE_MISSING_CRYPTO_ALG_ARGUMENT = 12000002,
    HUKS_ERR_CODE_INVALID_CRYPTO_ALG_ARGUMENT = 12000003,
    HUKS_ERR_CODE_FILE_OPERATION_FAIL = 12000004,
    HUKS_ERR_CODE_COMMUNICATION_FAIL = 12000005,
    HUKS_ERR_CODE_CRYPTO_FAIL = 12000006,
    HUKS_ERR_CODE_KEY_AUTH_PERMANENTLY_INVALIDATED = 12000007,
    HUKS_ERR_CODE_KEY_AUTH_VERIFY_FAILED = 12000008,
    HUKS_ERR_CODE_KEY_AUTH_TIME_OUT = 12000009,
    HUKS_ERR_CODE_SESSION_LIMIT = 12000010,
    HUKS_ERR_CODE_ITEM_NOT_EXIST = 12000011,
    HUKS_ERR_CODE_EXTERNAL_ERROR = 12000012,
    HUKS_ERR_CODE_CREDENTIAL_NOT_EXIST = 12000013,
    HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014,
    HUKS_ERR_CODE_CALL_SERVICE_FAILED = 12000015,
};

/**
 * @brief hks tag type
 */
enum HksTagType {
    HKS_TAG_TYPE_INVALID = 0 << 28,
    HKS_TAG_TYPE_INT = 1 << 28,
    HKS_TAG_TYPE_UINT = 2 << 28,
    HKS_TAG_TYPE_ULONG = 3 << 28,
    HKS_TAG_TYPE_BOOL = 4 << 28,
    HKS_TAG_TYPE_BYTES = 5 << 28,
};

/**
 * @brief hks send type
 */
enum HksSendType {
    HKS_SEND_TYPE_ASYNC = 0,
    HKS_SEND_TYPE_SYNC,
};

/**
 * @brief hks user auth type
 */
enum HksUserAuthType {
    HKS_USER_AUTH_TYPE_FINGERPRINT = 1 << 0,
    HKS_USER_AUTH_TYPE_FACE = 1 << 1,
    HKS_USER_AUTH_TYPE_PIN = 1 << 2,
};

/**
 * @brief hks auth access type
 */
enum HksAuthAccessType {
    HKS_AUTH_ACCESS_INVALID_CLEAR_PASSWORD = 1 << 0,
    HKS_AUTH_ACCESS_INVALID_NEW_BIO_ENROLL = 1 << 1,
};

/**
 * @brief hks challenge type
 */
enum HksChallengeType {
    HKS_CHALLENGE_TYPE_NORMAL = 0,
    HKS_CHALLENGE_TYPE_CUSTOM = 1,
    HKS_CHALLENGE_TYPE_NONE = 2,
};

/**
 * @brief hks challenge position
 */
enum HksChallengePosition {
    HKS_CHALLENGE_POS_0 = 0,
    HKS_CHALLENGE_POS_1,
    HKS_CHALLENGE_POS_2,
    HKS_CHALLENGE_POS_3,
};

/**
 * @brief hks secure sign type
 */
enum HksSecureSignType {
    HKS_SECURE_SIGN_WITH_AUTHINFO = 1,
};

#define HKS_ASSIGN_ENUM_VALUE(x, y) x = y,

#define HKS_ASSIGN_PARAM_ALG_ENUM \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_INVALID, HKS_TAG_TYPE_INVALID | 0) \
    /* Base algrithom TAG: 1 - 200 */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ALGORITHM, HKS_TAG_TYPE_UINT | 1) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_PURPOSE, HKS_TAG_TYPE_UINT | 2) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_SIZE, HKS_TAG_TYPE_UINT | 3) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_DIGEST, HKS_TAG_TYPE_UINT | 4) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_PADDING, HKS_TAG_TYPE_UINT | 5) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_BLOCK_MODE, HKS_TAG_TYPE_UINT | 6) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_TYPE, HKS_TAG_TYPE_UINT | 7) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ASSOCIATED_DATA, HKS_TAG_TYPE_BYTES | 8) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_NONCE, HKS_TAG_TYPE_BYTES | 9) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IV, HKS_TAG_TYPE_BYTES | 10) \
    /* Key derivation TAG */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_INFO, HKS_TAG_TYPE_BYTES | 11) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_SALT, HKS_TAG_TYPE_BYTES | 12) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_PWD, HKS_TAG_TYPE_BYTES | 13) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ITERATION, HKS_TAG_TYPE_UINT | 14) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_GENERATE_TYPE, HKS_TAG_TYPE_UINT | 15) /* choose from enum HksKeyGenerateType */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_DERIVE_MAIN_KEY, HKS_TAG_TYPE_BYTES | 16) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_DERIVE_FACTOR, HKS_TAG_TYPE_BYTES | 17) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_DERIVE_ALG, HKS_TAG_TYPE_UINT | 18) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_AGREE_ALG, HKS_TAG_TYPE_UINT | 19) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_AGREE_PUBLIC_KEY_IS_KEY_ALIAS, HKS_TAG_TYPE_BOOL | 20) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_AGREE_PRIVATE_KEY_ALIAS, HKS_TAG_TYPE_BYTES | 21) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_AGREE_PUBLIC_KEY, HKS_TAG_TYPE_BYTES | 22) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_ALIAS, HKS_TAG_TYPE_BYTES | 23) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_DERIVE_KEY_SIZE, HKS_TAG_TYPE_UINT | 24) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IMPORT_KEY_TYPE, HKS_TAG_TYPE_UINT | 25) /* choose from enum HksImportKeyType */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_UNWRAP_ALGORITHM_SUITE, HKS_TAG_TYPE_UINT | 26) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_CIPHER_TEXT, HKS_TAG_TYPE_BYTES | 27) \
    /* parameters required by HuksCoreChipsetPlatformDecrypt */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_PEER_PUBLIC_KEY, HKS_TAG_TYPE_BYTES | 28) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_DERIVE_AGREE_KEY_STORAGE_FLAG, HKS_TAG_TYPE_UINT | 29) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_RSA_PSS_SALT_LEN_TYPE, HKS_TAG_TYPE_UINT | 30) /* only supported for PSS padding */\
    /* Key authentication related TAG: 201 - 300 */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ACTIVE_DATETIME, HKS_TAG_TYPE_ULONG | 201) \
    /* Date when new "messages" should not be created. */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ORIGINATION_EXPIRE_DATETIME, HKS_TAG_TYPE_ULONG | 202) \
    /* Date when existing "messages" should not be used. */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_USAGE_EXPIRE_DATETIME, HKS_TAG_TYPE_ULONG | 203) \
    /* Key creation time */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_CREATION_DATETIME, HKS_TAG_TYPE_ULONG | 204) \
    /* Other authentication related TAG: 301 - 500 */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ALL_USERS, HKS_TAG_TYPE_BOOL | 301) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_USER_ID, HKS_TAG_TYPE_UINT | 302) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_NO_AUTH_REQUIRED, HKS_TAG_TYPE_BOOL | 303) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_USER_AUTH_TYPE, HKS_TAG_TYPE_UINT | 304) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_AUTH_TIMEOUT, HKS_TAG_TYPE_UINT | 305) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_AUTH_TOKEN, HKS_TAG_TYPE_BYTES | 306) \
    /* Key secure access control and user auth TAG */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_AUTH_ACCESS_TYPE, HKS_TAG_TYPE_UINT | 307) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_SECURE_SIGN_TYPE, HKS_TAG_TYPE_UINT | 308) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_CHALLENGE_TYPE, HKS_TAG_TYPE_UINT | 309) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_CHALLENGE_POS, HKS_TAG_TYPE_UINT | 310) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_AUTH_PURPOSE, HKS_TAG_TYPE_UINT | 311) \
    /* Attestation related TAG: 501 - 600 */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_CHALLENGE, HKS_TAG_TYPE_BYTES | 501) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_APPLICATION_ID, HKS_TAG_TYPE_BYTES | 502) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_BRAND, HKS_TAG_TYPE_BYTES | 503) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_DEVICE, HKS_TAG_TYPE_BYTES | 504) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_PRODUCT, HKS_TAG_TYPE_BYTES | 505) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_SERIAL, HKS_TAG_TYPE_BYTES | 506) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_IMEI, HKS_TAG_TYPE_BYTES | 507) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_MEID, HKS_TAG_TYPE_BYTES | 508) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_MANUFACTURER, HKS_TAG_TYPE_BYTES | 509) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_MODEL, HKS_TAG_TYPE_BYTES | 510) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_ALIAS, HKS_TAG_TYPE_BYTES | 511) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_SOCID, HKS_TAG_TYPE_BYTES | 512) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_UDID, HKS_TAG_TYPE_BYTES | 513) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_SEC_LEVEL_INFO, HKS_TAG_TYPE_BYTES | 514) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_ID_VERSION_INFO, HKS_TAG_TYPE_BYTES | 515) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ATTESTATION_BASE64, HKS_TAG_TYPE_BOOL | 516) \
    /* Extention TAG: 1001 - 9999 */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IS_KEY_ALIAS, HKS_TAG_TYPE_BOOL | 1001) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_STORAGE_FLAG, HKS_TAG_TYPE_UINT | 1002) /* choose from enum HksKeyStorageType */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IS_ALLOWED_WRAP, HKS_TAG_TYPE_BOOL | 1003) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_WRAP_TYPE, HKS_TAG_TYPE_UINT | 1004) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_AUTH_ID, HKS_TAG_TYPE_BYTES | 1005) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_ROLE, HKS_TAG_TYPE_UINT | 1006) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_FLAG, HKS_TAG_TYPE_UINT | 1007) /* choose from enum HksKeyFlag */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IS_ASYNCHRONIZED, HKS_TAG_TYPE_UINT | 1008) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_SECURE_KEY_ALIAS, HKS_TAG_TYPE_BOOL | 1009) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_SECURE_KEY_UUID, HKS_TAG_TYPE_BYTES | 1010) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_DOMAIN, HKS_TAG_TYPE_UINT | 1011) \
    /* Inner-use TAG: 10001 - 10999 */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_PACKAGE_NAME, HKS_TAG_TYPE_BYTES | 10002) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ACCESS_TIME, HKS_TAG_TYPE_UINT | 10003) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_USES_TIME, HKS_TAG_TYPE_UINT | 10004) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_CRYPTO_CTX, HKS_TAG_TYPE_ULONG | 10005) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_PAYLOAD_LEN, HKS_TAG_TYPE_UINT | 10008) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_AE_TAG, HKS_TAG_TYPE_BYTES | 10009) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IS_KEY_HANDLE, HKS_TAG_TYPE_ULONG | 10010) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_INIT_CHALLENGE, HKS_TAG_TYPE_BYTES | 10011) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IS_USER_AUTH_ACCESS, HKS_TAG_TYPE_BOOL | 10012) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_USER_AUTH_CHALLENGE, HKS_TAG_TYPE_BYTES | 10013) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_USER_AUTH_ENROLL_ID_INFO, HKS_TAG_TYPE_BYTES | 10014) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_USER_AUTH_SECURE_UID, HKS_TAG_TYPE_BYTES | 10015) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_AUTH_RESULT, HKS_TAG_TYPE_INT | 10016) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IF_NEED_APPEND_AUTH_INFO, HKS_TAG_TYPE_BOOL | 10017) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_VERIFIED_AUTH_TOKEN, HKS_TAG_TYPE_BYTES | 10018) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_IS_APPEND_UPDATE_DATA, HKS_TAG_TYPE_BOOL | 10019) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_ACCESS_TIME, HKS_TAG_TYPE_ULONG | 10020) \
    /* TAGs used for paramSetOut */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_SYMMETRIC_KEY_DATA, HKS_TAG_TYPE_BYTES | 20001) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ASYMMETRIC_PUBLIC_KEY_DATA, HKS_TAG_TYPE_BYTES | 20002) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_ASYMMETRIC_PRIVATE_KEY_DATA, HKS_TAG_TYPE_BYTES | 20003) \

#define HKS_ASSIGN_PARAM_FILE_ENUM \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_PROCESS_NAME, HKS_TAG_TYPE_BYTES | 10001) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY, HKS_TAG_TYPE_BYTES | 10006) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_KEY_VERSION, HKS_TAG_TYPE_UINT | 10007) \
    /* Os version related TAG */\
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_OS_VERSION, HKS_TAG_TYPE_UINT | 10101) \
    HKS_ASSIGN_ENUM_VALUE(HKS_TAG_OS_PATCHLEVEL, HKS_TAG_TYPE_UINT | 10102) \

/**
 * @brief hks Tag
 */
enum HksTag {
    /**
     * HUKS tags for alg enum
     */
    HKS_ASSIGN_PARAM_ALG_ENUM

    /**
     * HUKS tags for key file enum
     */
    HKS_ASSIGN_PARAM_FILE_ENUM
};

/**
 * @brief hks blob
 */
struct HksBlob {
    uint32_t size;
    uint8_t *data;
};

/**
 * @brief hks param
 */
struct HksParam {
    uint32_t tag;
    union {
        bool boolParam;
        int32_t int32Param;
        uint32_t uint32Param;
        uint64_t uint64Param;
        struct HksBlob blob;
    };
};

/**
 * @brief hks param set
 */
struct HksParamSet {
    uint32_t paramSetSize;
    uint32_t paramsCnt;
    struct HksParam params[];
};

/**
 * @brief hks certificate chain
 */
struct HksCertChain {
    struct HksBlob *certs;
    uint32_t certsCount;
};

/**
 * @brief hks key info
 */
struct HksKeyInfo {
    struct HksBlob alias;
    struct HksParamSet *paramSet;
};

/**
 * @brief hks public key info
 */
struct HksPubKeyInfo {
    enum HksKeyAlg keyAlg;
    uint32_t keySize;
    uint32_t nOrXSize;
    uint32_t eOrYSize;
    uint32_t placeHolder;
};

/**
 * @brief hks rsa key material
 */
struct HksKeyMaterialRsa {
    enum HksKeyAlg keyAlg;
    uint32_t keySize;
    uint32_t nSize;
    uint32_t eSize;
    uint32_t dSize;
};

/**
 * @brief hks ecc key material
 */
struct HksKeyMaterialEcc {
    enum HksKeyAlg keyAlg;
    uint32_t keySize;
    uint32_t xSize;
    uint32_t ySize;
    uint32_t zSize;
};

/**
 * @brief hks dsa key material
 */
struct HksKeyMaterialDsa {
    enum HksKeyAlg keyAlg;
    uint32_t keySize;
    uint32_t xSize;
    uint32_t ySize;
    uint32_t pSize;
    uint32_t qSize;
    uint32_t gSize;
};

/**
 * @brief hks dh key material
 */
struct HksKeyMaterialDh {
    enum HksKeyAlg keyAlg;
    uint32_t keySize;
    uint32_t pubKeySize;
    uint32_t priKeySize;
    uint32_t reserved;
};

/**
 * @brief hks 25519 key material
 */
struct HksKeyMaterial25519 {
    enum HksKeyAlg keyAlg;
    uint32_t keySize;
    uint32_t pubKeySize;
    uint32_t priKeySize;
    uint32_t reserved;
};

/**
 * @brief hks user auth token plaintext data
 */
typedef struct HksPlaintextData {
    uint8_t challenge[TOKEN_SIZE];
    uint64_t time;
    uint32_t authTrustLevel;
    uint32_t authType;
    uint32_t authMode;
    uint32_t securityLevel;
} __attribute__((__packed__)) HksPlaintextData;

/**
 * @brief hks user auth token ciphertext data
 */
typedef struct HksCiphertextData {
    int32_t userId;
    uint64_t secureUid;
    uint64_t enrolledId;
    uint64_t credentialId;
} __attribute__((__packed__)) HksCiphertextData;

/**
 * @brief hks user auth token
 */
typedef struct __attribute__((__packed__)) HksUserAuthToken {
    uint32_t version;
    HksPlaintextData plaintextData;
    HksCiphertextData ciphertextData;
    uint8_t tag[HKS_AE_TAG_LEN];
    uint8_t iv[HKS_AE_NONCE_LEN];
    uint8_t sign[SHA256_SIGN_LEN];
} __attribute__((__packed__)) HksUserAuthToken;

/**
 * @brief hks user auth token key
 */
struct HksAuthTokenKey {
    uint8_t macKey[HKS_KEY_BLOB_AT_KEY_BYTES];
    uint8_t cipherKey[HKS_KEY_BLOB_AT_KEY_BYTES];
};

/**
 * @brief hks secure sign auth info
 */
typedef struct __attribute__((__packed__)) HksSecureSignAuthInfo {
    uint32_t userAuthType;
    uint64_t authenticatorId;
    uint64_t credentialId;
} __attribute__((__packed__)) HksSecureSignAuthInfo;

#define HKS_DERIVE_DEFAULT_SALT_LEN 16
#define HKS_HMAC_DIGEST_SHA512_LEN 64
#define HKS_DEFAULT_RANDOM_LEN 16
#define HKS_MAX_KEY_AUTH_ID_LEN 64
#define HKS_KEY_MATERIAL_NUM 3
#define HKS_MAX_KEY_LEN (HKS_KEY_BYTES(HKS_RSA_KEY_SIZE_4096) * HKS_KEY_MATERIAL_NUM)
#define HKS_MAX_KEY_MATERIAL_LEN (sizeof(struct HksPubKeyInfo) + HKS_MAX_KEY_LEN + HKS_AE_TAG_LEN)

/**
 * @brief hks store header info
 */
struct HksStoreHeaderInfo {
    uint16_t version;
    uint16_t keyCount;
    uint32_t totalLen; /* key buffer total len */
    uint32_t sealingAlg;
    uint8_t salt[HKS_DERIVE_DEFAULT_SALT_LEN];
    uint8_t hmac[HKS_HMAC_DIGEST_SHA512_LEN];
};

/**
 * @brief hks store key info
 */
struct HksStoreKeyInfo {
    uint16_t keyInfoLen; /* current keyinfo len */
    uint16_t keySize;    /* keySize of key from crypto hal after encrypted */
    uint8_t random[HKS_DEFAULT_RANDOM_LEN];
    uint8_t flag;        /* import or generate key */
    uint8_t keyAlg;
    uint8_t keyMode;
    uint8_t digest;
    uint8_t padding;
    uint8_t rsv;
    uint16_t keyLen;     /* keyLen from paramset, e.g. aes-256 */
    uint32_t purpose;
    uint32_t role;
    uint16_t domain;
    uint8_t aliasSize;
    uint8_t authIdSize;
};

/**
 * @brief hks 25519 key pair
 */
struct Hks25519KeyPair {
    uint32_t publicBufferSize;
    uint32_t privateBufferSize;
};

static inline bool IsAdditionOverflow(uint32_t a, uint32_t b)
{
    return (UINT32_MAX - a) < b;
}

static inline bool IsInvalidLength(uint32_t length)
{
    return (length == 0) || (length > MAX_OUT_BLOB_SIZE);
}

static inline int32_t CheckBlob(const struct HksBlob *blob)
{
    if ((blob == NULL) || (blob->data == NULL) || (blob->size == 0)) {
        return HKS_ERROR_INVALID_ARGUMENT;
    }
    return HKS_SUCCESS;
}

/**
 * @brief hks chipset platform decrypt scene
 */
enum HksChipsetPlatformDecryptScene {
    HKS_CHIPSET_PLATFORM_DECRYPT_SCENE_TA_TO_TA = 1,
};

#ifdef __cplusplus
}
#endif

#endif /* HKS_TYPE_H */