

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include "ksdk_mbedtls_config.h"
#endif

#include "cop_common.h"


#define CLEAN_RETURN(value) \
    {                       \
        ret = (value);        \
        goto cleanup;       \
    }


/******************************************************************************/
/******************** CRYPTO_InitHardware **************************************/
/******************************************************************************/
/*!
 * @brief Application init for various Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic init for Crypto Hw acceleration and Hw entropy modules.
 */
void CRYPTO_InitHardware(void)
{
#if defined(FSL_FEATURE_SOC_CASPER_COUNT) && (FSL_FEATURE_SOC_CASPER_COUNT > 0)
    /* Initialize CASPER */
    CASPER_Init(CASPER_START_ADDR);
#endif
}


#if defined(MBEDTLS_RSA_PUBLIC_ALT)
#if defined(MBEDTLS_STD_CASPER_PKHA)

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdio.h>
#define mbedtls_calloc calloc
#define mbedtls_free free
#endif

#include "mbedtls/bignum.h"
#include "mbedtls/rsa.h"

#define ciL    (sizeof(mbedtls_mpi_uint))         /* chars in limb  */
#define biL    (ciL << 3)               /* bits  in limb  */

static uint8_t *msg_ret_std        = (uint8_t *)CASPER_START_ADDR;

static void reverse_array(uint8_t *src, size_t src_len)
{
    int i;

    for (i = 0; i < src_len / 2; i++)
    {
        uint8_t tmp;

        tmp = src[i];
        src[i] = src[src_len - 1 - i];
        src[src_len - 1 - i] = tmp;
    }
}

#if defined (MBEDTLS_COP_SUB_ABS_ALT)
/*
 * Unsigned subtraction: X = |A| - |B|  (HAC 14.9)
 */
#if defined(MBEDTLS_MPI_SUB_ABS_ALT)
/* Access to original version of mbedtls_mpi_sub_abs function. */
int mbedtls_mpi_sub_abs_orig(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B);
#else
int mbedtls_mpi_sub_abs(mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B)
{
  size_t sizeA = mbedtls_mpi_size(A);
  size_t sizeB = mbedtls_mpi_size(B);
  int ret;
  size_t sizeC;
  uint8_t *ptrA = &msg_ret_std[0];
  uint8_t *ptrB = &msg_ret_std[STD_PKHA_INT_MAX_BYTES];
  uint8_t *ptrC = &msg_ret_std[STD_PKHA_INT_MAX_BYTES + STD_PKHA_INT_MAX_BYTES];
  uint32_t n = 0;
  mbedtls_mpi TB;
        
  mbedtls_mpi_init( &TB );

  if( X == B )
  {
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &TB, B ) );
    B = &TB;
  }
    
  if( X != A )
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( X, A ) );

  memcpy(ptrC, A->p, (A->n << 2));
  memcpy(ptrB, B->p, (B->n << 2));

        
  if (sizeB < sizeA)
  {
    memset(&ptrB[sizeB], 0, (sizeA - sizeB));
    sizeB = sizeA;
  }        

  if (sizeA % 8)
  {
    sizeA = ((sizeA >> 3) + 1) << 3; 
    memset(&ptrB[sizeB], 0, (sizeA - sizeB));
    memset(&ptrC[sizeB], 0, (sizeA - sizeB));
  }

  ret = (int)CASPER_ModSub1(ptrA, sizeA >> 2, ptrB, sizeA >> 2, ptrC);
  for( n = sizeA >> 2; n > 0; n-- )
    if( ((uint32_t*)ptrC)[n - 1] != 0 )
      break;
            
  sizeC = n << 2;

  if (ret != kStatus_Success)
    CLEAN_RETURN(MBEDTLS_ERR_MPI_NOT_ACCEPTABLE);

  memcpy(X->p, ptrC, sizeC);
  X->n = sizeC >> 2;
  X->s = 1;
    
cleanup:
    
  mbedtls_mpi_free( &TB );
  return (ret);
}
#endif /* MBEDTLS_MPI_SUB_ABS_ALT */
#endif


#if defined (MBEDTLS_COP_MUL_ALT)
/*
 * Baseline multiplication: X = A * B  (HAC 14.12)
 */
