/**
 * \file aes_alt.h
 *
 * \brief   This file contains alternate AES definitions and functions.
 *
 *          The Advanced Encryption Standard (AES) specifies a FIPS-approved
 *          cryptographic algorithm that can be used to protect electronic
 *          data.
 *
 *          The AES algorithm is a symmetric block cipher that can
 *          encrypt and decrypt information. For more information, see
 *          <em>FIPS Publication 197: Advanced Encryption Standard</em> and
 *          <em>ISO/IEC 18033-2:2006: Information technology -- Security
 *          techniques -- Encryption algorithms -- Part 2: Asymmetric
 *          ciphers</em>.
 *
 *          The AES-XTS block mode is standardized by NIST SP 800-38E
 *          <https://nvlpubs.nist.gov/nistpubs/legacy/sp/nistspecialpublication800-38e.pdf>
 *          and described in detail by IEEE P1619
 *          <https://ieeexplore.ieee.org/servlet/opac?punumber=4375278>.
 */


#ifndef MBEDTLS_AES_ALT_H
#define MBEDTLS_AES_ALT_H


#ifdef __cplusplus
extern "C" {
#endif

#if defined(MBEDTLS_AES_ALT)

#if defined(MBEDTLS_STD_HASHCRYPT_AES)
/**
 * \brief          AES context structure
 */
#define mbedtls_aes_context hashcrypt_handle_t

#else
// Regular implementation
//

/**
 * \brief The AES context-type definition.
 */
typedef struct
{
    int nr;                     /*!< The number of rounds. */
    uint32_t *rk;               /*!< AES round keys. */
    uint32_t buf[68];           /*!< Unaligned data buffer. This buffer can
                                     hold 32 extra Bytes, which can be used for
                                     one of the following purposes:
                                     <ul><li>Alignment if VIA padlock is
                                             used.</li>
                                     <li>Simplifying key expansion in the 256-bit
                                         case by generating an extra round key.
                                         </li></ul> */
}
mbedtls_aes_context;
#endif /* MBEDTLS_STD_HASHCRYPT_AES */

#endif /* MBEDTLS_AES_ALT */

#ifdef __cplusplus
}
#endif

#endif /* aes_alt.h */
