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
  *  This demo shows how to configure the TMR1 peripheral to generate three 
  *  complementary TMR1 signals, to insert a defined dead time value, to use the break 
  *  feature and to lock the desired parameters.
  *  
  *  TMR1 Configuration to:
  *  
  *      1/ Generate 3 complementary PWM signals with 3 different duty cycles:
  *        TIM1CLK is fixed to SystemCoreClock, the TMR1 Prescaler is equal to 0 so the 
  *        TMR1 counter clock used is SystemCoreClock.
  *        * SystemCoreClock is set to 180 MHz .
  *
  *        The objective is to generate PWM signal at 17.57 KHz:
  *        - TIM1_Period = (SystemCoreClock / 17570) - 1
  *
  *        The Three Duty cycles are computed as the following description: 
  *
  *        The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
  *        The channel 2 duty cycle is set to 25% so channel 2N is set to 75%.
  *        The channel 3 duty cycle is set to 12.5% so channel 3N is set to 87.5%.
  *        The Timer pulse is calculated as follows:
  *          - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
  *
  *      2/ Insert a dead time equal to 11/SystemCoreClock ns
  *      3/ Configure the break feature, active at High level, and using the automatic 
  *         output enable feature
  *      4/ Use the Locking parameters level1. 
  *      
  *  The TMR1 waveform can be displayed using an oscilloscope.
  *  
  *  Set-up 
  *    - Connect the TMR1 pins to an oscilloscope to monitor the different waveforms:
  *      - TMR1_CH1  pin   
  *      - TMR1_CH1N pin  
  *      - TMR1_CH2  pin   
  *      - TMR1_CH2N pin  
  *      - TMR1_CH3  pin   
  *      - TMR1_CH3N pin 
  *
  *    - Connect the TMR1 break pin TMR1_BKIN pin (PA.6) to the GND. To generate a 
  *      break event, switch this pin level from 0V to 3.3V.  
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

 



