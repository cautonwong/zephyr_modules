/**
  ******************************************************************************
  * @file    lib_uart.c 
  * @author  Application Team
  * @version V1.0
  * @date    2021-10-18
  * @brief   UART library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_uart.h"

/*
// UART_DLAB register
*/
#define UART_DLAB_EN                   (0x80UL)
#define UART_DLAB_EN_CLR               REG_BIT_NOT(UART_DLAB_EN)
/*
// UART_LCR register
*/
#define UART_LCR_PARITY_MASK           (0x38UL)
#define UART_LCR_STOPBIT               (0x04UL)
#define UART_LCR_DATALEN_MASK          (0x03UL)
/*
// UART_FCR register
*/
#define UART_FCR_FIFOEN                (0x1UL)
#define UART_FCR_RXFIFORESET           (1UL << 1)
#define UART_FCR_TXFIFORESET           (1UL << 2)
#define UART_FCR_RT_MASK               (3UL << 6)
/*
// UART_LSR register
*/
#define UART_LSR_DR                    (1UL << 0)
#define UART_LSR_OE                    (1UL << 1)
#define UART_LSR_PE                    (1UL << 2)
#define UART_LSR_FE                    (1UL << 3)
#define UART_LSR_TEMT                  (1UL << 6)
#define UART_LSR_RFE                   (1UL << 7)
/*
// UART_IIR register
*/
#define UART_IIR_XFIFOR_MASK           (0xFUL)
#define UART_IIR_XFIFOR_BUSY_DETECT    (0x7UL)
#define UART_IIR_XFIFOR_RXFIFO_TIMEOUT (0xCUL)
#define UART_IIR_RT_FIFOEN             (3UL << 6)
/*
// UART_MCR register
*/
#define UART_MCR_IREN                  (1UL << 6)
#define UART_MCR_IREN_CLR              REG_BIT_NOT(UART_MCR_IREN)
/*
// UART_DLH register
*/
#define UART_DLH_DLH_MASK              (0xFFUL)
/*
// UART_DLL register
*/
#define UART_DLL_DLL_MASK              (0xFFUL)

// Registers' reset value
#define UART_MCR_RSTVAL                (0UL)
#define UART_DLL_RSTVAL                (0UL)
#define UART_DLH_RSTVAL                (0UL)
#define UART_LCR_RSTVAL                (0UL)
#define UART_IER_RSTVAL                (0UL)
#define UART_FCR_RSTVAL                (0UL)

#define UART_BASEADDR_OFFSET           (0x800UL)

/* Exported Functions ------------------------------------------------------- */

/**
  * @brief  Initializes the UART peripheral registers to their default reset values.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @retval None
  */
void UART_DeInit(UART_Type *UARTx)
{
  __IO uint32_t tmp = 0UL;

  UNUSED(tmp);

  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  
  UARTx->MCR = UART_MCR_RSTVAL;
  UARTx->LCR |= UART_DLAB_EN;
  UARTx->DLL = UART_DLL_RSTVAL;
  UARTx->DLH = UART_DLH_RSTVAL;
  UARTx->LCR &= UART_DLAB_EN_CLR;
  UARTx->LCR = UART_LCR_RSTVAL;
  UARTx->IER = UART_IER_RSTVAL;
  /* clear flag */
  tmp = UARTx->LSR;
  tmp = UARTx->USR;
  /* reset FIFO */
  UARTx->FCR |= (UART_FCR_RXFIFORESET|UART_FCR_TXFIFORESET);
  UARTx->FCR = UART_FCR_RSTVAL;
}

/**
  * @brief  Fills each UART_InitType member with its default value.
  * @param  InitStruct: pointer to an UART_InitType structure which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitType *UART_InitStruct)
{
  UART_InitStruct->Baudrate    = 9600UL;
  UART_InitStruct->SerialClock = 48000000UL;
  UART_InitStruct->Parity      = UART_PARITY_NONE;
  UART_InitStruct->DataLength  = UART_DATALEN_8B;
  UART_InitStruct->StopBit     = UART_STOPBIT_1;
}

/**
  * @brief  UART initialization.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @param  UART_InitStruct:UART configuration.
  *          Baudrate: Baudrate value
  *          Parity:
  *               UART_PARITY_EVEN 
  *               UART_PARITY_ODD
  *               UART_PARITY_0
  *               UART_PARITY_1
  *               UART_PARITY_NONE
  *           DataLength:
  *               UART_DATALEN_8B
  *               UART_DATALEN_7B
  *               UART_DATALEN_6B
  *               UART_DATALEN_5B
  *           StopBit:
  *               UART_STOPBIT_1
  *               UART_STOPBIT_1_5
  *               UART_STOPBIT_2
  * @retval None
  */
