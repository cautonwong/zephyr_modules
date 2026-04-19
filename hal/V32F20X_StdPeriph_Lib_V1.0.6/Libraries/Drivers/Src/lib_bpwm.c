/**
  ******************************************************************************
  * @file    lib_bpwm.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-07-06
  * @brief   This file provides all the BPWM firmware functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/  
#include "lib_bpwm.h"

/** @addtogroup StdPeriph_Driver
  * @{
  */

/** @defgroup BPWM
  * @brief BPWM driver modules
  * @{
  */

/** @defgroup BPWM_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup BPWM_Private_Defines
  * @{
  */

/*******************  Bit definition for BPWM CTRL register  ********************/
#define BPWM_CTL_ID_MASK                ((uint32_t)0x000000C0)
#define BPWM_CTL_MC_MASK                ((uint32_t)0x00000030)
#define BPWM_CTL_TSEL                   ((uint32_t)0x00000008)

#define BPWM_CTL_IE_Pos                 ((uint32_t)0x00000001)                           
#define BPWM_CTL_IE_Msk                 (((uint32_t)0x00000001) << BPWM_CTL_IE_Pos)                
#define BPWM_CTL_IE                      BPWM_CTL_IE_Msk     
                                        
#define BPWM_CTL_CLR_Pos                ((uint32_t)0x00000002)                                     
#define BPWM_CTL_CLR_Msk                (((uint32_t)0x00000001) << BPWM_CTL_CLR_Pos)              
#define BPWM_CTL_CLR                     BPWM_CTL_CLR_Msk   
                                        
#define BPWM_CTL_IFG_Pos                ((uint32_t)0x00000000)                                   
#define BPWM_CTL_IFG_Msk                (((uint32_t)0x00000001) << BPWM_CTL_IFG_Pos)              
#define BPWM_CTL_IFG                    BPWM_CTL_IFG_Msk        

#define BPWM_CTL_ID_MC_TSEL_CLR         REG_BIT_NOT(BPWM_CTL_ID_MASK |\
                                                   BPWM_CTL_MC_MASK |\
                                                   BPWM_CTL_TSEL)
#define BPWM_CTL_IE_IFG_CLR             REG_BIT_NOT(BPWM_CTL_IE |\
                                                   BPWM_CTL_IFG)

/*******************  Bit definition for BPWM CCTL register  ********************/
#define BPWM_CCTL_CCIGG_Pos             ((uint32_t)0x00000000)                                       
#define BPWM_CCTL_CCIGG_Msk             (((uint32_t)0x00000001) << BPWM_CCTL_CCIGG_Pos)           
#define BPWM_CCTL_CCIGG                 BPWM_CCTL_CCIGG_Msk   
                                        
#define BPWM_CCTL_CAP_Pos               ((uint32_t)0x00000008)                                    
#define BPWM_CCTL_CAP_Msk               (((uint32_t)0x00000001) << BPWM_CCTL_CAP_Pos)             
#define BPWM_CCTL_CAP                   BPWM_CCTL_CAP_Msk             
                                        
#define BPWM_CCTL_OUTEN_Pos             ((uint32_t)0x00000009)                                    
#define BPWM_CCTL_OUTEN_Msk             (((uint32_t)0x00000001) << BPWM_CCTL_OUTEN_Pos)           
#define BPWM_CCTL_OUTEN                  BPWM_CCTL_OUTEN_Msk           
                                        
#define BPWM_CCTL_SCCI_Pos              ((uint32_t)0x0000000A)                                   
#define BPWM_CCTL_SCCI_Msk              (((uint32_t)0x00000001) << BPWM_CCTL_SCCI_Pos)            
#define BPWM_CCTL_SCCI                  BPWM_CCTL_SCCI_Msk  
                                        
#define BPWM_CCTL_COV_Pos               ((uint32_t)0x00000001)                                 
#define BPWM_CCTL_COV_Msk               (((uint32_t)0x00000001) << BPWM_CCTL_COV_Pos)             
#define BPWM_CCTL_COV                   BPWM_CCTL_COV_Msk             
                                        
#define BPWM_CCTL_CCIE_Pos              ((uint32_t)0x00000004)                                    
#define BPWM_CCTL_CCIE_Msk              (((uint32_t)0x00000001) << BPWM_CCTL_CCIE_Pos)            
#define BPWM_CCTL_CCIE                  BPWM_CCTL_CCIE_Msk   
                                        
#define BPWM_CCTL_OUTMOD_Pos            ((uint32_t)0x00000005)                                    
#define BPWM_CCTL_OUTMOD_Msk            (((uint32_t)0x00000007) << BPWM_CCTL_OUTMOD_Pos)          
#define BPWM_CCTL_OUTMOD                BPWM_CCTL_OUTMOD_Msk  
                                        
