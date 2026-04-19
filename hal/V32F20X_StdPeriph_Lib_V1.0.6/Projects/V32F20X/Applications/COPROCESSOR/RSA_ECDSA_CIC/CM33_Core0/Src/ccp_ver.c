/**
  ******************************************************************************
  * @file    ccp_ver.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 
 #include "ecdsa.h"
 #include "entropy.h"
 #include "ctr_drbg.h"
 #include "pk.h"
 #include "base64.h"
 #include <string.h>
 #include <stdlib.h>
 
#define mbedtls_printf     printf
 
#define CASPER_ECC_P256 1
#define Accel_SetABCD_Addr(ab, cd) CASPER_Wr32b(((uint32_t)ab & 0xFFFF) | ((uint32_t)cd << 16), CASPER_CP_CFG);
#define Accel_crypto_mul(ctrl)    CASPER_Wr32b((uint32_t)ctrl, CASPER_CP_CTRL);
#define Accel_done()                                       \
    {                                                      \
        register uint32_t status;                          \
        do                                                 \
        {                                                  \
            status = CASPER_Rd32b(CASPER_CP_STATUS);       \
        } while (0 == (status & CASPER_STATUS_DONE_MASK)); \
    }
#define Accel_CIC_mul(ctrl)      CASPER_Wr32b((uint32_t)ctrl, CASPER_CP_CIC_CFG);

/*******************************************************************************
 * Includes
 ******************************************************************************/

#if CASPER_ECC_P256
#include "test_ecmul256.h"
#include "test_ecdoublemul256.h"
#elif CASPER_ECC_P384
#include "test_ecmul384.h"
#include "test_ecdoublemul384.h"
#endif

#include <string.h>

#include "ccp_ver.h"
#include "lib_ccp.h"
#include "CIC_data.h"
#include "mbedtls/rsa.h"
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "test_ecmul256.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 
 
// /*! @brief Define to Adapter Mars+/Casper */
// /** Peripheral CASPER base pointer */

extern uint32_t CA_MK_OFF(const void *addr);

#define TEST_ASSERT(a)       \
    if (!(a))                \
    {                        \
        printf("error\r\n"); \
        do                   \
        {                    \
        } while (1);         \
    }




/*******************************************************************************
 * Variables
 ******************************************************************************/
#define RSA_PT  "AABBCC03020100FFFFFFFFFF" \
                "1122330A0B0CCCDDDDDDDDDD"


static const unsigned pubkey0[2048 / 32] = {
    0x232577d1, 0xa1c2d50d, 0x99706557, 0x46c818ab, 0xaa53916b, 0x63f5f64b, 0x93cd68f4, 0x1ed00fb7,
    0xea292749, 0x39de13c1, 0x065b5911, 0x884b13c9, 0xe6f6c061, 0xef47223e, 0x92e9e488, 0x3931a79d,
    0x14861755, 0xde93cc46, 0x1e74bf9a, 0xb4a3d058, 0x2b63c4b1, 0xd37d1bf7, 0x3fd70745, 0x5095a782,
    0xec4bcd7b, 0xbef831fb, 0x7f682470, 0x56a9a012, 0x6136775a, 0x2777c47d, 0x89b3f94a, 0x62fa6f9f,
    0xc97a18ab, 0x55d68409, 0x39007ccb, 0xe3514d48, 0xe817cc0e, 0xafd713ba, 0x14a82e21, 0xe5ff1433,
    0x385a8131, 0x31f2ece8, 0x8d395a2a, 0x85622d91, 0x67634847, 0xb219d21d, 0x1ef8efaa, 0xfaa05682,
    0x109b9a8a, 0x41042b7e, 0x0ebe7f64, 0xdae23bff, 0x5cfd544b, 0x74b9cbf2, 0x9563cafb, 0x462b3911,
    0x16e9cdf4, 0x68ed6d7f, 0xc6e45a20, 0x65838412, 0xa261fc8b, 0xbdd913f2, 0xc1782e4d, 0xbad47a84,
};
static const unsigned plaintext0[2048 / 32] = {
    0x4b4fb4bc, 0x9da3c722, 0x1fa87ba2, 0xf312d3f1, 0xb3823c63, 0x0917140a, 0xa07c69d7, 0xc2c92b88,
    0x7e732102, 0xd3420e56, 0x7c089aa2, 0x518dc5f5, 0xdeb09cc4, 0x9d429cf9, 0x2deca5b4, 0x430bb1a7,
    0xe8fd387c, 0x083ec701, 0x518db8a2, 0x407db831, 0x5b2bf516, 0x570eb451, 0xc4f202a9, 0x77f504da,
    0x5b73edac, 0x61e5667e, 0xf131bd94, 0xf2d3ce56, 0x09c828d6, 0x57ce7f8f, 0xcfba290b, 0xf53c3d7f,
    0x16bd7ae8, 0x6e8ad8fd, 0x7995a8ba, 0x5d2102ef, 0x982a4658, 0x2d362945, 0x2428b8d3, 0xb6c2f765,
    0x608adb30, 0xfe6be10e, 0xdfcd8056, 0x37bbc360, 0x5d00f1a4, 0xbde4493f, 0x9fb4eab5, 0x80a14649,
    0x7a56082c, 0x1caf81b2, 0x21bb7186, 0x53576457, 0xf58300d2, 0xfbfb82b0, 0xf303a568, 0xeb7f0d4d,
    0x2c4b0b4e, 0xaf50cac4, 0x6f9d7808, 0x3f120e32, 0x9fa1cd64, 0x2a94b3ab, 0x95a4908d, 0x70992c9d,
};
static const unsigned signature0[2048 / 32] = {
    0x892b6f74, 0x85c033f9, 0x33ab8b20, 0x74007e6a, 0xf1687e00, 0x96960052, 0x875dbc47, 0xe2d51612,
    0x804bf80e, 0x0bcc5205, 0x5b630d07, 0x741553a4, 0xe77737da, 0xffdd47b3, 0xcad941db, 0xda40f72e,
    0x2a42eb3b, 0xdfd88bb2, 0xadd387fe, 0xaf641538, 0x72ce8a31, 0x965b713d, 0x35e78b46, 0xfee41c44,
    0x7ef74f17, 0x496ddbc7, 0xd9f09955, 0x26eda243, 0x210b25e9, 0x6e032a66, 0x430800e1, 0xabbe7f89,
    0xd339cc87, 0x81cac45c, 0x06e9e6ec, 0x32d5be61, 0x0632d363, 0x5404adb0, 0xa2dad9fa, 0x62dbc7a9,
    0xc299bd0e, 0xcc9ff240, 0x71d5c214, 0x3131e9b3, 0x6a8a974a, 0xc49551d8, 0xe457c1da, 0x45d99126,
    0x451c6b46, 0x51b753f7, 0x1ec0663e, 0x69d2429f, 0x404788b8, 0x8a28dd70, 0xc86f9d1b, 0xcb6bad9a,
    0xd84d8836, 0x37cff304, 0xf4c3ae42, 0x3dce66d0, 0x3fbf9896, 0x028c75dc, 0xa05f626b, 0x7e65b998,
};
static const unsigned pub_e = 0x10001;

static uint8_t plaintext[2048 / 8] = {0};

__IO unsigned gAB[4096 / 32] __attribute__((section(CASPER_STR_ADDR)));
__IO unsigned gCD[64 * 256 / 32] __attribute__((section(CASPER_STR_ADDR)));
__IO unsigned gResult[(64 * 256 / 32) + 2] __attribute__((section(CASPER_STR_ADDR)));


