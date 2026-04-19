/**
  ******************************************************************************
  * @file    lib_gpio.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-14
  * @brief   GPIO library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_gpio.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup GPIO 
  * @brief GPIO driver modules
  * @{
  */

/** @defgroup GPIO_Private_Defines
  * @{
  */
/* Private macro -------------------------------------------------------------*/
/* GPIO_MODER */
#define GPIO_MODER_MODER0                    ((uint32_t)0x00000003)
/* GPIO_OSPEEDER */
#define GPIO_OSPEEDER_OSPEEDR0               ((uint32_t)0x00000003)
/* GPIO_OTYPER */
#define GPIO_OTYPER_OT_0                     ((uint32_t)0x00000001)
/* GPIO_PUPDR */
#define GPIO_PUPDR_PUPDR0                    ((uint32_t)0x00000003)
/* GPIO_LCKR */
#define GPIO_LCKR_LOCK                       ((uint32_t)0x00010000)
/* GPIO_ANARTC_LCKR */
#define GPIO_ANARTC_LCKR_PI8                 ((uint32_t)0x00000008)
/* GPIO_ANARTC_BSRR */
#define GPIO_ANARTC_BSRR_PI8                 ((uint32_t)0x00000008)
/* GPIO_ANARTC_ODR */
#define GPIO_ANARTC_ODR_PCx_MASK             ((uint32_t)0x00000007)
#define GPIO_ANARTC_ODR_PIx_MASK             ((uint32_t)0x00000008)
#define GPIO_ANARTC_ODR_PI8                  ((uint32_t)0x00000008)
/* GPIO_ANARTC_AFRH */
#define GPIO_ANARTC_AFRH_PC13_POS            (0UL)
#define GPIO_ANARTC_AFRH_PC13_MASK           (0xFUL << GPIO_ANARTC_AFRH_PC13_POS)
#define GPIO_ANARTC_AFRH_PC14_POS            (4UL)
#define GPIO_ANARTC_AFRH_PC14_MASK           (0xFUL << GPIO_ANARTC_AFRH_PC14_POS)
#define GPIO_ANARTC_AFRH_PC15_POS            (8UL)
#define GPIO_ANARTC_AFRH_PC15_MASK           (0xFUL << GPIO_ANARTC_AFRH_PC15_POS)
#define GPIO_ANARTC_AFRH_PI8_POS             (12UL)
#define GPIO_ANARTC_AFRH_PI8_MASK            (0xFUL << GPIO_ANARTC_AFRH_PI8_POS)

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitType structure which will be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitType* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitType structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_Type* GPIOx, GPIO_InitType* GPIO_InitStruct)
{
  uint32_t pinpos = 0x00, pos = 0x00 , currentpin = 0x00;
  uint32_t tmp = 0x00;

  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
  assert_parameters(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
  assert_parameters(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

  /* -------------------------Configure the port pins---------------- */
  /*-- GPIO Mode Configuration --*/
  if ((GPIOx == GPIOC) && \
      (GPIO_InitStruct->GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)))
  {
    if(GPIO_InitStruct->GPIO_Pin & GPIO_Pin_13)
    {
      tmp = RTCANA->GPIOMODER;
      tmp &= 0xFC;
      tmp |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << 0);
      RTCANA->GPIOMODER = tmp;

      tmp = RTCANA->GPIOOSPEEDR;
      tmp &= 0xFC;
      tmp |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << 0);
      RTCANA->GPIOOSPEEDR = tmp;

      tmp = RTCANA->GPIOOTYPER;
      tmp &= 0xE;
      tmp |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << 0);
      RTCANA->GPIOOTYPER = tmp;

      tmp = RTCANA->GPIOPUPDR;
      tmp &= 0xFC;
      tmp |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << 0);
      RTCANA->GPIOPUPDR = tmp;
    }
    if(GPIO_InitStruct->GPIO_Pin & GPIO_Pin_14)
    {
      tmp = RTCANA->GPIOMODER;
      tmp &= 0xF3;
      tmp |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << 2);
      RTCANA->GPIOMODER = tmp;

      tmp = RTCANA->GPIOOSPEEDR;
      tmp &= 0xF3;
      tmp |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << 2);
      RTCANA->GPIOOSPEEDR = tmp;

      tmp = RTCANA->GPIOOTYPER;
      tmp &= 0xD;
      tmp |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << 1);
      RTCANA->GPIOOTYPER = tmp;

      tmp = RTCANA->GPIOPUPDR;
      tmp &= 0xF3;
      tmp |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << 2);
      RTCANA->GPIOPUPDR = tmp;
    }
    if(GPIO_InitStruct->GPIO_Pin & GPIO_Pin_15)
    {
      tmp = RTCANA->GPIOMODER;
      tmp &= 0xCF;
      tmp |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << 4);
      RTCANA->GPIOMODER = tmp;

      tmp = RTCANA->GPIOOSPEEDR;
      tmp &= 0xCF;
      tmp |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << 4);
      RTCANA->GPIOOSPEEDR = tmp;

      tmp = RTCANA->GPIOOTYPER;
      tmp &= 0xB;
      tmp |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << 2);
      RTCANA->GPIOOTYPER = tmp;

      tmp = RTCANA->GPIOPUPDR;
      tmp &= 0xCF;
      tmp |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << 4);
      RTCANA->GPIOPUPDR = tmp;
    }
  }
  else if ((GPIOx == GPIOI) && \
           (GPIO_InitStruct->GPIO_Pin & GPIO_Pin_8))
  {
    tmp = RTCANA->GPIOMODER;
    tmp &= 0x3F;
    tmp |= (((uint32_t)GPIO_InitStruct->GPIO_Mode) << 6);
    RTCANA->GPIOMODER = tmp;

    tmp = RTCANA->GPIOOSPEEDR;
    tmp &= 0x3F;
    tmp |= ((uint32_t)(GPIO_InitStruct->GPIO_Speed) << 6);
    RTCANA->GPIOOSPEEDR = tmp;

    tmp = RTCANA->GPIOOTYPER;
    tmp &= 0x7;
    tmp |= (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << 3);
    RTCANA->GPIOOTYPER = tmp;

    tmp = RTCANA->GPIOPUPDR;
    tmp &= 0x3F;
    tmp |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << 6);
    RTCANA->GPIOPUPDR = tmp;
  }
  
  for (pinpos = 0x00; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x01) << pinpos;
    /* Get the port pins position */
    currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

    if (currentpin == pos)
    {      
      MODIFY_REG(GPIOx->MODER, \
                 GPIO_MODER_MODER0 << (pinpos * 2), \
                 ((uint32_t)GPIO_InitStruct->GPIO_Mode) << (pinpos * 2));
      
      if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || \
          (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
      {
        /* Check Speed mode parameters */
        assert_parameters(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed));

        /* Speed mode configuration */
        MODIFY_REG(GPIOx->OSPEEDR, \
                   GPIO_OSPEEDER_OSPEEDR0 << (pinpos * 2), \
                   ((uint32_t)GPIO_InitStruct->GPIO_Speed) << (pinpos * 2));

        /* Check Output mode parameters */
        assert_parameters(IS_GPIO_OTYPE(GPIO_InitStruct->GPIO_OType));

        /* Output mode configuration*/
        MODIFY_REG(GPIOx->OTYPER, \
                   GPIO_OTYPER_OT_0 << ((uint16_t)pinpos), \
                   (uint16_t)(((uint16_t)GPIO_InitStruct->GPIO_OType) << ((uint16_t)pinpos)));
      }

      /* Pull-up Pull down resistor configuration*/
      MODIFY_REG(GPIOx->PUPDR, \
                GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2), \
                (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2)));
    }
  }
}

