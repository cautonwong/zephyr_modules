/*
 * Copyright (c) 2026 Vango Technologies
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include "tfm_plat_crypto_keys.h"
#include "crypto_keys/tfm_builtin_key_ids.h"
#include "flash_layout.h"
#include "psa/crypto.h"

/* Simulated HUK for Phase 5 Dimension 3.1 */
static const uint8_t simulated_huk[] = "VANGO-V32-HUK-SIMULATION-SECRET";

static enum tfm_plat_err_t tfm_plat_get_huk(const void *ctx,
                                            uint8_t *buf, size_t buf_len,
                                            size_t *key_len,
                                            psa_key_bits_t *key_bits,
                                            psa_algorithm_t *algorithm,
                                            psa_key_type_t *type)
{
    (void)ctx;
    size_t copy_len = sizeof(simulated_huk);
    
    if (buf_len < copy_len) {
        return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    
    memcpy(buf, simulated_huk, copy_len);
    *key_len = copy_len;
    *key_bits = copy_len * 8;
    *algorithm = PSA_ALG_HKDF(PSA_ALG_SHA_256);
    *type = PSA_KEY_TYPE_DERIVE;

    return TFM_PLAT_ERR_SUCCESS;
}

static const tfm_plat_builtin_key_descriptor_t builtin_key_table[] = {
    {
        .key_id = TFM_BUILTIN_KEY_ID_HUK,
        .slot_number = 0,
        .lifetime = PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
            PSA_KEY_PERSISTENCE_READ_ONLY,
            PSA_KEY_LOCATION_LOCAL_STORAGE),
        .loader_key_func = tfm_plat_get_huk,
        .loader_key_ctx = NULL
    }
};

size_t tfm_plat_builtin_key_get_desc_table_ptr(const tfm_plat_builtin_key_descriptor_t *desc_ptr[])
{
    *desc_ptr = builtin_key_table;
    return sizeof(builtin_key_table) / sizeof(builtin_key_table[0]);
}

size_t tfm_plat_builtin_key_get_policy_table_ptr(const tfm_plat_builtin_key_policy_t *policy_ptr[])
{
    *policy_ptr = NULL;
    return 0;
}
