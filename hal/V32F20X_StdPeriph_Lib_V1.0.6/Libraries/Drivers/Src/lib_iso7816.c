/**
  ******************************************************************************
  * @file    lib_iso7816.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-07-06
  * @brief   ISO7816 library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_iso7816.h"
#include "lib_clk.h"

/*
// ISO7816_CFG
*/
#define ISO7816_CFG_RXACKSET           (0x10000UL)
#define ISO7816_CFG_TXRTYCNT_MASK      (0xF000UL)
#define ISO7816_CFG_LSB                (0x800UL)
#define ISO7816_CFG_AUTORXACK          (0x200UL)
#define ISO7816_CFG_ACKLEN             (0x10UL)
#define ISO7816_CFG_CHKP               (0x2UL)
#define ISO7816_CFG_EN                 (0x1UL)
#define ISO7816_CFG_EN_CLR             REG_BIT_NOT(ISO7816_CFG_EN)
/*
// ISO7816_BAUDDIVH
*/
#define ISO7816_BAUDDIVH_BAUDDIVH_MASK (0xFFUL)
/*
// ISO7816_BAUDDIVL
*/
#define ISO7816_BAUDDIVL_BAUDDIVL_MASK (0xFFUL)
/*
// ISO7816_CLK
*/
#define ISO7816_CLK_CLKEN              (0x80UL)
#define ISO7816_CLK_CLKDIV_MASK        (0x7FUL)
#define ISO7816_CLK_CLKDIV_CLR         REG_BIT_NOT(ISO7816_CLK_CLKDIV_MASK)
#define ISO7816_CLK_CLKEN_CLR          REG_BIT_NOT(ISO7816_CLK_CLKEN)
/*
// ISO7816_INFO
*/
#define ISO7816_INFO_CHKSUM            (0x2UL)
#define ISO7816_INFO_RXACK             (0x1UL)
//registers default reset values
#define ISO7816_INFO_RC_MASK           (0x3ECUL)
#define ISO7816_BAUDDIVL_RSTVAL        (0UL)
#define ISO7816_BAUDDIVH_RSTVAL        (0UL)
#define ISO7816_CFG_RSTVAL             (0x400)
#define ISO7816_CLK_RSTVAL             (0UL)

/* Exported Functions ------------------------------------------------------- */

/**
  * @brief  Initializes the ISO7816 peripheral registers to their default reset values.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @retval None
  */
void ISO7816_DeInit(ISO7816_Type *ISO7816x)
{
  /* Check parameters */
//  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  ISO7816x->CFG &= ISO7816_CFG_EN_CLR;
  ISO7816x->INFO = ISO7816_INFO_RC_MASK;  /* clear interrupt flag */
  ISO7816x->BAUDDIVH = ISO7816_BAUDDIVH_RSTVAL;
  ISO7816x->BAUDDIVL = ISO7816_BAUDDIVL_RSTVAL;
  ISO7816x->CFG = ISO7816_CFG_RSTVAL;
  ISO7816x->CLK = ISO7816_CLK_RSTVAL;
}

/**
  * @brief  Fills each InitStruct member with its default value.
  * @param  InitStruct: pointer to an ISO7816_InitType structure which will be initialized.
  * @retval None
  */
void ISO7816_StructInit(ISO7816_InitType *InitStruct)
{
  /*--------------- Reset ISO7816 init structure parameters values ---------------*/
  /* Initialize the FirstBit member */ 
  InitStruct->FirstBit = ISO7816_FIRSTBIT_MSB;
  /* Initialize the Parity member */ 
  InitStruct->Parity = ISO7816_PARITY_EVEN;
  InitStruct->SerialClock = 48000000UL;
  /* Initialize the Baudrate member */ 
  InitStruct->Baudrate = 9600;
  /* Initialize the TXRetry member */ 
  InitStruct->TXRetry = ISO7816_TXRTY_0;
  /* Initialize the RXACKLength member */ 
  InitStruct->RXACKLength = ISO7816_RXACKLEN_2;
  /* Initialize the TXNACKLength member */ 
  InitStruct->TXNACKLength = ISO7816_TXNACKLEN_0;
}

