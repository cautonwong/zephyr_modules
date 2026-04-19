
 /**
  ******************************************************************************
  * @file    lib_gpio_ex.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   This file provides all the GPIO Extension module firmware functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/  
#include "lib_gpio.h"
#include "lib_gpio_ex.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup GPIOEx 
  * @brief GPIOEx driver modules
  * @{
  */

/** @defgroup GPIOEx_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private_Defines
  * @{
  */

/****************  Bit definition for RTC_IODEC_MODE registers  ***************/
#define IODET_RTC_DETMODE_C13           ((uint32_t)0x00000003)  
#define IODET_RTC_DETMODE_I8            ((uint32_t)0x0000000C)  

/*****************  Bit definition for RTC_FIFO_STS registers  ****************/
#define IODET_RTC_FIFOSTS_C13_MASK      ((uint32_t)0x00000003)
#define RTC_FIFOSTS_MSK                 ((uint32_t)0x0000000F)  
#define RTC_FIFOSTS_ALL_EMPTY           ((uint32_t)0x00000005)  
#define RTC_FIFOSTS_IOC13               ((uint32_t)0x00000003)  
#define RTC_FIFOSTS_IOC13EMPTY          ((uint32_t)0x00000001)  
#define RTC_FIFOSTS_IOC13FULL           ((uint32_t)0x00000002)  
#define RTC_FIFOSTS_IOI8                ((uint32_t)0x0000000C)  
#define RTC_FIFOSTS_IOI8EMPTY           ((uint32_t)0x00000004)  
#define RTC_FIFOSTS_IOI8FULL            ((uint32_t)0x00000008) 

/**
  * @}
  */

/** @defgroup GPIOEx_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private_Functions
  * @{
  */

/**
  * @brief  Configures GPIO detection function.
  * @param  IODET_Pin: selects detect pin to configure.
  *         This parameter can be: IODET_PIN_C13 or IODET_PIN_I8
  * @param  TrigSrc: configures trigger mode.
  *         This parameter can be one of the following values:
  *         @arg IODET_TRIG_DISABLE
  *         @arg IODET_TRIG_RISING
  *         @arg IODET_TRIG_FALLING
  *         @arg IODET_TRIG_BOTH
  * @retval None
  */
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1) 
void IODET_ModeConfig(uint32_t IODET_Pin, uint32_t TrigSrc)
{
  uint32_t tmp;

  /* Parameter check */
  assert_parameters(IS_IODET_GPIO(IODET_Pin));
  assert_parameters(IS_IODET_TRIG(TrigSrc));

  tmp = RTC->IODECMODE;
  if(IODET_Pin == IODET_PIN_C13)
  {
    tmp &= (uint32_t)(~((uint32_t)IODET_RTC_DETMODE_C13));
  }
  else
  {
    tmp &= (uint32_t)(~((uint32_t)IODET_RTC_DETMODE_I8));
  }
  tmp |= (TrigSrc<<(2*IODET_Pin));
  RTC->IODECMODE = tmp;
}

/**
  * @brief  Returns the Detection Status
  * @param  IODET_Pin: selects detect pin to configure.
  *         This parameter can be: IODET_PIN_C13 or IODET_PIN_I8
  * @retval 0: Dectection Event times: 1~9
  *         1: No Dectection Event
  *         2: Dectection Event times: 10
  */
uint8_t IODET_GetEventStatus(uint32_t IODET_Pin)
{
  uint32_t tmp;

  /* Parameter check */
  assert_parameters(IS_IODET_GPIO(IODET_Pin));

  tmp = RTC->FIFOSTS;
  tmp &= IODET_RTC_FIFOSTS_C13_MASK << (2*IODET_Pin);
  tmp >>= 2*IODET_Pin;

  return tmp;
}

/**
  * @brief  Gets Detection data once
  * @param  IODET_DataStruct: Pointer to Data structure
  * @param  IODET_Pin: selects detect pin to configure.
  *         This parameter can be: IODET_PIN_C13 or IODET_PIN_I8
  * @retval None
  */
void IODET_GetFIFODataOnce(uint32_t IODET_Pin, IODET_DataType *IODET_DataStruct)
{
  uint32_t tmp;

  /* Parameter check */
  assert_parameters(IS_IODET_GPIO(IODET_Pin));

  if(IODET_Pin == IODET_PIN_C13)
  {
    tmp = RTC->DECDATAIO0;
  }
  else
  {
    tmp = RTC->DECDATAIO1;
  }

  *IODET_DataStruct = *(IODET_DataType*)&tmp;
}


