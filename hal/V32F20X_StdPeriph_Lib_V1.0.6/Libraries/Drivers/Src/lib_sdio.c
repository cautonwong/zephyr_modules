/**
  ******************************************************************************
  * @file    lib_sdio.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-04-16
  * @brief   SDIO library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_sdio.h"

/** @defgroup FLASH_Private_Defines
  * @{
  */ 

/* SDIO CMD mask */
#define SDIO_CMD_MASK                 (0x3FE30000UL)
#define SDIO_CMD_CLR                  REG_BIT_NOT(SDIO_CMD_MASK)
/* SDIO DATA mask */
#define SDIO_DATA_MASK                (0xFFFF0FFFUL)
#define SDIO_DATA_CLR                 REG_BIT_NOT(SDIO_DATA_MASK)
/* SDIO BlockSize mask */
#define SDIO_BLOCKSIZE_MASK           (0x00000FFFUL)
#define SDIO_BLOCKSIZE_CLR            REG_BIT_NOT(SDIO_BLOCKSIZE_MASK)
/* SDIO SDMABB mask */
#define SDIO_SDMABB_MASK              (0x00007000UL)
#define SDIO_SDMABB_CLR               REG_BIT_NOT(SDIO_SDMABB_MASK)
/* SDIO TransferBuffer mask */
#define SDIO_TRANSBUFF_MASK           (0xFFFF0FFFUL)
#define SDIO_TRANSBUFF_CLR            REG_BIT_NOT(SDIO_TRANSBUFF_MASK)

#define SDIO0_RESP_ADDR           ((uint32_t)(SDIO0_BASE + 0x210))
#define SDIO1_RESP_ADDR           ((uint32_t)(SDIO1_BASE + 0x210))

/**
  * @}
  */ 

/** @defgroup FLASH_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the SDIOx peripheral registers to their default reset values.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval None
  */
void SDIO_DeInit(SDIO_TypeDef *SDIOx)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));

  if(SDIOx == SDIO0)
  {
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_SDIO0);
  }
  else
  {
    SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_SDIO1);
  }

  SDIOx->MODE = 0x00000000;
  SDIOx->BLOCK_COUNT= 0x00000000;
  SDIOx->ARG = 0x00000000;
  SDIOx->CTRL1 = 0x00000000;
	SDIOx->CTRL2 = 0;
	
	SYSCFG0->SDIO_CTRL = 0;
}

/**
  * @brief  Resets the SDIOx peripheral.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval None
  */
void SDIO_SWReset(SDIO_TypeDef *SDIOx)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
	
  SDIOx->INFO = SDIO_INFO_SWR;
}

/**
  * @brief  Initializes the SDIO peripheral according to the specified 
  *         parameters in the SDIO_InitStruct.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SDIO_InitStruct : pointer to a SDIO_InitType structure 
  *         that contains the configuration information for the SDIO peripheral.
  * @retval None
  */
void SDIO_Init(SDIO_TypeDef *SDIOx, SDIO_InitType* SDIO_InitStruct)
{
  uint32_t tmpreg1 = 0;

  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
	
  if(SDIOx == SDIO0)
  {
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO0,ENABLE);
  }
  else if(SDIOx == SDIO1)
  {
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO1,ENABLE);
  }
  tmpreg1 = SDIOx->CTRL1;
  tmpreg1 &= ~SDIO_CTRL1_DATWIDTH_Msk;
  tmpreg1 |= SDIO_InitStruct->BusWide;
  SDIOx->CTRL1 |= tmpreg1;

  tmpreg1 = SDIOx->MODE;
  tmpreg1 &= ~SDIO_MODE_Msk;
  tmpreg1 |= SDIO_InitStruct->Mode;
  SDIOx->MODE = tmpreg1;

  /*config CLK*/
  tmpreg1 = SDIOx->CTRL2;
  SDIOx->CTRL2 = 0;
  tmpreg1 &= ~0xFFC0;
  tmpreg1 |= (SDIO_InitStruct->ClockDiv << 8);
  SDIOx->CTRL2 = tmpreg1|BIT2;
}

/**
  * @brief  Fills each SDIO_InitStruct member with its default value.
  * @param  SDIO_InitStruct: pointer to an SDIO_CMDInitType structure which 
  *   will be initialized.
  * @retval None
  */
