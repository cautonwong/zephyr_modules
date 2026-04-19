/**
  * @file    usbd_flash_if.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   Header for usbd_flash_if.c file.
******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_MAL_H
#define __FLASH_IF_MAL_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_dfu_mal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define FLASH_START_ADD                 0x00000000

#define FLASH_END_ADD                   0x00100000
#define FLASH_IF_STRING                 (unsigned char *) "@Internal Flash   /0x00000000/128*08Kg"

extern DFU_MAL_Prop_TypeDef DFU_Flash_cb;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __FLASH_IF_MAL_H */

/*********************************** END OF FILE ******************************/