/**
  * @brief  Enable Fast IO mode.
  * @param  FAST_IO_Pin: specifies the port bit to read.
  *         This parameter can be FAST_IOx_Pin_y where x can be (D,E) and y can be(0...15).
  * @param  NewState: new state of the specified UART receive FIFO.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FAST_IO_Cmd(uint32_t FAST_IO_Pin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_parameters(IS_GET_FAST_IO_PIN(FAST_IO_Pin));
  if (NewState != DISABLE)
  {
    IOCTRL->FAST_IO_CFG |= FAST_IO_Pin;
  }
  else
  {
    IOCTRL->FAST_IO_CFG &= ~FAST_IO_Pin;
  }
}  

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (D,E) to select the GPIO peripheral.
  * @param  FAST_IO_Pin: specifies the port bit to read.
  *         This parameter can be FAST_IOx_Pin_y where x can be (D,E) and y can be(0...15).
  * @retval The output port pin value.
  */
uint8_t FAST_IO_ReadOutputDataBit(uint32_t FAST_IO_Pin)
{
  /* Check the parameters */
  assert_parameters(IS_GET_FAST_IO_PIN(FAST_IO_Pin));
  
  if (IS_BIT_SET(CRC->IO_OUT, FAST_IO_Pin))
  {
    return (1U);
  }
  else
  {
    return (0U);
  }
}

/**
  * @brief  Sets the selected data port bits.
  * @note   This functions uses GPIOx_BSRR register to allow atomic read/modify 
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  * @param  FAST_IO_Pin: specifies the port bits to be written.
  *         This parameter can be FAST_IOx_Pin_y where x can be (D,E) and y can be(0...15).
  * @retval None
  */
void FAST_IO_SetBits(uint32_t FAST_IO_Pin)
{
  /* Check the parameters */
  assert_parameters(IS_FAST_IO_PIN(FAST_IO_Pin));
  
  WRITE_REG(CRC->IO_OUT, FAST_IO_Pin);
}

/**
  * @brief  Clears the selected data port bits.
  * @note   This functions uses GPIOx_BSRR register to allow atomic read/modify 
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  * @param  FAST_IO_Pin: specifies the port bits to be written.
  *         This parameter can be FAST_IOx_Pin_y where x can be (D,E) and y can be(0...15).
  * @retval None
  */
void FAST_IO_ResetBits(uint32_t FAST_IO_Pin)
{
  /* Check the parameters */
  assert_parameters(IS_FAST_IO_PIN(FAST_IO_Pin));
  
  WRITE_REG(CRC->IO_OUT, FAST_IO_Pin);
}


/**
  * @brief  Toggles the specified GPIO pins..
  * @param  FAST_IO_Pin: specifies the port bits to be written.
  *         This parameter can be FAST_IOx_Pin_y where x can be (D,E) and y can be(0...15).
  * @retval None
  */
void FAST_IO_ToggleBits(uint32_t FAST_IO_Pin)
{
  /* Check the parameters */
  assert_parameters(IS_FAST_IO_PIN(FAST_IO_Pin));

  NOR_BIT(CRC->IO_OUT, FAST_IO_Pin);
}
#endif

/**
  * @brief  GPIO pins wake up source configuration function.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @param  Event:
  *           GPIO_EVENT_DISABLE
  *           GPIO_EVENT_RISING_EDGE
  *           GPIO_EVENT_FALLING_EDGE
  *           GPIO_EVENT_DUAL_EDGE
  *           GPIO_EVENT_HIGH_LEVEL
  *           GPIO_EVENT_LOW_LEVEL
  * @retval None
  */
void GPIO_WKU_Config(GPIO_Type* GPIOx, uint16_t GPIO_Pin, uint16_t Event)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
  uint32_t pxx;
  uint32_t mode = 0x00, pola = 0x00, cr[4] = {0};

  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  assert_parameters(IS_GPIO_EVENT(Event));

  pxx = ((uint32_t)GPIOx - (uint32_t)GPIOA) / 0x400UL;

  mode = EXTI->MODE;
  pola = EXTI->POLA;
  cr[0] = EXTI->CR1;
  cr[1] = EXTI->CR2;
  cr[2] = EXTI->CR3;
  cr[3] = EXTI->CR4;

  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = GPIO_Pin & pos;

    if (currentpin == pos)
    {
      mode &= ~(3<<(pinpos*2));
      mode |= (((uint32_t)Event & 0x3) << (pinpos*2));
      pola &= ~(1<<pinpos);
      pola |= (((uint16_t)((Event & 0x4)>>2)) << (pinpos));
      cr[pinpos/4] &= ~(0xF<<((pinpos%4)*4));
      cr[pinpos/4] |= (pxx<<((pinpos%4)*4));
    }
  }
  EXTI->POLA = pola;

  EXTI->CR1 = cr[0];
  EXTI->CR2 = cr[1];
  EXTI->CR3 = cr[2];
  EXTI->CR4 = cr[3];

  EXTI->EMR |= GPIO_Pin;
  EXTI->MODE = mode;
}

