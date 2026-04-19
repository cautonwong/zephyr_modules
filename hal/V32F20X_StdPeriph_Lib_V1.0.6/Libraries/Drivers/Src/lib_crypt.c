/**
  ******************************************************************************
  * @file    lib_crypt.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2018-09-27
  * @brief   CRYPT library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_crypt.h"

/*
// CRYPT_PTR register
*/
#define CRYPT_PTR_PTR_MASK             (0x7FFFUL)
/*
// CRYPT_CARRY register
*/
#define CRYPT_CARRY_CARRY              (0x01UL)
/*
// CRYPT_CTRL register
*/
#define CRYPT_CTRL_ACT                 (1UL << 0)
#define CRYPT_CTRL_MODE_MULTIPLY       (0UL << 4)
#define CRYPT_CTRL_MODE_ADD            (1UL << 4)
#define CRYPT_CTRL_MODE_SUB            (2UL << 4)
#define CRYPT_CTRL_MODE_RSHIFT1        (3UL << 4)

/* Exported Functions ------------------------------------------------------- */

/**
  * @brief  Configures PTRA register, data in this address will be read out to do 
  *         the CRYPT calculation
  * @param  AddrA: the SRAM0 address(Bit 13:0, 0x20000000 ~ 0x20003FFF)
  * @retval None
  */
void CRYPTO_AddressAConfig(uint16_t AddrA)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_ADDR(AddrA));
  
  CRYPTO->PTRA = AddrA & CRYPT_PTR_PTR_MASK;
}

/**
  * @brief  Configures PTRB register, data in this address will be read out to do 
  *         the CRYPT calculation
  * @param  AddrB: the SRAM address(Bit 13:0, 0x20000000 ~ 0x20003FFF)
  * @retval None
  */
void CRYPTO_AddressBConfig(uint16_t AddrB)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_ADDR(AddrB));

  CRYPTO->PTRB = AddrB & CRYPT_PTR_PTR_MASK;
}

/**
  * @brief  Configures PTRO register, The CRYPT engine will write calculation 
  *         result into this address
  * @param  AddrO: the SRAM address(Bit 13:0, 0x20000000 ~ 0x20003FFF)
  * @retval None
  */
void CRYPTO_AddressOConfig(uint16_t AddrO)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_ADDR(AddrO)); 
  
  CRYPTO->PTRO = AddrO & CRYPT_PTR_PTR_MASK;
}

/**
  * @brief  Gets carry/borrow bit of add/sub operation.
  * @param  None
  * @retval carry/borrow bit value
  */
uint8_t CRYPTO_GetCarryBorrowBit(void)
{
  if (CRYPTO->CARRY & CRYPT_CARRY_CARRY)
    return (1);
  else
    return (0);
}

/**
  * @brief  Starts addition operation.
  * @param  Length: the VLI length of current operation
  *         This parameter can be:
  *             CRYPT_LENGTH_32
  *             CRYPT_LENGTH_64
  *             CRYPT_LENGTH_96
  *             CRYPT_LENGTH_128
  *             CRYPT_LENGTH_160
  *             CRYPT_LENGTH_192
  *             CRYPT_LENGTH_224
  *             CRYPT_LENGTH_256
  *             CRYPT_LENGTH_288
  *             CRYPT_LENGTH_320
  *             CRYPT_LENGTH_352
  *             CRYPT_LENGTH_384
  *             CRYPT_LENGTH_416
  *             CRYPT_LENGTH_448
  *             CRYPT_LENGTH_480
  *             CRYPT_LENGTH_512
  * @param  Nostop: if the CPU will be stop when the CRYPT engine is busy
  *         This parameter can be:
  *             CRYPT_STOPCPU
  *             CRYPT_NOSTOPCPU
  * @retval None
  */
void CRYPTO_StartAdd(uint32_t Length, uint32_t Nostop)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_LENGTH(Length)); 
  assert_parameters(IS_CRYPT_NOSTOP(Nostop));
  
  CRYPTO->CTRL = (Nostop \
                 |Length \
                 |CRYPT_CTRL_MODE_ADD \
                 |CRYPT_CTRL_ACT);
}