/**
  * @brief  Locks GPIO Pins configuration registers.
  * @note   The locked registers are GPIOx_MODER, GPIOx_OTYPER, GPIOx_OSPEEDR,
  *         GPIOx_PUPDR, GPIOx_AFRL and GPIOx_AFRH.
  * @note   The configuration of the locked GPIO pins can no longer be modified
  *         until the next reset.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be locked.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_PinLockConfig(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  __IO uint32_t tmp = 0UL;

  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  
  if((GPIOx == GPIOC) && \
     (GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)))
  {
    tmp = GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    tmp >>= 13U;
  }
  else if ((GPIOx == GPIOI) && \
           (GPIO_Pin & GPIO_Pin_8))
  {
    tmp = GPIO_ANARTC_LCKR_PI8;
  }
  
  if (tmp)
  {
    /* Set LCKK bit */
    WRITE_REG(RTCANA->GPIOLCKR, tmp | GPIO_LCKR_LOCK);
    /* Reset LCKK bit */
    WRITE_REG(RTCANA->GPIOLCKR, tmp);
    /* Set LCKK bit */
    WRITE_REG(RTCANA->GPIOLCKR, tmp | GPIO_LCKR_LOCK);
    /* Read LCKK bit*/
    tmp = READ_REG(RTCANA->GPIOLCKR);
    /* Read LCKK bit*/
    tmp = READ_REG(RTCANA->GPIOLCKR);
  }
    
  /* Set LCKK bit */
  WRITE_REG(GPIOx->LCKR, GPIO_Pin | GPIO_LCKR_LOCK);
  /* Reset LCKK bit */
  WRITE_REG(GPIOx->LCKR, GPIO_Pin);
  /* Set LCKK bit */
  WRITE_REG(GPIOx->LCKR, GPIO_Pin | GPIO_LCKR_LOCK);
  /* Read LCKK bit*/
  tmp = READ_REG(GPIOx->LCKR);
  /* Read LCKK bit*/
  tmp = READ_REG(GPIOx->LCKR);
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GET_GPIO_PIN(GPIO_Pin));
  
  if (IS_BIT_SET(GPIOx->IDR, GPIO_Pin))
  {
    return (1U);
  }
  else
  {
    return (0U);
  }
}