void SDIO_CmdStructInit(SDIO_CMDInitType* SDIO_CmdInitStruct)
{
  SDIO_CmdInitStruct->CmdIndex = 0;
  SDIO_CmdInitStruct->CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStruct->CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStruct->Argument = 0;
  SDIO_CmdInitStruct->Response = SDIO_Response_No;
}

/**
  * @brief  Read one data word from Rx register.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  Device: Specifies the device. 
  *   This parameter can be one of the following values:
  *     @arg SDIO_DEVICE_SDCard
  *     @arg SDIO_DEVICE_SDR
  *     @arg SDIO_DEVICE_DDR
  *     @arg SDIO_DEVICE_HS200
  *     @arg SDIO_DEVICE_HS400
  *     @arg SDIO_DEVICE_ENHANCEDHS400
  * @retval void
  */
void SDIO_SelectDevice(SDIO_TypeDef *SDIOx, uint8_t Device)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_SDIO_DEVICE(Device));
	
  SDIOx->MODE = Device;
}

/**
  * @brief  Initializes the SDIO Command according to the specified 
  *         parameters in the SDIO_CmdInitStruct and send the command.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SDIO_CmdInitStruct : pointer to a SDIO_CMDInitType 
  *         structure that contains the configuration information for the SDIO command.
  * @retval STD status
  */
STD_StatusType SDIO_SendCommand(SDIO_TypeDef *SDIOx, SDIO_CMDInitType *SDIO_CmdInitStruct)
{
  uint32_t tmpreg;
	uint32_t tickstart;
  
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_SDIO_RESPONSE(SDIO_CmdInitStruct->Response));
  assert_parameters(IS_CMDTYPE(SDIO_CmdInitStruct->CmdType));
  
  tickstart = STD_GetTick();
	while((SDIOx->STATUS2 & BIT0) != 0)
	{
		if((STD_GetTick() - tickstart) > 10)
		{
			return STD_TIMEOUT;
		}
	}
				
  SDIOx->ARG = SDIO_CmdInitStruct->Argument;
  tmpreg = SDIOx->CMD;
  tmpreg &= SDIO_CMD_CLR;  //0x3FE30000UL
  if(SDIO_CmdInitStruct->CmdIndex == 24)
  {
    tmpreg = 0x20001|SDIO_CmdInitStruct->CmdIndex<<24|1<<22|1<<20|1;
  }
  else
  {
    tmpreg |= (SDIO_CmdInitStruct->CmdIndex<<24) | SDIO_CmdInitStruct->CmdType
           | SDIO_CmdInitStruct->Response;
  }
  tmpreg &= ~BIT21;  //Data Present Select
  if(SDIO_CmdInitStruct->DataMode == SDIO_DATA)  //Data
  {
    SDIOx->BLOCK_COUNT = 0;
    if(SDIO_CmdInitStruct->DataInit.DMAMode == SDIO_SDMA)
    {
      SDIOx->ADDR = SDIO_CmdInitStruct->DataInit.SDMAAddr;
      SDIOx->BLOCK_COUNT = SDIO_CmdInitStruct->DataInit.SDMABufferBoundary<<12;
    }
    SDIOx->BLOCK_COUNT |= (SDIO_CmdInitStruct->DataInit.BlockCount<<16) \
											 |(7<<12) \
                       |SDIO_CmdInitStruct->DataInit.BlockSize ;

    tmpreg |= SDIO_CMD_DMA_EN; //DMA
    tmpreg &= ~(0x30UL);  //MSBS DTDS
    tmpreg |= SDIO_CmdInitStruct->DataInit.TransferDir|SDIO_CmdInitStruct->DataInit.MultiSingleMode;
    tmpreg |= BIT21;  //CMD with data
  }

  SDIOx->CMD = tmpreg;

  tickstart = STD_GetTick();
	while((SDIOx->STATUS3 & BIT0) != 1)
	{
		if((STD_GetTick() - tickstart) > 100)
		{
			return STD_TIMEOUT;
		}
	}
	
	return STD_OK;
}

/**
  * @brief  Returns command index of last command for which response received.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @retval Returns the command index of the last command response received.
  */