#if defined(MBEDTLS_MPI_MUL_MPI_ALT)
int mbedtls_mpi_mul_mpi_orig( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
#else
int mbedtls_mpi_mul_mpi( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
#endif /* MBEDTLS_MPI_MUL_MPI_ALT */
{
  int ret;
  size_t i, j;
  size_t mulSize = 0;
  size_t mulTmpSize = 0;
  mbedtls_mpi TA, TB;
  size_t sizeA = mbedtls_mpi_size(A);
  size_t sizeB = mbedtls_mpi_size(B);
  size_t sizeC;
  uint8_t *ptrA = &msg_ret_std[0];
  uint8_t *ptrB = &msg_ret_std[600];
  uint8_t *ptrC = &msg_ret_std[1200];
  uint32_t n = 0;

  mbedtls_mpi_init( &TA ); mbedtls_mpi_init( &TB );

  if( X == A ) { MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &TA, A ) ); A = &TA; }
  if( X == B ) { MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &TB, B ) ); B = &TB; }

  for( i = A->n; i > 0; i-- )
    if( A->p[i - 1] != 0 )
      break;

  for( j = B->n; j > 0; j-- )
    if( B->p[j - 1] != 0 )
      break;
        
        

  MBEDTLS_MPI_CHK( mbedtls_mpi_grow( X, i + j ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_lset( X, 0 ) );

  i = i << 2;
  j = j << 2;
  memcpy(ptrA, A->p, i);
  memcpy(ptrB, B->p, j);
    
  if (i % 8)
  {
    mulTmpSize = i;
    i = ((i >> 3) + 1) << 3; 
    memset(&ptrA[mulTmpSize], 0, (i - mulTmpSize));
  }
  
  if (j % 8)
  {
    mulTmpSize = j;
    j = ((j >> 3) + 1) << 3; 
    memset(&ptrB[mulTmpSize], 0, (j - mulTmpSize));
  }

  CASPER_ModMul(ptrA, i >> 2, ptrB, j >> 2, ptrC);

  
  for( n = (i+j) >> 2; n > 0; n-- )
    if( ((uint32_t*)ptrC)[n - 1] != 0 )
      break;
            
  sizeC = n << 2;
  memcpy(X->p, ptrC, sizeC);
  X->n = sizeC >> 2;

  X->s = A->s * B->s;

cleanup:

  mbedtls_mpi_free( &TB ); mbedtls_mpi_free( &TA );

  return( ret );
}

#endif

#if defined(MBEDTLS_COP_ADD_ABS_ALT)
/*
 * Unsigned addition: X = |A| + |B|  (HAC 14.7)
 */
#if defined(MBEDTLS_MPI_ADD_ABS_ALT)
int mbedtls_mpi_add_abs_orig( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
#else
int mbedtls_mpi_add_abs( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *B )
#endif /* MBEDTLS_MPI_ADD_ABS_ALT */
{
  int ret;
  size_t i = 0, j = 0, tmpLen = 0, n = 0, sizeC = 0;
  mbedtls_mpi_uint *o, *p, c, tmp;
  uint8_t *ptrA = &msg_ret_std[0];
  uint8_t *ptrB = ptrA + STD_PKHA_INT_MAX_BYTES;
  uint8_t *ptrC = ptrB + STD_PKHA_INT_MAX_BYTES;
  
  if( X == B )
  {
    const mbedtls_mpi *T = A; A = X; B = T;
  }

  if( X != A )
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( X, A ) );

  /*
  * X should always be positive as a result of unsigned additions.
  */
  X->s = 1;

  for( i = A->n; i > 0; i-- )
    if( A->p[i - 1] != 0 )
      break;

  for( j = B->n; j > 0; j-- )
    if( B->p[j - 1] != 0 )
      break;

  MBEDTLS_MPI_CHK( mbedtls_mpi_grow( X, j ) );        
  if (i == 0)
  {
    memcpy(X->p, B->p, j << 2);
    X->n = j;
    goto cleanup;
  }
  
  if (j == 0)
  {
    memcpy(X->p, A->p, i << 2);
    X->n = i;
    goto cleanup;
  }
          
     
  i = i << 2;
  j = j << 2;
  memcpy(ptrC, A->p, i);
  memcpy(ptrB, B->p, j);
        

  if (i > j)
  {
    memset(&ptrB[j], 0, i - j);
    j = i;
  }
  else
  {
    memset(&ptrC[i], 0, j - i);
    i = j;
  }
  
  tmpLen = j;
    
  
  if (tmpLen % 8)
  {
    tmpLen = ((tmpLen >> 3) + 1) << 3; 
    memset(&ptrC[j], 0, (tmpLen - j));
    memset(&ptrB[j], 0, (tmpLen - j));
  }
  
  memset(&ptrC[tmpLen], 0, (tmpLen + 8));
  memset(&ptrB[tmpLen], 0, (tmpLen + 8));
  
  tmpLen = tmpLen + 8;
  
  CASPER_ModAdd(ptrA, tmpLen >> 2, ptrB, tmpLen >> 2, ptrC);
  
  for( n = tmpLen >> 2; n > 0; n-- )
    if( ((uint32_t*)ptrC)[n - 1] != 0 )
      break;
            
  sizeC = n << 2;
  memcpy(X->p, ptrC, sizeC);
  X->n = sizeC >> 2;

cleanup:

  return( ret );
}

