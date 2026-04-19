/**
  * @file    usbh_usr.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   This file includes the usb host library user callbacks
******************************************************************************/

/* Includes ------------------------------------------------------------------ */
#include <string.h>
#include "usbh_usr.h"
#include "usbh_cdc_core.h"
#include "board.h"

/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_CDC_DEMO_USER_CALLBACKS
* @{
*/

/** @defgroup USBH_USR 
* @brief    This file includes the usb host stack user callbacks
* @{
*/

/** @defgroup USBH_USR_Private_TypesDefinitions
* @{
*/
/**
* @}
*/


/** @defgroup USBH_USR_Private_Defines
* @{
*/

/**
* @}
*/


/** @defgroup USBH_USR_Private_Macros
* @{
*/

/**
* @}
*/


/** @defgroup USBH_USR_Private_Variables
* @{
*/
extern USB_OTG_CORE_HANDLE USB_OTG_Core;
extern USBH_HOST USB_Host;
extern CDC_Usercb_TypeDef UserCb;

uint32_t needSend;
uint32_t txBuffLen;
uint8_t txBuff[1024];

/* Points to the DEVICE_PROP structure of current device */
/* The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_Callbacks = {
  USBH_USR_Init,
  USBH_USR_DeInit,
  USBH_USR_DeviceAttached,
  USBH_USR_ResetDevice,
  USBH_USR_DeviceDisconnected,
  USBH_USR_OverCurrentDetected,
  USBH_USR_DeviceSpeedDetected,
  USBH_USR_Device_DescAvailable,
  USBH_USR_DeviceAddressAssigned,
  USBH_USR_Configuration_DescAvailable,
  USBH_USR_Manufacturer_String,
  USBH_USR_Product_String,
  USBH_USR_SerialNum_String,
  USBH_USR_EnumerationDone,
  USBH_USR_UserInput,
  USBH_USR_Application,
  USBH_USR_DeviceNotSupported,
  USBH_USR_UnrecoveredError
};

/**
* @}
*/

/** @defgroup USBH_USR_Private_Constants
* @{
*/
/*--------------- Messages ---------------*/
uint8_t MSG_HOST_INIT[] = "> Host Library Initialized\r\n";
uint8_t MSG_DEV_ATTACHED[] = "> Device Attached\r\n";
uint8_t MSG_DEV_DISCONNECTED[] = "> Device Disconnected\r\n";
uint8_t MSG_DEV_ENUMERATED[] = "> Enumeration completed\r\n";
uint8_t MSG_DEV_HIGHSPEED[] = "> High speed device detected\r\n";
uint8_t MSG_DEV_FULLSPEED[] = "> Full speed device detected\r\n";
uint8_t MSG_DEV_LOWSPEED[] = "> Low speed device detected\r\n";
uint8_t MSG_DEV_ERROR[] = "> Device fault\r\n";
uint8_t MSG_CDC_CLASS[] = "> CDC device connected\r\n";
uint8_t MSG_UNREC_ERROR[] = "> Unrecovered error\r\n";
/**
* @}
*/

/** @defgroup USBH_USR_Private_FunctionPrototypes
* @{
*/
static void CDC_OutputData(uint8_t * ptr, uint32_t len);
/**
* @}
*/


/** @defgroup USBH_USR_Private_Functions
* @{
*/


/**
* @brief  USBH_USR_Init 
* @param  None
* @retval None
*/
void USBH_USR_Init(void)
{
  static uint8_t startup = 0;
  
  needSend = 0;
  if (startup == 0)
  {
    startup = 1;
    BSP_Printf_Init();
    
#ifdef USE_USB_OTG_HS
  #ifdef USE_EMBEDDED_PHY
  printf("USB OTG HS_IN_FS MSC Host");
  #else
  printf("USB OTG HS MSC Host");
  #endif
#else
    printf("USB OTG FS CDC Host");
#endif
    printf("> USB Host library started.\n\r");
    printf("USB Host Library v2.2.1\r\n");
  }
}

/**
* @brief  USBH_USR_DeviceAttached 
*         Displays the message on device attached
* @param  None
* @retval None
*/
void USBH_USR_DeviceAttached(void)
{
  printf("%s", (char *)MSG_DEV_ATTACHED);
}


/**
* @brief  USBH_USR_UnrecoveredError
* @param  None
* @retval None
*/
void USBH_USR_UnrecoveredError(void)
{
  /* Set default screen color */
  printf("%s", (char *)MSG_UNREC_ERROR);
}


/**
* @brief  USBH_DisconnectEvent
*         Device disconnect event
* @param  None
* @retval Status
*/
void USBH_USR_DeviceDisconnected(void)
{
  printf("%s", (char *)MSG_DEV_DISCONNECTED);
}

/**
* @brief  USBH_USR_ResetUSBDevice 
* @param  None
* @retval None
*/
void USBH_USR_ResetDevice(void)
{
  /* callback for USB-Reset */
}


/**
* @brief  USBH_USR_DeviceSpeedDetected 
*         Displays the message on LCD for device speed
* @param  Device speed
* @retval None
*/
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
  if (DeviceSpeed == HPRT0_PRTSPD_HIGH_SPEED)
  {
    printf("%s", (char *)MSG_DEV_HIGHSPEED);
  }
  else if (DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
  {
    printf("%s", (char *)MSG_DEV_FULLSPEED);
  }
  else if (DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
  {
    printf("%s", (char *)MSG_DEV_LOWSPEED);
  }
  else
  {
    printf("%s", (char *)MSG_DEV_ERROR);
  }
}

/**
* @brief  USBH_USR_Device_DescAvailable 
*         Displays the message on LCD for device descriptor
* @param  device descriptor
* @retval None
*/
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{
  USBH_DevDesc_TypeDef *hs;
  hs = DeviceDesc;
  
  printf("VID : %04uh\n\r", (uint32_t) (*hs).idVendor);
  printf("PID : %04uh\n\r", (uint32_t) (*hs).idProduct);
}

/**
* @brief  USBH_USR_DeviceAddressAssigned 
*         USB device is successfully assigned the Address 
* @param  None
* @retval None
*/
void USBH_USR_DeviceAddressAssigned(void)
{

}


/**
* @brief  USBH_USR_Conf_Desc 
*         Displays the message on LCD for configuration descriptor
* @param  Configuration descriptor
* @retval None
*/
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef * itfDesc,
                                          USBH_EpDesc_TypeDef * epDesc)
{
  USBH_InterfaceDesc_TypeDef *id;

  id = itfDesc;

  if ((*id).bInterfaceClass == COMMUNICATION_DEVICE_CLASS_CODE)
  {
    printf("%s", (char *)MSG_CDC_CLASS);
  }
  else if ((*id).bInterfaceClass == 0x03)
  {
    printf("USB Class NOT supported");
  }
}

/**
* @brief  USBH_USR_Manufacturer_String 
*         Displays the message on LCD for Manufacturer String 
* @param  Manufacturer String 
* @retval None
*/
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
  printf("Manufacturer : %s\r\n", (char *)ManufacturerString);
}

