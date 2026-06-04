/*
 * Copyright (c) 2024 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * MbedTLS Hardware Alternate Implementation for Vango V32F20x
 *
 * The V32F20x hardware encryption engine (ENCENG) supports:
 *   - AES-128/256 ECB/CBC acceleration
 *   - SHA-256 hardware digest
 *
 * This file provides the MbedTLS "ALT" hook layer so that when TF-M
 * calls any AES or SHA PSA operation, it is transparently redirected
 * to V32F20x hardware rather than the MbedTLS software fallback.
 *
 * Engineering checklist for completing hardware integration:
 *   1. Include the actual lib_enceng.h / lib_sha.h HAL headers
 *   2. Replace the TODO stubs with real register-level calls
 *   3. Set MBEDTLS_AES_ALT and MBEDTLS_SHA256_ALT in mbedtls_config.h
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* ============================================================
 * AES Hardware Acceleration (MBEDTLS_AES_ALT)
 * ============================================================ */
#if defined(MBEDTLS_AES_ALT)

#include "mbedtls/aes.h"

void mbedtls_aes_init(mbedtls_aes_context *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    /*
     * TODO: Initialize V32F20x ENCENG peripheral
     * ENCENG_DeInit();
     * ENCENG_AES_Init(ENCENG_AES_KEY_128);
     */
}

void mbedtls_aes_free(mbedtls_aes_context *ctx)
{
    if (ctx == NULL) return;
    /*
     * TODO: ENCENG_DeInit();
     */
    memset(ctx, 0, sizeof(*ctx));
}

int mbedtls_aes_setkey_enc(mbedtls_aes_context *ctx,
                            const unsigned char *key,
                            unsigned int keybits)
{
    if (keybits != 128 && keybits != 256) {
        return MBEDTLS_ERR_AES_INVALID_KEY_LENGTH;
    }
    /*
     * TODO: Load key into ENCENG registers
     * ENCENG_AES_SetKey(key, keybits);
     */
    ctx->nr = (keybits == 256) ? 14 : 10;
    memcpy(ctx->buf, key, keybits / 8);
    return 0;
}

int mbedtls_aes_setkey_dec(mbedtls_aes_context *ctx,
                            const unsigned char *key,
                            unsigned int keybits)
{
    /* ENCENG handles decryption with the same key loading */
    return mbedtls_aes_setkey_enc(ctx, key, keybits);
}

int mbedtls_aes_crypt_ecb(mbedtls_aes_context *ctx,
                           int mode,
                           const unsigned char input[16],
                           unsigned char output[16])
{
    /*
     * TODO: Trigger V32F20x hardware AES-ECB:
     *   if (mode == MBEDTLS_AES_ENCRYPT)
     *       ENCENG_AES_Encrypt(input, output, 16);
     *   else
     *       ENCENG_AES_Decrypt(input, output, 16);
     */
    (void)ctx;
    (void)mode;
    memcpy(output, input, 16); /* Software passthrough placeholder */
    return 0;
}

#endif /* MBEDTLS_AES_ALT */

/* ============================================================
 * SHA-256 Hardware Acceleration (MBEDTLS_SHA256_ALT)
 * ============================================================ */
#if defined(MBEDTLS_SHA256_ALT)

#include "mbedtls/sha256.h"

void mbedtls_sha256_init(mbedtls_sha256_context *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    /*
     * TODO: ENCENG_SHA256_Init();
     */
}

void mbedtls_sha256_free(mbedtls_sha256_context *ctx)
{
    if (ctx == NULL) return;
    memset(ctx, 0, sizeof(*ctx));
}

void mbedtls_sha256_clone(mbedtls_sha256_context *dst,
                           const mbedtls_sha256_context *src)
{
    *dst = *src;
}

int mbedtls_sha256_starts(mbedtls_sha256_context *ctx, int is224)
{
    (void)is224;
    ctx->is224 = is224;
    /*
     * TODO: ENCENG_SHA256_Start(is224 ? ENCENG_SHA224 : ENCENG_SHA256);
     */
    return 0;
}

int mbedtls_sha256_update(mbedtls_sha256_context *ctx,
                           const unsigned char *input,
                           size_t ilen)
{
    (void)ctx;
    (void)input;
    (void)ilen;
    /*
     * TODO: ENCENG_SHA256_Update(input, ilen);
     */
    return 0;
}

int mbedtls_sha256_finish(mbedtls_sha256_context *ctx,
                           unsigned char *output)
{
    (void)ctx;
    (void)output;
    /*
     * TODO: ENCENG_SHA256_Finish(output);
     */
    return 0;
}

#endif /* MBEDTLS_SHA256_ALT */