#endif


/*
 * Do an RSA public key operation
 */
static int mbedtls_mpi_exp_mod_shim(mbedtls_mpi *X,
                                    const mbedtls_mpi *A,
                                    const mbedtls_mpi *E,
                                    const mbedtls_mpi *N , mbedtls_mpi *prec_RR )
{
  int ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
  size_t sizeA = mbedtls_mpi_size(A);
  size_t sizeN = mbedtls_mpi_size(N);
  size_t sizeE = mbedtls_mpi_size(E);
  uint8_t *ptrX = mbedtls_calloc(4, STD_PKHA_INT_MAX_BYTES);
  uint8_t *ptrA = ptrX + STD_PKHA_INT_MAX_BYTES;
  uint8_t *ptrN = ptrA + STD_PKHA_INT_MAX_BYTES;
  uint8_t *ptrE = ptrN + STD_PKHA_INT_MAX_BYTES;
  mbedtls_mpi tmp;
  mbedtls_mpi RR;
  size_t sizeMax;

  sizeMax = sizeA > sizeN ? sizeA : sizeN;
     
  mbedtls_mpi_init( &RR );
  mbedtls_mpi_init( &tmp );

  if (NULL == ptrX)
  {
    CLEAN_RETURN(MBEDTLS_ERR_MPI_ALLOC_FAILED);
  }

  MBEDTLS_MPI_CHK( mbedtls_mpi_grow( &tmp,  (N->n+1)) );
    
  if( mbedtls_mpi_cmp_mpi( A, N ) >= 0 )
  MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &tmp, A, N ) );
  else
  {
    mbedtls_mpi_copy( &tmp, A);
  }
    
  sizeA = mbedtls_mpi_size(&tmp);

  if (sizeA % 4) sizeA = ((sizeA >> 2) + 1) << 2;
  if (sizeE % 4) sizeE = ((sizeE >> 2) + 1) << 2;

  MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&tmp, ptrA, sizeA));
  reverse_array(ptrA, sizeA);

  MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(N, ptrN, sizeN));
  reverse_array(ptrN, sizeN);

  MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(E, ptrE, sizeE));
  reverse_array(ptrE, sizeE);

  if (sizeN < sizeMax)
  {
    memset(&ptrN[sizeN], 0, sizeMax - sizeN);
  }

  // R = A^E mod N
  CASPER_ModExp((CASPER_Type*)CASPER_START_ADDR, ptrA, sizeA / 4U, ptrN, sizeN / 4U, ptrE, sizeE / 4U, ptrX);

  reverse_array(ptrX, sizeN);
  MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(X, ptrX, sizeN));

cleanup:
  if (ptrX != NULL)
  {
    mbedtls_free(ptrX);
  }

  mbedtls_mpi_free( &tmp );

  return ret;
}


