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
  *   This demo shows how to configure the TMR peripheral to generate four different 
  *   signals with four different delays.
  *   
  *   GTMR0 Configuration: 
  *     GTMR0 CLK = SystemCoreClock / 4,
  *     The objective is to get GTMR0 counter clock at 1 KHz:
  *      - Prescaler = (GTMR0 CLK / GTMR0 counter clock) - 1
  *     And generate 4 signals with 4 different delays:
  *     GTMR0_CH1 delay = CCR1_Val/GTMR0 counter clock = 1000 ms
  *     GTMR0_CH2 delay = CCR2_Val/GTMR0 counter clock = 500 ms
  *     GTMR0_CH3 delay = CCR3_Val/GTMR0 counter clock = 250 ms
  *     GTMR0_CH4 delay = CCR4_Val/GTMR0 counter clock = 125 ms
  *     
  *   Set-up 
  *     - Connect the following pins to an oscilloscope to monitor the different 
  *       waveforms:
  *        - PC.06
  *        - PA.15 (GTMR0_CH1)
  *        - PB.03 (GTMR0_CH2)
  *        - PB.10 (GTMR0_CH3)
  *        - PB.11 (GTMR0_CH4)
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