#define BPWM_CCTL_CM_Pos                ((uint32_t)0x0000000E)                                 
#define BPWM_CCTL_CM_Msk                (((uint32_t)0x00000003) << BPWM_CCTL_CM_Pos)              
#define BPWM_CCTL_CM                    BPWM_CCTL_CM_Msk 

#define BPWM_CCTL_CM_MASK               ((uint32_t)0x0000C000)   
#define BPWM_CCTL_OUTMOD_MASK           ((uint32_t)0x000000E0)   
#define BPWM_CCTL_CCIFG                 ((uint32_t)0x00000001)   

#define BPWM_CCTL_CAP_OUTMODE_CCIFG_COV_CLR     REG_BIT_NOT(BPWM_CCTL_CAP      |\
                                                        BPWM_CCTL_OUTMOD_MASK |\
                                                        BPWM_CCTL_COV         |\
                                                        BPWM_CCTL_CCIFG)

#define BPWM_CCTL_CM_CCIFG_COV_CLR      REG_BIT_NOT(BPWM_CCTL_CM_MASK |\
                                                   BPWM_CCTL_COV     |\
                                                   BPWM_CCTL_CCIFG)

#define BPWM_CCTL_CCIE_CCIFG_COV_CLR    REG_BIT_NOT(BPWM_CCTL_CCIE |\
                                                   BPWM_CCTL_COV  |\
                                                   BPWM_CCTL_CCIFG)

#define BPWM_CCTL_OUTEN_CCIFG_COV_CLR   REG_BIT_NOT(BPWM_CCTL_OUTEN |\
                                                   BPWM_CCTL_COV    |\
                                                BPWM_CCTL_CCIFG)

/*******************  Bit definition for BPWM_O_SEL register  ********************/
#define BPWM_SEL_O_SEL_SEL0             ((uint32_t)0x0000000F) 

#define BPWM_O_SEL_O_SEL0_Pos           ((uint32_t)0x00000000)                                     
#define BPWM_O_SEL_O_SEL0_Msk           (((uint32_t)0x0000000F)  << BPWM_O_SEL_O_SEL0_Pos)          
#define BPWM_O_SEL_O_SEL0               BPWM_O_SEL_O_SEL0_Msk                   
#define BPWM_O_SEL_O_SEL1_Pos           ((uint32_t)0x00000004)                                    
#define BPWM_O_SEL_O_SEL1_Msk           (((uint32_t)0x0000000F) << BPWM_O_SEL_O_SEL1_Pos)          
#define BPWM_O_SEL_O_SEL1               BPWM_O_SEL_O_SEL1_Msk                   
#define BPWM_O_SEL_O_SEL2_Pos           ((uint32_t)0x00000008)                                    
#define BPWM_O_SEL_O_SEL2_Msk           (((uint32_t)0x0000000F) << BPWM_O_SEL_O_SEL2_Pos)          
#define BPWM_O_SEL_O_SEL2               BPWM_O_SEL_O_SEL2_Msk                   
#define BPWM_O_SEL_O_SEL3_Pos           ((uint32_t)0x0000000C)                                   
#define BPWM_O_SEL_O_SEL3_Msk           (((uint32_t)0x0000000F) << BPWM_O_SEL_O_SEL3_Pos)          
#define BPWM_O_SEL_O_SEL3               BPWM_O_SEL_O_SEL3_Msk                   

/*****************  Bits definition for BPWM_I_SEL01 register  ********************/
#define BPWM_I_SEL01_I_SEL00_Pos        ((uint32_t)0x00000000)                                     
#define BPWM_I_SEL01_I_SEL00_Msk        (((uint32_t)0x00000003) << BPWM_I_SEL01_I_SEL00_Pos)       
#define BPWM_I_SEL01_I_SEL00            BPWM_I_SEL01_I_SEL00_Msk   

/**
  * @}
  */

/** @defgroup BPWM_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup BPWM_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup BPWM_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup BPWM_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the BPWM peripheral registers to their default reset
  *         values.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @retval None
  */