int mbedtls_rsa_public(mbedtls_rsa_context *ctx, const unsigned char *input, unsigned char *output)
{
  int ret = 0;
  size_t olen = 0;
  mbedtls_mpi T;

  mbedtls_mpi_init(&T);

#if defined(MBEDTLS_THREADING_C)
  if ((ret = mbedtls_mutex_lock(&ctx->mutex)) != 0)
  {
    return (ret);
  }  
#endif

  MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&T, input, ctx->len));

  if (mbedtls_mpi_cmp_mpi(&T, &ctx->N) >= 0)
  {
    ret = MBEDTLS_ERR_MPI_BAD_INPUT_DATA;
    goto cleanup;
  }

  olen = ctx->len;

  MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod_shim(&T, &T, &ctx->E, &ctx->N , &ctx->RN ));
  MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&T, output, olen));

cleanup:
#if defined(MBEDTLS_THREADING_C)
  if (mbedtls_mutex_unlock(&ctx->mutex) != 0)
  {
    return (MBEDTLS_ERR_THREADING_MUTEX_ERROR);
  } 
#endif

  mbedtls_mpi_free(&T);

  if (ret != 0)
    return (MBEDTLS_ERR_RSA_PUBLIC_FAILED + ret);

  return (0);
}

#endif /* MBEDTLS_STD_CASPER_PKHA */
#endif /* MBEDTLS_RSA_PUBLIC_ALT */

/*
 * Right-shift: X >>= 1
 */
int mbedtls_mpi_shift_r1_shim( uint32_t *X, size_t Xn)
{
  size_t i = 0;
  mbedtls_mpi_uint r0 = 0, r1 = 0;
  size_t HighBit = X[Xn - 1] & 0x80000000U;
  int j = 0;
  
  for(j = Xn; j > 0; j--)
  {
    if (X[j - 1] != 0)
      break;
  }

  /*
  * shift by count % limb_size
  */

  for( i = j; i > 0; i-- )
  {
    r1 = X[i - 1] << (biL - 1);
    X[i - 1] >>= 1;
    X[i - 1] |= r0;
    r0 = r1;
  }

  X[Xn - 1] = X[Xn - 1] | HighBit;
  return( 0 );
}


/*
 * Compare with 0
 */
int mbedtls_mpi_cmp_mpi_zero_shim( uint32_t *X, uint32_t Xn )
{
  size_t i = 0, j = 0;
  int Xs = 1, Ys = 0;

  if ((X[Xn - 1] & 0x80000000) != 0)
    return -1;

  for( i = Xn; i > 0; i-- )
    if( X[i - 1] != 0 )
      return 1;

  return( 0 );
}

int mbedtls_mpi_cmp_mpi_shim(uint32_t *X, uint32_t *Y, uint32_t len)
{
  uint32_t i = 0;
  int ret = 0;
  
  CASPER_ModSub1( (uint8_t*)X, len, (uint8_t*)Y, len, (uint8_t*)X ) ;
  
  if ((X[len -1] & 0x80000000) != 0)
  {
    ret = -1;
    goto exit;
  }
  
  for( i = len; i > 0; i-- )
  {
    if( X[i - 1] != 0 )
    {
      ret = 1;
      goto exit;
    }
  }
  
  ret = 0;
exit:
  CASPER_ModAdd( (uint8_t*)X, len, (uint8_t*)Y, len, (uint8_t*)X ) ;
  return ret;
}



/*
 * Modular inverse: X = A^-1 mod N  (HAC 14.61 / 14.64)
 */
