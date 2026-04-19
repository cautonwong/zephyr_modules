/**
  ******************************************************************************
  * @file    Templates/readme.txt 
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-08-24
  * @brief   readme
  ******************************************************************************
  * @Description
  * 
  *   This demo is a I2S0 DMA transmitting project. The PLL1 is set to 245.76MHz
  * for I2S0 transmitting. The audio sampling frequency is 48kHz. I2S0 will output
  * 8*16bit data(0x1111...0x8888).
  *
  * Audio Freq = PLL1    / I2S_CLKDIV / (bits in single channel * left and rigth channel)
  * 48K        = 245.76M / 160        / (16                     * 2)
  *
  * Hardware:
  *   I2S0 WS   : PB.9
  *   I2S0 SCK  : PB.10
  *   I2S0 SD   : PB.15
  *   I2S0 MCK  : PC.6
  *   
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, SCTEK SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Vangotech</center></h2>
  ******************************************************************************
  */ 

/*********************************** END OF FILE ******************************/