void BPWM_DeInit(BPWM_Type *BPWMx)
{
  uint32_t tmp = 0;
  uint32_t i = 0;
  
  /* Check the parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));	
  
  BPWM_OutputCmd(BPWMx, BPWM_CHANNEL_0, DISABLE);
  BPWM_OutputCmd(BPWMx, BPWM_CHANNEL_1, DISABLE);
  BPWM_OutputCmd(BPWMx, BPWM_CHANNEL_2, DISABLE);
  
  BPWMx->CTL = 0;
  for(i = 0; i < 3; i++)
  {
    BPWMx->CCTL[i] = 0;
    BPWMx->CCR[i] = 0;
  }

  if(BPWMx == BPWM4) 
  {
    tmp = BPWM4_7_SEL->O_SEL;
    tmp &= ~BPWM_O_SEL_O_SEL0_Msk;
    tmp |= BPWM_OUTPUT_OFF<<BPWM_O_SEL_O_SEL0_Pos;
    BPWM4_7_SEL->O_SEL = tmp;
    return;
  }
  
  if(BPWMx == BPWM5) 
  {
    tmp = BPWM4_7_SEL->O_SEL;
    tmp &= ~BPWM_O_SEL_O_SEL1_Msk;
    tmp |= BPWM_OUTPUT_OFF<<BPWM_O_SEL_O_SEL1_Pos;
    BPWM4_7_SEL->O_SEL = tmp;
    return;    
  }
  
  if(BPWMx == BPWM6) 
  {
    tmp = BPWM4_7_SEL->O_SEL;
    tmp &= ~BPWM_O_SEL_O_SEL2_Msk;
    tmp |= BPWM_OUTPUT_OFF<<BPWM_O_SEL_O_SEL2_Pos;
    BPWM4_7_SEL->O_SEL = tmp;
    return;       
  }
  if(BPWMx == BPWM7) 
  {
    tmp = BPWM4_7_SEL->O_SEL;
    tmp &= ~BPWM_O_SEL_O_SEL3_Msk;
    tmp |= BPWM_OUTPUT_OFF<<BPWM_O_SEL_O_SEL3_Pos;
    BPWM4_7_SEL->O_SEL = tmp;
    return;       
  }

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
  if(BPWMx == BPWM0) 
  {
    tmp = BPWM0_3_SEL->O_SEL;
    tmp &= ~BPWM_O_SEL_O_SEL0_Msk;
    tmp |= BPWM_OUTPUT_OFF<<BPWM_O_SEL_O_SEL0_Pos;
    BPWM0_3_SEL->O_SEL = tmp;
    return;
  }
  
  if(BPWMx == BPWM1) 
  {
    tmp = BPWM0_3_SEL->O_SEL;
    tmp &= ~BPWM_O_SEL_O_SEL1_Msk;
    tmp |= BPWM_OUTPUT_OFF<<BPWM_O_SEL_O_SEL1_Pos;
    BPWM0_3_SEL->O_SEL = tmp;
    return;    
  }
  
  if(BPWMx == BPWM2) 
  {
    tmp = BPWM0_3_SEL->O_SEL;
    tmp &= ~BPWM_O_SEL_O_SEL2_Msk;
    tmp |= BPWM_OUTPUT_OFF<<BPWM_O_SEL_O_SEL2_Pos;
    BPWM0_3_SEL->O_SEL = tmp;
    return;       
  }
  if(BPWMx == BPWM3) 
  {
    tmp = BPWM0_3_SEL->O_SEL;
    tmp &= ~BPWM_O_SEL_O_SEL3_Msk;
    tmp |= BPWM_OUTPUT_OFF<<BPWM_O_SEL_O_SEL3_Pos;
    BPWM0_3_SEL->O_SEL = tmp;
    return;       
  }
  
#endif  
}

/**
  * @brief  Fills each BPWM_BaseInitType member with its default value.
  * @param  BPWM_BaseInitStruct: pointer to a BPWM_BaseInitType structure which will be initialized.
  * @retval None
  */
void BPWM_BaseStructInit(BPWM_BaseInitType *BPWM_BaseInitStruct)
{
  /*------------ Reset BPWM base init structure parameters values ------------*/
  /* Initialize the ClockDivision member */
  BPWM_BaseInitStruct->ClockDivision = BPWM_CLKDIV_2;
  /* Initialize the ClockSource member */
  BPWM_BaseInitStruct->ClockSource = BPWM_CLKSRC_APBD128; 
  /* Initialize the Mode member */
  BPWM_BaseInitStruct->Mode = BPWM_MODE_STOP; 
}

/**
  * @brief  Initializes the BPWM Time Base Unit peripheral according to 
  *         the specified parameters in the BPWM_BaseInitStruct.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  BPWM_BaseInitStruct:pointer to a BPWM_BaseInitStruct structure 
  *         that contains the configuration information for the 
  *         specified BPWMx peripheral.
  *         This parameter can be any combination of the following values:
  *             ClockDivision:
  *                 BPWM_CLKDIV_2
  *                 BPWM_CLKDIV_4
  *                 BPWM_CLKDIV_8
  *                 BPWM_CLKDIV_16
  *             Mode:
  *                 BPWM_MODE_STOP
  *                 BPWM_MODE_UPCOUNT
  *                 BPWM_MODE_CONTINUOUS
  *                 BPWM_MODE_UPDOWN
  *             ClockSource:
  *                 BPWM_CLKSRC_APB
  *                 BPWM_CLKSRC_APBD128
  * @retval None
  */
void BPWM_BaseInit(BPWM_Type *BPWMx, BPWM_BaseInitType *BPWM_BaseInitStruct)
{
  uint32_t tmp = 0;

  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CLKDIV(BPWM_BaseInitStruct->ClockDivision));
  assert_parameters(IS_BPWM_CNTMODE(BPWM_BaseInitStruct->Mode));
  assert_parameters(IS_BPWM_CLKSRC(BPWM_BaseInitStruct->ClockSource));

  tmp = BPWMx->CTL & BPWM_CTL_ID_MC_TSEL_CLR;
  tmp |= (BPWM_BaseInitStruct->ClockDivision\
         |BPWM_BaseInitStruct->Mode\
         |BPWM_BaseInitStruct->ClockSource);
  BPWMx->CTL = tmp;
}