/**
  * @brief  Get the specified GPIO_Pin wakeup state.
  * @param  GPIO_Pin: specifies the pins flags to check.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval The wakeup state of EXTI.
  */
FlagStatus GPIO_GetWKUStatus(uint16_t GPIO_Pin)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_parameters(IS_GET_GPIO_PIN(GPIO_Pin));
  
  if (EXTI->WKU&GPIO_Pin)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clear the specified GPIO_Pin wakeup state.
  * @param  GPIO_Pin: specifies the pins flags to check.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None.
  */
void GPIO_ClearWKUStatus(uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_parameters(IS_GET_GPIO_PIN(GPIO_Pin));
  
  EXTI->WKU |= ((uint32_t)GPIO_Pin << 16);
}

/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_WKU_DeInit(void)
{
  EXTI->EMR   = 0;
  EXTI->POLA  = 0;
  EXTI->MODE  = 0;
  EXTI->NODEG = 0;
  EXTI->PR    = EXTI->PR;
  EXTI->CR1   = 0;
  EXTI->CR2   = 0;
  EXTI->CR3   = 0;
  EXTI->CR4   = 0;
}

/**
  * @brief  GPIO pins interrupt source configuration function.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @param  Event:
  *           GPIO_EVENT_DISABLE
  *           GPIO_EVENT_RISING_EDGE
  *           GPIO_EVENT_FALLING_EDGE
  *           GPIO_EVENT_DUAL_EDGE
  *           GPIO_EVENT_HIGH_LEVEL
  *           GPIO_EVENT_LOW_LEVEL
  * @retval None
  */
void GPIO_INT_Config(GPIO_Type* GPIOx, uint16_t GPIO_Pin, uint16_t Event)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
  uint32_t pxx;
  uint32_t mode, pola, cr[4];

  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  assert_parameters(IS_GPIO_EVENT(Event));

  pxx = ((uint32_t)GPIOx - (uint32_t)GPIOA) / 0x400UL;

  mode  = EXTI->MODE;
  pola  = EXTI->POLA;
  cr[0] = EXTI->CR1;
  cr[1] = EXTI->CR2;
  cr[2] = EXTI->CR3;
  cr[3] = EXTI->CR4;

  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = GPIO_Pin & pos;

    if (currentpin == pos)
    {
      mode &= ~(0x3 << (pinpos*2));
      mode |= (((uint32_t)Event & 0x3) << (pinpos*2));
      pola &= ~(1<<pinpos);
      pola |= (((uint16_t)((Event & 0x4)>>2)) << (pinpos));
      cr[pinpos/4] &= ~(0xF<<((pinpos%4)*4));
      cr[pinpos/4] |= (pxx<<((pinpos%4)*4));
    }
  }
  EXTI->POLA = pola;

  EXTI->CR1 = cr[0];
  EXTI->CR2 = cr[1];
  EXTI->CR3 = cr[2];
  EXTI->CR4 = cr[3];

  EXTI->IMR |= GPIO_Pin;

  #if defined V32F20XXX_CM0_CORE
  SYSCFG1->M0_INT_MASK &= ~((uint32_t)GPIO_Pin);
  #endif

  EXTI->MODE = mode;
}
/**
  * @brief  Generates a Software interrupt.
  * @param  GPIO_Pin: specifies the pins to be enabled or disabled..
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_GenerateSWInterrupt(uint16_t GPIO_Pin)
{
  /* Check the parameters */
 assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  
  EXTI->SWIER |= GPIO_Pin;
}

/**
  * @brief  Checks whether the specified GPIO_Pin (or EXTI line) flag is set or not.
  * @param  GPIO_Pin: specifies the pins flag to check.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval The new state of EXTI_Line (SET or RESET).
  */
FlagStatus GPIO_GetFlagStatus(uint16_t GPIO_Pin)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_parameters(IS_GET_GPIO_PIN(GPIO_Pin));
  
  if ((EXTI->PR & GPIO_Pin) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @brief  Clears the GPIO_Pin's ( or EXTI's line) pending flags.
  * @param  GPIO_Pin: specifies the pins flags to clear.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_ClearFlag(uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_parameters(IS_GET_GPIO_PIN(GPIO_Pin));
  
  EXTI->PR = GPIO_Pin;
}

/**
  * @brief  Checks whether the specified GPIO_Pin (or EXTI line) is asserted or not.
  * @param  GPIO_Pin: specifies the pins flags to check.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval The new state of EXTI_Line (SET or RESET).
  */
INTStatus GPIO_GetINTStatus(uint16_t GPIO_Pin)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  /* Check the parameters */
  assert_parameters(IS_GET_GPIO_PIN(GPIO_Pin));
  
  enablestatus =  EXTI->IMR & GPIO_Pin;
  if (((EXTI->PR & GPIO_Pin) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/*********************************** END OF FILE ******************************/