#if defined(MBEDTLS_MPI_INV_MOD_ALT)
int mbedtls_mpi_inv_mod_orig_shim( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *N )
#else
int mbedtls_mpi_inv_mod_shim( mbedtls_mpi *X, const mbedtls_mpi *A, const mbedtls_mpi *N )
#endif /* MBEDTLS_MPI_INV_MOD_ALT */
{
  int ret = 0;
  uint32_t len = 0;
  mbedtls_mpi G, V1, TA;
  uint8_t *pTA = &msg_ret_std[0];
  uint8_t *pTU = pTA + STD_PKHA_INT_MAX_BYTES;
  uint8_t *pU1 = pTU + STD_PKHA_INT_MAX_BYTES;
  uint8_t *pU2 = pU1 + STD_PKHA_INT_MAX_BYTES;
  uint8_t *pTB = pU2 + STD_PKHA_INT_MAX_BYTES;
  uint8_t *pTV = pTB + STD_PKHA_INT_MAX_BYTES;
  uint8_t *pV1 = pTV + STD_PKHA_INT_MAX_BYTES;
  uint8_t *pV2 = pV1 + STD_PKHA_INT_MAX_BYTES;
  uint8_t *pN = pV2 + STD_PKHA_INT_MAX_BYTES;
  uint32_t *pU132 = (uint32_t *)pU1;
  uint32_t *pU232 = (uint32_t *)pU2;
  uint32_t *pV232 = (uint32_t *)pV2;
  uint32_t *pV132 = (uint32_t *)pV1;
  uint32_t *pTU32 = (uint32_t *)pTU;
  uint32_t *pTV32 = (uint32_t *)pTV;

  if(mbedtls_mpi_cmp_int( N, 1 ) <= 0)
    return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

  memset(pTA, 0, STD_PKHA_INT_MAX_BYTES * 9);

  mbedtls_mpi_init( &TA ); 
  mbedtls_mpi_init( &G );
  mbedtls_mpi_init( &V1 );

  MBEDTLS_MPI_CHK( mbedtls_mpi_gcd( &G, A, N ) );

  if(mbedtls_mpi_cmp_int( &G, 1 ) != 0)
  {
    ret = MBEDTLS_ERR_MPI_NOT_ACCEPTABLE;
    goto cleanup;
  }

    
  MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &TA, A, N ) );

  if (TA.s < 0)
  {
    CASPER_ModSub1(pTA, TA.n, (uint8_t*)TA.p, TA.n, pTA);
  }
  else
  {
    memcpy(pTA, TA.p, TA.n << 2);
  }
  memcpy(pTU, pTA, TA.n << 2);
  
  if (N->s < 0)
  {
    CASPER_ModSub1(pTB, N->n, (uint8_t*)N->p, N->n, pTB);
  }
  else
  {
    memcpy(pTB, N->p, N->n << 2);
  }
  memcpy(pTV, pTB, N->n << 2);
  memcpy(pN, pTB, N->n << 2);
  ((uint32_t *)pU1)[0] = 1U;
  ((uint32_t *)pV2)[0] = 1U;

  len = TA.n > N->n ? TA.n : N->n;
  if (len % 8)
  {
    len = ((len >> 3) + 1) << 3;
  }
    
  len = len + 2; // Addition may overflow, so set aside some space

  do
  {     
    while( ( pTU32[0] & 1 ) == 0 )
    {
      mbedtls_mpi_shift_r1_shim( pTU32, len) ;

      if(((pU132[0] & 1 ) != 0) || ((pU232[0] & 1 ) != 0))
      {
        CASPER_ModAdd( pU1, len, pTB, len, pU1 ) ;
        CASPER_ModSub1( pU2, len, pTA, len, pU2 ) ;
      }

      mbedtls_mpi_shift_r1_shim( pU132, len) ;
      mbedtls_mpi_shift_r1_shim( pU232, len) ;
    }

    while( ( pTV32[0] & 1 ) == 0 )
    {
      mbedtls_mpi_shift_r1_shim( pTV32, len) ;

      if(((pV132[0] & 1U ) != 0) || ((pV232[0] & 1U ) != 0))
      {
        CASPER_ModAdd( pV1, len, pTB, len, pV1 ) ;
        CASPER_ModSub1( pV2, len, pTA, len, pV2) ;
      }

      mbedtls_mpi_shift_r1_shim( pV132, len) ;
      mbedtls_mpi_shift_r1_shim( pV232, len) ;
    }

    if(mbedtls_mpi_cmp_mpi_shim( pTU32, pTV32, len ) >= 0)
    {
      CASPER_ModSub1( pTU, len, pTV, len, pTU) ;
      CASPER_ModSub1( pU1, len, pV1, len, pU1 ) ;
      CASPER_ModSub1( pU2, len, pV2, len, pU2) ;
    }
    else
    {
      CASPER_ModSub1( pTV, len, pTU, len, pTV ) ;
      CASPER_ModSub1( pV1, len, pU1, len, pV1 ) ;
      CASPER_ModSub1( pV2, len, pU2, len, pV2) ;
    }
  }while(mbedtls_mpi_cmp_mpi_zero_shim( pTU32, len) != 0);

  while(mbedtls_mpi_cmp_mpi_zero_shim( pV132, len ) < 0)
  {
    CASPER_ModAdd( pV1, len, pN, len, pV1 ) ;
  }
    
  V1.s = 1;
  if ((pV1[len - 1] & 0x80000000) != 0)
  {
    V1.s = -1;
    memset(pTV, 0, len << 2);
    CASPER_ModSub1(pTV, len, pV1, len, pV1);
  }
    
    
  if (V1.n < len - 2)
  {
    MBEDTLS_MPI_CHK( mbedtls_mpi_grow( &V1, len - 2 -  V1.n) );
  }
    
  memcpy(V1.p, pV1, (len -2) << 2);
  V1.n = len - 2;
  while( mbedtls_mpi_cmp_mpi( &V1, N ) >= 0 )
  {
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &V1, &V1, N ) );
  }

  MBEDTLS_MPI_CHK( mbedtls_mpi_copy( X, &V1 ) );

