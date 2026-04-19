/**
  * @file    usbd_conf_template.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   usb device configuration template file
******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

/* Includes ------------------------------------------------------------------*/
#include "usb_conf.h"

/** @defgroup USB_CONF_Exported_Defines
  * @{
  */ 
#define USE_USB_OTG_HS  

#define USBD_CFG_MAX_NUM           1
#define USB_MAX_STR_DESC_SIZ       64 
#define USBD_EP0_MAX_PACKET_SIZE   64

/**
  * @}
  */ 


/** @defgroup USB_CONF_Exported_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USB_CONF_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USB_CONF_Exported_Variables
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup USB_CONF_Exported_FunctionsPrototype
  * @{
  */ 
/**
  * @}
  */ 


#endif //__USBD_CONF__H__

/*********************************** END OF FILE ******************************/