/**
  * @brief  Fills each BPWM_OCInitType member with its default value.
  * @param  BPWM_OCInitType: pointer to an BPWM_OCInitType structure which will be initialized.
  * @retval None
  */
void BPWM_OCStructInit(BPWM_OCInitType *BPWM_OCInitType)
{
  /*------- Reset BPWM output channel init structure parameters values --------*/
  /* Initialize the Channel member */ 
  BPWM_OCInitType->Channel = BPWM_CHANNEL_0;
  /* Initialize the OutMode member */  
  BPWM_OCInitType->OutMode = BPWM_OUTMOD_CONST;
  /* Initialize the Period member */  
  BPWM_OCInitType->Period = 0; 
}

/**
  * @brief  Initializes BPWM channel output compare function.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  BPWM_OCInitStruct: pointer to a BPWM_OCInitType structure 
  *         that contains the configuration information for the 
  *         specified BPWMx peripheral.
  *         This parameter can be any combination of the following values:
  *             Channel:
  *                 BPWM_CHANNEL_0
  *                 BPWM_CHANNEL_1
  *                 BPWM_CHANNEL_2
  *             OutMode:
  *                 BPWM_OUTMOD_CONST
  *                 BPWM_OUTMOD_SET
  *                 BPWM_OUTMOD_TOGGLE_RESET
  *                 BPWM_OUTMOD_SET_RESET
  *                 BPWM_OUTMOD_TOGGLE
  *                 BPWM_OUTMOD_RESET
  *                 BPWM_OUTMOD_TOGGLE_SET
  *                 BPWM_OUTMOD_RESET_SET
  *             Period: 0 ~ 0xFFFF
  * @retval None
  */
void BPWM_OCInit(BPWM_Type *BPWMx, BPWM_OCInitType *BPWM_OCInitStruct)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CHANNEL(BPWM_OCInitStruct->Channel));
  assert_parameters(IS_BPWM_OUTMODE(BPWM_OCInitStruct->OutMode));
  assert_parameters(IS_BPWM_CCR(BPWM_OCInitStruct->Period));

  tmp = BPWMx->CCTL[BPWM_OCInitStruct->Channel] & BPWM_CCTL_CAP_OUTMODE_CCIFG_COV_CLR;
  tmp |= BPWM_OCInitStruct->OutMode;
  BPWMx->CCTL[BPWM_OCInitStruct->Channel] = tmp;
  BPWMx->CCR[BPWM_OCInitStruct->Channel] = BPWM_OCInitStruct->Period;
}

/**
  * @brief  Fills each BPWM_ICInitType member with its default value.
  * @param  BPWM_ICInitType: pointer to a BPWM_OCInitType structure which will be initialized.
  * @retval None
  */
void BPWM_ICStructInit(BPWM_ICInitType *BPWM_ICInitType)
{
  /*------- Reset BPWM output channel init structure parameters values --------*/
  /* Initialize the Channel member */ 
  BPWM_ICInitType->Channel = BPWM_CHANNEL_0;
  /* Initialize the CaptureMode member */  
  BPWM_ICInitType->CaptureMode = BPWM_CM_DISABLE;
}

/**
  * @brief  Initializes BPWM channel input capture function according to the specified
  *         parameters in the BPWM_ICInitStruct.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  BPWM_ICInitStruct: pointer to a BPWM_ICInitType structure 
  *         that contains the configuration information for the 
  *         specified BPWMx peripheral.
  *         This parameter can be any combination of the following values:
  *             Channel:
  *                 BPWM_CHANNEL_0
  *                 BPWM_CHANNEL_1
  *                 BPWM_CHANNEL_2
  *             CaptureMode:
  *                 BPWM_CM_DISABLE
  *                 BPWM_CM_RISING
  *                 BPWM_CM_FALLING
  *                 BPWM_CM_BOTH
  * @retval None
  */