cleanup:

  mbedtls_mpi_free( &TA );
  mbedtls_mpi_free( &G );
  mbedtls_mpi_free( &V1 );
    
  return( ret );
}


#if defined(MBEDTLS_RSA_PRIVATE_ALT)
#if defined(MBEDTLS_STD_CASPER_PKHA)

#include "board.h"
/*
 * Generate or update blinding values, see section 10 of:
 *  KOCHER, Paul C. Timing attacks on implementations of Diffie-Hellman, RSA,
 *  DSS, and other systems. In : Advances in Cryptology-CRYPTO'96. Springer
 *  Berlin Heidelberg, 1996. p. 104-113.
 */
static int rsa_prepare_blinding( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
  int ret = 0, count = 0;

  if( ctx->Vf.p != NULL )
  {
    /* We already have blinding values, just update them by squaring */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &ctx->Vi, &ctx->Vi, &ctx->Vi ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &ctx->Vi, &ctx->Vi, &ctx->N ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &ctx->Vf, &ctx->Vf, &ctx->Vf ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &ctx->Vf, &ctx->Vf, &ctx->N ) );

    goto cleanup;
  }

  /* Unblinding value: Vf = random number, invertible mod N */
  do {
    if( count++ > 10 )
      return( MBEDTLS_ERR_RSA_RNG_FAILED );

    MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &ctx->Vf, ctx->len - 1, f_rng, p_rng ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_gcd( &ctx->Vi, &ctx->Vf, &ctx->N ) );
  } while( mbedtls_mpi_cmp_int( &ctx->Vi, 1 ) != 0 );
    
    
  /* Blinding value: Vi =  Vf^(-e) mod N */
  MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod_shim( &ctx->Vi, &ctx->Vf, &ctx->N ) );
  MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod_shim(&ctx->Vi, &ctx->Vi, &ctx->E, &ctx->N , &ctx->RN ));

cleanup:
  return( ret );
}

/*
 * Exponent blinding supposed to prevent side-channel attacks using multiple
 * traces of measurements to recover the RSA key. The more collisions are there,
 * the more bits of the key can be recovered. See [3].
 *
 * Collecting n collisions with m bit long blinding value requires 2^(m-m/n)
 * observations on avarage.
 *
 * For example with 28 byte blinding to achieve 2 collisions the adversary has
 * to make 2^112 observations on avarage.
 *
 * (With the currently (as of 2017 April) known best algorithms breaking 2048
 * bit RSA requires approximately as much time as trying out 2^112 random keys.
 * Thus in this sense with 28 byte blinding the security is not reduced by
 * side-channel attacks like the one in [3])
 *
 * This countermeasure does not help if the key recovery is possible with a
 * single trace.
 */
#define RSA_EXPONENT_BLINDING 28

/*
 * Do an RSA private key operation
 */