/**
  * @brief  Reads the specified GPIO input data port.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @retval GPIO input data port value.
  */
uint16_t GPIO_ReadInputData(GPIO_Type* GPIOx)
{
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((uint16_t)READ_REG(GPIOx->IDR));
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  *          This parameter can be GPIO_Pin_x where x can be (0..15).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GET_GPIO_PIN(GPIO_Pin));
  
  if (IS_BIT_SET(GPIOx->ODR, GPIO_Pin))
  {
    return (1U);
  }
  else
  {
    return (0U);
  }
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_Type* GPIOx)
{
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  
  return ((uint16_t)READ_REG(GPIOx->ODR));
}

/**
  * @brief  Sets the selected data port bits.
  * @note   This functions uses GPIOx_BSRR register to allow atomic read/modify 
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_SetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  
  if((GPIOx == GPIOC) && \
     (GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)))
  {
    tmp = GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    tmp >>= 13U;
  }
  else if ((GPIOx == GPIOI) && \
           (GPIO_Pin & GPIO_Pin_8))
  {
    tmp = GPIO_ANARTC_BSRR_PI8;
  }
  
  if (tmp)
  {
    WRITE_REG(RTCANA->GPIOBSRR, GPIO_Pin);
  }
  
  WRITE_REG(GPIOx->BSRR, GPIO_Pin);
}

/**
  * @brief  Clears the selected data port bits.
  * @note   This functions uses GPIOx_BSRR register to allow atomic read/modify 
  *         accesses. In this way, there is no risk of an IRQ occurring between
  *         the read and the modify access.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  *          This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
  * @retval None
  */
void GPIO_ResetBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  
  if((GPIOx == GPIOC) && \
     (GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)))
  {
    tmp = GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    tmp >>= 13U;
  }
  else if ((GPIOx == GPIOI) && \
           (GPIO_Pin & GPIO_Pin_8))
  {
    tmp = GPIO_ANARTC_BSRR_PI8;
  }
  
  if (tmp)
  {
    WRITE_REG(RTCANA->GPIOBSRR, GPIO_Pin<<16UL);
  }
  
  WRITE_REG(GPIOx->BSRR, GPIO_Pin<<16UL);
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *          This parameter can be one of GPIO_Pin_x where x can be (0..15).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *          This parameter can be one of the BitAction enum values:
  *            @arg Bit_RESET: to clear the port pin
  *            @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_Type* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
{
  uint32_t tmp = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GET_GPIO_PIN(GPIO_Pin));
  assert_parameters(IS_BIT_ACTION(BitVal));
  
  
  if((GPIOx == GPIOC) && \
     (GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)))
  {
    tmp = GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    tmp >>= 13U;
  }
  else if ((GPIOx == GPIOI) && \
           (GPIO_Pin & GPIO_Pin_8))
  {
    tmp = GPIO_ANARTC_BSRR_PI8;
  }
  
  if (tmp)
  {
    if (BitVal != RESET)
    {
      WRITE_REG(RTCANA->GPIOBSRR, GPIO_Pin);
    }
    else
    {
      WRITE_REG(RTCANA->GPIOBSRR, GPIO_Pin<<16UL);
    }
  }
  else
  {
    if (BitVal != RESET)
    {
      WRITE_REG(GPIOx->BSRR, GPIO_Pin);
    }
    else
    {
      WRITE_REG(GPIOx->BSRR, GPIO_Pin<<16UL);
    }
  }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_Type* GPIOx, uint16_t PortVal)
{
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));

  WRITE_REG(GPIOx->ODR, PortVal);
  
  if (GPIOx == GPIOC)
  {
    MODIFY_REG(RTCANA->GPIOODR, \
               GPIO_ANARTC_ODR_PCx_MASK, \
               (PortVal>>13UL)&GPIO_ANARTC_ODR_PCx_MASK);
  }
  else if (GPIOx == GPIOI)
  {
    MODIFY_REG(RTCANA->GPIOODR, \
               GPIO_ANARTC_ODR_PIx_MASK, \
               (PortVal>>5UL)&GPIO_ANARTC_ODR_PIx_MASK);
  }
}

/**
  * @brief  Toggles the specified GPIO pins..
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  * @retval None
  */
void GPIO_ToggleBits(GPIO_Type* GPIOx, uint16_t GPIO_Pin)
{
  uint32_t tmp = 0UL;
  
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GPIO_PIN(GPIO_Pin));
  
  if((GPIOx == GPIOC) && \
     (GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)))
  {
    tmp = GPIO_Pin & (GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    tmp >>= 13U;
  }
  else if ((GPIOx == GPIOI) && \
           (GPIO_Pin & GPIO_Pin_8))
  {
    tmp = GPIO_ANARTC_ODR_PI8;
  }
  
  if (tmp)
  {
    NOR_BIT(RTCANA->GPIOODR, tmp);
  }

  NOR_BIT(GPIOx->ODR, GPIO_Pin);
}

