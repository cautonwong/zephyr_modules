/**
  * @file    main.h
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program head.
******************************************************************************/

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "target.h"
#include "target_isr.h"
#include "board.h"

#define PLAY_I2S                        (I2S0)
#define PLAY_I2S_DMA_REQ                (SYSCFG0_DMA_REQUEST_I2S0_TX)
#define PLAY_I2S_PERH_RESET()           SYSCFG0_Periph0Reset(SYSCFG0_Periph0Reset_I2S0)
#define PLAY_I2S_ADDRESS                ((uint32_t)(&I2S0->TXDMA))
#define PLAY_I2S_WS_PIN                 (GPIO_Pin_9)
#define PLAY_I2S_WS_GPIO                (GPIOB)
#define PLAY_I2S_CLK_PIN                (GPIO_Pin_10)
#define PLAY_I2S_SCK_GPIO               (GPIOB)
#define PLAY_I2S_SD_PIN                 (GPIO_Pin_15)
#define PLAY_I2S_SD_GPIO                (GPIOB)
#define PLAY_I2S_MCK_PIN                (GPIO_Pin_6)
#define PLAY_I2S_MCK_GPIO               (GPIOC)
#define PLAY_I2S_WS_PINSRC              (GPIO_PinSource9)
#define PLAY_I2S_CLK_PINSRC             (GPIO_PinSource10)
#define PLAY_I2S_SD_PINSRC              (GPIO_PinSource15)
#define PLAY_I2S_MCK_PINSRC             (GPIO_PinSource6)

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/*********************************** END OF FILE ******************************/
