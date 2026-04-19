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
  *   This demo shows how to configure the TMR1 peripheral to generate 7 PWM signals 
  *   with 4 different duty cycles (50%, 37.5%, 25% and 12.5%).
  *   
  *   The objective is to generate 7 PWM signal at 17.57 KHz:
  *   - TIM1_Period = (SystemCoreClock / 17570) - 1
  *   The channel 1 and channel 1N duty cycle is set to 50%
  *   The channel 2 and channel 2N duty cycle is set to 37.5%
  *   The channel 3 and channel 3N duty cycle is set to 25%
  *   The channel 4 duty cycle is set to 12.5%
  *   The Timer pulse is calculated as follows:
  *     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  *   The TIM1 waveform can be displayed using an oscilloscope.
  * 
  *   Set-up 
  *     - Connect the TMR1 pins to an oscilloscope to monitor the different waveforms:
  *       - TMR1_CH1  pin   
  *       - TMR1_CH1N pin  
  *       - TMR1_CH2  pin   
  *       - TMR1_CH2N pin  
  *       - TMR1_CH3  pin   
  *       - TMR1_CH3N pin 
  *       - TMR1_CH4  pin   
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

 