void UART_Init(UART_Type *UARTx, UART_InitType *UART_InitStruct)
{
  uint32_t tmpreg = 0, reg = 0;
  uint64_t tmpvalue;
  uint32_t fractionaldivider, integerdivider;
  
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_SERIALCLK(UART_InitStruct->SerialClock));
  assert_parameters(IS_UART_PARITY(UART_InitStruct->Parity));
  assert_parameters(IS_UART_DATALEN(UART_InitStruct->DataLength));
  assert_parameters(IS_UART_STOPBIT(UART_InitStruct->StopBit));
  assert_parameters(UART_InitStruct->Baudrate > 0);
  assert_parameters((UART_InitStruct->SerialClock/UART_InitStruct->Baudrate/16) > 0);

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
  if ((UARTx == UART0)\
    ||(UARTx == UART1)\
    ||(UARTx == UART2)\
    ||(UARTx == UART3)\
    ||(UARTx == UART4)\
    ||(UARTx == UART5)\
    ||(UARTx == UART6)\
    ||(UARTx == UART7)\
    ||(UARTx == UART8)\
    ||(UARTx == UART9)\
    ||(UARTx == UART10)\
    ||(UARTx == UART11)\
    ||(UARTx == UART12)\
    ||(UARTx == UART13))
  {
    SYSCFG0_FlexcommUARTRxCmd((FLEXCOMM_Type)UART_GET_INDEX(UARTx), DISABLE);
  }
#endif
  
  /* integerdivider */
  tmpvalue = ((25*(uint64_t)UART_InitStruct->SerialClock) / (4*((uint64_t)UART_InitStruct->Baudrate)));
  integerdivider = (uint32_t)tmpvalue;
  tmpreg = integerdivider / 100;
  UARTx->LCR |= UART_DLAB_EN;
  UARTx->DLH = ((tmpreg>>8) & UART_DLH_DLH_MASK);
  UARTx->DLL = (tmpreg & UART_DLL_DLL_MASK);
  /* fractionaldivider */
  fractionaldivider = integerdivider - (100 * tmpreg);
  fractionaldivider = (((fractionaldivider * 64) + 50) / 100) & ((uint8_t)0x3F);
  UARTx->DLF = fractionaldivider;

  UARTx->LCR &= (~UART_DLAB_EN);
  
  reg &= ~(UART_LCR_PARITY_MASK  \
          |UART_LCR_DATALEN_MASK \
          |UART_LCR_STOPBIT);
  reg |= (UART_InitStruct->Parity \
         |UART_InitStruct->DataLength \
         |UART_InitStruct->StopBit);
  UARTx->LCR = reg;
  
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
  if ((UARTx == UART0)\
    ||(UARTx == UART1)\
    ||(UARTx == UART2)\
    ||(UARTx == UART3)\
    ||(UARTx == UART4)\
    ||(UARTx == UART5)\
    ||(UARTx == UART6)\
    ||(UARTx == UART7)\
    ||(UARTx == UART8)\
    ||(UARTx == UART9)\
    ||(UARTx == UART10)\
    ||(UARTx == UART11)\
    ||(UARTx == UART12)\
    ||(UARTx == UART13))
  {
    SYSCFG0_FlexcommUARTRxCmd((FLEXCOMM_Type)UART_GET_INDEX(UARTx), ENABLE);
  }
#endif
}

/**
  * @brief  Configures UART receive FIFO.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @param  Level: receive FIFO interrupt level.
  *         This parameter can be one of the following values:
  *           UART_FIFOLEVEL_1 
  *           UART_FIFOLEVEL_4 
  *           UART_FIFOLEVEL_8 
  *           UART_FIFOLEVEL_14
  * @param  NewState: new state of the specified UART receive FIFO.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_ReceiveFIFOConfig(UART_Type *UARTx, uint32_t Level, FunctionalState NewState)
{
  uint32_t tmp = 0U;
  
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_RXFLEV(Level));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    tmp |= UART_FCR_FIFOEN;
  }
  tmp |= Level;
  UARTx->FCR = tmp;
}

/**
  * @brief  Enables or disables UART specified interrupt.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @param  INTMask: specifies the UART interrupt source to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  *                 UART_INT_RX
  *                 UART_INT_TXE
  *                 UART_INT_RXERR
  * @param  NewState: new state of the specified UART receive FIFO.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_INTConfig(UART_Type *UARTx, uint32_t INTMask, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_INTEN(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    UARTx->IER |= INTMask;
  }
  else
  {
    UARTx->IER &= ~INTMask;
  }
}

/**
  * @brief  Gets UART specified interrupt status.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @param  INTMask: specifies the UART interrupt source to check.
  *         This parameter can be one of the following values:
  *             UART_INT_RX
  *             UART_INT_TXE
  *             UART_INT_RXERR
  *             UART_INT_RXERR_OV
  *             UART_INT_RXERR_PE
  *             UART_INT_RXERR_FE
  *             UART_INT_BUSY_DETECT
  *             UART_INT_RXFIFO_TIMEOUT
  * @retval  The new state of UART specified interrupt status (SET or RESET).
  */