/**
  * @brief  Initializes ISO7816.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @param  ISO7816_InitStruct:iso7816 configuration.
  *            FirstBit:
  *                ISO7816_FIRSTBIT_MSB
  *                ISO7816_FIRSTBIT_LSB
  *            Parity:
  *                ISO7816_PARITY_EVEN
  *                ISO7816_PARITY_ODD
  *            Baudrate: baudrate value to configure, 200UL ~ 2625000UL
  *            TXRetry:
  *                ISO7816_TXRTY_0 ~ ISO7816_TXRTY_15
  *            RXACKLength:
  *                ISO7816_RXACKLEN_2
  *                ISO7816_RXACKLEN_1
  *            TXNACKLength:
  *                ISO7816_TXNACKLEN_0
  *                ISO7816_TXNACKLEN_1
  *                ISO7816_TXNACKLEN_2
  * @retval None
  */
void ISO7816_Init(ISO7816_Type *ISO7816x, ISO7816_InitType *ISO7816_InitStruct)
{
  uint32_t tmp;
  uint16_t div;
  uint32_t pclk;
  
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_FIRSTBIT(ISO7816_InitStruct->FirstBit));
  assert_parameters(IS_ISO7816_PARITY(ISO7816_InitStruct->Parity));
  assert_parameters(IS_ISO7816_BAUDRATE(ISO7816_InitStruct->Baudrate));
  assert_parameters(IS_ISO7816_TXRTY(ISO7816_InitStruct->TXRetry));
  assert_parameters(IS_ISO7816_RXACKLEN(ISO7816_InitStruct->RXACKLength));
  assert_parameters(IS_ISO7816_TXNACKLEN(ISO7816_InitStruct->TXNACKLength));
  assert_parameters(IS_ISO7816_SERIALCLK(ISO7816_InitStruct->SerialClock));

  tmp = ISO7816x->CFG;
  tmp &= ~(ISO7816_CFG_ACKLEN\
          |ISO7816_CFG_AUTORXACK\
          |ISO7816_CFG_LSB\
          |ISO7816_CFG_CHKP\
          |ISO7816_CFG_RXACKSET\
          |ISO7816_CFG_TXRTYCNT_MASK);
  tmp |= (ISO7816_InitStruct->FirstBit\
         |ISO7816_InitStruct->Parity\
         |ISO7816_InitStruct->TXRetry\
         |ISO7816_InitStruct->RXACKLength\
         |ISO7816_InitStruct->TXNACKLength);
  ISO7816x->CFG = tmp;

  pclk = ISO7816_InitStruct->SerialClock;
  div = 0x10000 - (pclk/ISO7816_InitStruct->Baudrate);
  ISO7816x->BAUDDIVH = (div>>8) & ISO7816_BAUDDIVH_BAUDDIVH_MASK;
  ISO7816x->BAUDDIVL = div & ISO7816_BAUDDIVL_BAUDDIVL_MASK;
}

/**
  * @brief  Enables or disables ISO7816.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @param  NewState: new state of the ISO7816 peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void ISO7816_Cmd(ISO7816_Type *ISO7816x, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState == ENABLE)
  {
    ISO7816x->CFG |= ISO7816_CFG_EN;
  }
  else
  {
    ISO7816x->CFG &= ISO7816_CFG_EN_CLR;
  }
}

/**
  * @brief  Configures ISO7816 clock divider.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @param  Prescaler:1~128
  * @retval None
  */
void ISO7816_CLKDIVConfig(ISO7816_Type *ISO7816x, uint32_t Prescaler)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_PRESCALER(Prescaler));  
  
  tmp = ISO7816x->CLK & ISO7816_CLK_CLKDIV_CLR;
  tmp |= ((Prescaler - 1)&ISO7816_CLK_CLKDIV_MASK);
  ISO7816x->CLK = tmp;
}

/**
  * @brief  Enables or disables ISO7816 clock output function.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163 
  * @param  NewState: new state of the ISO7816 clock output function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ISO7816_CLKOutputCmd(ISO7816_Type *ISO7816x, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    ISO7816x->CLK |= ISO7816_CLK_CLKEN;
  }
  else
  {
    ISO7816x->CLK &= ISO7816_CLK_CLKEN_CLR;
  }
}

/**
  * @brief  Reads ISO7816 data.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163 
  * @retval The received data.
  */
uint8_t ISO7816_ReceiveData(ISO7816_Type *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));

  return ISO7816x->DATA;
}