uint8_t SDIO_GetCommandResponse(SDIO_TypeDef *SDIOx)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
	
  if(SDIOx->STATUS3 & SDIO_STATUS_CMD_INDEXERR)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Returns response received from the card for the last command.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SDIO_RESP: Specifies the SDIO response register. 
  *   This parameter can be one of the following values:
  *     @arg SDIO_RESP1: Response Register 1
  *     @arg SDIO_RESP2: Response Register 2
  *     @arg SDIO_RESP3: Response Register 3
  *     @arg SDIO_RESP4: Response Register 4
  * @retval The Corresponding response register value.
  */
uint32_t SDIO_GetResponse(SDIO_TypeDef *SDIOx, uint32_t SDIO_RESP)
{
  __IO uint32_t tmp = 0;

  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_SDIO_RESP(SDIO_RESP));

  if(SDIOx == SDIO0)
    tmp = SDIO0_RESP_ADDR + SDIO_RESP;
  if(SDIOx == SDIO1)
    tmp = SDIO1_RESP_ADDR + SDIO_RESP;
  
  return (*(__IO uint32_t *) tmp); 
}

/**
  * @brief  Read one data word from Rx register.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @retval Data received
  */
uint32_t SDIO_ReadData(SDIO_TypeDef *SDIOx)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
	
  return SDIOx->DATA;
}

/**
  * @brief  Enables or disables the VDD1 of SDIO peripheral.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  NewState : This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_VDD1Cmd(SDIO_TypeDef *SDIOx, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if(NewState == ENABLE)
  {
    SDIOx->CTRL1 |= BIT8;
  }
  else
  {
    SDIOx->CTRL1 &= ~BIT8;
  }
}

/**
  * @brief  Sets the VDD1 of SDIO peripheral.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  Volatage
  *             - SDIO_CTRL1_VDD1VOT_1_8V
  *             - SDIO_CTRL1_VDD1VOT_3_0V
  *             - SDIO_CTRL1_VDD1VOT_3_3V
  * @retval None
  */
void SDIO_SetVDD1Voltage(SDIO_TypeDef *SDIOx, uint16_t Volatage)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_SDIO_VDD1(Volatage));

  SDIOx->CTRL1 &= ~SDIO_CTRL1_VDD1VOT_Msk;
  SDIOx->CTRL1 |= Volatage;
}

/**
  * @brief  Enables or disables the VDD2 of SDIO peripheral.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  NewState : This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_VDD2Cmd(SDIO_TypeDef *SDIOx, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if(NewState == ENABLE)
    SDIOx->CTRL1 |= BIT12;
  else
    SDIOx->CTRL1 &= ~BIT12;
}

/**
  * @brief  Sets  the VDD2 of SDIO peripheral.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  Volatage
  *             - SDIO_CTRL1_VDD1VOT_1_8V
  *             - SDIO_CTRL1_VDD1VOT_3_0V
  *             - SDIO_CTRL1_VDD1VOT_3_3V
  * @retval None
  */
void SDIO_SetVDD2Voltage(SDIO_TypeDef *SDIOx, uint16_t Volatage)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_SDIO_VDD2(Volatage));

  SDIOx->CTRL1 &= ~SDIO_CTRL1_VDD2VOT_Msk;
  SDIOx->CTRL1 |= Volatage;
}

/**
  * @brief  Enables or disables the SDIO Clock.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  NewState: new state of the SDIO Clock. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_ClockCmd(SDIO_TypeDef *SDIOx, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  if(SDIOx == SDIO0)
  {
    if(NewState == ENABLE)
      SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO0,ENABLE);
    else
      SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO0,DISABLE);
  }
  else if(SDIOx == SDIO1)
  {
    if(NewState == ENABLE)
      SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO1,ENABLE);
    else
      SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO0,DISABLE);
  }
}

/**
  * @brief  Enables or disables the SDIO CRC.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  NewState: new state of the SDIO Clock. This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SDIO_CRCCheckCmd(SDIO_TypeDef *SDIOx, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
	
  if (NewState == ENABLE)
  {
    SDIOx->CMD |= SDIO_CMD_CRC_EN;
  }
  else
  {
    SDIOx->CMD &= ~SDIO_CMD_CRC_EN;
  }
}

/**
  * @brief  Enables or disables the SDIO interrupts.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SDIO_IT: specifies the SDIO interrupt sources to be enabled or disabled.
  *   This parameter can be one or a combination of the following values:
  *          SDIO_IT_CC: 
  *          SDIO_IT_TC: 
  *          SDIO_IT_DMA: DMA interrupt
  * @param  NewState: new state of the specified SDIO interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None 
  */
