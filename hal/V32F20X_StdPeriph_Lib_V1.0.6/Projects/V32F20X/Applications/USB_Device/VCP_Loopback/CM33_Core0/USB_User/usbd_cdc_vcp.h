/**
  * @file    usbd_cdc_vcp.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Header for usbd_cdc_vcp.c file.
******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_VCP_H
#define __USBD_CDC_VCP_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_core_loopback.h"
#include "string.h"
/* Exported typef ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* send data function */
void VCP_SendData( USB_OTG_CORE_HANDLE *pdev, uint8_t* pbuf, uint32_t  buf_len);
uint32_t VCP_CheckDataSent (void);
void VCP_ReceiveData(USB_OTG_CORE_HANDLE *pdev, uint8_t  *pbuf, uint32_t   buf_len);
uint32_t VCP_CheckDataReceived(void);

#endif /* __USBD_CDC_VCP_H */

/*********************************** END OF FILE ******************************/
