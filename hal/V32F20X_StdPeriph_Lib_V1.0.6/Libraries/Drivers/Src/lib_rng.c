/**
  ******************************************************************************
  * @file    lib_rng.c 
  * @author  Application Team
  * @version V1.0
  * @date    2020-10-27
  * @brief   RNG module driver.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_rng.h"
#include "lib_syscfg.h"

/**
  * @brief  De-initializes the RNG peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void RNG_DeInit(void)
{
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_RNG);
}

/**
  * @brief  Fills each RNG member with its default value.
  * @param  InitStruct: pointer to an RNG_InitType structure which will be initialized.
  * @retval None
  */
void RNG_StructInit(RNG_InitType *RNG_InitStruct)
{
  RNG_InitStruct->RNG_InverterChainSelect = RNG_INVCHNSEL_LONGEST;
	RNG_InitStruct->RNG_SampleCount = 100000;
	RNG_InitStruct->RNG_Bypass = RNG_BYPASS_AUTOCORR_ERR|\
														RNG_BYPASS_CRNGT_ERR|\
														RNG_BYPASS_VN_ERR;
}

/**
  * @brief  RNG initialization.
  * @param  RNG_InitType:RNG configuration.
  *         RNG_InverterChainSelect: Selects the length of inverters in the ring oscillator.
  *           This parameter can be any combination of the following values:
  *               RNG_INVCHNSEL_SHORTEST
  *               RNG_INVCHNSEL_SHORT   
  *               RNG_INVCHNSEL_LONG    
  *               RNG_INVCHNSEL_LONGEST
  *         RNG_SampleCount : Sets the number of clock cycles between two consecutive 
  *           ring oscillator samples.
  *           Range:0~0xFFFFFFFF
  *         RNG_Bypass : Bypass test funtions.
  *         This parameter can be any combination of the following values:
  *               RNG_BYPASS_NONE
  *               RNG_BYPASS_AUTOCORR_ERR
  *               RNG_BYPASS_CRNGT_ERR   
  *               RNG_BYPASS_VN_ERR    
  * @retval None
  */
void RNG_Init(RNG_InitType *RNG_InitStruct)
{
  /* Check the parameters */
  assert_parameters(IS_RNG_INVERTER_CHAIN_SELECT(RNG_InitStruct->RNG_InverterChainSelect));
  assert_parameters(IS_RNG_BYPASS(RNG_InitStruct->RNG_Bypass));
  
	RNG->CFG = RNG_InitStruct->RNG_InverterChainSelect;
	RNG->CNT = RNG_InitStruct->RNG_SampleCount;
	RNG->BYPASS = RNG_InitStruct->RNG_Bypass;
}

/**
  * @brief  Enables or disables specified interrupt.
  * @param  INTMask: specifies the RNG interrupt source to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *                 RNG_VN_ERR      
  *                 RNG_CRNGT_ERR   
  *                 RNG_AUTOCORR_ERR
	*                 RNG_EHR_VALID   
  * @param  NewState: new state of RNG.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RNG_INTConfig(uint32_t INTMask, uint32_t NewState)
{
  /* Check the parameters */
  assert_parameters(IS_RNG_STATUS(INTMask));
  
	if (NewState != DISABLE)
  {
    RNG->IMR |= INTMask;
  }
  else
  {
    RNG->IMR &= ~INTMask;
  }
}

/**
  * @brief  Gets RNG specified interrupt status.
  * @param  INTMask: specifies the interrupt source to check.
  *         This parameter can be one of the following values:
  *             RNG_VN_ERR      
  *             RNG_CRNGT_ERR   
  *             RNG_AUTOCORR_ERR
  *             RNG_EHR_VALID   
  * @retval  The new state of RNG specified interrupt status (SET or RESET).
  */
ITStatus RNG_GetINTStatus(uint32_t INTMask)
{
	uint32_t tmp = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_ONE_RNG_STATUS(INTMask));
  
  switch (INTMask)
  {
    default:
      break;
    
    case RNG_VN_ERR:
      tmp = RNG->ISR & RNG_VN_ERR;
      break;
    
    case RNG_CRNGT_ERR:
      tmp = RNG->ISR & RNG_CRNGT_ERR;
      break;
    
    case RNG_AUTOCORR_ERR:
      tmp = RNG->ISR & RNG_AUTOCORR_ERR;
      break;
    
    case RNG_EHR_VALID:
      tmp = RNG->ISR & RNG_EHR_VALID;
      break;
  }
  
  if (tmp)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears RNG specified interrupt status.
  * @param  INTMask: specifies the RNG interrupt source to clear.
  *         This parameter can be any combination of the following values:
  *             RNG_VN_ERR        
  *             RNG_CRNGT_ERR     
	*             RNG_AUTOCORR_ERR  
	*             RNG_EHR_VALID     
  * @retval None
  */
void RNG_ClearINTStatus(uint32_t INTMask)
{
  /* Check the parameters */
  assert_parameters(IS_RNG_STATUS(INTMask));
  
	RNG->ICR = INTMask;
}

/**
  * @brief  Enable the RNG entropy source.
  * @param  NewState: New status of the RNG entropy source.
  *         This parameter can be the following values:
  *             ENABLE        
  *             DISABLE         
  * @retval None
  */
void RNG_Cmd(uint32_t NewState)
{
  /* Check the parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
	if (NewState != DISABLE)
	{
		RNG->CMD = RNG_RNGEN;
	}
	else
	{
		RNG->CMD = 0;
	}
}

/**
  * @brief  Read random number from RNG data register.
  * @param  buff: Buffer to fill while read.
  *         len: Buffer length(1~24)
  * @retval None
  */
void RNG_ReadData(uint8_t *buff, uint32_t len)
{
  uint32_t tmpreg;
  uint32_t i;
  uint32_t m;
  
  /* Check the parameters */
  assert_parameters(buff != NULL);
  assert_parameters(IS_RNG_READ_DATA_LEN(len));
  
  for (i = 0; i < len; i++)
  {
    m = i%4;
    if (m == 0)
    {
      tmpreg = RNG->DATA[i/4];
    }
    buff[i] = (tmpreg >> (m*8))&0xFF;
  }
}

/*********************************** END OF FILE ******************************/
