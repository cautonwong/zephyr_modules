/**
  ******************************************************************************
  * @file    readme.txt 
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-08-17
  * @brief   readme
  ******************************************************************************
  *   @Description
  *   
  *    This demo shows how to configure the TMR1 peripheral to generate 6 Steps.
  *    In this example, a software COM event is generated each 100 ms: using the SysTick 
  *    interrupt.
  *    The break Polarity is used at High level.
  *  
  *    The following Table describes the TMR1 Channels states:
  *                -----------------------------------------------
  *               | Step1 | Step2 | Step3 | Step4 | Step5 | Step6 |
  *     ----------------------------------------------------------
  *    |Channel1  |   1   |   0   |   0   |   0   |   0   |   1   |
  *     ----------------------------------------------------------
  *    |Channel1N |   0   |   0   |   1   |   1   |   0   |   0   |
  *     ----------------------------------------------------------
  *    |Channel2  |   0   |   0   |   0   |   1   |   1   |   0   |
  *     ----------------------------------------------------------
  *    |Channel2N |   1   |   1   |   0   |   0   |   0   |   0   |
  *     ----------------------------------------------------------
  *    |Channel3  |   0   |   1   |   1   |   0   |   0   |   0   |
  *     ----------------------------------------------------------
  *    |Channel3N |   0   |   0   |   0   |   0   |   1   |   1   |
  *     ----------------------------------------------------------
  *     
  *    Set-up 
  *      - Connect the TMR1 pins to an oscilloscope to monitor the different waveforms:
  *        - TMR1_CH3  pin 
  *        - TMR1_CH1N pin  
  *        - TMR1_CH2  pin   
  *        - TMR1_CH3N pin 
  *        - TMR1_CH1  pin   
  *        - TMR1_CH2N pin 
  *   
  *   @attention
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

 



