/**
  ******************************************************************************
  * @file    lib_bspi.c
  * @author  VT Application Team
  * @version V3.5.0
  * @date    2021-10-18
  * @brief   This file provides all the BSPI firmware functions..
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_bspi.h"

#define SPI_MISC_RSTValue    (0UL)

#define SPI_STS_WREN_Mask    (0xFFFF0000UL)
#define SPI_STS_WREN_ITLVL   (0x00700000UL)

#define SPI_STS_ITEN_SET     (0x40004000UL)
#define SPI_STS_ITEN_CLR     (0x40000000UL)
#define SPI_STS_ITSTS_CLR    (0x80008000UL)


#define SPI_SET_STSREG(x)    (x | (x<<16))
#define SPI_CLR_STSREG(x)    (0 | (x<<16))
#define SPI_CTRL_LSBF        (0x1000UL)
#define SPI_CTRL_SCKSEL_MASK (0x7UL)


/**
  * @brief  Reset SPI device.
  * @param  SPIx:BSPI0~BSPI5
  * @retval None
  */
void BSPI_DeviceInit(BSPI_Type *SPIx)
{
  __IO uint32_t dummy_data = 0UL;
 
  UNUSED(dummy_data);

  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx));
 
  if(SPIx==BSPI0)
	{
		SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI0);
	}
	else if(SPIx==BSPI1)
	{
	  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI1);
	}
	else if(SPIx==BSPI2)
	{
	  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI2);
	}
	else if(SPIx==BSPI3)
	{
	 SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI3);
	}
	else if(SPIx==BSPI4)
	{
	  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI4);
	}	
	else if(SPIx==BSPI5)
	{
	  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_BSPI5);
	}	
  while(SYSCFG1->SW_RST_REQ);	

  
  /* Disable SPI */
  SPIx->CTRL = 0;
  /* SPI soft reset */
  SPIx->CTRL |= SPI_CTRL_SPIRST;
  SPIx->CTRL &= ~SPI_CTRL_SPIRST;
  /* Clear flag */
  dummy_data = SPIx->RXDAT;
  SPIx->TXSTS = SPI_STS_WREN_Mask | SPI_TXSTS_TXIF;
  SPIx->RXSTS = SPI_STS_WREN_Mask | SPI_RXSTS_RXIF;
  /* write default values */
  SPIx->MISC = SPI_MISC_RSTValue;
}

/**
  * @brief  Fills each BSPI_InitType member with its default value.
  * @param  InitStruct: pointer to an BSPI_InitType structure which will be initialized.
  * @retval None
  */
void BSPI_StructInit(BSPI_InitType *InitStruct)
{
  /*--------------- Reset SPI init structure parameters values ---------------*/
  /* Initialize the ClockDivision member */
  InitStruct->ClockDivision = SPI_CLKDIV_2;
  /* Initialize the CSNSoft member */
  InitStruct->CSNSoft = SPI_CSNSOFT_DISABLE;
  /* Initialize the Mode member */
  InitStruct->Mode = SPI_MODE_MASTER; 
  /* Initialize the SPH member */
  InitStruct->SPH = SPI_SPH_0; 
  /* Initialize the SPO member */
  InitStruct->SPO = SPI_SPO_0; 
  /* Initialize the SWAP member */
  InitStruct->SWAP = SPI_SWAP_DISABLE; 
}

/**
  * @brief  SPI initialization.
  * @param  SPIx:BSPI0~BSPI5
            InitStruct: SPI configuration.
                Mode:
                    SPI_MODE_MASTER
                    SPI_MODE_SLAVE
                SPH:
                    SPI_SPH_0
                    SPI_SPH_1
                SPO:
                    SPI_SPO_0
                    SPI_SPO_1
                ClockDivision:
                    SPI_CLKDIV_2
                    SPI_CLKDIV_4
                    SPI_CLKDIV_8
                    SPI_CLKDIV_16
                    SPI_CLKDIV_32
                    SPI_CLKDIV_64
                    SPI_CLKDIV_128
                CSNSoft:
                    SPI_CSNSOFT_ENABLE
                    SPI_CSNSOFT_DISABLE
                SWAP:
                    SPI_SWAP_ENABLE
                    SPI_SWAP_DISABLE
  * @retval None
  */
