/**
  * @file    usbd_cdc_core.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   header file for the usbd_cdc_core.c file.
******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#ifndef __USB_CDC_CORE_H_
#define __USB_CDC_CORE_H_

#include  "usbd_ioreq.h"

/** @addtogroup USB_OTG_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup usbd_cdc
  * @brief This file is the Header file for USBD_cdc.c
  * @{
  */ 


/** @defgroup usbd_cdc_Exported_Defines
  * @{
  */ 
#define USB_CDC_CONFIG_DESC_SIZ                (67)
#define USB_CDC_DESC_SIZ                       (67-9)

#define DEVICE_CLASS_CDC                        0x02
#define DEVICE_SUBCLASS_CDC                     0x00

#define CDC_DATA_IN_PACKET_SIZE                CDC_DATA_MAX_PACKET_SIZE
        
#define CDC_DATA_OUT_PACKET_SIZE               CDC_DATA_MAX_PACKET_SIZE

/**
  * @}
  */ 
/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */
typedef struct _CDC_IF_PROP
{
  uint16_t (*pIf_DataTx)   (void);
  uint16_t (*pIf_DataRx)   (uint32_t Len);
}
CDC_IF_Prop_TypeDef;
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

extern USBD_Class_cb_TypeDef  USBD_CDC_cb;
/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */
/**
  * @}
  */ 

#endif  /* __USB_CDC_CORE_H_ */
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/*********************************** END OF FILE ******************************/
