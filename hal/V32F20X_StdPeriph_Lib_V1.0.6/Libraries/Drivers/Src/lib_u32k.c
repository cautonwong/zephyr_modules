/**
  ******************************************************************************
  * @file    lib_u32k.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   u32k library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_u32k.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup U32K 
  * @{
  */ 
  
/** @defgroup U32K Private define
  * @{
  */

#define U32K_RESET_VALUE            ((uint32_t)0x40000000)  /*Control Enable*/

/**
  * @}
  */
  
/**
  * @brief  Deinitializes the U32K peripheral registers to their default reset 
            values.
  * @param  U32Kx: U32K0 or U32K1
  * @retval None
  */
void U32K_DeInit(U32K_Type U32Kx)
{
  /* Check parameters */
  assert_parameters(IS_ALL_U32K(U32Kx));

  /* Reset U32K */
  PMU->RETRAMCFG = 0;
  if (U32Kx == U32K0)
  {
    PMU->UART32K_0_CFG = U32K_RESET_VALUE;
  }
  else
  {
    PMU->UART32K_1_CFG = U32K_RESET_VALUE;
  }
}

/**
  * @brief  Fills each U32K_InitType member with its default value.
  * @param  U32K_InitStruct: pointer to an U32K_InitType structure which will be initialized.
  * @retval None
  */
void U32K_InitStruct_Init(U32K_InitType *U32K_InitStruct)
{
/*---------------- Reset U32K init structure parameters values ----------------*/
  /* initialize the U32K Baudrate member */
  U32K_InitStruct->Baudrate  = 0;
  /* initialize the U32K Auto-calibration member */
  U32K_InitStruct->AutoCal   = U32K_AUTO_CAL_ON;
  /* initialize the U32K Debounce member */
  U32K_InitStruct->Debounce  = U32K_DEBOUNCE_0;
  /* initialize the U32K FirstBit member */
  U32K_InitStruct->FirstBit  = U32K_FIRSTBIT_LSB;
  /* initialize the U32K Parity member */
  U32K_InitStruct->Parity    = U32K_PARITY_NONE;
  /* initialize the U32K Parity check member */
  U32K_InitStruct->Pcheck    = U32K_PARITY_CHECK_NOT;
  /* initialize the U32K Receive data member */
  U32K_InitStruct->LineSel   = U32K_USE_RX0;
  /* initialize the U32K Enable member */
  U32K_InitStruct->WKU_nByte = 0;
}

/**
  * @brief  U32K initialization.
  * @param  U32Kx: U32K0 or U32K1
  * @param  U32K_InitType: U32K configuration
  *             Debounce:
  *               @arg U32K_DEBOUNCE_NONE
  *               @arg U32K_DEBOUNCE_60US
  *               @arg U32K_DEBOUNCE_90US
  *               @arg U32K_DEBOUNCE_120US
  *             Parity:
  *               @arg U32K_PARITY_NONE
  *               @arg U32K_PARITY_EVEN
  *               @arg U32K_PARITY_ODD
  *               @arg U32K_PARITY_0
  *             FirstBit:
  *               @arg U32K_FIRSTBIT_LSB
  *               @arg U32K_FIRSTBIT_MSB
  *             AutoCal:
  *               @arg U32K_AUTOCAL_ON
  *               @arg U32K_AUTOCAL_OFF
  *             LineSel:
  *               @arg U32K_LINE_RX0
  *               @arg U32K_LINE_RX1
  *               @arg U32K_LINE_RX2
  *               @arg U32K_LINE_RX3
  *               @arg U32K_LINE_RX4
  *               @arg U32K_LINE_RX5
  *             Baudrate: Baudrate value
  *             Pcheck:
  *               @arg U32K_PARITY_CHECK_GOOD
  *               @arg U32K_PARITY_CHECK_NOT
  *             WKU_nByte:
  *               @arg 0~31
  * @retval None
  */