void SDIO_ITConfig(SDIO_TypeDef *SDIOx, uint32_t SDIO_IT, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
	
  SDIOx->INTEN = SDIO_IT;
}

/**
  * @brief  Enables or disables the status.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SDIO_Status: specifies the SDIO status to be enabled or disabled.
  *   This parameter can be one or a combination of the following values:
  *          SDIO_IT_CC: 
  *          SDIO_IT_TC: 
  *          SDIO_IT_DMA: DMA interrupt
  * @param  NewState: new state of the specified SDIO interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None 
  */
void SDIO_StatusConfig(SDIO_TypeDef *SDIOx, uint32_t SDIO_Status, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
  assert_parameters(IS_SDIO_STATUSMASK(SDIO_Status));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
	
  SDIOx->STATUS3_MASK = SDIO_Status;
}

/**
  * @brief  Checks whether the specified SDIO flag is set or not.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SDIO_FLAG: specifies the SDIO flag status.
  *   This parameter can be one or a combination of the following values:
  *          SDIO_FLAG_CMDSENT: 
  *          SDIO_FLAG_TRANComplete: 
  *          SDIO_FLAG_DMA: 
  *          SDIO_FLAG_WriterBuffer: 
  *          SDIO_FLAG_ReadBuffer: 
  *          SDIO_FLAG_InsertCard: 
  *          SDIO_FLAG_CMDTIMEOUT: 
  *          SDIO_FLAG_CMDCRCERR: 
  *          SDIO_FLAG_CMDENDBITERR: 
  *          SDIO_FLAG_CMDIndexERR: 
  *          SDIO_FLAG_ResponseERR: 
  * @retval None 
  */
FlagStatus SDIO_GetFlagStatus(SDIO_TypeDef *SDIOx, uint32_t SDIO_FLAG)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
	
  if (SDIOx->STATUS3 & SDIO_FLAG)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Checks whether the specified SDIO interrupt flag is set or not.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SDIO_IT: specifies the SDIO interrupt status.
  *   This parameter can be one of the following values:
  *          SDIO_INTEN_CMDSENT
  *          SDIO_INTEN_TRANComplete 
  *          SDIO_INTEN_BlockGap
  *          SDIO_INTEN_DMA
  *          SDIO_INTEN_WriterBuffer 
  *          SDIO_INTEN_ReadBuffer 
  *          SDIO_INTEN_InsertCard 
  *          SDIO_FINTEN_ERR 
  *          SDIO_INTEN_CMDTIMEOUT
  *          SDIO_INTEN_CMDCRCERR 
  *          SDIO_INTEN_CMDENDBITERR 
  *          SDIO_INTEN_CMDIndexERR 
  *          SDIO_INTEN_ResponseERR 
  *          SDIO_INTEN_ALL 
  * @retval SET or RESET 
  */
ITStatus SDIO_GetITStatus(SDIO_TypeDef *SDIOx, uint32_t SDIO_IT)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
	
  if (SDIOx->STATUS3 & SDIO_IT)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clear the specified SDIO interrupt flag.
  * @param  SDIOx : where x can be 0 to 1 to select the SDIO peripheral.
  * @param  SDIO_IT: specifies the SDIO interrupt status.
  *   This parameter can be one or a combination of the following values:
  *          SDIO_INTEN_CMDSENT
  *          SDIO_INTEN_TRANComplete 
  *          SDIO_INTEN_BlockGap
  *          SDIO_INTEN_DMA
  *          SDIO_INTEN_WriterBuffer 
  *          SDIO_INTEN_ReadBuffer 
  *          SDIO_INTEN_InsertCard 
  *          SDIO_FINTEN_ERR 
  *          SDIO_INTEN_CMDTIMEOUT
  *          SDIO_INTEN_CMDCRCERR 
  *          SDIO_INTEN_CMDENDBITERR 
  *          SDIO_INTEN_CMDIndexERR 
  *          SDIO_INTEN_ResponseERR 
  *          SDIO_INTEN_ALL 
  * @retval None
  */
void SDIO_ClearITStatus(SDIO_TypeDef *SDIOx, uint32_t SDIO_IT)
{
  /* Check parameters */
  assert_parameters(IS_SDIO_ALL_INSTANCE(SDIOx));
	
  SDIOx->STATUS3 = SDIO_IT;
}

/**
  * @}
  */

/*********************************** END OF FILE ******************************/
