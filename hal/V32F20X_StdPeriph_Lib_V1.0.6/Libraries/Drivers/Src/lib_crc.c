/**
  ******************************************************************************
  * @file    lib_crc.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-04-16
  * @brief   CRC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_crc.h"
#include <string.h>
#include "lib_syscfg.h"

/**
  * @brief  De-initializes the CRC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void CRC_DeInit(void)
{
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_CRC);
}

/**
  * @brief  Fills each RNG_InitStruct member with its default value.
  * @param  InitStruct: pointer to an RNG_InitType structure which will be initialized.
  * @retval None
  */
void CRC_StructInit(CRC_InitType *CRC_InitStruct)
{
  CRC_InitStruct->CRC_Polynomial = CRC_Polynomial_CRC32;
  CRC_InitStruct->CRC_ReverseIn = CRC_ReverseIn_Enable;
  CRC_InitStruct->CRC_ComplementIn = CRC_ComplementIn_Disable;
  CRC_InitStruct->CRC_ReverseOut = CRC_ReverseOut_Enable;
  CRC_InitStruct->CRC_ComplementOut = CRC_ComplementOut_Enable;
  CRC_InitStruct->Seed = 0xFFFFFFFF;
}

/**
  * @brief  CRC initialization.
  * @param  CRC_InitType:CRC configuration.
  * @retval None
  */
void CRC_Init(CRC_InitType *CRC_InitStruct)
{
  /* Check the parameters */
  assert_parameters(IS_CRC_POLYNOMIAL(CRC_InitStruct->CRC_Polynomial));
  assert_parameters(IS_CRC_REVERSEIN(CRC_InitStruct->CRC_ReverseIn));
  assert_parameters(IS_CRC_COMPLEMENTIN(CRC_InitStruct->CRC_ComplementIn));
  assert_parameters(IS_CRC_REVERSEOUT(CRC_InitStruct->CRC_ReverseOut));
  assert_parameters(IS_CRC_COMPLEMENTOUT(CRC_InitStruct->CRC_ComplementOut));
  
  /* Configure CRC module and write the seed */
  CRC->MODE = CRC_InitStruct->CRC_Polynomial
              |CRC_InitStruct->CRC_ReverseIn
              |CRC_InitStruct->CRC_ComplementIn
              |CRC_InitStruct->CRC_ReverseOut
              |CRC_InitStruct->CRC_ComplementOut;
  CRC->SEED = CRC_InitStruct->Seed;
}

/**
  * @brief  Writes data to the CRC module.
  * @param  Data: Input data stream, MSByte in Data[0].
  * @param  DataSize: Size of the input data buffer in bytes.
  * @retval None
  */
void CRC_WriteData(const uint8_t *Data, uint32_t DataSize)
{
    const uint32_t *data32;

    /* 8-bit reads and writes till source address is aligned 4 bytes */
    while ((0 != DataSize) && (0 != ((uint32_t)Data&3U)))
    {
        *((__O uint8_t *)&(CRC->WR_DATA)) = *Data;
        Data++;
        DataSize--;
    }

    /* use 32-bit reads and writes as long as possible */
    data32 = (const uint32_t *)Data;
    while (DataSize >= sizeof(uint32_t))
    {
        *((__O uint32_t *)&(CRC->WR_DATA)) = *data32;
        data32++;
        DataSize -= sizeof(uint32_t);
    }

    Data = (const uint8_t *)data32;

    /* 8-bit reads and writes till end of data buffer */
    while (0 != DataSize)
    {
        *((__O uint8_t *)&(CRC->WR_DATA)) = *Data;
        Data++;
        DataSize--;
    }
}

/**
  * @brief  Reads 32-bit checksum from the CRC module..
  * @param  None
  * @retval Return final 32-bit checksum
  */
uint32_t CRC_Get32bitResult(void)
{
    return CRC->SUM;
}

/**
  * @brief  Reads 16-bit checksum from the CRC module..
  * @param  None
  * @retval Return final 16-bit checksum
  */
uint16_t CRC_Get16bitResult(void)
{
    return (uint16_t)CRC->SUM;
}

/*********************************** END OF FILE ******************************/