ITStatus UART_GetINTStatus(UART_Type *UARTx, uint32_t INTMask)
{
  uint32_t tmp = 0UL;
  
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_INTGET(INTMask));
  
  switch (INTMask)
  {
    default:
      break;
    
    case UART_INT_RX:
      tmp = UARTx->LSR & UART_LSR_DR;
      break;
    
    case UART_INT_TXE:
      tmp = UARTx->LSR & UART_LSR_TEMT;
      break;
    
    case UART_INT_RXERR:
      tmp = UARTx->LSR & UART_LSR_RFE;
      break;
    
    case UART_INT_RXERR_OV:
      tmp = UARTx->LSR & UART_LSR_OE;
      break;
    
    case UART_INT_RXERR_PE:
      tmp = UARTx->LSR & UART_LSR_PE;
      break;
    
    case UART_INT_RXERR_FE:
      tmp = UARTx->LSR & UART_LSR_FE;
      break;
    
    case UART_INT_BUSY_DETECT:
      if ((UARTx->IIR & UART_IIR_XFIFOR_MASK) == UART_IIR_XFIFOR_BUSY_DETECT)
      {
        tmp = 1;
      }
      break;
      
    case UART_INT_RXFIFO_TIMEOUT:
      if ((UARTx->IIR & UART_IIR_XFIFOR_MASK) == UART_IIR_XFIFOR_RXFIFO_TIMEOUT)
      {
        tmp = 1;
      }
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
  * @brief  Clears UART specified interrupt status.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @param  INTMask: specifies the UART interrupt source to clear.
  *         This parameter can be any combination of the following values:
  *             UART_INT_RXERR
  *             UART_INT_BUSY_DETECT
  * @retval None
  */
void UART_ClearINTStatus(UART_Type *UARTx, uint32_t INTMask)
{
  __IO uint32_t tmp = 0UL;

  UNUSED(tmp);

  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_INTCLR(INTMask));
  
  if (INTMask & UART_INT_BUSY_DETECT)
  {
    tmp = UARTx->USR;
  }
  if (INTMask & UART_INT_RXERR)
  {
    tmp = UARTx->LSR;
  }
}

/**
  * @brief  Gets UART specified flag status.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @param  FlagMask: specifies the UART flag status to check.
  *         This parameter can be one of the following values: 
  *             UART_FLAG_RX
  *             UART_FLAG_RXERR
  *             UART_FLAG_RXERR_OV
  *             UART_FLAG_RXERR_PE
  *             UART_FLAG_RXERR_FE
  *             UART_FLAG_BREAK_INT
  *             UART_FLAG_TXE
  *             UART_FLAG_RXFIFO_USED
  * @retval  The new state of UART specified flag status (SET or RESET).
  */
FlagStatus UART_GetFlag(UART_Type *UARTx, uint32_t FlagMask)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_FLAGGET(FlagMask));
  
  if (FlagMask & 0x80000000UL)
  {
    if (UARTx->LSR & FlagMask)
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
    if ((UARTx->IIR & FlagMask) == UART_IIR_RT_FIFOEN)
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
  * @brief  Gets UART INTPending status.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @retval  The highest priority pending interrupt.
  *          0x1 : no interrupt pending
  *          0x2 : transmitter empty
  *          0x4 : received data available
  *          0x6 : receiver line error
  *          0x7 : busy detect
  *          0xC : receive FIFO timeout
  */
uint8_t UART_GetINTPendingStatus(UART_Type *UARTx)
{
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  
  return (UARTx->IIR & UART_IIR_XFIFOR_MASK);
}

/**
  * @brief  Sends UART data.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @param  ch: data to send..
  * @retval None
  */
void UART_SendData(UART_Type *UARTx, uint8_t ch)
{
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  
  UARTx->THR = ch;
}

/**
  * @brief  Reads UART received data.
  * @param  UARTx: select the UART peripheral.
  *         CM0 : UART14 ~ UART19
  *         CM33 : UART0 ~ UART19
  * @retval The received data.
  */
uint8_t UART_ReceiveData(UART_Type *UARTx)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));

  return (UARTx->RBR);
}

/**
  * @brief  Enables or disables UART IrDA SIR function.
  * @param  UARTx: select the UART peripheral.
  * @param  NewState: new state of the specified UART IrDA SIR function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void UART_IrDASIRCmd(UART_Type *UARTx, uint32_t NewState)
{
  __IO uint32_t *addr_sys_iren;
  uint32_t instance_num;
  
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  addr_sys_iren = &SYSCFG1->IREN;
  
  instance_num = UART_GET_INDEX(UARTx);
  
  if (NewState != DISABLE)
  {
    *addr_sys_iren |= 1UL << instance_num;
    UARTx->MCR |= UART_MCR_IREN;
  }
  else
  {
    *addr_sys_iren &= ~(1UL << instance_num);
    UARTx->MCR &= UART_MCR_IREN_CLR;
  }
}

/*********************************** END OF FILE ******************************/
