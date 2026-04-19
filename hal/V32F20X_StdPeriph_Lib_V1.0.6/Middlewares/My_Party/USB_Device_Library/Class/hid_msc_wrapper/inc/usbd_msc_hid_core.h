/**
  * @file    usbd_msc_hid_core.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   header file for the usbd_msc_hid_core.c file.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#ifndef __USB_MSC_HID_CORE_H_
#define __USB_MSC_HID_CORE_H_

#include  "usbd_ioreq.h"

/** @addtogroup USB_OTG_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup USBD_HID
  * @brief This file is the Header file for USBD_msc.c
  * @{
  */ 
#define HID_INTERFACE 0x0
#define MSC_INTERFACE 0x1

/** @defgroup USBD_HID_Exported_Defines
  * @{
  */ 
#define USB_MSC_HID_CONFIG_DESC_SIZ  (USB_HID_CONFIG_DESC_SIZ -9 + USB_MSC_CONFIG_DESC_SIZ)
/**
  * @}
  */ 


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */


/**
  * @}
  */ 



/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */ 

extern USBD_Class_cb_TypeDef  USBD_MSC_HID_cb;
/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */ 

/**
  * @}
  */ 

#endif  /* __USB_HID_CORE_H_ */
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/*********************************** END OF FILE ******************************/