uint8_t testBase64Buff[512] = {0};
uint8_t rsaKeyBuff[1800] = {0};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/


//SOFTWARE RNG FUNCTION
static int myrand( void *rng_state, unsigned char *output, size_t len )
{
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
  size_t i = 0;

  if( rng_state != NULL )
      rng_state  = NULL;

  for( i = 0; i < len; ++i )
    //output[i] = 0xa5;
    output[i] = rand();
#else
  if( rng_state != NULL )
      rng_state = NULL;

  arc4random_buf( output, len );
#endif /* !OpenBSD && !NetBSD */

  return( 0 );
}


static void dump_buf( const char *title, unsigned char *buf, size_t len )
{
    size_t i = 0;

    mbedtls_printf( "%s", title );
    for( i = 0; i < len; i++ )
        mbedtls_printf("%c%c", "0123456789ABCDEF" [buf[i] / 16],
                       "0123456789ABCDEF" [buf[i] % 16] );
    mbedtls_printf( "\n" );
}

static void dump_pubkey( const char *title, mbedtls_ecdsa_context *key )
{
    unsigned char buf[300] = {0};
    size_t len = 0;

    if( mbedtls_ecp_point_write_binary( &key->grp, &key->Q,
                MBEDTLS_ECP_PF_UNCOMPRESSED, &len, buf, sizeof buf ) != 0 )
    {
        mbedtls_printf("internal error\n");
        return;
    }

    dump_buf( title, buf, len );
}



unsigned int CCP_Init_Ver(void)
{
  uint32_t err = 0;

  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_CRYPTCOP, ENABLE);
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_CRYPTCOP);
  CASPER_Init(CASPER_START_ADDR);
  
  return 0;
}

void CCP_OpMul6464NoSum_Ver(void)
{
  uint32_t tmp = 0;
  int32_t i = 0;
  uint32_t ab[64/32] = {0x11111111, 0x22222222};
  uint32_t cd[64/32] = {0x33333333, 0x44444444};
  uint32_t Result[128/32] = {0};


  printf("\r\n\r\n************* kCASPER_OpMul6464NoSum ****************\r\n");
  printf("----1. Real Value----\r\n");
  printf("ba value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",ab[1],ab[0] , (ab+1),ab);
  printf("dc value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",cd[1],cd[0] , (cd+1),cd);
  printf("Res address:0x%p\r\n", &Result);
  Result[0] = 0x1;
  printf("Result:0x%08X %08X %08X %08X\r\n",Result[3],Result[2],Result[1],Result[0]);
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  
  printf("\r\n");

  printf("---- 2. Final WRITE in ---- \r\n");
  CASPER_Wr32b(((uint32_t)ab&0xFFFF0000) ,CASPER_CP_SRAMBADDR);
  printf("SRAMBADDR:0x%X\r\n",CASPER_Rd32b(CASPER_CP_SRAMBADDR));
  Accel_SetABCD_Addr(CA_MK_OFF(ab), CA_MK_OFF(cd));
  printf("CFG:0x%X\r\n",CASPER_Rd32b(CASPER_CP_CFG));
  //set result

  tmp = Accel_IterOpcodeResaddr(0, (uint32_t)kCASPER_OpMul6464NoSum, CA_MK_OFF(Result));
  Accel_crypto_mul(tmp);
  printf("\r\nCTRL:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_CTRL));

  printf("\r\n---- 3. RESULT ---- \r\n");
  Accel_done();
  printf("STATUS:0x%X\r\n",CASPER_Rd32b(CASPER_CP_STATUS));
  printf("Result :");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%08X ",Result[i]);
  }
  printf("\r\n");
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

    // Multi Big Number via software
}

void CCP_OpMul6464Sum_Ver(void)
{
  uint32_t tmp = 0;
  int32_t i = 0;
  uint32_t ab[64/32] = {0x11111111, 0x22222222};
  uint32_t cd[64/32] = {0x33333333, 0x44444444};
  uint32_t Result[128/32] = {0};

  printf("\r\n\r\nk************* CASPER_OpMul6464Sum ****************\r\n");
  printf("----1. Real Value----\r\n");
  printf("ba value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",ab[1],ab[0] , (ab+1),ab);
  printf("dc value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",cd[1],cd[0] , (cd+1),cd);
  printf("Res address:0x%p\r\n", &Result);
  Result[0] = 0x1;
  printf("Result:0x%08X %08X %08X %08X\r\n",Result[3],Result[2],Result[1],Result[0]);
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  printf("---- 2. Final WRITE in ---- \r\n");
  CASPER_Wr32b(((uint32_t)ab&0xFFFF0000) ,CASPER_CP_SRAMBADDR);
  printf("SRAMBADDR:0x%X\r\n",CASPER_Rd32b(CASPER_CP_SRAMBADDR));
  Accel_SetABCD_Addr(CA_MK_OFF(ab), CA_MK_OFF(cd));
  printf("CFG:0x%X\r\n",CASPER_Rd32b(CASPER_CP_CFG));
  //set result
  tmp = Accel_IterOpcodeResaddr(0, (uint32_t)kCASPER_OpMul6464Sum, CA_MK_OFF(Result));
  Accel_crypto_mul(tmp);
  printf("\r\nCTRL:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_CTRL));

  printf("\r\n---- 3. RESULT ---- \r\n");
  Accel_done();
  printf("STATUS:0x%X\r\n",CASPER_Rd32b(CASPER_CP_STATUS));
  printf("Result :");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%08X ",Result[i]);
  }
  printf("\r\n");
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

    // Multi Big Number via software
}

//Easy Mult Ver function
//NoSum will not add result highest 64bits in last one cycle
void CCP_OpMul6464FullSum_Ver(void)
{
  uint32_t tmp = 0;
  int32_t i = 0;
  uint32_t ab[64/32] = {0x11111111, 0x22222222};
  uint32_t cd[64/32] = {0x33333333, 0x44444444};
  uint32_t Result[128/32] = {0};

  printf("\r\n\r\nk************* CASPER_OpMul6464FullSum ****************\r\n");
  printf("----1. Real Value----\r\n");
  printf("ba value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",ab[1],ab[0] , (ab+1),ab);
  printf("dc value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",cd[1],cd[0] , (cd+1),cd);
  printf("Res address:0x%p\r\n", &Result);
  Result[0] = 0x1;
  printf("Result:0x%08X %08X %08X %08X\r\n",Result[3],Result[2],Result[1],Result[0]);
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  printf("---- 2. Final WRITE in ---- \r\n");
  CASPER_Wr32b(((uint32_t)ab&0xFFFF0000) ,CASPER_CP_SRAMBADDR);
  printf("SRAMBADDR:0x%X\r\n",CASPER_Rd32b(CASPER_CP_SRAMBADDR));
  Accel_SetABCD_Addr(CA_MK_OFF(ab), CA_MK_OFF(cd));
  printf("CFG:0x%X\r\n",CASPER_Rd32b(CASPER_CP_CFG));
  //set result
  tmp = Accel_IterOpcodeResaddr(0, (uint32_t)kCASPER_OpMul6464FullSum, CA_MK_OFF(Result));
  Accel_crypto_mul(tmp);
  printf("\r\nCTRL:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_CTRL));

  printf("\r\n---- 3. RESULT ---- \r\n");
  Accel_done();
  printf("STATUS:0x%X\r\n",CASPER_Rd32b(CASPER_CP_STATUS));
  printf("Result :");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%08X ",Result[i]);
  }
  printf("\r\n");
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  // Multi Big Number via software
}

