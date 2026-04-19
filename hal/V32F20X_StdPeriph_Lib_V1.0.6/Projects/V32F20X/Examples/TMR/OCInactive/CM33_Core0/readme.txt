/**
  ******************************************************************************
  * @file    Templates/readme.txt 
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-08-17
  * @brief   readme
  ******************************************************************************
  * @Description
  * 
  *   This demo shows how to configure the TMR peripheral in Output Compare Inactive 
  *   mode with the corresponding Interrupt requests for each channel.
  *   
  *   ETMR1 Configuration: 
  *     ETMR1 CLK = SystemCoreClock / 4,
  *     The objective is to get ETMR1 counter clock at 1 KHz:
  *      - Prescaler = (TIM2CLK / ETMR1 counter clock) - 1
  *     And generate 4 signals with 4 different delays:
  *     ETMR1_CH1 delay = CCR1_Val/ETMR1 counter clock = 1000 ms
  *     ETMR1_CH2 delay = CCR2_Val/ETMR1 counter clock = 500 ms
  *     ETMR1_CH3 delay = CCR3_Val/ETMR1 counter clock = 250 ms
  *     ETMR1_CH4 delay = CCR4_Val/ETMR1 counter clock = 125 ms
  *     
  *   Set-up 
  *     - Connect the following pins to an oscilloscope to monitor the different 
  *       waveforms:
  *         - PC.06
  *         - PC.07
  *         - PC.08 
  *         - PC.09
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
