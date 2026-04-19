/**
  * @file    usb_bsp.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   This file implements the board support package for the USB host library
******************************************************************************/

/* Includes ------------------------------------------------------------------ */

#include "usb_bsp.h"

/** @addtogroup USBH_USER
* @{
*/

/** @defgroup USB_BSP
  * @brief This file is responsible to offer board support package
  * @{
  */

/** @defgroup USB_BSP_Private_Defines
  * @{
  */
//#define USE_ACCURATE_TIME
#define TIM_MSEC_DELAY                     0x01
#define TIM_USEC_DELAY                     0x02
#define HOST_OVRCURR_PORT                  GPIOE
#define HOST_OVRCURR_LINE                  GPIO_Pin_1
#define HOST_OVRCURR_PORT_SOURCE           GPIO_PortSourceGPIOE
#define HOST_OVRCURR_PIN_SOURCE            GPIO_PinSource1
#define HOST_OVRCURR_PORT_RCC              RCC_APB2Periph_GPIOE
#define HOST_OVRCURR_EXTI_LINE             EXTI_Line1
#define HOST_OVRCURR_IRQn                  EXTI1_IRQn

#define HOST_SOF_OUTPUT_RCC                RCC_APB2Periph_GPIOA
#define HOST_SOF_PORT                      GPIOA
#define HOST_SOF_SIGNAL                    GPIO_Pin_8

/**
  * @}
  */


/** @defgroup USB_BSP_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */



/** @defgroup USB_BSP_Private_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup USBH_BSP_Private_Variables
  * @{
  */
#ifdef USE_ACCURATE_TIME
__IO uint32_t BSP_delay = 0;
#endif
/**
  * @}
  */

/** @defgroup USBH_BSP_Private_FunctionPrototypes
  * @{
  */

#ifdef USE_ACCURATE_TIME
static void BSP_SetTime(uint8_t Unit);
static void BSP_Delay(uint32_t nTime, uint8_t Unit);
static void USB_OTG_BSP_TimeInit(void);
#endif
/**
  * @}
  */

/** @defgroup USB_BSP_Private_Functions
  * @{
  */

/**
  * @brief  USB_OTG_BSP_Init
  *         Initializes BSP configurations
  * @param  None
  * @retval None
  */

void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE * pdev)
{
#if defined (USE_USB_OTG_FS)
  /* USB clock 48MHz XTAL */
  SYSCFG0_USBFSClockConfig(SYSCFG0_USBFS_CLKSRC_PLL1, 3);
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_USBFS, ENABLE);
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_USBFS);
  STD_Delay(20);
#endif
  
#if defined (USE_USB_OTG_HS)
  /* USB clock 12MHz XTAL */
  SYSCFG0_USBHSClockConfig(SYSCFG0_USBHS_CLKSRC_XOH, 1);
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_USBHS, ENABLE);
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_USBHS);
  STD_Delay(20);
#endif
}

/**
  * @brief  USB_OTG_BSP_EnableInterrupt
  *         Configures USB Global interrupt
  * @param  None
  * @retval None
  */
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE * pdev)
{
uint32_t prioritygroup;
#if defined (USE_USB_OTG_FS)
  NVIC_DisableIRQ(USB_FS_IRQn);
  prioritygroup = NVIC_GetPriorityGrouping();
  NVIC_SetPriority(USB_FS_IRQn, NVIC_EncodePriority(prioritygroup, 3, 0));
  NVIC_EnableIRQ(USB_FS_IRQn);
#endif
#if defined (USE_USB_OTG_HS)
  NVIC_DisableIRQ(USB_HS_IRQn);
  prioritygroup = NVIC_GetPriorityGrouping();
  NVIC_SetPriority(USB_HS_IRQn, NVIC_EncodePriority(prioritygroup, 3, 0));
  NVIC_EnableIRQ(USB_HS_IRQn);
#endif
}

/**
  * @brief  BSP_Drive_VBUS
  *         Drives the Vbus signal through IO
  * @param  state : VBUS states
  * @retval None
  */

void USB_OTG_BSP_DriveVBUS(USB_OTG_CORE_HANDLE * pdev, uint8_t state)
{

}

/**
  * @brief  USB_OTG_BSP_ConfigVBUS
  *         Configures the IO for the Vbus and OverCurrent
  * @param  None
  * @retval None
  */

void USB_OTG_BSP_ConfigVBUS(USB_OTG_CORE_HANDLE * pdev)
{
}

/**
  * @brief  USB_OTG_BSP_TimeInit
  *         Initializes delay unit using Timer2
  * @param  None
  * @retval None
  */
static void USB_OTG_BSP_TimeInit(void)
{
#ifdef USE_ACCURATE_TIME
#endif
}

/**
  * @brief  USB_OTG_BSP_uDelay
  *         This function provides delay time in micro sec
  * @param  usec : Value of delay required in micro sec
  * @retval None
  */
#define count_us   12
void USB_OTG_BSP_uDelay(const uint32_t usec)
{

#ifdef USE_ACCURATE_TIME
#endif
  uint32_t count = count_us * usec;
  do
  {
    if (--count == 0)
    {
      return;
    }
  }
  while (1);
}


/**
  * @brief  USB_OTG_BSP_mDelay
  *          This function provides delay time in milli sec
  * @param  msec : Value of delay required in milli sec
  * @retval None
  */
void USB_OTG_BSP_mDelay(const uint32_t msec)
{
#ifdef USE_ACCURATE_TIME
  
#endif
  STD_Delay(msec);
}


/**
  * @brief  USB_OTG_BSP_TimerIRQ
  *         Time base IRQ
  * @param  None
  * @retval None
  */

void USB_OTG_BSP_TimerIRQ(void)
{
#ifdef USE_ACCURATE_TIME
#endif
}

#ifdef USE_ACCURATE_TIME
/**
  * @brief  BSP_Delay
  *         Delay routine based on TIM2
  * @param  nTime : Delay Time 
  * @param  unit : Delay Time unit : mili sec / micro sec
  * @retval None
  */
static void BSP_Delay(uint32_t nTime, uint8_t unit)
{
}

/**
  * @brief  BSP_SetTime
  *         Configures TIM2 for delay routine based on TIM2
  * @param  unit : msec /usec
  * @retval None
  */
static void BSP_SetTime(uint8_t unit)
{
}

#endif

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