void BSPI_Init(BSPI_Type *SPIx, BSPI_InitType *SPI_InitStruct)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx));  
  assert_parameters(IS_BSPI_MODE(SPI_InitStruct->Mode));
  assert_parameters(IS_BSPI_SPH(SPI_InitStruct->SPH));
  assert_parameters(IS_BSPI_SPO(SPI_InitStruct->SPO));
  assert_parameters(IS_BSPI_CLKDIV(SPI_InitStruct->ClockDivision));
  assert_parameters(IS_BSPI_CSN(SPI_InitStruct->CSNSoft));
  assert_parameters(IS_BSPI_SWAP(SPI_InitStruct->SWAP));
    
 tmp = SPIx->CTRL;
  tmp &= ~(SPI_CTRL_MOD\
          |SPI_CTRL_LSBF\
          |SPI_CTRL_SCKPHA\
          |SPI_CTRL_SCKPOL\
          |SPI_CTRL_CSGPIO\
          |SPI_CTRL_SWAP\
          |SPI_CTRL_SCKSEL_MASK);
  tmp |= (SPI_InitStruct->Mode\
         |SPI_InitStruct->SPH\
         |SPI_InitStruct->SPO\
         |SPI_InitStruct->CSNSoft\
         |SPI_InitStruct->SWAP\
         |SPI_InitStruct->ClockDivision);
  SPIx->CTRL = tmp;
}

/**
  * @brief  Enables or disables SPI.
  * @param  SPIx:BSPI0~BSPI5
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void BSPI_Cmd(BSPI_Type *SPIx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState == ENABLE)
    SPIx->CTRL |= SPI_CTRL_SPIEN;
  else
    SPIx->CTRL &= ~SPI_CTRL_SPIEN;
}

/**
  * @brief  SPI interrupt config.
  * @param  SPIx:BSPI0~BSPI5
            INTMask: can use the '|' operator
                SPI_INT_TX     
                SPI_INT_RX
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void BSPI_INTConfig(BSPI_Type *SPIx, uint32_t INTMask, uint32_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_BSPI_INT(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (INTMask & 0x80000000)
  {
    if (NewState == ENABLE)
      SPIx->TXSTS = SPI_STS_ITEN_SET;
    else
      SPIx->TXSTS = SPI_STS_ITEN_CLR;
  }
  else
  {  
    INTMask &= 0xFFFF;
    tmp = SPIx->RXSTS;
    tmp &= ~SPI_RXSTS_RXIF;
    if (NewState == ENABLE)
    {
      tmp |= INTMask;
      SPIx->RXSTS = tmp;
    }
    else
    {
      tmp &= ~INTMask;
      SPIx->RXSTS = tmp;
    }
  }
}

/**
  * @brief  Get status flag.
  * @param  SPIx:BSPI0~BSPI5
            Status:
                SPI_STS_TXIF   
                SPI_STS_TXEMPTY 
                SPI_STS_TXFUR   
                SPI_STS_RXIF    
                SPI_STS_RXFULL  
                SPI_STS_RXFOV   
                SPI_STS_BSY     
                SPI_STS_RFF     
                SPI_STS_RNE     
                SPI_STS_TNF     
                SPI_STS_TFE     
  * @retval Flag status.
  */
uint8_t BSPI_GetStatus(BSPI_Type *SPIx, uint32_t Status)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_BSPI_STSR(Status));  
  
  if ((Status&0xE0000000) == 0x80000000)
  {
    if (Status&SPIx->TXSTS)
      return 1;
    else
      return 0;
  }
  else if ((Status&0xE0000000) == 0x40000000)
  {
    if (Status&SPIx->RXSTS)
      return 1;
    else
      return 0;
  }
  else
  {
    if (Status&SPIx->MISC)
      return 1;
    else
      return 0;
  }
}

/**
  * @brief  Clear status flag.
  * @param  SPIx:BSPI0~BSPI5
            Status: can use the '|' operator
                SPI_STS_TXIF     
                SPI_STS_RXIF        
  * @retval None
  */
