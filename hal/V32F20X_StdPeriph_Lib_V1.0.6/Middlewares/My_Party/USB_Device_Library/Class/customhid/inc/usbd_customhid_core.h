/**
  * @file    usbd_customhid_core.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   header file for the usbd_customhid_core.c file.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#ifndef __USB_CUSTOMHID_CORE_H_
#define __USB_CUSTOMHID_CORE_H_

#include  "usbd_ioreq.h"
/** @addtogroup USB_OTG_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup USBD_CUSTOMHID
  * @brief This file is the Header file for usbd_customhid_core.c
  * @{
  */ 


/** @defgroup USBD_CUSTOMHID_Exported_Defines
  * @{
  */ 
#define USBD_CUSTOM_HID_REPORT_DESC_SIZE     163

#define USB_CUSTOM_HID_CONFIG_DESC_SIZ       41
#define USB_CUSTOM_HID_DESC_SIZ              9

#define CUSTOM_HID_DESCRIPTOR_TYPE           0x21
#define CUSTOM_HID_REPORT_DESC               0x22


#define CUSTOM_HID_REQ_SET_PROTOCOL          0x0B
#define CUSTOM_HID_REQ_GET_PROTOCOL          0x03

#define CUSTOM_HID_REQ_SET_IDLE              0x0A
#define CUSTOM_HID_REQ_GET_IDLE              0x02

#define CUSTOM_HID_REQ_SET_REPORT            0x09
#define CUSTOM_HID_REQ_GET_REPORT            0x01

#define LED1_REPORT_ID                       0x01
#define LED1_REPORT_COUNT                    0x01

#define LED2_REPORT_ID                       0x02
#define LED2_REPORT_COUNT                    0x01

#define LED3_REPORT_ID                       0x03
#define LED3_REPORT_COUNT                    0x01

#define LED4_REPORT_ID                       0x04
#define LED4_REPORT_COUNT                    0x01

#define KEY_REPORT_ID                        0x05
#define TAMPER_REPORT_ID                     0x06
#define ADC_REPORT_ID                        0x07
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
extern USBD_Class_cb_TypeDef  USBD_CUSTOMHID_cb;
/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */ 
uint8_t USBD_CUSTOM_HID_SendReport (USB_OTG_CORE_HANDLE  *pdev, 
                                 uint8_t *report,
                                 uint16_t len);
/**
  * @}
  */ 

#endif  /* __USB_CUSTOMHID_CORE_H_ */
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/*********************************** END OF FILE ******************************/
