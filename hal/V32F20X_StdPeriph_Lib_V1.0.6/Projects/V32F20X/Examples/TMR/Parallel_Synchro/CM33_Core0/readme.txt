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
  *   This demo shows timers synchronisation in parallel mode, GTMR2 is configured 
  *   as Master Timer,GTMR0 and GTMR1 are slaves for GTMR2.
  *   The Master TMRer GTMR2 is running at 187.5 KHz and the duty cycle
  *   is equal to 25%
  *   The GTMR0 is running:
  *   - At (GTMR2 frequency)/ (GTMR0 period + 1) = 18.75 KHz and a duty cycle
  *   equal to TMR3_CCR1/(TMR3_ARR + 1) = 30%
  *   The GTMR1 is running:
  *   - At (GTMR2 frequency)/ (GTMR1 period + 1) = 37.5 KHz and a duty cycle
  *   equal to TMR4_CCR1/(TMR4_ARR + 1) = 60%
  *   
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