/**
  * @brief  Changes the mapping of the specified pin.
  * @param  GPIOx: where x can be (A..I) to select the GPIO peripheral.
  * @param  GPIO_PinSource: specifies the pin for the Alternate function.
  *         This parameter can be GPIO_PinSourcex where x can be (0..15).
  * @param  GPIO_AFSelection: selects the pin to used as Alternate function.
  *          This parameter can be one of the following values:
  *            @arg GPIO_AF0_MCO1 : MCO1 Alternate Function mapping 
  *            @arg GPIO_AF0_MCO2 : MCO2 Alternate Function mapping 
  *            @arg GPIO_AF0_MCO3 : MCO3 Alternate Function mapping 
  *            @arg GPIO_AF0_MCO4 : MCO4 Alternate Function mapping 
  *            @arg GPIO_AF0_RTC_PLLDIV0 : RTC PLLDIV Alternate Function mapping 
  *            @arg GPIO_AF0_RTC_PLLDIV1 : RTC PLLDIV Alternate Function mapping 
  *            @arg GPIO_AF0_RTC_IODET1 : RTC IODET Alternate Function mapping 
  *            @arg GPIO_AF0_RTC_IODET2 : RTC IODET Alternate Function mapping 
  *            @arg GPIO_AF0_RTC_SP_O : RTC_SP Alternate Function mapping 
  *            @arg GPIO_AF0_SWDIO : SWDIO Alternate Function mapping 
  *            @arg GPIO_AF0_SWCLK : SWCLK Alternate Function mapping 
  *            @arg GPIO_AF0_M0_SWDIO : M0_SWDIO Alternate Function mapping 
  *            @arg GPIO_AF0_M0_SWCLK : M0_SWCLK Alternate Function mapping 
  *            @arg GPIO_AF1_GTMR0_IO1_ETR : Alternate Function mapping 
  *            @arg GPIO_AF1_GTMR0_IO2 : Alternate Function mapping 
  *            @arg GPIO_AF1_GTMR0_IO3 : Alternate Function mapping 
  *            @arg GPIO_AF1_GTMR0_IO4 : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_BKIN : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_O1_N : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_IO1 : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_IO2 : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_IO3 : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_IO4 : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_ETR : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_O2_N : Alternate Function mapping 
  *            @arg GPIO_AF1_ETMR0_O3_N : Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR3_IO1 : GTMR3_IO1 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR3_IO2 : GTMR3_IO2 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR3_IO3 : GTMR3_IO3 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR3_IO4 : GTMR3_IO4 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR1_IO1 : GTMR1_IO1 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR1_IO2 : GTMR1_IO2 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR1_IO3 : GTMR1_IO3 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR1_IO4 : GTMR1_IO4 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR2_IO1 : GTMR2_IO1 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR2_IO2 : GTMR2_IO2 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR2_IO3 : GTMR2_IO3 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR2_IO4 : GTMR2_IO4 Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR1_ETR : GTMR1_ETR Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR2_ETR : GTMR2_ETR Alternate Function mapping 
  *            @arg GPIO_AF2_GTMR3_ETR : GTMR3_ETR Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_ETR : ETMR1_ETR Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_O1_N : ETMR1_O1_N Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_BKIN : ETMR1_BKIN Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_O2_N : ETMR1_O2_N Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_O3_N : ETMR1_O3_N Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_IO1 : ETMR1_IO1 Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_IO2 : ETMR1_IO2 Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_IO3 : ETMR1_IO3 Alternate Function mapping 
  *            @arg GPIO_AF3_ETMR1_IO4 : ETMR1_IO4 Alternate Function mapping 
  *            @arg GPIO_AF3_BTMR0_3_EXT_CLK : BTMR0_3_EXT_CLK Alternate Function mapping 
  *            @arg GPIO_AF3_BPWM0 : BPWM0 Alternate Function mapping 
  *            @arg GPIO_AF3_BPWM1 : BPWM1 Alternate Function mapping 
  *            @arg GPIO_AF3_BPWM2 : BPWM2 Alternate Function mapping 
  *            @arg GPIO_AF3_BPWM3 : BPWM3 Alternate Function mapping 
  *            @arg GPIO_AF3_LPBTMR0_EXTIN : LPBTMR0_EXTIN Alternate Function mapping 
  *            @arg GPIO_AF3_LPBTMR1_EXTIN : LPBTMR1_EXTIN Alternate Function mapping 
  *            @arg GPIO_AF4_FC2_RTS_SCL_SSEL1 : _FC2_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF4_FC2_SSEL2 : FC2_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF4_FC0_SSEL2 : FC0_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF4_FC0_RTS_SCL_SSEL1 : FC0_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF4_FC0_CTS_SDA_SSEL0 : FC0_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF4_FC1_RTS_SCL_SSEL1 : FC1_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF4_FC1_CTS_SDA_SSEL0 : FC1_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF4_FC1_SSEL2 : FC1_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF4_FC2_CTS_SDA_SSEL0 : FC2_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF4_FC0_SCK : FC0_SCK Alternate Function mapping 
  *            @arg GPIO_AF4_FC0_RXD_SDA_MOSI : FC0_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF4_FC2_SCK : FC2_SCK Alternate Function mapping 
  *            @arg GPIO_AF4_FC1_SCK : FC1_SCK Alternate Function mapping 
  *            @arg GPIO_AF4_FC1_RXD_SDA_MOSI : FC1_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF4_FC1_TXD_SCL_MISO : FC1_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF4_FC2_RXD_SDA_MOSI : FC2_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF4_FC2_TXD_SCL_MISO : FC2_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF4_FC2_SSEL3 : FC2_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF4_FC0_TXD_SCL_MISO : FC0_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF4_FC0_SSEL3 : FC0_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF4_FC1_SSEL3 : FC1_SSEL3Alternate Function mapping 
  *            @arg GPIO_AF5_FC3_CTS_SDA_SSEL0 : FC3_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF5_FC3_SCK : FC3_SCK Alternate Function mapping 
  *            @arg GPIO_AF5_FC3_TXD_SCL_MISO : FC3_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF5_FC3_RXD_SDA_MOSI : FC3_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF5_FC3_SSEL3 : FC3_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF5_FC4_CTS_SDA_SSEL0 : FC4_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF5_FC4_SCK : FC4_SCK Alternate Function mapping 
  *            @arg GPIO_AF5_FC4_TXD_SCL_MISO : FC4_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF5_FC4_RXD_SDA_MOSI : FC4_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF5_FC3_RTS_SCL_SSEL1 : FC3_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF5_FC3_SSEL2 : FC3_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF5_I2S0_MCK : I2S0_MCK Alternate Function mapping 
  *            @arg GPIO_AF5_I2S0_SD : I2S0_DA Alternate Function mapping 
  *            @arg GPIO_AF5_I2S0_WS : I2S0_WS Alternate Function mapping 
  *            @arg GPIO_AF5_I2S0_SCK : I2S0_SCK Alternate Function mapping 
  *            @arg GPIO_AF5_FC4_SSEL2 : FC4_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF5_FC4_RTS_SCL_SSEL1 : FC4_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF5_FC4_SSEL3 : FC4_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF6_FC5_CTS_SDA_SSEL0 : FC5_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF6_FC5_SCK : FC5_SCK Alternate Function mapping 
  *            @arg GPIO_AF6_FC5_TXD_SCL_MISO : FC5_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF6_FC5_RXD_SDA_MOSI : FC5_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF6_I2S1_MCK : I2S1_MCK Alternate Function mapping 
  *            @arg GPIO_AF6_I2S1_WS : I2S1_WS Alternate Function mapping
  *            @arg GPIO_AF6_I2S1_SCK : I2S1_SCK Alternate Function mapping
  *            @arg GPIO_AF6_I2S1_SD : I2S1_SD Alternate Function mapping
  *            @arg GPIO_AF6_FC5_SSEL3 : FC5_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF6_FC13_SSEL3 : FC13_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF6_FC12_SCK : FC12_SCK Alternate Function mapping 
  *            @arg GPIO_AF6_FC12_CTS_SDA_SSEL0 : FC12_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF6_FC12_RTS_SCL_SSEL1 : FC12_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF6_FC12_RXD_SDA_MOSI : FC12_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF6_FC12_TXD_SCL_MISO : FC12_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF6_FC12_SSEL2 : FC12_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF6_FC12_SSEL3 : FC12_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF6_FC13_SCK : FC13_SCK Alternate Function mapping 
  *            @arg GPIO_AF6_FC13_CTS_SDA_SSEL0 : FC13_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF6_FC13_RTS_SCL_SSEL1 : FC13_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF6_FC13_RXD_SDA_MOSI : FC13_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF6_FC13_TXD_SCL_MISO : FC13_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF6_FC13_SSEL2 : FC13_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF6_FC5_RTS_SCL_SSEL1 : FC5_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF6_FC5_SSEL2 : FC5_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF7_FC7_CTS_SDA_SSEL0 : FC7_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF7_FC7_RTS_SCL_SSEL1 : FC7_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF7_FC7_TXD_SCL_MISO : FC7_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF7_FC7_RXD_SDA_MOSI : FC7_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF7_FC7_SCK : FC7_SCK Alternate Function mapping 
  *            @arg GPIO_AF7_FC6_SCK : FC6_SCK Alternate Function mapping 
  *            @arg GPIO_AF7_FC6_TXD_SCL_MISO : FC6_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF7_FC6_RXD_SDA_MOSI : FC6_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF7_FC6_CTS_SDA_SSEL0 : FC6_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF7_FC6_RTS_SCL_SSEL1 : FC6_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF7_FC8_TXD_SCL_MISO : FC8_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF7_FC8_RXD_SDA_MOSI : FC8_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF7_FC8_SCK : FC8_SCK Alternate Function mapping 
  *            @arg GPIO_AF7_FC8_CTS_SDA_SSEL0 : FC8_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF7_FC8_RTS_SCL_SSEL1 : FC8_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF7_FC8_SSEL2 : FC8_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF7_FC8_SSEL3 : FC8_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF7_FC7_SSEL3 : FC7_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF7_FC7_SSEL2 : FC7_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF7_FC6_SSEL3 : FC6_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF7_FC6_SSEL2 : FC6_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF8_FC10_TXD_SCL_MISO : FC10_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF8_FC10_RXD_SDA_MOSI : FC10_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF8_FC12_RXD_SDA_MOSI : FC12_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF8_FC9_TXD_SCL_MISO : FC9_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF8_FC9_RXD_SDA_MOSI : FC9_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF8_FC9_SCK : FC9_SCK Alternate Function mapping 
  *            @arg GPIO_AF8_FC12_TXD_SCL_MISO : FC12_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF8_FC11_TXD_SCL_MISO : FC11_TXD_SCL_MISO Alternate Function mapping 
  *            @arg GPIO_AF8_FC11_RXD_SDA_MOSI : FC11_RXD_SDA_MOSI Alternate Function mapping 
  *            @arg GPIO_AF8_FC11_CTS_SDA_SSEL0 : FC11_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF8_FC11_RTS_SCL_SSEL1 : FC11_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF8_FC10_RTS_SCL_SSEL1 : FC10_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF8_FC10_CTS_SDA_SSEL0 : FC10_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF8_FC10_SCK : FC10_SCK Alternate Function mapping 
  *            @arg GPIO_AF8_FC10_SSEL2 : FC10_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF8_FC10_SSEL3 : FC10_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF8_FC9_RTS_SCL_SSEL1 : FC9_RTS_SCL_SSEL1 Alternate Function mapping 
  *            @arg GPIO_AF8_FC9_SSEL2 : FC9_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF8_FC9_SSEL3 : FC9_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF8_FC9_CTS_SDA_SSEL0 : FC9_CTS_SDA_SSEL0 Alternate Function mapping 
  *            @arg GPIO_AF8_FC11_SCK : FC11_SCK Alternate Function mapping 
  *            @arg GPIO_AF8_FC11_SSEL3 : FC11_SSEL3 Alternate Function mapping 
  *            @arg GPIO_AF8_FC11_SSEL2 : FC11_SSEL2 Alternate Function mapping 
  *            @arg GPIO_AF9_CMP0_OUT : CMP0_OUT Alternate Function mapping 
  *            @arg GPIO_AF9_CAN0_RX : CAN0_RX Alternate Function mapping 
  *            @arg GPIO_AF9_CAN0_TX : CAN0_TX Alternate Function mapping 
  *            @arg GPIO_AF9_CAN1_RX : CAN1_RX Alternate Function mapping 
  *            @arg GPIO_AF9_CAN1_TX : CAN1_TX Alternate Function mapping 
  *            @arg GPIO_AF9_ISO78160_CLK : ISO78160_CLK Alternate Function mapping 
  *            @arg GPIO_AF9_ISO78160_DAT : ISO78160_DAT Alternate Function mapping 
  *            @arg GPIO_AF9_ISO78161_CLK : ISO78161_CLK Alternate Function mapping 
  *            @arg GPIO_AF9_ISO78161_DAT : ISO78161_DAT Alternate Function mapping 
  *            @arg GPIO_AF9_CMP1_OUT : CMP1_OUT Alternate Function mapping 
  *            @arg GPIO_AF10_ISO78162_DAT : ISO78162_DAT Alternate Function mapping 
  *            @arg GPIO_AF10_ISO78163_CLK : ISO78163_CLK Alternate Function mapping 
  *            @arg GPIO_AF10_ISO78163_DAT : ISO78163_DAT Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_D5 : EADC_D5 Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_D6 : EADC_D6 Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_D7 : EADC_D7 Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_CLK : EADC_CLK Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_D0 : EADC_D0 Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_D1 : EADC_D1 Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_D2 : EADC_D2 Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_D3 : EADC_D3 Alternate Function mapping 
  *            @arg GPIO_AF10_EADC_D4 : EADC_D4 Alternate Function mapping 
  *            @arg GPIO_AF10_ENGY_CF2 : ENGY_CF2 Alternate Function mapping 
  *            @arg GPIO_AF10_ISO78162_CLK : ISO78162_CLK Alternate Function mapping 
  *            @arg GPIO_AF11_RMII0_CLK_IN : RMII0_CLK_IN Alternate Function mapping 
  *            @arg GPIO_AF11_RMDIO0 : RMDIO0 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII1_TXD1 : RMII1_TXD1 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII0_RX_DV : RMII0_RX_DV Alternate Function mapping 
  *            @arg GPIO_AF11_RMDPPS_OUT0 : RMDPPS_OUT0 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII0_TX_EN : RMII0_TX_EN Alternate Function mapping 
  *            @arg GPIO_AF11_RMII0_TXD0 : RMII0_TXD0 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII0_TXD1 : RMII0_TXD1 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII1_CLK_IN : RMII1_CLK_IN Alternate Function mapping 
  *            @arg GPIO_AF11_RMDCLK0 : RMDCLK0 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII1_RXD0 : RMII1_RXD0 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII1_RXD1 : RMII1_RXD1 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII0_RXD0 : RMII0_RXD0 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII0_RXD1 : RMII0_RXD1 Alternate Function mapping 
  *            @arg GPIO_AF11_RMDPPS_OUT1 : RMDPPS_OUT1 Alternate Function mapping 
  *            @arg GPIO_AF11_RMDCLK1 : RMDCLK1 Alternate Function mapping 
  *            @arg GPIO_AF11_RMDIO1 : RMDIO1 Alternate Function mapping 
  *            @arg GPIO_AF11_RMII1_RX_DV : RMII1_RX_DV Alternate Function mapping 
  *            @arg GPIO_AF11_RMII1_TX_EN : RMII1_TX_EN Alternate Function mapping 
  *            @arg GPIO_AF11_RMII1_TXD0 : RMII1_TXD0 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_D4 : SDIO0_D4 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_D5 : SDIO0_D5 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_D6 : SDIO0_D6 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_D7 : SDIO0_D7 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_D0 : SDIO0_D0 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_D1 : SDIO0_D1 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_D2 : SDIO0_D2 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_D3 : SDIO0_D3 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_CLK : SDIO0_CLK Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_CMD : SDIO0_CMD Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_IO3 : OSPI0_IO3 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_IO2 : OSPI0_IO2 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_IO1 : OSPI0_IO1 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_IO0 : OSPI0_IO0 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_IO6 : OSPI0_IO6 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_IO7 : OSPI0_IO7 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_IO4 : OSPI0_IO4 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_IO5 : OSPI0_IO5 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_IO2 : OSPI1_IO2 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_SCK_N : OSPI1_SCK_N Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_SS_0_N : OSPI1_SS_0_N Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_IO1 : OSPI1_IO1 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_TXDM_RXDS : OSPI1_TXDM_RXDS Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_IO0 : OSPI1_IO0 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_D0 : SDIO1_D0 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_D1 : SDIO1_D1 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_D2 : SDIO1_D2 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_CLK : SDIO1_CLK Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_D4 : SDIO1_D4 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_D5 : SDIO1_D5 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_D6 : SDIO1_D6 Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_D7 : SDIO1_D7 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_SCK : OSPI1_SCK Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_IO3 : OSPI1_IO3 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_IO4 : OSPI1_IO4 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_IO5 : OSPI1_IO5 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_IO6 : OSPI1_IO6 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI1_IO7 : OSPI1_IO7 Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_SCK : OSPI0_SCK Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_TXDM_RXDS : OSPI0_TXDM_RXDS Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_SCK_N : OSPI0_SCK_N Alternate Function mapping 
  *            @arg GPIO_AF12_OSPI0_SS_0_N : OSPI0_SS_0_N Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_WR_PRT : SDIO1_WR_PRT Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_CARD_DET : SDIO1_CARD_DET Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_WR_PRT : SDIO0_WR_PRT Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO0_CARD_DET : SDIO0_CARD_DET Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_CMD : SDIO1_CMD Alternate Function mapping 
  *            @arg GPIO_AF12_SDIO1_D3 : SDIO1_D3 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_HSYNC : DCMI_HSYNC Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_PIXCLK : DCMI_PIXCLK Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D0 : DCMI_D0 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D1 : DCMI_D1 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D10 : DCMI_D10 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D5 : DCMI_D5 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_VSYNC : DCMI_VSYNC Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D6 : DCMI_D6 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D7 : DCMI_D7 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D2 : DCMI_D2 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D3 : DCMI_D3 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D8 : DCMI_D8 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D4 : DCMI_D4 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D9 : DCMI_D9 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D11 : DCMI_D11 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D12 : DCMI_D12 Alternate Function mapping 
  *            @arg GPIO_AF13_DCMI_D13 : DCMI_D13 Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI1_CK : BSPI1_CK Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI0_MOSI : BSPI0_MOSI Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI1_CS : BSPI1_CS Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI1_MISO : BSPI1_MISO Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI1_MOSI : BSPI1_MOSI Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI3_CS : BSPI3_CS Alternate Function mapping 
  *            @arg GPIO_AF14_BTMR4_7_EXT_CLK : BTMR4_7_EXT_CLK Alternate Function mapping 
  *            @arg GPIO_AF14_BPWM5 : BPWM5 Alternate Function mapping 
  *            @arg GPIO_AF14_ENGY_CF1 : ENGY_CF1 Alternate Function mapping 
  *            @arg GPIO_AF14_ENGY_CF2 : ENGY_CF2 Alternate Function mapping 
  *            @arg GPIO_AF14_UART14_RX : UART14_RX Alternate Function mapping 
  *            @arg GPIO_AF14_UART14_TX : UART14_TX Alternate Function mapping 
  *            @arg GPIO_AF14_UART17_TX : UART17_TX Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI0_CK : BSPI0_CK Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI0_CS : BSPI0_CS Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI0_MISO : BSPI0_MISO Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI2_CK : BSPI2_CK Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI3_MISO : BSPI3_MISO Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI3_CK : BSPI3_CK Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI3_MOSI : BSPI3_MOSI Alternate Function mapping 
  *            @arg GPIO_AF14_UART18_TX : UART18_TX Alternate Function mapping 
  *            @arg GPIO_AF14_UART18_RX : UART18_RX Alternate Function mapping 
  *            @arg GPIO_AF14_UART19_TX : UART19_TX Alternate Function mapping 
  *            @arg GPIO_AF14_UART19_RX : UART19_RX Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI5_CS : BSPI5_CS Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI5_CK : BSPI5_CK Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI5_MISO : BSPI5_MISO Alternate Function mapping 
  *            @arg GPIO_AF14_UART15_RX : UART15_RX Alternate Function mapping 
  *            @arg GPIO_AF14_UART15_TX : UART15_TX Alternate Function mapping 
  *            @arg GPIO_AF14_UART16_RX : UART16_RX Alternate Function mapping 
  *            @arg GPIO_AF14_UART16_TX : UART16_TX Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI4_CK : BSPI4_CK Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI4_CS : BSPI4_CS Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI4_MISO : BSPI4_MISO Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI4_MOSI : BSPI4_MOSI Alternate Function mapping 
  *            @arg GPIO_AF14_UART17_RX : UART17_RX Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI5_MOSI : BSPI5_MOSI Alternate Function mapping 
  *            @arg GPIO_AF14_ENGY_CF0 : ENGY_CF0 Alternate Function mapping 
  *            @arg GPIO_AF14_BPWM4 : BPWM4 Alternate Function mapping 
  *            @arg GPIO_AF14_BPWM6 : BPWM6 Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI2_MISO : BSPI2_MISO Alternate Function mapping 
  *            @arg GPIO_AF14_I2C14_SCL : I2C14_SCL Alternate Function mapping 
  *            @arg GPIO_AF14_I2C14_SDA : I2C14_SDA Alternate Function mapping 
  *            @arg GPIO_AF14_BPWM7 : BPWM7 Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI2_CS : BSPI2_CS Alternate Function mapping 
  *            @arg GPIO_AF14_BSPI2_MOSI : BSPI2_MOSI Alternate Function mapping 
  * @retval None
  */