void BPWM_ICInit(BPWM_Type *BPWMx, BPWM_ICInitType *BPWM_ICInitStruct)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CHANNEL(BPWM_ICInitStruct->Channel));
  assert_parameters(IS_BPWM_CAPMODE(BPWM_ICInitStruct->CaptureMode));

  tmp = BPWMx->CCTL[BPWM_ICInitStruct->Channel] & BPWM_CCTL_CM_CCIFG_COV_CLR;
  tmp |= (BPWM_ICInitStruct->CaptureMode | BPWM_CCTL_CAP);
  BPWMx->CCTL[BPWM_ICInitStruct->Channel] = tmp;
}

/**
  * @brief  Enables or disables BPWM base interrupt.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  NewState: new state of the BPWM base interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BPWM_BaseINTConfig(BPWM_Type *BPWMx, FunctionalState NewState)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmp = BPWMx->CTL & BPWM_CTL_IE_IFG_CLR;
  if (NewState == ENABLE)
  {
    tmp |= BPWM_CTL_IE;
  }
  BPWMx->CTL = tmp;
}

/**
  * @brief  Checks whether the BPWM interrupt has occurred or not.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @retval The new state of BPWM base interrupt (SET or RESET).
  */
ITStatus BPWM_GetBaseINTStatus(BPWM_Type *BPWMx)
{
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  
  if (BPWMx->CTL & BPWM_CTL_IFG)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears BPWM base interrupt status.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @retval None.
  */
void BPWM_ClearBaseINTStatus(BPWM_Type *BPWMx)
{
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));

  BPWMx->CTL |= BPWM_CTL_IFG;
}

/**
  * @brief  Enables or disables the specified channel interrupt.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  Channel: specifies the BPWM channel to configure.
  *         This parameter can be one of the following values:
  *         @arg BPWM_CHANNEL_0
  *         @arg BPWM_CHANNEL_1
  *         @arg BPWM_CHANNEL_2
  * @param  NewState: new state of the BPWM base interrupt.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval  None
  */
void BPWM_ChannelINTConfig(BPWM_Type *BPWMx, uint32_t Channel, FunctionalState NewState)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CHANNEL(Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));

  tmp = BPWMx->CCTL[Channel] & BPWM_CCTL_CCIE_CCIFG_COV_CLR;
  if (NewState == ENABLE)
  {
    tmp |= BPWM_CCTL_CCIE;
  }
  BPWMx->CCTL[Channel] = tmp;
}

/**
  * @brief  Gets channel interrupt status.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  Channel: specifies the BPWM channel to check.
  *         This parameter can be one of the following values:
  *         @arg BPWM_CHANNEL_0
  *         @arg BPWM_CHANNEL_1 
  *         @arg BPWM_CHANNEL_2 
  * @param  IntMask: specifies the BPWM channel interrupt to check.
  *         This parameter can be one of the following values:
  *         @arg BPWM_INT_CCIFG
  *         @arg BPWM_INT_COV
  * @retval  The new state of BPWM channel interrupt (SET or RESET).
  */
ITStatus BPWM_GetChannelINTStatus(BPWM_Type *BPWMx, uint32_t Channel, uint32_t IntMask)
{
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CHANNEL(Channel));
  assert_parameters(IS_BPWM_CH_INTR(IntMask));

  if (BPWMx->CCTL[Channel] & IntMask)
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/**
  * @brief  Clears channel interrupt status.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  Channel: specifies the BPWM channel to check.
  *         This parameter can be one of the following values:
  *         @arg BPWM_CHANNEL_0
  *         @arg BPWM_CHANNEL_1 
  *         @arg BPWM_CHANNEL_2 
  * @param  IntMask: specifies the BPWM channel interrupt to check.
  *         This parameter can be one of the following values:
  *         @arg BPWM_INT_CCIFG
  *         @arg BPWM_INT_COV
  * @retval  None
  */
void BPWM_ClearChannelINTStatus(BPWM_Type *BPWMx, uint32_t Channel, uint32_t IntMask)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CHANNEL(Channel));
  assert_parameters(IS_BPWM_CH_INTC(IntMask));

  tmp = BPWMx->CCTL[Channel];
  tmp &= ~BPWM_INT_MASK;
  tmp |= IntMask;
  BPWMx->CCTL[Channel] = tmp;
}

/**
  * @brief  Clears the BPWMx counter.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @retval None
  */
void BPWM_ClearCounter(BPWM_Type *BPWMx)
{
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));

  BPWMx->CTL |= BPWM_CTL_CLR;
}

/**
  * @brief  Configures BPWM channel CCR value.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  Channel: specifies the BPWM channel to configure.
  *         This parameter can be one of the following values:
  *         @arg BPWM_CHANNEL_0
  *         @arg BPWM_CHANNEL_1 
  *         @arg BPWM_CHANNEL_2 
  *         Period: 0 ~ 0xFFFF
  * @retval None
  */