int mbedtls_rsa_private( mbedtls_rsa_context *ctx,
                 int (*f_rng)(void *, unsigned char *, size_t),
                 void *p_rng,
                 const unsigned char *input,
                 unsigned char *output )
{
  int ret = 0;
  size_t olen = 0;

  /* Temporary holding the result */
  mbedtls_mpi T;

  /* Temporaries holding P-1, Q-1 and the
   * exponent blinding factor, respectively. */
  mbedtls_mpi P1, Q1, R;

#if !defined(MBEDTLS_RSA_NO_CRT)
  /* Temporaries holding the results mod p resp. mod q. */
  mbedtls_mpi TP, TQ;

  /* Temporaries holding the blinded exponents for
   * the mod p resp. mod q computation (if used). */
  mbedtls_mpi DP_blind, DQ_blind;

  /* Pointers to actual exponents to be used - either the unblinded
   * or the blinded ones, depending on the presence of a PRNG. */
  mbedtls_mpi *DP = &ctx->DP;
  mbedtls_mpi *DQ = &ctx->DQ;
#else
  /* Temporary holding the blinded exponent (if used). */
  mbedtls_mpi D_blind;

  /* Pointer to actual exponent to be used - either the unblinded
  * or the blinded one, depending on the presence of a PRNG. */
  mbedtls_mpi *D = &ctx->D;
#endif /* MBEDTLS_RSA_NO_CRT */

  /* Temporaries holding the initial input and the double
  * checked result; should be the same in the end. */
  mbedtls_mpi I, C;

#if defined(MBEDTLS_THREADING_C)
  if( ( ret = mbedtls_mutex_lock( &ctx->mutex ) ) != 0 )
    return( ret );
#endif

  /* MPI Initialization */
  mbedtls_mpi_init( &T );

  mbedtls_mpi_init( &P1 );
  mbedtls_mpi_init( &Q1 );
  mbedtls_mpi_init( &R );

  if( f_rng != NULL )
  {
#if defined(MBEDTLS_RSA_NO_CRT)
    mbedtls_mpi_init( &D_blind );
#else
    mbedtls_mpi_init( &DP_blind );
    mbedtls_mpi_init( &DQ_blind );
#endif
  }

#if !defined(MBEDTLS_RSA_NO_CRT)
  mbedtls_mpi_init( &TP ); mbedtls_mpi_init( &TQ );
#endif

  mbedtls_mpi_init( &I );
  mbedtls_mpi_init( &C );

  /* End of MPI initialization */

  MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( &T, input, ctx->len ) );
  if( mbedtls_mpi_cmp_mpi( &T, &ctx->N ) >= 0 )
  {
    ret = MBEDTLS_ERR_MPI_BAD_INPUT_DATA;
    goto cleanup;
  }

  MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &I, &T ) );

  if( f_rng != NULL )
  {
    /*
    * Blinding
    * T = T * Vi mod N
    */

    MBEDTLS_MPI_CHK( rsa_prepare_blinding( ctx, f_rng, p_rng ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T, &T, &ctx->Vi ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &T, &T, &ctx->N ) );

    /*
    * Exponent blinding
    */
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &P1, &ctx->P, 1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( &Q1, &ctx->Q, 1 ) );

#if defined(MBEDTLS_RSA_NO_CRT)
    /*
    * D_blind = ( P - 1 ) * ( Q - 1 ) * R + D
    */
    MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &R, RSA_EXPONENT_BLINDING, f_rng, p_rng ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &D_blind, &P1, &Q1 ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &D_blind, &D_blind, &R ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &D_blind, &D_blind, &ctx->D ) );

    D = &D_blind;
#else
    /*
    * DP_blind = ( P - 1 ) * R + DP
    */
    MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &R, RSA_EXPONENT_BLINDING, f_rng, p_rng ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &DP_blind, &P1, &R ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &DP_blind, &DP_blind, &ctx->DP ) );

    DP = &DP_blind;

    /*
    * DQ_blind = ( Q - 1 ) * R + DQ
    */
    MBEDTLS_MPI_CHK( mbedtls_mpi_fill_random( &R, RSA_EXPONENT_BLINDING, f_rng, p_rng ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &DQ_blind, &Q1, &R ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &DQ_blind, &DQ_blind, &ctx->DQ ) );

    DQ = &DQ_blind;