void GPIO_PinAFConfig(GPIO_Type* GPIOx, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
  /* Check the parameters */
  assert_parameters(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_parameters(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
  assert_parameters(IS_GPIO_AF(GPIO_AF));
  
  if((GPIOx == GPIOC) && (GPIO_PinSource == GPIO_PinSource13))
  {
    MODIFY_REG(RTCANA->GPIOAFRH, \
               GPIO_ANARTC_AFRH_PC13_MASK, \
               ((uint32_t)GPIO_AF<<GPIO_ANARTC_AFRH_PC13_POS)&GPIO_ANARTC_AFRH_PC13_MASK);
  }
  else if ((GPIOx == GPIOC) && (GPIO_PinSource == GPIO_PinSource14))
  {
    MODIFY_REG(RTCANA->GPIOAFRH, \
               GPIO_ANARTC_AFRH_PC14_MASK, \
               ((uint32_t)GPIO_AF<<GPIO_ANARTC_AFRH_PC14_POS)&GPIO_ANARTC_AFRH_PC14_MASK);
  }
  else if ((GPIOx == GPIOC) && (GPIO_PinSource == GPIO_PinSource15))
  {
    MODIFY_REG(RTCANA->GPIOAFRH, \
               GPIO_ANARTC_AFRH_PC15_MASK, \
               ((uint32_t)GPIO_AF<<GPIO_ANARTC_AFRH_PC15_POS)&GPIO_ANARTC_AFRH_PC15_MASK);
  }
    else if ((GPIOx == GPIOI) && (GPIO_PinSource == GPIO_PinSource8))
  {
    MODIFY_REG(RTCANA->GPIOAFRH, \
               GPIO_ANARTC_AFRH_PI8_MASK, \
               ((uint32_t)GPIO_AF<<GPIO_ANARTC_AFRH_PI8_POS)&GPIO_ANARTC_AFRH_PI8_MASK);
  }
  else
  {
    MODIFY_REG(GPIOx->AFR[GPIO_PinSource >> 0x03], \
               ((uint32_t)0xF << ((uint32_t)(GPIO_PinSource & 0x07) * 4)), \
               ((uint32_t)(GPIO_AF) << ((uint32_t)(GPIO_PinSource & 0x07) * 4)));
  }
}
/**
  * @}
  */

/**
  * @}
  */

/*********************************** END OF FILE ******************************/