void CCP_OpAdd64_Ver(void)
{
  uint32_t tmp = 0;
  int32_t i = 0;
  uint32_t ab[64/32] = {0x11111111, 0x22222222};
  uint32_t cd[64/32] = {0x33333333, 0x44444444};
  uint32_t Result[128/32] = {0};


  printf("\r\n\r\n************* kCASPER_OpAdd64 ****************\r\n");
  printf("----1. Real Value----\r\n");
  printf("ba value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",ab[1],ab[0] , (ab+1),ab);
  printf("dc value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",cd[1],cd[0] , (cd+1),cd);
  printf("Res address:0x%p\r\n", &Result);
  Result[0] = 0x1;
  printf("Result:0x%08X %08X %08X %08X\r\n",Result[3],Result[2],Result[1],Result[0]);
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  printf("---- 2. Final WRITE in ---- \r\n");
  CASPER_Wr32b(((uint32_t)ab&0xFFFF0000) ,CASPER_CP_SRAMBADDR);
  printf("SRAMBADDR:0x%X\r\n",CASPER_Rd32b(CASPER_CP_SRAMBADDR));
  Accel_SetABCD_Addr(CA_MK_OFF(ab), CA_MK_OFF(cd));
  printf("CFG:0x%X\r\n",CASPER_Rd32b(CASPER_CP_CFG));
  //set result
  tmp = Accel_IterOpcodeResaddr(0, (uint32_t)kCASPER_OpAdd64, CA_MK_OFF(Result));
  Accel_crypto_mul(tmp);
  printf("\r\nCTRL:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_CTRL));

  printf("\r\n---- 3. RESULT ---- \r\n");
  Accel_done();
  printf("STATUS:0x%X\r\n",CASPER_Rd32b(CASPER_CP_STATUS));
  printf("Result :");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%08X ",Result[i]);
  }
  printf("\r\n");
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  // Multi Big Number via software
}

void CCP_OpSub64_Ver(void)
{
  uint32_t tmp = 0;
  int32_t i = 0;
  uint32_t ab[64/32] = {0x11111111, 0x22222222};
  uint32_t cd[64/32] = {0x33333333, 0x44444444};
  uint32_t Result[128/32] ={0x33333333, 0x44444444};


  printf("\r\n\r\n************* kCASPER_OpSub64 ****************\r\n");
  printf("----1. Real Value----\r\n");
  printf("ba value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",ab[1],ab[0] , (ab+1),ab);
  printf("dc value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",cd[1],cd[0] , (cd+1),cd);
  printf("Res address:0x%p\r\n", &Result);
  //Result[0] = 0x1;
  printf("Result:0x%08X %08X %08X %08X\r\n",Result[3],Result[2],Result[1],Result[0]);
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  printf("---- 2. Final WRITE in ---- \r\n");
  CASPER_Wr32b(((uint32_t)ab&0xFFFF0000) ,CASPER_CP_SRAMBADDR);
  printf("SRAMBADDR:0x%X\r\n",CASPER_Rd32b(CASPER_CP_SRAMBADDR));
  Accel_SetABCD_Addr(CA_MK_OFF(ab), CA_MK_OFF(cd));
  printf("CFG:0x%X\r\n",CASPER_Rd32b(CASPER_CP_CFG));
  //set result
  tmp = Accel_IterOpcodeResaddr(0, (uint32_t)kCASPER_OpSub64, CA_MK_OFF(Result));
  Accel_crypto_mul(tmp);
  printf("\r\nCTRL:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_CTRL));

  printf("\r\n---- 3. RESULT ---- \r\n");
  Accel_done();
  printf("STATUS:0x%X\r\n",CASPER_Rd32b(CASPER_CP_STATUS));
  printf("Result :");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%08X ",Result[i]);
  }
  printf("\r\n");
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  // Multi Big Number via software
}

void CCP_OpCopy_Ver(void)
{
  uint32_t tmp = 0;
  int32_t i = 0;
  uint32_t ab[64/32] = {0x11111111, 0x22222222};
  uint32_t cd[64/32] = {0x33333333, 0x44444444};
  uint32_t Result[128/32] ={0};

  printf("\r\n\r\n************* kCASPER_OpCopy ****************\r\n");
  printf("----1. Real Value----\r\n");
  printf("ba value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",ab[1],ab[0] , (ab+1),ab);
  printf("dc value: 0x%08X %08X \r\naddress : 0x%p %p\r\n",cd[1],cd[0] , (cd+1),cd);
  printf("Res address:0x%p\r\n", &Result);
  Result[0] = 0x1;
  printf("Result:0x%08X %08X %08X %08X\r\n",Result[3],Result[2],Result[1],Result[0]);
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  printf("---- 2. Final WRITE in ---- \r\n");
  CASPER_Wr32b(((uint32_t)ab&0xFFFF0000) ,CASPER_CP_SRAMBADDR);
  printf("SRAMBADDR:0x%X\r\n",CASPER_Rd32b(CASPER_CP_SRAMBADDR));
  Accel_SetABCD_Addr(CA_MK_OFF(ab), CA_MK_OFF(cd));
  printf("CFG:0x%X\r\n",CASPER_Rd32b(CASPER_CP_CFG));
  //set result
  tmp = Accel_IterOpcodeResaddr(0, (uint32_t)kCASPER_OpCopy, CA_MK_OFF(Result));
  Accel_crypto_mul(tmp);
  printf("\r\nCTRL:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_CTRL));

  printf("\r\n---- 3. RESULT ---- \r\n");
  Accel_done();
  printf("STATUS:0x%X\r\n",CASPER_Rd32b(CASPER_CP_STATUS));
  printf("Result :");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%08X ",Result[i]);
  }
  printf("\r\n");
  printf("Address:");
  for (i= 3 ; i >= 0 ; i--)
  {
    printf("%p ",(Result+i));
  }
  printf("\r\n");

  // Multi Big Number via software
}