#endif /* MBEDTLS_RSA_NO_CRT */
  }

#if defined(MBEDTLS_RSA_NO_CRT)
  MBEDTLS_MPI_CHK( mbedtls_mpi_exp_mod_shim_pri( &T, &T, D, &ctx->N, &ctx->RN ) );
#else
  /*
  * Faster decryption using the CRT
  *
  * TP = input ^ dP mod P
  * TQ = input ^ dQ mod Q
  */ 
  MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod_shim( &TP, &T, DP, &ctx->P, &ctx->RP ));
  MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod_shim( &TQ, &T, DQ, &ctx->Q, &ctx->RQ ) );

  /*
  * T = (TP - TQ) * (Q^-1 mod P) mod P
  */
  MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &T, &TP, &TQ ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &TP, &T, &ctx->QP ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &T, &TP, &ctx->P ) );

  /*
  * T = TQ + T * Q
  */
  MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &TP, &T, &ctx->Q ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &T, &TQ, &TP ) );
#endif /* MBEDTLS_RSA_NO_CRT */

  if( f_rng != NULL )
  {
    /*
    * Unblind
    * T = T * Vf mod N
    */
    MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &T, &T, &ctx->Vf ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &T, &T, &ctx->N ) );
  }

  /* Verify the result to prevent glitching attacks. */
  MBEDTLS_MPI_CHK(mbedtls_mpi_exp_mod_shim( &C, &T, &ctx->E, &ctx->N, &ctx->RN ) );

  if( mbedtls_mpi_cmp_mpi( &C, &I ) != 0 )
  {
    ret = MBEDTLS_ERR_RSA_VERIFY_FAILED;
    goto cleanup;
  }

  olen = ctx->len;
  MBEDTLS_MPI_CHK( mbedtls_mpi_write_binary( &T, output, olen ) );

cleanup:
#if defined(MBEDTLS_THREADING_C)
  if( mbedtls_mutex_unlock( &ctx->mutex ) != 0 )
    return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

  mbedtls_mpi_free( &P1 );
  mbedtls_mpi_free( &Q1 );
  mbedtls_mpi_free( &R );

  if( f_rng != NULL )
  {
#if defined(MBEDTLS_RSA_NO_CRT)
    mbedtls_mpi_free( &D_blind );
#else
    mbedtls_mpi_free( &DP_blind );
    mbedtls_mpi_free( &DQ_blind );
#endif
  }

  mbedtls_mpi_free( &T );

#if !defined(MBEDTLS_RSA_NO_CRT)
  mbedtls_mpi_free( &TP ); mbedtls_mpi_free( &TQ );
#endif

  mbedtls_mpi_free( &C );
  mbedtls_mpi_free( &I );

  if( ret != 0 )
    return( MBEDTLS_ERR_RSA_PRIVATE_FAILED + ret );

  return( 0 );
}

#endif /* MBEDTLS_STD_CASPER_PKHA */
#endif /* MBEDTLS_RSA_PRIVATE_ALT */



int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
  status_t result = kStatus_Success;

  if (result == kStatus_Success)
  {
    *olen = len;
    return 0;
  }
  else
  {
    return result;
  }
}


/******************************************************************************/
/*************************** FreeRTOS ********************************************/
/******************************************************************************/
#if defined(USE_RTOS) && defined(FSL_RTOS_FREE_RTOS) && defined(MBEDTLS_STD_FREERTOS_CALLOC_ALT)
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"

/*---------HEAP_3 calloc --------------------------------------------------*/

void *pvPortCalloc(size_t num, size_t size)
{
  void *pvReturn;

  vTaskSuspendAll();
  {
    pvReturn = calloc(num, size);
    traceMALLOC(pvReturn, xWantedSize);
  }
  (void)xTaskResumeAll();

#if (configUSE_MALLOC_FAILED_HOOK == 1)
  {
    if (pvReturn == NULL)
    {
      extern void vApplicationMallocFailedHook(void);
      vApplicationMallocFailedHook();
    }
  }
#endif

  return pvReturn;
}
#endif /* USE_RTOS && defined(FSL_RTOS_FREE_RTOS) && defined(MBEDTLS_STD_FREERTOS_CALLOC_ALT) */