/**
  * @brief  Writes ISO7816 data.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163 
  * @param  ch: data to send
  * @retval None
  */
void ISO7816_SendData(ISO7816_Type *ISO7816x, uint8_t ch)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  ISO7816x->DATA = ch;
}

/**
  * @brief  ENables or disables ISO7816 interrupt.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @param  INTMask: specifies the ISO7816 interrupt source to be enabled or disabled.
  *         This parameter can be any combination of the following values
  *             ISO7816_INT_TXRTYERR
  *             ISO7816_INT_RXOV
  *             ISO7816_INT_RX
  *             ISO7816_INT_TXDONE
  *             ISO7816_INT_RXERR
  * @param  NewState: new state of the ISO7816 interrupt source.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ISO7816_INTConfig(ISO7816_Type *ISO7816x, uint32_t INTMask, FunctionalState NewState)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_INTC(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState == ENABLE)
  {
    ISO7816x->CFG |= INTMask;
  }
  else
  {
    ISO7816x->CFG &= ~INTMask;
  }
}

/**
  * @brief  Gets ISO7816 interrupt state.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @param  INTMask: specifies the ISO7816 interrupt source to check.
  *         This parameter can be one of the following values:
  *             ISO7816_INT_TXRTYERR
  *             ISO7816_INT_TXDONE
  *             ISO7816_INT_RXOV
  *             ISO7816_INT_RX
  *             ISO7816_INT_RXERR
  * @retval The new state of ISO7816 interrupt (SET or RESET).
  */
ITStatus ISO7816_GetINTStatus(ISO7816_Type *ISO7816x, uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_INTR(INTMask));
  
  if (ISO7816x->INFO & INTMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears ISO7816 interrupt state.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @param  INTMask: specifies the ISO7816 interrupt source to check.
  *         This parameter can be any combination of the following values
  *             ISO7816_INT_TXRTYERR
  *             ISO7816_INT_TXDONE
  *             ISO7816_INT_RXOV
  *             ISO7816_INT_RX
  *             ISO7816_INT_RXERR
  * @retval None
  */
void ISO7816_ClearINTStatus(ISO7816_Type *ISO7816x, uint32_t INTMask)
{
    uint32_t tmp;
    
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x)); 
  assert_parameters(IS_ISO7816_INTC(INTMask));
  
  tmp = ISO7816x->INFO;
  tmp &= ~ISO7816_INFO_RC_MASK;
  tmp |= INTMask;
  ISO7816x->INFO = tmp;
}

/**
  * @brief  Gets ISO7816 peripheral flag.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @param  FlagMask: specifies the ISO7816 flag to check.
            This parameter can be: ISO7816_FLAG_DMATXDONE
  * @retval The new state of ISO7816 flag (SET or RESET).
  */
FlagStatus ISO7816_GetFlag(ISO7816_Type *ISO7816x, uint32_t FlagMask)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_FLAG(FlagMask));  
  
  if (ISO7816x->INFO & FlagMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears ISO7816 peripheral flag.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @param  FlagMask: specifies the ISO7816 flag to clear.
            This parameter can be: ISO7816_FLAG_DMATXDONE
  * @retval None
  */
void ISO7816_ClearFlag(ISO7816_Type *ISO7816x, uint32_t FlagMask)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x)); 
  assert_parameters(IS_ISO7816_FLAG(FlagMask));  

  tmp = ISO7816x->INFO;
  tmp &= ~ISO7816_INFO_RC_MASK;
  tmp |= FlagMask;
  ISO7816x->INFO = tmp;
}

/**
  * @brief  Gets last transmited ACK.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @retval ACK value
  */
uint8_t ISO7816_GetLastTransmitACK(ISO7816_Type *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  if (ISO7816x->INFO&ISO7816_INFO_RXACK)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Gets last received check sum bit.
  * @param  ISO7816x: select the ISO7816 peripheral.
  *         CM0 : ISO78162 ~ ISO78163
  *         CM33 : ISO78160 ~ ISO78163
  * @retval CHKSUM bit value
  */
uint8_t ISO7816_GetLastReceiveCHKSUM(ISO7816_Type *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  if (ISO7816x->INFO&ISO7816_INFO_CHKSUM)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*********************************** END OF FILE ******************************/