//Easy Mult Ver function
void CCP_Mul6464NoSumBigNum_Ver(void)
{
  uint32_t tmp = 0;
  int32_t i = 0;
  int32_t mA = 0,mC = 0,mResult = 0;
  unsigned signature0[128 / 32] = {0x11111111, 0x11111111, 0x11111111, 0x11111111};
  unsigned plaintext0[128 / 32] = {0x33333333, 0x44444444, 0x33333333, 0x44444444};

  mA = sizeof(signature0)/sizeof(signature0[0]);//how long of array a
  mC = sizeof(plaintext0)/sizeof(plaintext0[0]);
  mResult = mA+mC;
  uint32_t* plaintext = (uint32_t*)malloc(mResult * sizeof(uint32_t));


  printf("----1. Real Value----\r\n");
  printf("\r\nab Value: 0x");
  for (i = (mA-1) ;i >= 0; i--)
  {
    printf("%08X ",signature0[i]);
  }
  printf("\r\nAddress : 0x");
  for (i = (mA-1) ;i >= 0; i--)
  {
    printf("%p ",signature0+i);
  }
  printf("\r\ncd Value: 0x");
  for (i = (mC-1) ;i >= 0; i--)
  {
    printf("%08X ",plaintext0[i]);
  }
  printf("\r\nAddress : 0x");
  for (i = (mC-1) ;i >= 0; i--)
  {
    printf("%p ",plaintext0+i);
  }
  printf("\r\nresValue: 0x");
  for (i = (mResult-1) ;i >= 0; i--)
  {
    printf("%08X ",plaintext[i]);
  }
  printf("\r\nRes Addr : 0x");
  for (i = (mResult-1) ;i >= 0; i--)
  {
    printf("%p ",plaintext+i);
  }

  printf("\r\n---- 3. Final WRITE in ---- \r\n");

  Accel_SetABCD_Addr(CA_MK_OFF(signature0),0);//for sub, cd can be 0
  printf("CFG:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_CFG));
  CASPER_Wr32b(0x20000000 ,CASPER_CP_SRAMBADDR);
  printf("SRAMBADDR:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_SRAMBADDR));
  //set result
  printf("Mode: kCASPER_OpSub64\r\n");
  tmp = Accel_IterOpcodeResaddr(1 , (uint32_t)kCASPER_OpSub64, CA_MK_OFF(plaintext));
  Accel_crypto_mul(tmp);
  printf("CTRL:0x%08X\r\n",CASPER_Rd32b(CASPER_CP_CTRL));

  printf("\r\n---- 4. RESULT ---- \r\n");
  Accel_done();
  printf("STATUS:0x%X\r\n",CASPER_Rd32b(CASPER_CP_STATUS));
  printf("\r\nresValue: 0x");
  for (i = (mResult-1) ;i >= 0; i--)
  {
    printf("%08X ",plaintext[i]);
  }
  printf("\r\nRes Addr : 0x");
  for (i = (mResult-1) ;i >= 0; i--)
  {
    printf("%p ",plaintext+i);
  }
  printf("\r\n");
  //	free(plaintext);
  //	*plaintext = NULL;
}


/* CIC verify function
 * Easy,ugly,simply function
 * need struct optimazed
 */
unsigned int CCP_CIC_Ver(void)
{
  CIC_InitType  CIC_InitStruct = {0};
  uint32_t ResultLength = 0;
  uint32_t BaseAddress  = 0;
  uint32_t* ResAddress  = (uint32_t *)gResult;
  uint32_t *msg_ret     = NULL;
  uint32_t i = 0;
  uint64_t* retAdd = NULL;
  uint32_t* retAdd1 = NULL;
  uint32_t* DT_LOC = NULL;
  uint32_t* DT_LOC1 = NULL;
  uint32_t* TMP_LOC = NULL;
  uint32_t* TMP_LOC1 = NULL;
  
  
  msg_ret = ResAddress;//(uint32_t*)CASPER_START_ADDR;

  //struct Init and Write CIC CFG
  CIC_InitStruct.ChannelNum       = 0;
  CIC_InitStruct.ResultLenth      = 1023;
  CIC_InitStruct.IntegrateType    = CIC_Integrate_1bit;
  CIC_InitStruct.DecimationOffset = 0;
  CIC_InitStruct.DecimationRate   = 7; 
  CIC_InitStruct.Order            = CIC_Order_3;   
  Accel_CIC_mul(Accel_CIC_Config(&CIC_InitStruct));

  memset(ResAddress,0x00,64*1024);

  //Ready Data
  DT_LOC = &msg_ret[1024+3096];
  DT_LOC1 = &msg_ret[6144+3096];

  TMP_LOC = &msg_ret[256+3096];
  TMP_LOC1 = &msg_ret[512+3096];

  memcpy(DT_LOC, (const uint32_t *)(uintptr_t)(CIC_Data), 4096*4);//1024*5*4);
  //input data :CDoff;  temp data :ABoff
  Accel_SetABCD_Addr(CA_MK_OFF((void *)TMP_LOC), CA_MK_OFF((void *)DT_LOC));

  //cic integral
  Accel_crypto_mul(Accel_IterOpcodeResaddr(0,(uint32_t)kCASPER_CIC_Integrate,CA_MK_OFF(ResAddress)));
  Accel_done();

  retAdd = (uint64_t*)ResAddress;


  // cic differential 
  Accel_SetABCD_Addr(CA_MK_OFF((void *)TMP_LOC1), CA_MK_OFF((void *)ResAddress));
  Accel_crypto_mul(Accel_IterOpcodeResaddr(0,(uint32_t)kCASPER_CIC_Comb,CA_MK_OFF(DT_LOC1)));
  Accel_done();


  retAdd = (uint64_t*)DT_LOC1;
  retAdd1 = DT_LOC1;
  for (i = 0; i < 1023; i++)
  {
    retAdd1[i] = (uint32_t)(retAdd[i] & 0x00000000FFFFFFFF);
    printf("%d,\r\n",retAdd1[i]);
  }

  return 0;
}


int mbedtls_RSA2048_SHA256_encrypt_SelfTest(void)
{
//#define KEY_LEN 128 //RSA1024
#define KEY_LEN 256
#define PT_LEN  24
  unsigned char rsa_plaintext[PT_LEN+1] = {0};
  unsigned char rsa_ciphertext[KEY_LEN] = {0};
  int ret = 0;
  uint32_t time = 0;
  uint32_t i = 0;
  uint32_t use_len = 0;
  mbedtls_rsa_context* rsa = NULL;
  mbedtls_mpi K = {0};
  mbedtls_pk_context rsaKey = {0};
  mbedtls_pk_info_t *pk_info = NULL;

  

#define RSA_N     "BE94F2B614C734CE5CC3AE638B594CFA" \
                  "888EBBDE6ECE5717C90A9D7210F27BE8" \
                  "7B3B1533FAE838238E3CC1704A686F8A" \
                  "0BE431CB70EDD80895E09D4B64F67331" \
                  "8D35A644F610ED6B670C336E5AB905FD" \
                  "0862A3E116547B2F78AAFD90664244EB" \
                  "65A5B5930497920AE229AFCE6EDD706D" \
                  "5BDB2912AA05C85C3CF9CDA117C41ECE" \
                  "EA6ED50524F7231131735431B3B746A2" \
                  "E91E557CAA9487BBC26A9A958860C55E" \
                  "36750887820B8BA48C81A56A72AE555D" \
                  "BC5CBD72AB7A4F6457DFEB3CF2E0296C" \
                  "A84E33B91DE3C540093048CDD87863FB" \
                  "F6E87A8B72E785FB13DA3C3D467A94D6" \
                  "3A89717994F99877EC457565591FA197" \
                  "31355EE9FAA4AFDA4F72CEA4B5C3545B"

#define RSA_E   "10001"
  
#define RSA_D "0CCA7561B812489E83065519743C4998" \
              "D4FA736C71D6626D03BEB5237734B711" \
              "3AD813CBB9CEC519C9CD951402C2709D" \
              "FCBF53823A71941ABB6868562B9008DA" \
              "2E068842BF9B123C2F9DD783D40DEFF3" \
              "74111EBB98229263F4BED126D45E253F" \
              "0142F665481D1E1DA1E1375DECFDEAB2" \
              "444478C4BA6989F17ADC2F2B5D2B79FF" \
              "BE77CA67CAA4AF1FC1EEF855E4E64B36" \
              "9567BF9F2CA737E0EC0B026207988E7C" \
              "6E37B4B44CB36DA19735D13ADE4DBD49" \
              "2D2E04882F508EDBB4D2EFCCF05C9060" \
              "3F37237E9A1CC9EDDCA6F06AA974D579" \
              "DB1A0E4E97BE1428E6DACDE9262E2323" \
              "2BA79442F152737D45A8DD37397BAD1A" \
              "CEA22653EF93748D24CED72AC2E7A019"

#define RSA_P "E8029ED93123D539EF99559A386AEAD7" \
              "185825D1E1262577C9879C08665242A4" \
              "250C16365EC6A4ED6E67D05793EAE8B7" \
              "44F039C0DD6682761354E498B5683868" \
              "F35075543BE23C980732FBA8F995B2EC" \
              "97944DE4C6FA72B2CA28578BBB0D4632" \
              "DA135BF2E3FCD58C8DC9527B6159E08D" \
              "B95B67332C52953D65127AF7A3FBB6B3"

#define RSA_Q "D249B494B66C900500197A130F260E29" \
              "8ADAC9BB3DED94EC0145902B69E6CFF6" \
              "0FE38617341AF2965BF9813931AA5594" \
              "04C15C316457036BD3C4DF0372D6DAC3" \
              "6AFE934F93262B59A9E23BCB46CE08B3" \
              "615013962B2519A0A31C188DCDB3B673" \
              "B8C48B7874C8AE909FC0092F03370265" \
              "FEB50A7AA8FD9DE8FE483B9A8EA0FFB9"
  
  printf("rsa encrypt test start\r\n");
  mbedtls_pk_init(&rsaKey);
  if( ( pk_info = (mbedtls_pk_info_t *)mbedtls_pk_info_from_type( MBEDTLS_PK_RSA ) ) == NULL )
    return( MBEDTLS_ERR_PK_UNKNOWN_PK_ALG );
  if( ( ret = mbedtls_pk_setup( &rsaKey, pk_info ) ) != 0 )
    return( ret );
  rsa = rsaKey.pk_ctx;
    /* Ready data */
  
  //key
#if defined(MBEDTLS_PKCS1_V15)
  mbedtls_rsa_init( rsa, MBEDTLS_RSA_PKCS_V15, 0 );
#endif
  
#if defined(MBEDTLS_PKCS1_V21)
  mbedtls_rsa_init( rsa, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA256 );
#endif
  mbedtls_mpi_init( &K );
  //import value
  //pubkey part
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_N  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( rsa, &K, NULL, NULL, NULL, NULL ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_E  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( rsa, NULL, NULL, NULL, NULL, &K ) );
  //privatekey part
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_Q  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( rsa, NULL, NULL, &K, NULL, NULL ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_D  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( rsa, NULL, NULL, NULL, &K, NULL ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_P  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( rsa, NULL, &K, NULL, NULL, NULL ) );
  //check fully
  MBEDTLS_MPI_CHK( mbedtls_rsa_complete( rsa ) );
  if( mbedtls_rsa_check_pubkey(  rsa ) != 0 ||
      mbedtls_rsa_check_privkey( rsa ) != 0 )
  {
    ret = 1;
    goto cleanup;
  }

    

  if( mbedtls_rsa_check_pubkey(  rsa ) != 0 ||
  mbedtls_rsa_check_privkey( rsa ) != 0 )
  {
    ret = 1;
    goto cleanup;
  } 

  memset( rsa_plaintext, 0, PT_LEN+1);
  memcpy( rsa_plaintext, RSA_PT, PT_LEN);

  if( mbedtls_rsa_pkcs1_encrypt( rsa, myrand, NULL, MBEDTLS_RSA_PUBLIC,
                   PT_LEN, rsa_plaintext,
                   rsa_ciphertext ) != 0 )
  {
    ret = 1;
    goto cleanup;
  }

  mbedtls_pk_write_key_pem(&rsaKey, rsaKeyBuff, 1800);
  
  ret = mbedtls_base64_encode( testBase64Buff, 512, &use_len, rsa_ciphertext, rsa->len );

  printf("\r\n");
  printf("key:\r\n");
  printf("%s", rsaKeyBuff);
  printf("\r\n");

  printf("\r\n");
  printf("plain data len:");

  printf("%d\r\n",PT_LEN);

  printf("plain data:\r\n");
  printf("\r\nplain text: %s\r\n",rsa_plaintext);


  printf("\r\n");
  printf("cipher data base64:\r\n");
  printf("%s\r\n",testBase64Buff);
    

  memset( rsa_plaintext, 0, PT_LEN+1);
  if( mbedtls_rsa_pkcs1_decrypt( rsa, myrand, NULL,
                                MBEDTLS_RSA_PRIVATE, &use_len, rsa_ciphertext,
                                rsa_plaintext,24) != 0 )
  {
    ret = 1;
    goto cleanup;
  }
  
  printf("\r\nplain text: %s\r\n",rsa_plaintext);
  for(i = 0; i < PT_LEN; i++)
  {
    if (rsa_plaintext[i] != RSA_PT[i])
    {
      ret = 1;
    }
  }

cleanup:
  mbedtls_mpi_free( &K );
  mbedtls_rsa_free( rsa );
  mbedtls_pk_free( &rsaKey );
  return( ret );
}


/* RSA Self Ver */
int mbedtls_RSA2048_SHA256_Verify_SelfTest(void)
{
//#define KEY_LEN 128 //RSA1024
#define KEY_LEN 256
#define PT_LEN  24

  mbedtls_rsa_context rsa = {0};
  mbedtls_mpi K = {0};
  unsigned char rsa_plaintext[PT_LEN] = {0};
  unsigned char rsa_ciphertext[KEY_LEN] = {0};
  unsigned char sha256sum[32] = {0};
  int ret = 0;

#define RSA_N     "BE94F2B614C734CE5CC3AE638B594CFA" \
                  "888EBBDE6ECE5717C90A9D7210F27BE8" \
                  "7B3B1533FAE838238E3CC1704A686F8A" \
                  "0BE431CB70EDD80895E09D4B64F67331" \
                  "8D35A644F610ED6B670C336E5AB905FD" \
                  "0862A3E116547B2F78AAFD90664244EB" \
                  "65A5B5930497920AE229AFCE6EDD706D" \
                  "5BDB2912AA05C85C3CF9CDA117C41ECE" \
                  "EA6ED50524F7231131735431B3B746A2" \
                  "E91E557CAA9487BBC26A9A958860C55E" \
                  "36750887820B8BA48C81A56A72AE555D" \
                  "BC5CBD72AB7A4F6457DFEB3CF2E0296C" \
                  "A84E33B91DE3C540093048CDD87863FB" \
                  "F6E87A8B72E785FB13DA3C3D467A94D6" \
                  "3A89717994F99877EC457565591FA197" \
                  "31355EE9FAA4AFDA4F72CEA4B5C3545B"

#define RSA_E   "10001"
  
#define RSA_D "0CCA7561B812489E83065519743C4998" \
              "D4FA736C71D6626D03BEB5237734B711" \
              "3AD813CBB9CEC519C9CD951402C2709D" \
              "FCBF53823A71941ABB6868562B9008DA" \
              "2E068842BF9B123C2F9DD783D40DEFF3" \
              "74111EBB98229263F4BED126D45E253F" \
              "0142F665481D1E1DA1E1375DECFDEAB2" \
              "444478C4BA6989F17ADC2F2B5D2B79FF" \
              "BE77CA67CAA4AF1FC1EEF855E4E64B36" \
              "9567BF9F2CA737E0EC0B026207988E7C" \
              "6E37B4B44CB36DA19735D13ADE4DBD49" \
              "2D2E04882F508EDBB4D2EFCCF05C9060" \
              "3F37237E9A1CC9EDDCA6F06AA974D579" \
              "DB1A0E4E97BE1428E6DACDE9262E2323" \
              "2BA79442F152737D45A8DD37397BAD1A" \
              "CEA22653EF93748D24CED72AC2E7A019"

#define RSA_P "E8029ED93123D539EF99559A386AEAD7" \
              "185825D1E1262577C9879C08665242A4" \
              "250C16365EC6A4ED6E67D05793EAE8B7" \
              "44F039C0DD6682761354E498B5683868" \
              "F35075543BE23C980732FBA8F995B2EC" \
              "97944DE4C6FA72B2CA28578BBB0D4632" \
              "DA135BF2E3FCD58C8DC9527B6159E08D" \
              "B95B67332C52953D65127AF7A3FBB6B3"

#define RSA_Q "D249B494B66C900500197A130F260E29" \
              "8ADAC9BB3DED94EC0145902B69E6CFF6" \
              "0FE38617341AF2965BF9813931AA5594" \
              "04C15C316457036BD3C4DF0372D6DAC3" \
              "6AFE934F93262B59A9E23BCB46CE08B3" \
              "615013962B2519A0A31C188DCDB3B673" \
              "B8C48B7874C8AE909FC0092F03370265" \
              "FEB50A7AA8FD9DE8FE483B9A8EA0FFB9"

printf("\r\nrsa verify test start\r\n");
  /* Ready data */
  //key
#if defined(MBEDTLS_PKCS1_V15)
  mbedtls_rsa_init( &rsa, MBEDTLS_RSA_PKCS_V15, 0 );
#endif
  
#if defined(MBEDTLS_PKCS1_V21)
  mbedtls_rsa_init( &rsa, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA256 );
#endif

  mbedtls_mpi_init( &K );
  //import value
  //pubkey part
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_N  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( &rsa, &K, NULL, NULL, NULL, NULL ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_E  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( &rsa, NULL, NULL, NULL, NULL, &K ) );
  //privatekey part
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_Q  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( &rsa, NULL, NULL, &K, NULL, NULL ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_D  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( &rsa, NULL, NULL, NULL, &K, NULL ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_P  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( &rsa, NULL, &K, NULL, NULL, NULL ) );
  //check fully
  MBEDTLS_MPI_CHK( mbedtls_rsa_complete( &rsa ) );
  if( mbedtls_rsa_check_pubkey(  &rsa ) != 0 ||
      mbedtls_rsa_check_privkey( &rsa ) != 0 )
  {
    ret = 1;
    goto cleanup;
  }

  //plaintext
  memcpy( rsa_plaintext, RSA_PT, PT_LEN);
  printf("mbedtls_sha256_ret\r\n");
  ret += mbedtls_sha256_ret( rsa_plaintext, PT_LEN, sha256sum , 0);

  printf("mbedtls_rsa_pkcs1_sign\r\n");
  if( mbedtls_rsa_pkcs1_sign( &rsa, myrand, NULL,
                              MBEDTLS_RSA_PRIVATE, MBEDTLS_MD_SHA256, 0,
                              sha256sum, rsa_ciphertext ) != 0 )
    {
        ret = 1;
        goto cleanup;
    }

#if defined(MBEDTLS_PKCS1_V15)
  mbedtls_rsa_init( &rsa, MBEDTLS_RSA_PKCS_V15, 0 );
#endif
  
#if defined(MBEDTLS_PKCS1_V21)
  mbedtls_rsa_init( &rsa, MBEDTLS_RSA_PKCS_V21, MBEDTLS_MD_SHA256 );
#endif
  mbedtls_mpi_init( &K );
  //import value
  //pubkey part
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_N  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( &rsa, &K, NULL, NULL, NULL, NULL ) );
  MBEDTLS_MPI_CHK( mbedtls_mpi_read_string( &K, 16, RSA_E  ) );
  MBEDTLS_MPI_CHK( mbedtls_rsa_import( &rsa, NULL, NULL, NULL, NULL, &K ) );
    
  printf("mbedtls_rsa_pkcs1_verify\r\n");
  if( mbedtls_rsa_pkcs1_verify( &rsa, NULL, NULL,
                                MBEDTLS_RSA_PUBLIC, MBEDTLS_MD_SHA256, 0,
                                sha256sum,rsa_ciphertext ) != 0 )
  {
    ret = 1;
    goto cleanup;
  }
  //NEED CLEANUP
  mbedtls_mpi_free( &K );
  mbedtls_rsa_free( &rsa );
  printf("RSA test ok\r\n");
  return 0;
  
  
cleanup:
  mbedtls_mpi_free( &K );
  mbedtls_rsa_free( &rsa );
  return 1;
}


int CIC_Test(void)
{
  CCP_CIC_Ver();
  return 0;
}

int ECC_Test(void)
{
  int i = 0;
  int m1 = 0, m2 = 0;
  int errors = 0;

  /* ECC tests */
  CASPER_ecc_init(kCASPER_ECC_P256);
  /* Begin code to test elliptic curve scalar multiplication. */

 
  PRINTF("Casper ECC Demo P256\r\n\r\n");
  for (i = 0; i < 8; i++)
  {
    PRINTF("Round: %d\r\n", i);

    uint32_t X1[8], Y1[8];
    uint32_t *X3 = &test_ecmulans256[i][0];
    uint32_t *Y3 = &test_ecmulans256[i][8];

    CASPER_ECC_SECP256R1_Mul((CASPER_Type*)CASPER_START_ADDR, X1, Y1, &test_ecmulans256[0][0], &test_ecmulans256[0][8],
                             test_ecmulscalar256[i]);
    CASPER_ECC_equal(&m1, X1, X3);
    CASPER_ECC_equal(&m2, Y1, Y3);
    if (m1 != 0 || m2 != 0)
    {
        errors++;
    }
  }
  if (errors != 0)
  {
    PRINTF("Not all EC scalar multipication tests were successful.\r\n\r\n");
    PRINTF("%d / 8 tests failed.\n", errors);
  }
  else
  {
      PRINTF("All EC scalar multiplication tests were successful.\r\n\r\n");
  }
    /* End code to test elliptic curve scalar multiplication. */
  
  /* Begin code to test elliptic curve double scalar multiplication. */
  {
    int i = 0;
    int m1 = 0, m2 = 0;

    int errors = 0;
    uint32_t c3[256U / 32U], c4[256U / 32U];
    for (i = 0; i < 8; i++)
    {
      PRINTF("Round: %d\r\n", i);
      uint32_t *c1 = &test_ecddoublemul_result256[i][0];
      uint32_t *c2 = &test_ecddoublemul_result256[i][256U / 32U];
      CASPER_ECC_SECP256R1_MulAdd((CASPER_Type*)CASPER_START_ADDR, c3, c4, &test_ecddoublemul_base256[0][0],
                                  &test_ecddoublemul_base256[0][256U / 32U], &test_ecddoublemul_scalars256[i][0],
                                  &test_ecddoublemul_base256[1][0], &test_ecddoublemul_base256[1][256U / 32U],
                                  &test_ecddoublemul_scalars256[i][256U / 32U]);

      CASPER_ECC_equal(&m1, c1, c3);
      CASPER_ECC_equal(&m2, c2, c4);
      if (m1 != 0 || m2 != 0)
      {
        errors++;
      }
    }
    if (errors != 0)
    {
      PRINTF("Not all EC double scalar multipication tests were successful.\r\n\r\n");
      PRINTF("%d / 8 tests failed.\n", errors);
    }
    else
    {
      PRINTF("All EC double scalar multiplication tests were successful.\r\n\r\n");
    }
  }

  return 0;
}

int RSA_Test(void)
{
  int ret = 0;
  
  ret |= mbedtls_RSA2048_SHA256_encrypt_SelfTest();
  ret |= mbedtls_RSA2048_SHA256_Verify_SelfTest();
  return ret;
}

int CCP_Base_Test(void)
{
  uint32_t len = 0;
  
  CCP_Init_Ver();
  CCP_OpMul6464NoSum_Ver();
  CCP_OpMul6464Sum_Ver();
  CCP_OpMul6464FullSum_Ver();
  CCP_OpAdd64_Ver();
  CCP_OpSub64_Ver();
  CCP_OpCopy_Ver();
  CCP_Mul6464NoSumBigNum_Ver();
  CASPER_Init(CASPER_START_ADDR);
  //ModExp test
  len = sizeof(plaintext0) / sizeof(uint32_t);
  CASPER_ModExp((CASPER_Type*)CASPER_START_ADDR, (void *)signature0, len, (void *)pubkey0, len, (uint8_t*)&pub_e, 1, (uint8_t *)gResult);

  if (0 == memcmp(plaintext0, (uint8_t *)gResult, sizeof(plaintext0)/sizeof(plaintext0[0])*4))
  {
    PRINTF("\r\n\r\nModExp Test passed.\r\n");
    return 0;
  }
  else
  {
    PRINTF("\r\n");
    for (int i = 0 ;i <= (sizeof(plaintext0)/sizeof(plaintext0[0])*4); i++)
    {
      printf("%08X",gResult[i]);
    }
    PRINTF("\r\n\r\nModExp Test failed.\r\n");
    return 1;
  }
}


int ecdsa_ver_256(void)
{
  int ret = 1;
  int exit_code = 1;
  
  mbedtls_ecdsa_context ctx_sign = {0}, ctx_verify = {0};
  mbedtls_entropy_context entropy = {0};
  mbedtls_ctr_drbg_context ctr_drbg = {0};
  unsigned char message[100] = {0};
  unsigned char hash[32] = {0};
  unsigned char sig[MBEDTLS_ECDSA_MAX_LEN] = {0};
  size_t sig_len = 0;
  const char *pers = "ecdsa";
  uint16_t i = 0;

  //((void) argv);
  mbedtls_ecdsa_init( &ctx_sign );	
  mbedtls_ecdsa_init( &ctx_verify ); 
  mbedtls_ctr_drbg_init( &ctr_drbg );

  memset( sig, 0, sizeof( sig ) );
  memset( message, 0x25, sizeof( message ) );


  /*
   * Generate a key pair for signing
   */
  printf( "\n  . Seeding the random number generator..." );



  mbedtls_entropy_init( &entropy );
  if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
                             (const unsigned char *) pers,
                             strlen( pers ) ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n  . Generating key pair..." );


  if( ( ret = mbedtls_ecdsa_genkey( &ctx_sign, MBEDTLS_ECP_DP_SECP256R1,
                            mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret );
    goto exit;
  }

  printf( " ok (key size: %d bits)\n", (int) ctx_sign.grp.pbits );

  dump_pubkey( "  + Public key: ", &ctx_sign );
  printf("\r\n\r\n");

  /*
   * Compute message hash
   */
  printf( "  . Computing message hash..." );


  if( ( ret = mbedtls_sha256_ret( message, sizeof( message ), hash, 0 ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_sha256_ret returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n" );

  printf("\r\n  + Hash:");
  for (i = 0; i < sizeof( hash ); i++)
  {
    printf("0x%02x ",hash[i]);
  }
  printf("\r\n");

  /*
   * Sign message hash
   */
  printf( "  . Signing message hash..." );


  if( ( ret = mbedtls_ecdsa_write_signature( &ctx_sign, MBEDTLS_MD_SHA256,
                                     hash, sizeof( hash ),
                                     sig, &sig_len,
                                     mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret );
    goto exit;
  }
  printf( " ok (signature length = %u)\n", (unsigned int) sig_len );


  printf("\r\n  + Signature:");
  for (i = 0; i < sig_len; i++)
  {
    printf("0x%02x ",sig[i]);
  }
  printf("\r\n");

  /*
   * Transfer public information to verifying context
   *
   * We could use the same context for verification and signatures, but we
   * chose to use a new one in order to make it clear that the verifying
   * context only needs the public key (Q), and not the private key (d).
   */
  printf( "  . Preparing verification context..." );

  if( ( ret = mbedtls_ecp_group_copy( &ctx_verify.grp, &ctx_sign.grp ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecp_group_copy returned %d\n", ret );
    goto exit;
  }

  if( ( ret = mbedtls_ecp_copy( &ctx_verify.Q, &ctx_sign.Q ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecp_copy returned %d\n", ret );
    goto exit;
  }

  /*
   * Verify signature
   */
  printf( " ok\n  . Verifying signature..." );

  if( ( ret = mbedtls_ecdsa_read_signature( &ctx_verify,
                                    hash, sizeof( hash ),
                                    sig, sig_len ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_read_signature returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n" );

  exit_code = 0;

exit:
  mbedtls_ecdsa_free( &ctx_verify );
  mbedtls_ecdsa_free( &ctx_sign );
  mbedtls_ctr_drbg_free( &ctr_drbg );
  mbedtls_entropy_free( &entropy );

  return( exit_code );
}    


int ecdsa_ver_384(void)
{
  int ret = 1;
  int exit_code = 1;
  mbedtls_ecdsa_context ctx_sign = {0}, ctx_verify = {0};
  mbedtls_entropy_context entropy = {0};
  mbedtls_ctr_drbg_context ctr_drbg = {0};
  unsigned char message[100] = {0};
  unsigned char hash[32] = {0};
  unsigned char sig[MBEDTLS_ECDSA_MAX_LEN] = {0};
  size_t sig_len = 0;
  const char *pers = "ecdsa";
  uint16_t i = 0;

  //((void) argv);
  mbedtls_ecdsa_init( &ctx_sign );	
  mbedtls_ecdsa_init( &ctx_verify ); 
  mbedtls_ctr_drbg_init( &ctr_drbg );

  memset( sig, 0, sizeof( sig ) );
  memset( message, 0x25, sizeof( message ) );


  /*
   * Generate a key pair for signing
   */
  printf( "\n  . Seeding the random number generator..." );



  mbedtls_entropy_init( &entropy );
  if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
                             (const unsigned char *) pers,
                             strlen( pers ) ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n  . Generating key pair..." );


  if( ( ret = mbedtls_ecdsa_genkey( &ctx_sign, MBEDTLS_ECP_DP_SECP384R1,
                            mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret );
    goto exit;
  }

  printf( " ok (key size: %d bits)\n", (int) ctx_sign.grp.pbits );

  dump_pubkey( "  + Public key: ", &ctx_sign );
  printf("\r\n\r\n");

  /*
   * Compute message hash
   */
  printf( "  . Computing message hash..." );


  if( ( ret = mbedtls_sha256_ret( message, sizeof( message ), hash, 0 ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_sha256_ret returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n" );

  printf("\r\n  + Hash:");
  for (i = 0; i < sizeof( hash ); i++)
  {
    printf("0x%02x ",hash[i]);
  }
  printf("\r\n");

  /*
   * Sign message hash
   */
  printf( "  . Signing message hash..." );


  if( ( ret = mbedtls_ecdsa_write_signature( &ctx_sign, MBEDTLS_MD_SHA256,
                                     hash, sizeof( hash ),
                                     sig, &sig_len,
                                     mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret );
    goto exit;
  }
  printf( " ok (signature length = %u)\n", (unsigned int) sig_len );


  printf("\r\n  + Signature:");
  for (i = 0; i < sig_len; i++)
  {
    printf("0x%02x ",sig[i]);
  }
  printf("\r\n");

  /*
   * Transfer public information to verifying context
   *
   * We could use the same context for verification and signatures, but we
   * chose to use a new one in order to make it clear that the verifying
   * context only needs the public key (Q), and not the private key (d).
   */
  printf( "  . Preparing verification context..." );

  if( ( ret = mbedtls_ecp_group_copy( &ctx_verify.grp, &ctx_sign.grp ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecp_group_copy returned %d\n", ret );
    goto exit;
  }

  if( ( ret = mbedtls_ecp_copy( &ctx_verify.Q, &ctx_sign.Q ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecp_copy returned %d\n", ret );
    goto exit;
  }

  /*
   * Verify signature
   */
  printf( " ok\n  . Verifying signature..." );

  if( ( ret = mbedtls_ecdsa_read_signature( &ctx_verify,
                                    hash, sizeof( hash ),
                                    sig, sig_len ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_read_signature returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n" );

  exit_code = 0;

exit:
  mbedtls_ecdsa_free( &ctx_verify );
  mbedtls_ecdsa_free( &ctx_sign );
  mbedtls_ctr_drbg_free( &ctr_drbg );
  mbedtls_entropy_free( &entropy );

  return( exit_code );
}  


int ecdsa_ver_512(void)
{
  int ret = 1;
  int exit_code = 1;
  mbedtls_ecdsa_context ctx_sign = {0}, ctx_verify = {0};
  mbedtls_entropy_context entropy = {0};
  mbedtls_ctr_drbg_context ctr_drbg = {0};
  unsigned char message[100] = {0};
  unsigned char hash[32] = {0};
  unsigned char sig[MBEDTLS_ECDSA_MAX_LEN] = {0};
  size_t sig_len = 0;
  const char *pers = "ecdsa";
  uint16_t i = 0;

  //((void) argv);
  mbedtls_ecdsa_init( &ctx_sign );	
  mbedtls_ecdsa_init( &ctx_verify ); 
  mbedtls_ctr_drbg_init( &ctr_drbg );

  memset( sig, 0, sizeof( sig ) );
  memset( message, 0x25, sizeof( message ) );


  /*
   * Generate a key pair for signing
   */
  printf( "\n  . Seeding the random number generator..." );



  mbedtls_entropy_init( &entropy );
  if( ( ret = mbedtls_ctr_drbg_seed( &ctr_drbg, mbedtls_entropy_func, &entropy,
                             (const unsigned char *) pers,
                             strlen( pers ) ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ctr_drbg_seed returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n  . Generating key pair..." );


  if( ( ret = mbedtls_ecdsa_genkey( &ctx_sign, MBEDTLS_ECP_DP_SECP521R1,
                            mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret );
    goto exit;
  }

  printf( " ok (key size: %d bits)\n", (int) ctx_sign.grp.pbits );

  dump_pubkey( "  + Public key: ", &ctx_sign );
  printf("\r\n\r\n");

  /*
   * Compute message hash
   */
  printf( "  . Computing message hash..." );


  if( ( ret = mbedtls_sha256_ret( message, sizeof( message ), hash, 0 ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_sha256_ret returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n" );

  printf("\r\n  + Hash:");
  for (i = 0; i < sizeof( hash ); i++)
  {
    printf("0x%02x ",hash[i]);
  }
  printf("\r\n");

  
  printf("\r\n  + Hash:");
  for (i = 0; i < sizeof( hash ); i++)
  {
    printf("%02x",hash[i]);
  }
  printf("\r\n");
  
  /*
   * Sign message hash
   */
  printf( "  . Signing message hash..." );


  if( ( ret = mbedtls_ecdsa_write_signature( &ctx_sign, MBEDTLS_MD_SHA256,
                                     hash, sizeof( hash ),
                                     sig, &sig_len,
                                     mbedtls_ctr_drbg_random, &ctr_drbg ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret );
    goto exit;
  }
  printf( " ok (signature length = %u)\n", (unsigned int) sig_len );


  printf("\r\n  + Signature:");
  for (i = 0; i < sig_len; i++)
  {
    printf("0x%02x ",sig[i]);
  }
  printf("\r\n");
  
  
  printf("\r\n  + Signature:");
  for (i = 0; i < sig_len; i++)
  {
    printf("%02x",sig[i]);
  }
  printf("\r\n");

  /*
   * Transfer public information to verifying context
   *
   * We could use the same context for verification and signatures, but we
   * chose to use a new one in order to make it clear that the verifying
   * context only needs the public key (Q), and not the private key (d).
   */
  printf( "  . Preparing verification context..." );

  if( ( ret = mbedtls_ecp_group_copy( &ctx_verify.grp, &ctx_sign.grp ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecp_group_copy returned %d\n", ret );
    goto exit;
  }

  if( ( ret = mbedtls_ecp_copy( &ctx_verify.Q, &ctx_sign.Q ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecp_copy returned %d\n", ret );
    goto exit;
  }

  /*
   * Verify signature
   */
  printf( " ok\n  . Verifying signature..." );

  if( ( ret = mbedtls_ecdsa_read_signature( &ctx_verify,
                                    hash, sizeof( hash ),
                                    sig, sig_len ) ) != 0 )
  {
    printf( " failed\n  ! mbedtls_ecdsa_read_signature returned %d\n", ret );
    goto exit;
  }

  printf( " ok\n" );

  exit_code = 0;

exit:
  mbedtls_ecdsa_free( &ctx_verify );
  mbedtls_ecdsa_free( &ctx_sign );
  mbedtls_ctr_drbg_free( &ctr_drbg );
  mbedtls_entropy_free( &entropy );

  return( exit_code );
}    

/*!
 * @brief Main function.
 */
int CCP_Ver(void)
{
  int ret = 0;
    
  CASPER_Init(CASPER_START_ADDR);
  printf("\r\n=========================== CIC_Test =============================\r\n");
  ret += CIC_Test();
  printf("\r\n======================== CCP_Base_Test ===========================\r\n");
  ret += CCP_Base_Test();
  printf("\r\n=========================== RSA_Test =============================\r\n");
  ret += RSA_Test();
  printf("\r\n=========================== ECC_Test =============================\r\n");
 ret += ECC_Test();
  printf("\r\n======================== ECDSA_256_Test ===========================\r\n");
  ret += ecdsa_ver_256();
  printf("\r\n======================== ECDSA_384_Test ===========================\r\n");
  ret += ecdsa_ver_384();
  printf("\r\n======================== ECDSA_512_Test ===========================\r\n");
  ret += ecdsa_ver_512();

  if (0 ==  ret)
  {
    printf("\r\n\r\n CPP test pass!\r\n");
  }
  else
  {
    printf("\r\n\r\n CPP test fail!\r\n");
  }

  while(1);

}