void BPWM_CCRConfig(BPWM_Type *BPWMx, uint32_t Channel, uint16_t Period)
{
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CHANNEL(Channel));

  BPWMx->CCR[Channel] = Period;
}

/**
  * @brief  Configures BPWM output line.
  * @param  BPWMx_SEL: select the BPWM0_3 ro BPWM4_7 peripheral.
  *         @arg BPWM0_3_SEL
  *         @arg BPWM4_7_SEL
  * @param  OLine: can use the '|' operator
  *         @arg BPWM_OLINE_0
  *         @arg BPWM_OLINE_1 
  *         @arg BPWM_OLINE_2 
  *         @arg BPWM_OLINE_3 
  * @param  OutSelection:
  *         @arg BPWM0_OUT0
  *         @arg BPWM0_OUT1 
  *         @arg BPWM0_OUT2 
  *         @arg BPWM1_OUT0 
  *         @arg BPWM1_OUT1 
  *         @arg BPWM1_OUT2 
  *         @arg BPWM2_OUT0 
  *         @arg BPWM2_OUT1 
  *         @arg BPWM2_OUT2 
  *         @arg BPWM3_OUT0 
  *         @arg BPWM3_OUT1 
  *         @arg BPWM3_OUT2 
  *         @arg BPWM4_OUT0
  *         @arg BPWM4_OUT1 
  *         @arg BPWM4_OUT2 
  *         @arg BPWM5_OUT0 
  *         @arg BPWM5_OUT1 
  *         @arg BPWM5_OUT2 
  *         @arg BPWM6_OUT0 
  *         @arg BPWM6_OUT1 
  *         @arg BPWM6_OUT2 
  *         @arg BPWM7_OUT0 
  *         @arg BPWM7_OUT1 
  *         @arg BPWM7_OUT2 
  * @note   BPWM Single channel's output waveform can be output on multiple output lines.
  *         Multiple-line configuration can be performed by using the '|' operator.
  *         ex: BPWM_OLineConfig(BPWM0_OUT0, BPWM_OLINE_0 | BPWM_OLINE_2)
  *             BPWM0 channel0 output by BPWM0&BPWM2's line.
  * @retval  None
  */
void BPWM_OLineConfig(BPWM_SEL_Type *BPWMx_SEL, uint32_t OLine, uint32_t OutSelection)
{
  uint32_t tmp;
  uint32_t position = 0;
  
  /* Check parameters */
  assert_parameters(IS_BPWM_SEL_INSTANCE(BPWMx_SEL));
  assert_parameters(IS_BPWM_OUTLINE(OLine));
  assert_parameters(IS_BPWM_OUTSEL(OutSelection));
  
  tmp = BPWMx_SEL->O_SEL;
  while ((OLine >> position) != 0UL)
  {
    if ((OLine >> position) & 1UL)
    {
      tmp &= ~(BPWM_SEL_O_SEL_SEL0 << (position * 4));
      tmp |= (OutSelection << (position * 4));
    }
    position++;
  }
  BPWMx_SEL->O_SEL = tmp;
}

/**
  * @brief  BPWM output compare channel 0.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  OCInitType:BPWM output compare configuration.
  *             OutMode:
  *                 BPWM_OUTMOD_CONST
  *                 BPWM_OUTMOD_SET
  *                 BPWM_OUTMOD_TOGGLE_RESET
  *                 BPWM_OUTMOD_SET_RESET
  *                 BPWM_OUTMOD_TOGGLE
  *                 BPWM_OUTMOD_RESET
  *                 BPWM_OUTMOD_TOGGLE_SET
  *                 BPWM_OUTMOD_RESET_SET
  *             Period: 0 ~ 0xFFFF
  * @retval None
  */
void BPWM_OC0Init(BPWM_Type *BPWMx, BPWM_OCInitType *OCInitType)
{
  uint32_t tmp;
                      
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  
  tmp = BPWMx->CCTL[0];
  tmp &= ~(BPWM_CCTL_OUTMOD | BPWM_CCTL_CCIGG);
  tmp |= OCInitType->OutMode;
  BPWMx->CCTL[0] = tmp;
  BPWMx->CCR[0] = OCInitType->Period;
}

/**
  * @brief  BPWM output compare channel 1.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  OCInitType:BPWM output compare configuration.
  *             OutMode:
  *                 BPWM_OUTMOD_CONST
  *                 BPWM_OUTMOD_SET
  *                 BPWM_OUTMOD_TOGGLE_RESET
  *                 BPWM_OUTMOD_SET_RESET
  *                 BPWM_OUTMOD_TOGGLE
  *                 BPWM_OUTMOD_RESET
  *                 BPWM_OUTMOD_TOGGLE_SET
  *                 BPWM_OUTMOD_RESET_SET
  *             Period: 0 ~ 0xFFFF
  * @retval None
  */
