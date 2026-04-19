/**
  * @file    usbd_ioreq.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   header file for the usbd_ioreq.c file
******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __USBD_IOREQ_H_
#define __USBD_IOREQ_H_

/* Includes ------------------------------------------------------------------*/
#include  "usbd_def.h"
#include  "usbd_core.h"

/** @addtogroup USB_OTG_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup USBD_IOREQ
  * @brief header file for the usbd_ioreq.c file
  * @{
  */ 

/** @defgroup USBD_IOREQ_Exported_Defines
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_IOREQ_Exported_Types
  * @{
  */


/**
  * @}
  */ 



/** @defgroup USBD_IOREQ_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USBD_IOREQ_Exported_Variables
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USBD_IOREQ_Exported_FunctionsPrototype
  * @{
  */ 

USBD_Status  USBD_CtlSendData (USB_OTG_CORE_HANDLE  *pdev, 
                               uint8_t *buf,
                               uint16_t len);

USBD_Status  USBD_CtlContinueSendData (USB_OTG_CORE_HANDLE  *pdev, 
                               uint8_t *pbuf,
                               uint16_t len);

USBD_Status USBD_CtlPrepareRx (USB_OTG_CORE_HANDLE  *pdev, 
                               uint8_t *pbuf,                                 
                               uint16_t len);

USBD_Status  USBD_CtlContinueRx (USB_OTG_CORE_HANDLE  *pdev, 
                              uint8_t *pbuf,                                          
                              uint16_t len);

USBD_Status  USBD_CtlSendStatus (USB_OTG_CORE_HANDLE  *pdev);

USBD_Status  USBD_CtlReceiveStatus (USB_OTG_CORE_HANDLE  *pdev);

uint16_t  USBD_GetRxCount (USB_OTG_CORE_HANDLE  *pdev , 
                           uint8_t epnum);

/**
  * @}
  */ 

#endif /* __USBD_IOREQ_H_ */

/**
  * @}
  */ 

/**
* @}
*/ 
/*********************************** END OF FILE ******************************/
