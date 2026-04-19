/**
  * @file    usb_bsp.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   This file is responsible to offer board support package and is 
  *          configurable by user.
******************************************************************************/
/* Includes ------------------------------------------------------------------ */
#include "usb_bsp.h"

/** @addtogroup USB_OTG_DEVICE_LIBRARY
* @{
*/

/** @defgroup USB_BSP
* @brief This file is responsible to offer board support package
* @{
*/

/** @defgroup USB_BSP_Private_Defines
* @{
*/
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

/**
* @}
*/

/** @defgroup USBH_BSP_Private_FunctionPrototypes
* @{
*/
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
#ifndef RCH_AUTOTRIM
  /* USB clock 48MHz XTAL */
  SYSCFG0_USBFSClockConfig(SYSCFG0_USBFS_CLKSRC_PLL1, 3);
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_USBFS, ENABLE);
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_USBFS);
#else
  MCO_InitType MCO_InitStruct;
  Autotrim_InitType Autotrim_Initstruct;
  
  /* USB clock 48MHz RCH */
  SYSCFG0_USBFSClockConfig(SYSCFG0_USBFS_CLKSRC_RCH, 1);
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_USBFS, ENABLE);
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_USBFS);
  STD_Delay(20);
  MCO_InitStruct.Source = CLK_MCOSOURCE_RCH;
  MCO_InitStruct.Divider = 256;
  MCO_InitStruct.Output = ENABLE;
  CLK_MCOConfig(CLK_MCO1, &MCO_InitStruct);//IOA8
  
  CLK_AutotrimCmd(DISABLE);
  Autotrim_Initstruct.Autotrim_SRC = SYSLP_AUTOTRIMC_SRC_SEL_RCH;
  Autotrim_Initstruct.Autotrim_LowerExpt = 48000000/1000*(1 - 0.0015);//1ms
  Autotrim_Initstruct.Autotrim_UpperExpt = 48000000/1000*(1 + 0.0015);
  CLK_AutotrimInit(&Autotrim_Initstruct);
  CLK_AutotrimCmd(ENABLE);
#endif
#endif
  
#if defined (USE_USB_OTG_HS)
  /* USB clock 12MHz XTAL */
  SYSCFG0_USBHSClockConfig(SYSCFG0_USBFS_CLKSRC_XOH, 1);
  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_USBHS, ENABLE);
  SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_USBHS);
  STD_Delay(20);
#endif
}

/**
* @brief  USB_OTG_BSP_EnableInterrupt
*         Enable USB Global interrupt
* @param  None
* @retval None
*/
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE * pdev)
{
uint32_t prioritygroup;
#if defined (USE_USB_OTG_FS)
  NVIC_DisableIRQ(USB_FS_IRQn);
  prioritygroup = NVIC_GetPriorityGrouping();
  NVIC_SetPriority(USB_FS_IRQn, NVIC_EncodePriority(prioritygroup, 5, 0));
  NVIC_EnableIRQ(USB_FS_IRQn);
#endif
  
#if defined (USE_USB_OTG_HS)
  NVIC_DisableIRQ(USB_HS_IRQn);
  prioritygroup = NVIC_GetPriorityGrouping();
  NVIC_SetPriority(USB_HS_IRQn, NVIC_EncodePriority(prioritygroup, 5, 0));
  NVIC_EnableIRQ(USB_HS_IRQn);
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
  STD_Delay(msec);
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
