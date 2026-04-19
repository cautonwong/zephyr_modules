/**
  * @file    usb_otg.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   OTG Core Header
******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_OTG__
#define __USB_OTG__


/** @addtogroup USB_OTG_DRIVER
  * @{
  */
  
/** @defgroup USB_OTG
  * @brief This file is the 
  * @{
  */ 


/** @defgroup USB_OTG_Exported_Defines
  * @{
  */ 


void USB_OTG_InitiateSRP(void);
void USB_OTG_InitiateHNP(uint8_t state , uint8_t mode);
void USB_OTG_Switchback (USB_OTG_CORE_DEVICE *pdev);
uint32_t  USB_OTG_GetCurrentState (USB_OTG_CORE_DEVICE *pdev);

/**
  * @}
  */ 


/** @defgroup USB_OTG_Exported_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USB_OTG_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USB_OTG_Exported_Variables
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USB_OTG_Exported_FunctionsPrototype
  * @{
  */ 
/**
  * @}
  */ 


#endif //__USB_OTG__


/**
  * @}
  */ 

/**
  * @}
  */ 
/*********************************** END OF FILE ******************************/