void BPWM_OC1Init(BPWM_Type *BPWMx, BPWM_OCInitType *OCInitType)
{
  uint32_t tmp;
                      
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CCR(OCInitType->Period));
  
  tmp = BPWMx->CCTL[1];
  tmp &= ~(BPWM_CCTL_OUTMOD | BPWM_CCTL_CCIGG);
  tmp |= OCInitType->OutMode;
  BPWMx->CCTL[1] = tmp;
  BPWMx->CCR[1] = OCInitType->Period;
}

/**
  * @brief  BPWM output compare channel 2.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  OCInitType:BPWM output compare configuration.
  *             OutMode:
  *                 BPWM_OUTMOD_CONST
  *                 BPWM_OUTMOD_SET
  *                 BPWM_OUTMOD_TOGGLE_RESET
  *                 BPWM_OUTMOD_SET_RESET
  *                 BPWM_OUTMOD_TOGGLE
  *                 BPWM_OUTMOD_RESET
  *                 BPWM_OUTMOD_TOGGLE_SET
  *                 BPWM_OUTMOD_RESET_SET
  *             Period: 0 ~ 0xFFFF
  * @retval None
  */
void BPWM_OC2Init(BPWM_Type *BPWMx, BPWM_OCInitType *OCInitType)
{
  uint32_t tmp;
                      
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  
  tmp = BPWMx->CCTL[2];
  tmp &= ~(BPWM_CCTL_OUTMOD | BPWM_CCTL_CCIGG);
  tmp |= OCInitType->OutMode;
  BPWMx->CCTL[2] = tmp;
  BPWMx->CCR[2] = OCInitType->Period;
}



/**
  * @brief  Channel0 input capture initialization.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  CaptureMode: specifies the Capture edge
  *         @arg BPWM_CM_DISABLE
  *         @arg BPWM_CM_RISING 
  *         @arg BPWM_CM_FALLING
  *         @arg BPWM_CM_BOTH    
  * @retval  None
  */
void BPWM_IC0Init(BPWM_Type *BPWMx, uint32_t CaptureMode)
{
    uint32_t tmp;
    
    tmp = BPWMx->CCTL[0];
    tmp &= ~(BPWM_CCTL_CM_Msk|BPWM_CCTL_CAP);
    tmp |= (CaptureMode|BPWM_CCTL_CAP);
    BPWMx->CCTL[0] = tmp;
}

/**
  * @brief  Channel1 input capture initialization.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  CaptureMode: specifies the Capture edge
  *         @arg BPWM_CM_DISABLE
  *         @arg BPWM_CM_RISING 
  *         @arg BPWM_CM_FALLING
  *         @arg BPWM_CM_BOTH   
  * @retval  None
  */
void BPWM_IC1Init(BPWM_Type *BPWMx, uint32_t CaptureMode)
{
    uint32_t tmp;
    
    tmp = BPWMx->CCTL[1];
    tmp &= ~(BPWM_CCTL_CM_Msk|BPWM_CCTL_CAP);
    tmp |= (CaptureMode|BPWM_CCTL_CAP);
    BPWMx->CCTL[1] = tmp;
}

/**
  * @brief  Channel2 input capture initialization.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  CaptureMode: specifies the Capture edge
  *         @arg BPWM_CM_DISABLE
  *         @arg BPWM_CM_RISING 
  *         @arg BPWM_CM_FALLING
  *         @arg BPWM_CM_BOTH   
  * @retval  None
  */
void BPWM_IC2Init(BPWM_Type *BPWMx, uint32_t CaptureMode)
{
    uint32_t tmp;
    
    tmp = BPWMx->CCTL[2];
    tmp &= ~(BPWM_I_SEL01_I_SEL00_Msk|BPWM_CCTL_CAP);
    tmp |= (CaptureMode|BPWM_CCTL_CAP);
    BPWMx->CCTL[2] = tmp;
}


/**
  * @brief  Enables or disables BPWM output function.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  Channel: specifies the BPWM channel to configure.
  *         This parameter can be one of the following values:
  *         @arg BPWM_CHANNEL_0
  *         @arg BPWM_CHANNEL_1
  *         @arg BPWM_CHANNEL_2
  * @param  NewState: new state of BPWM output function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval  None
  */
void BPWM_OutputCmd(BPWM_Type *BPWMx, uint32_t Channel, FunctionalState NewState)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));  
  assert_parameters(IS_BPWM_CHANNEL(Channel));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  

  tmp = BPWMx->CCTL[Channel] & BPWM_CCTL_OUTEN_CCIFG_COV_CLR;
  if (NewState == ENABLE)
  {
    tmp |= BPWM_CCTL_OUTEN;
  }
  BPWMx->CCTL[Channel] = tmp;
}

