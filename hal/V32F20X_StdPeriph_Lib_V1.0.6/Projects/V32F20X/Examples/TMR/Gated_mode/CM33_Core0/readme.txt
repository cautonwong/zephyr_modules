/**
  ******************************************************************************
  * @file    readme.txt 
  * @author  Application Team
  * @version V1.0.0
  * @date    2022-08-17
  * @brief   readme
  ******************************************************************************
  * @Description
  * 
  *   This demo shows how to test Gated mode with an external trigger.
  *   
  *   Gated mode test -----
  *     1/TMR1 is configured as Master Timer:
  *      - Toggle Mode is used
  * 
  *     2/TMR1 is configured as Slave Timer for an external Trigger connected
  *      to TMR1 TI2 pin (TMR1 CH2 configured as input pin):
  *      - The TMR1 TI2FP2 is used as Trigger Input
  *      - Rising edge is used to start and stop the TMR1: Gated Mode.
  * 
  *       The Three Timers are running at: 
  *       TMRx frequency = TMRx clock counter/ 2*(TIMx_Period + 1) = 432.432 KHz. 
  *       
  *   Set-up 
  *   - Connect the following pins to an oscilloscope to monitor the different waveforms:
  *       - TMR1 CH1 
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