/**
  * @brief  Starts multiplication operation.
  * @param  Length: the VLI length of current operation
  *         This parameter can be:
  *             CRYPT_LENGTH_32
  *             CRYPT_LENGTH_64
  *             CRYPT_LENGTH_96
  *             CRYPT_LENGTH_128
  *             CRYPT_LENGTH_160
  *             CRYPT_LENGTH_192
  *             CRYPT_LENGTH_224
  *             CRYPT_LENGTH_256
  *             CRYPT_LENGTH_288
  *             CRYPT_LENGTH_320
  *             CRYPT_LENGTH_352
  *             CRYPT_LENGTH_384
  *             CRYPT_LENGTH_416
  *             CRYPT_LENGTH_448
  *             CRYPT_LENGTH_480
  *             CRYPT_LENGTH_512
  * @param  Nostop: if the CPU will be stop when the CRYPT engine is busy
  *         This parameter can be:
  *             CRYPT_STOPCPU
  *             CRYPT_NOSTOPCPU
  * @retval None
  */
void CRYPTO_StartMultiply(uint32_t Length, uint32_t Nostop)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_LENGTH(Length)); 
  assert_parameters(IS_CRYPT_NOSTOP(Nostop));
  
  CRYPTO->CTRL = (Nostop \
                 |Length \
                 |CRYPT_CTRL_MODE_MULTIPLY \
                 |CRYPT_CTRL_ACT);
}

/**
  * @brief  Starts subtraction operation.
  * @param  Length: the VLI length of current operation
  *         This parameter can be:
  *             CRYPT_LENGTH_32
  *             CRYPT_LENGTH_64
  *             CRYPT_LENGTH_96
  *             CRYPT_LENGTH_128
  *             CRYPT_LENGTH_160
  *             CRYPT_LENGTH_192
  *             CRYPT_LENGTH_224
  *             CRYPT_LENGTH_256
  *             CRYPT_LENGTH_288
  *             CRYPT_LENGTH_320
  *             CRYPT_LENGTH_352
  *             CRYPT_LENGTH_384
  *             CRYPT_LENGTH_416
  *             CRYPT_LENGTH_448
  *             CRYPT_LENGTH_480
  *             CRYPT_LENGTH_512
  * @param  Nostop: if the CPU will be stop when the CRYPT engine is busy
  *         This parameter can be:
  *             CRYPT_STOPCPU
  *             CRYPT_NOSTOPCPU
  * @retval None
  */
void CRYPTO_StartSub(uint32_t Length, uint32_t Nostop)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_LENGTH(Length)); 
  assert_parameters(IS_CRYPT_NOSTOP(Nostop));
  
  CRYPTO->CTRL = (Nostop \
                 |Length \
                 |CRYPT_CTRL_MODE_SUB \
                 |CRYPT_CTRL_ACT);
}

/**
  * @brief  Starts rigth shift 1-bit operation.
  * @param  Length: the VLI length of current operation
  *         This parameter can be:
  *             CRYPT_LENGTH_32
  *             CRYPT_LENGTH_64
  *             CRYPT_LENGTH_96
  *             CRYPT_LENGTH_128
  *             CRYPT_LENGTH_160
  *             CRYPT_LENGTH_192
  *             CRYPT_LENGTH_224
  *             CRYPT_LENGTH_256
  *             CRYPT_LENGTH_288
  *             CRYPT_LENGTH_320
  *             CRYPT_LENGTH_352
  *             CRYPT_LENGTH_384
  *             CRYPT_LENGTH_416
  *             CRYPT_LENGTH_448
  *             CRYPT_LENGTH_480
  *             CRYPT_LENGTH_512
  * @param  Nostop: if the CPU will be stop when the CRYPT engine is busy
  *         This parameter can be:
  *             CRYPT_STOPCPU
  *             CRYPT_NOSTOPCPU
  * @retval None
  */
void CRYPTO_StartRShift1(uint32_t Length, uint32_t Nostop)
{
  /* Check parameters */
  assert_parameters(IS_CRYPT_LENGTH(Length)); 
  assert_parameters(IS_CRYPT_NOSTOP(Nostop));
  
  CRYPTO->CTRL = (Nostop \
                 |Length \
                 |CRYPT_CTRL_MODE_RSHIFT1 \
                 |CRYPT_CTRL_ACT);
}

/**
  * @brief  Waits for last operation to complete. 
  * @param  None
  * @retval None
  */
void CRYPTO_WaitForLastOperation(void)
{
  while (CRYPTO->CTRL & CRYPT_CTRL_ACT)
  {
  }
}

/*********************************** END OF FILE ******************************/