/**
  * @brief  Sets BPWM channel output level.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  Channel: specifies the BPWM channel to configure.
  *         This parameter can be one of the following values:
  *         @arg BPWM_CHANNEL_0
  *         @arg BPWM_CHANNEL_1
  *         @arg BPWM_CHANNEL_2
  * @param  Level: selects output level in const out mode
  *         This parameter can be one of the following values:
  *         @arg BPWM_LEVEL_HIGH
  *         @arg BPWM_LEVEL_LOW
  * @retval  None
  */
void BPWM_SetOutLevel(BPWM_Type *BPWMx, uint32_t Channel, uint32_t Level)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));  
  assert_parameters(IS_BPWM_CHANNEL(Channel));
  assert_parameters(IS_BPWM_OUTLVL(Level));

  tmp = BPWMx->CCTL[Channel] & BPWM_CCTL_OUTEN_CCIFG_COV_CLR;
  tmp |= Level;
  BPWMx->CCTL[Channel] = tmp;
}

/**
  * @brief  Configures BPWM input line.
  * @param  BPWMx_SEL: select the BPWM0_3 or BPWM4_7 peripheral.
  *         @arg BPWM0_3_SEL
  *         @arg BPWM4_7_SEL
  * @param  ILine:
  *         @arg BPWM_ILINE_0
  *         @arg BPWM_ILINE_1 
  *         @arg BPWM_ILINE_2 
  *         @arg BPWM_ILINE_3 
  * @param  InSelection:
  *         @arg BPWM1_IN2
  *         @arg BPWM1_IN1  
  *         @arg BPWM1_IN0  
  *         @arg BPWM0_IN2  
  *         @arg BPWM0_IN1  
  *         @arg BPWM0_IN0  
  *         @arg BPWM3_IN2  
  *         @arg BPWM3_IN1  
  *         @arg BPWM3_IN0  
  *         @arg BPWM2_IN2  
  *         @arg BPWM2_IN1  
  *         @arg BPWM2_IN0
  *         @arg BPWM5_IN2
  *         @arg BPWM5_IN1  
  *         @arg BPWM5_IN0  
  *         @arg BPWM4_IN2  
  *         @arg BPWM4_IN1  
  *         @arg BPWM4_IN0  
  *         @arg BPWM7_IN2  
  *         @arg BPWM7_IN1  
  *         @arg BPWM7_IN0  
  *         @arg BPWM6_IN2  
  *         @arg BPWM6_IN1  
  *         @arg BPWM6_IN0
  * @retval  None
  */
void BPWM_ILineConfig(BPWM_SEL_Type *BPWMx_SEL, uint32_t ILine, uint32_t InSelection)
{
  __IO uint32_t *addr;
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_BPWM_INLINE(ILine));
  assert_parameters(IS_BPWM_INSEL(InSelection));

  addr = &BPWMx_SEL->I_SEL01 + ((InSelection&0xF00)>>8);
  tmp = *addr;
  tmp &= ~( 3 << (InSelection&0xFF));
  tmp |= (ILine << (InSelection&0xFF));
  *addr = tmp;
}

/**
  * @brief  Gets BPWM channel SCCI value.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  Channel: specifies the BPWM channel to check.
  *         This parameter can be one of the following values:
  *         @arg BPWM_CHANNEL_0
  *         @arg BPWM_CHANNEL_1
  *         @arg BPWM_CHANNEL_2
  * @retval  INx's input value when the TAR is equal to CCRx
  */
uint8_t BPWM_GetSCCI(BPWM_Type *BPWMx, uint32_t Channel)
{
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));
  assert_parameters(IS_BPWM_CHANNEL(Channel));
  
  if (BPWMx->CCTL[Channel] & BPWM_CCTL_SCCI)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Gets BPWM channel capture value.
  * @param  BPWMx: to select the BPWM peripheral.
  *         This parameter can be:
  *         CM0 : BPWM4 ~ BPWM7
  *         CM33 : BPWM0 ~ BPWM7
  * @param  Channel: specifies the BPWM channel to check.
  *         This parameter can be one of the following values
  *         @arg BPWM_CHANNEL_0
  *         @arg BPWM_CHANNEL_1 
  *         @arg BPWM_CHANNEL_2 
  * @retval  The value of CCRx.
  */
uint32_t BPWM_GetCapture(BPWM_Type *BPWMx, uint32_t Channel)
{  
  /* Check parameters */
  assert_parameters(IS_BPWM_ALL_INSTANCE(BPWMx));  
  assert_parameters(IS_BPWM_CHANNEL(Channel));
    
  return BPWMx->CCR[Channel];
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/*********************************** END OF FILE ******************************/
