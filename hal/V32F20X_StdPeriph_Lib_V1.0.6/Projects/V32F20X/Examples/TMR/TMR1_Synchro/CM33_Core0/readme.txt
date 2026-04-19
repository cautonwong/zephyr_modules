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
  *   This demo shows ETMR0 and TMRers(GTMR0 and GTMR1) synchronisation in parallel mode  
  *   The Master TMRer ETMR0 is running at:
  *   ETMR0 frequency = ETMR0 counter clock / (TMR1_Period + 1) = 187.5 KHz
  *   and the duty cycle is equal to: TMR1_CCR1/(TMR1_ARR + 1) = 50%
  *
  *   The GTMR0 is running at:
  *   (ETMR0 frequency)/ ((GTMR0 period +1)* (Repetition_Counter+1)) = 12.5 KHz and
  *   a duty cycle equal to TMR3_CCR1/(TMR3_ARR + 1) = 33.3%
  *
  *   The GTMR1 is running at:
  *   (ETMR0 frequency)/ ((GTMR1 period +1)* (Repetition_Counter+1)) = 18.75 KHz and
  *   a duty cycle equal to TMR4_CCR1/(TMR4_ARR + 1) = 50%
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
  */ /*********************************** END OF FILE ******************************/