void U32K_Init(U32K_Type U32Kx,  U32K_InitType *U32K_InitStruct)
{
  /* Check parameters */
  assert_parameters(IS_ALL_U32K(U32Kx));

  uint32_t u32k_config = ((uint32_t)0x00000000);

  /* Check parameters */
  assert_parameters(IS_ALL_U32K(U32Kx));
  assert_parameters(IS_U32K_LINESEL(U32K_InitStruct->LineSel));
  assert_parameters(IS_U32K_PARITY_CHECK(U32K_InitStruct->Pcheck));
  assert_parameters(IS_U32K_PARITY(U32K_InitStruct->Parity));
  assert_parameters(IS_U32K_FIRSTBIT(U32K_InitStruct->FirstBit));
  assert_parameters(IS_U32K_DEBOUNCE(U32K_InitStruct->Debounce));
  assert_parameters(IS_U32K_BAUDRATE(U32K_InitStruct->Baudrate));
  assert_parameters(IS_U32K_AUTO_CAL(U32K_InitStruct->AutoCal));

  /* U32K UART32K_0_CFG Configuration */
  u32k_config = U32K_InitStruct->Baudrate*2    /* Get the U32K Baudrate value */
              | U32K_InitStruct->AutoCal       /* Get the U32K Auto-calibration value */
              | U32K_InitStruct->Debounce      /* Get the U32K De-bounce value */
              | U32K_InitStruct->FirstBit      /* Get the U32K Receive order value */
              | U32K_InitStruct->LineSel       /* Get the U32K Receive data value */
              | U32K_InitStruct->Pcheck        /* Get the U32K Parity check value */
              | U32K_InitStruct->Parity;       /* Get the U32K Parity value */

  /* U32K RETRAMCFG Configuration */
  if(U32Kx == U32K0)
  {
    /* U32K Receive data counts to generate wakeup source */
    PMU->RETRAMCFG |= (U32K_InitStruct->WKU_nByte << 8); 
    /* Set U32K UART32K_0_CFG Configuration */
    PMU->UART32K_0_CFG = u32k_config;
  }
  else
  {
    /* U32K Receive data counts to generate wakeup source */
    PMU->RETRAMCFG |= (U32K_InitStruct->WKU_nByte << 16);
    /* Set U32K UART32K_0_CFG Configuration */
    PMU->UART32K_1_CFG = u32k_config;
  }
}

/**
  * @brief  Enables or Disables U32K.
  * @param  U32Kx: U32K0 or U32K1
  * @param  NewState: new state of the specified U32K peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void U32K_Cmd(U32K_Type U32Kx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_ALL_U32K(U32Kx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  /* Enable or Disable the selected U32K peripheral */
  if(U32Kx == U32K0)
  {
    if(NewState == ENABLE)
    {
      /* Enable the selected U32K peripheral */
      PMU->UART32K_0_CFG |= U32K_ENABLE;
    }
    else
    {
      /* DISABLE the selected U32K peripheral */
      PMU->UART32K_0_CFG &= ~U32K_ENABLE;
    }
  }
  else
  {
    if(NewState == ENABLE)
    {
      /* Enable the selected U32K peripheral */
      PMU->UART32K_1_CFG |= U32K_ENABLE;
    }
    else
    {
      /* DISABLE the selected U32K peripheral */
      PMU->UART32K_1_CFG &= ~U32K_ENABLE;
    }
  }
}

/**
  * @brief  Enables or disables U32K interrupt and wakeup.
  * @param  U32Kx: U32K0 or U32K1
  * @param  NewState: new state of the specified U32K interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void U32K_WKU_INT_Config(U32K_Type U32Kx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_ALL_U32K(U32Kx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  /* Set UART32K_0_CFG in U32K0_WKUEN */
  if(U32Kx == U32K0)
  {
    if(NewState==ENABLE)
    {
      PMU->UART32K_0_CFG |= U32K_WKU_INT_ENABLE;
    }
    else
    {
      PMU->UART32K_0_CFG &= ~U32K_WKU_INT_ENABLE;
    }
  }
  else
  {
    if(NewState==ENABLE)
    {
      PMU->UART32K_1_CFG |= U32K_WKU_INT_ENABLE;
    }
    else
    {
      PMU->UART32K_1_CFG &= ~U32K_WKU_INT_ENABLE;
    }
  }
}

/**
  * @brief  Gets U32K interrupt status.
  * @param  U32Kx: U32K0 or U32K1
  * @retval The new state of U32K interrupt (SET or RESET).
  */
ITStatus U32K_GetINTStatus(U32K_Type U32Kx)
{
  /* Check parameters */
  assert_parameters(IS_ALL_U32K(U32Kx));

  /* Check if the interrupt source is enabled or not */
  if(U32Kx == U32K0)
  {
    if(PMU->UART32K_0_CFG & U32K_WKU_INT_STS)
    {
      return SET;
    }
    else
    {
      return RESET;
    }
  }
  else
  {
    if(PMU->UART32K_1_CFG & U32K_WKU_INT_STS)
    {
      return SET;
    }
    else
    {
      return RESET;
    }
  }
}

/**
  * @brief  Clears U32K interrupt status bit.
  * @param  U32Kx: U32K0 or U32K1
  * @retval None.
  */
void U32K_ClearINTStatus(U32K_Type U32Kx)
{
  /* Check parameters */
  assert_parameters(IS_ALL_U32K(U32Kx));

  /* Clear the Interrupt status */
  if(U32Kx == U32K0)
  {
    PMU->UART32K_0_CFG |= U32K_WKU_INT_STS;
    while(PMU->UART32K_0_CFG & U32K_WKU_INT_STS);
  }
  else
  {
    PMU->UART32K_1_CFG |= U32K_WKU_INT_STS;
    while(PMU->UART32K_1_CFG & U32K_WKU_INT_STS);
  }
}

/**
  * @}
  */

/**
  * @}
  */
/*********************************** END OF FILE ******************************/