void BSPI_ClearStatus(BSPI_Type *SPIx, uint32_t Status)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_BSPI_STSC(Status));
    
  if (Status & 0x80000000)
  {
    SPIx->TXSTS = SPI_STS_ITSTS_CLR;
  }
  if (Status & 0x40000000)
  {   
    Status &= 0xFFFF;
    SPIx->RXSTS |= Status;
  }
}

/**
  * @brief  Load send data register.
  * @param  SPIx:BSPI0~BSPI5
            ch: data write to send data register
  * @retval None
  */
void BSPI_SendData(BSPI_Type *SPIx, uint8_t ch)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  
  SPIx->TXDAT = ch;
}

/**
  * @brief  Read receive data register.
  * @param  SPIx:BSPI0~BSPI5
  * @retval receive data value
  */
uint8_t BSPI_ReceiveData(BSPI_Type *SPIx)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  
  return (SPIx->RXDAT);
}

/**
  * @brief  Transmit fifo level configure.
  * @param  SPIx:BSPI0~BSPI5
            FIFOLevel:
                SPI_TXFLEV_0
                SPI_TXFLEV_1
                SPI_TXFLEV_2 
                SPI_TXFLEV_3 
                SPI_TXFLEV_4 
                SPI_TXFLEV_5 
                SPI_TXFLEV_6 
                SPI_TXFLEV_7 
  * @retval None
  */
void BSPI_TransmitFIFOLevelConfig(BSPI_Type *SPIx, uint32_t FIFOLevel)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_BSPI_TXFLEV(FIFOLevel));
    
  SPIx->TXSTS = SPI_STS_WREN_ITLVL | FIFOLevel;
}

/**
  * @brief  Receive fifo level configure.
  * @param  SPIx:BSPI0~BSPI5
            FIFOLevel:
                SPI_RXFLEV_0
                SPI_RXFLEV_1
                SPI_RXFLEV_2 
                SPI_RXFLEV_3 
                SPI_RXFLEV_4 
                SPI_RXFLEV_5 
                SPI_RXFLEV_6 
                SPI_RXFLEV_7 
  * @retval None
  */
void BSPI_ReceiveFIFOLevelConfig(BSPI_Type *SPIx, uint32_t FIFOLevel)
{
  uint32_t tmp;
    
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_BSPI_RXFLEV(FIFOLevel));
  
  tmp = SPIx->RXSTS;
  tmp &= ~(SPI_RXSTS_RXFLEV | SPI_RXSTS_RXIF);
  tmp |= FIFOLevel;
  SPIx->RXSTS = tmp;
}

/**
  * @brief  Get transmit fifo level.
  * @param  SPIx:BSPI0~BSPI5
  * @retval Transmit fifo level.
  */
uint8_t BSPI_GetTransmitFIFOLevel(BSPI_Type *SPIx)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx)); 
  
  return (SPIx->TXSTS & SPI_TXSTS_TXFFLAG);
}

/**
  * @brief  Get receive fifo level.
  * @param  SPIx:BSPI0~BSPI5
  * @retval Receive fifo level.
  */
uint8_t BSPI_GetReceiveFIFOLevel(BSPI_Type *SPIx)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx));  

  return (SPIx->RXSTS & SPI_RXSTS_RXFFLAG);
}

/**
  * @brief  FIFO smart mode.
  * @param  SPIx:BSPI0~BSPI5
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void BSPI_SmartModeCmd(BSPI_Type *SPIx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx));  
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SPIx->MISC |= SPI_MISC_SMART;
  }
  else
  {
    SPIx->MISC  &= ~SPI_MISC_SMART;
  }
}

/**
  * @brief  FIFO over write mode.
  * @param  SPIx:BSPI0~BSPI5
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void BSPI_OverWriteModeCmd(BSPI_Type *SPIx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_BSPI_ALL_INSTANCE(SPIx));  
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SPIx->MISC  |= SPI_MISC_OVER;
  }
  else
  {
    SPIx->MISC  &= ~SPI_MISC_OVER;
  }
}

/******************* (C) COPYRIGHT Vango Technologies, Inc *****END OF FILE****/