/**
* @brief  USBH_USR_Product_String 
*         Displays the message on LCD for Product String
* @param  Product String
* @retval None
*/
void USBH_USR_Product_String(void *ProductString)
{
  printf("Product : %s\r\n", (char *)ProductString);
}

/**
* @brief  USBH_USR_SerialNum_String 
*         Displays the message on LCD for SerialNum_String 
* @param  SerialNum_String 
* @retval None
*/
void USBH_USR_SerialNum_String(void *SerialNumString)
{
  printf("Serial Number : %s\r\n", (char *)SerialNumString);
}



/**
* @brief  EnumerationDone 
*         User response request is displayed to ask application jump to class
* @param  None
* @retval None
*/
void USBH_USR_EnumerationDone(void)
{
  /* Enumeration complete */
  printf("%s", (char *)MSG_DEV_ENUMERATED);
  UserCb.Receive = CDC_OutputData;
}


/**
* @brief  USBH_USR_DeviceNotSupported
*         Device is not supported
* @param  None
* @retval None
*/
void USBH_USR_DeviceNotSupported(void)
{
  printf("No registered class for this device. \n\r");
}


/**
* @brief  USBH_USR_UserInput
*         User Action for application state entry
* @param  None
* @retval USBH_USR_Status : User response for key button
*/
USBH_USR_Status USBH_USR_UserInput(void)
{
  USBH_USR_Status usbh_usr_status;

  usbh_usr_status = USBH_USR_RESP_OK;

  return usbh_usr_status;
}

/**
* @brief  USBH_USR_OverCurrentDetected
*         Over Current Detected on VBUS
* @param  None
* @retval Status
*/
void USBH_USR_OverCurrentDetected(void)
{
  printf("Overcurrent detected.\r\n");
}


/**
* @brief  USBH_USR_Application 
*         Demo application for mass storage
* @param  None
* @retval Status
*/
int USBH_USR_Application(void)
{
  if (needSend)
  {
    needSend = 0;
    CDC_SendData(txBuff, txBuffLen);
  }
  return (0);
}

/**
* @brief  USBH_USR_DeInit
*         Deinit User state and associated variables
* @param  None
* @retval None
*/
void USBH_USR_DeInit(void)
{
}

/*
**
* @brief  Displays a maximum of 40 small font char on the LCD.
* @param  ptr: pointer to string to display on LCD.
* @retval None
*/
static void CDC_OutputData(uint8_t * ptr, uint32_t len)
{
  printf("data received:");
  for (uint32_t i = 0; i < len; i++)
  {
    printf("0x%x ", ptr[i]);
  }
  printf("\r\n");
}


void LoadSendBuffer(uint8_t *buff, uint32_t len)
{
  needSend = 1;
  txBuffLen = len;
  memcpy(txBuff, buff, len);
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

/**
* @}
*/

/*********************************** END OF FILE ******************************/
