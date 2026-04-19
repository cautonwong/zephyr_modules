/**
  * @file    usbd_audio_out_if.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   header file for the usbd_audio_out_if.c file.
******************************************************************************/
/* Includes ------------------------------------------------------------------*/

#ifndef __USB_AUDIO_OUT_IF_H_
#define __USB_AUDIO_OUT_IF_H_

/** @addtogroup USB_OTG_DEVICE_LIBRARY
  * @{
  */
  
/** @defgroup usbd_audio
  * @brief This file is the Header file for USBD_audio.c
  * @{
  */ 


/** @defgroup usbd_audio_Exported_Defines
  * @{
  */ 
/* Audio Commands enumeration */
typedef enum
{
  AUDIO_CMD_PLAY = 1,
  AUDIO_CMD_PAUSE,
  AUDIO_CMD_STOP,
}AUDIO_CMD_TypeDef;

/* Mute commands */
#define AUDIO_MUTE                      0x01
#define AUDIO_UNMUTE                    0x00

/* Functions return value */
#define AUDIO_OK                        0x00
#define AUDIO_FAIL                      0xFF

/* Audio Machine States */
#define AUDIO_STATE_INACTIVE            0x00
#define AUDIO_STATE_ACTIVE              0x01
#define AUDIO_STATE_PLAYING             0x02
#define AUDIO_STATE_PAUSED              0x03
#define AUDIO_STATE_STOPPED             0x04
#define AUDIO_STATE_ERROR               0x05

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

extern AUDIO_FOPS_TypeDef  AUDIO_OUT_fops;

/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */
/**
  * @}
  */ 

#endif  /* __USB_AUDIO_OUT_IF_H_ */
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/*********************************** END OF FILE ******************************/
