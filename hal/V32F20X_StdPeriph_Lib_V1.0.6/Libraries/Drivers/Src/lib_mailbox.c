/**
  ******************************************************************************
  * @file    lib_mailbox.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   Mailbox library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_mailbox.h"

/* Private macro -------------------------------------------------------------*/
/* SYSCFG0_MB_DUALCM33_EXC */
#define SYSCFG0_MB_DUALCM33_EXC_MUTEX         (1UL << 0)
/* SYSCFG0_MB_DUALCM33_INT */
#define SYSCFG0_MB_DUALCM33_INT_MAIN2SUB      (1UL << 0)
#define SYSCFG0_MB_DUALCM33_INT_SUB2MAIN      (1UL << 1)
/* SYSCFG0_MAILBOX_M332M0_INT */
#define SYSCFG0_MAILBOX_M332M0_INT_MAIN       (1UL << 0)
#define SYSCFG0_MAILBOX_M332M0_INT_SUB        (1UL << 1)
/* SYSCFG0_MB_DUALCM33_INTCLR */
#define SYSCFG0_MB_DUALCM33_INTCLR_MAIN2SUB   (1UL << 0)
#define SYSCFG0_MB_DUALCM33_INTCLR_SUB2MAIN   (1UL << 1)
/* SYSCFG0_MAILBOX_M02M33_INTCLR */
#define SYSCFG0_MAILBOX_M02M33_INTCLR_MAIN    (1UL << 0)
#define SYSCFG0_MAILBOX_M02M33_INTCLR_SUB     (1UL << 1)
#define SYSCFG0_MAILBOX_M02M33_INTSTS_MAIN    (1UL << 16)
#define SYSCFG0_MAILBOX_M02M33_INTSTS_SUB     (1UL << 17)
/* SYSCFG1_MAILBOX_M02M33_INT */
#define SYSCFG1_MAILBOX_M02M33_INT_MAIN        (1UL << 0)
#define SYSCFG1_MAILBOX_M02M33_INT_SUB         (1UL << 1)
/* SYSCFG1_MAILBOX_M332M0_INTCLR */
#define SYSCFG1_MAILBOX_M332M0_INTCLR_MAIN     (1UL << 0)
#define SYSCFG1_MAILBOX_M332M0_INTCLR_SUB      (1UL << 1)
/* SYSCFG1_MB_M332M0_STS */
#define SYSCFG1_MB_M332M0_STS_MAIN             (1UL << 0)
#define SYSCFG1_MB_M332M0_STS_SUB              (1UL << 1)

#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)

/**
  * @brief  Initializes CM33 core0 and core1 mutex to 1.
  * @param  None
  * @retval None
  */
void MB33_MutexInit(void)
{
  WRITE_REG(SYSCFG0->MB_DUALM33_EXC, SYSCFG0_MB_DUALCM33_EXC_MUTEX);
}

/**
  * @brief  Sets CM33 core0 and core1 mutex to 1.
  * @param  None
  * @retval None
  */
void MB33_SetMutex(void)
{
  WRITE_REG(SYSCFG0->MB_DUALM33_EXC, SYSCFG0_MB_DUALCM33_EXC_MUTEX);
}

/**
  * @brief  Gets CM33 core0 and core1 mutex value.
  * @param  None
  * @retval Mutex value.
  */
uint32_t MB33_GetMutex(void)
{
  return READ_REG(SYSCFG0->MB_DUALM33_EXC);
}

#endif /* V32F20XXX_CM33_CORE0 || V32F20XXX_CM33_CORE1 */

/**
  * @brief  Sets interrupt to other cores.
  * @param  MB_Int: specifies the interrupt to set.
  *          This parameter can be one of the following values:
  *            @arg MB_INT_CM33_CORE0: set interrupt to CM33 core0
  *            @arg MB_INT_CM33_CORE1: set interrupt to CM33 core1
  *            @arg MB_INT_CM0_CORE:   set interrupt to CM0 core
  * @retval None
  */
void MB_SetInterrupt(uint32_t MB_Int)
{
  /* Check the parameters */
  assert_parameters(IS_MB_INT(MB_Int));
  
#if defined (V32F20XXX_CM33_CORE0)
  
  if (MB_Int == MB_INT_CM33_CORE1)
  {
    WRITE_REG(SYSCFG0->MB_DUALM33_INT, SYSCFG0_MB_DUALCM33_INT_MAIN2SUB);
  }
  else if (MB_Int == MB_INT_CM0_CORE)
  {
    WRITE_REG(SYSCFG0->MB_M33ToM0_INT, SYSCFG0_MAILBOX_M332M0_INT_MAIN);
  }

#endif /* V32F20XXX_CM33_CORE0 */
  
#if defined (V32F20XXX_CM33_CORE1)
  
  if (MB_Int == MB_INT_CM33_CORE0)
  {
    WRITE_REG(SYSCFG0->MB_DUALM33_INT, SYSCFG0_MB_DUALCM33_INT_SUB2MAIN);
  }
  else if (MB_Int == MB_INT_CM0_CORE)
  {
    WRITE_REG(SYSCFG0->MB_M33ToM0_INT, SYSCFG0_MAILBOX_M332M0_INT_SUB);
  }

#endif /* V32F20XXX_CM33_CORE1 */

#if defined (V32F20XXX_CM0_CORE)

  if (MB_Int == MB_INT_CM33_CORE0)
  {
    WRITE_REG(SYSCFG1->MB_M0ToM33_INT, SYSCFG1_MAILBOX_M02M33_INT_MAIN);
  }
  else if (MB_Int == MB_INT_CM33_CORE1)
  {
    WRITE_REG(SYSCFG1->MB_M0ToM33_INT, SYSCFG1_MAILBOX_M02M33_INT_SUB);
  }

#endif /* V32F20XXX_CM0_CORE */
}

/**
  * @brief  Clears interrupt from other cores.
  * @param  MB_Int: specifies the interrupt to clear.
  *          This parameter can be one of the following values:
  *            @arg MB_INT_CM33_CORE0: clear interrupt from CM33 core0
  *            @arg MB_INT_CM33_CORE1: clear interrupt from CM33 core1
  *            @arg MB_INT_CM0_CORE:   clear interrupt from CM0 core
  * @retval None
  */
void MB_ClearInterrupt(uint32_t MB_Int)
{
  /* Check the parameters */
  assert_parameters(IS_MB_INT(MB_Int));
  
#if defined (V32F20XXX_CM33_CORE0)
  
  if (MB_Int == MB_INT_CM33_CORE1)
  {
    WRITE_REG(SYSCFG0->MB_DUALM33_INTCLR, SYSCFG0_MB_DUALCM33_INTCLR_SUB2MAIN);
  }
  else if (MB_Int == MB_INT_CM0_CORE)
  {
    WRITE_REG(SYSCFG0->MB_M0ToM33_INT, SYSCFG0_MAILBOX_M02M33_INTCLR_MAIN);
  }

#endif /* V32F20XXX_CM33_CORE0 */
  
#if defined (V32F20XXX_CM33_CORE1)
  
  if (MB_Int == MB_INT_CM33_CORE0)
  {
    WRITE_REG(SYSCFG0->MB_DUALM33_INTCLR, SYSCFG0_MB_DUALCM33_INTCLR_MAIN2SUB);
  }
  else if (MB_Int == MB_INT_CM0_CORE)
  {
    WRITE_REG(SYSCFG0->MB_M0ToM33_INT, SYSCFG0_MAILBOX_M02M33_INTCLR_SUB);
  }

#endif /* V32F20XXX_CM33_CORE1 */

#if defined (V32F20XXX_CM0_CORE)

  if (MB_Int == MB_INT_CM33_CORE0)
  {
    WRITE_REG(SYSCFG1->MB_M33ToM0_INTCLR, SYSCFG1_MAILBOX_M332M0_INTCLR_MAIN);
  }
  else if (MB_Int == MB_INT_CM33_CORE1)
  {
    WRITE_REG(SYSCFG1->MB_M33ToM0_INTCLR, SYSCFG1_MAILBOX_M332M0_INTCLR_SUB);
  }

#endif /* V32F20XXX_CM0_CORE */
}

/**
  * @brief  Gets interrupt from other cores.
  * @param  MB_Int: specifies the interrupt to get status.
  *          This parameter can be one of the following values:
  *            @arg MB_INT_CM33_CORE0: get interrupt from CM33 core0
  *            @arg MB_INT_CM33_CORE1: get interrupt from CM33 core1
  *            @arg MB_INT_CM0_CORE:   get interrupt from CM0 core
  * @retval Interrupt status
  */
ITStatus MB_GetInterrupt(uint32_t MB_Int)
{
  ITStatus status = RESET;
  
  /* Check the parameters */
  assert_parameters(IS_MB_INT(MB_Int));
  
#if defined (V32F20XXX_CM33_CORE0)
  
  if (MB_Int == MB_INT_CM33_CORE1)
  {
    if (IS_BIT_SET(SYSCFG0->MB_DUALM33_INT, SYSCFG0_MB_DUALCM33_INT_SUB2MAIN))
    {
      status = SET;
    }
    else
    {
      status = RESET;
    }
  }
  else if (MB_Int == MB_INT_CM0_CORE)
  {
    if (IS_BIT_SET(SYSCFG0->MB_M0ToM33_INT, SYSCFG0_MAILBOX_M02M33_INTSTS_MAIN))
    {
      status = SET;
    }
    else
    {
      status = RESET;
    }
  }

#endif /* V32F20XXX_CM33_CORE0 */
  
#if defined (V32F20XXX_CM33_CORE1)
  
  if (MB_Int == MB_INT_CM33_CORE0)
  {
    if (IS_BIT_SET(SYSCFG0->MB_DUALM33_INT, SYSCFG0_MB_DUALCM33_INT_MAIN2SUB))
    {
      status = SET;
    }
    else
    {
      status = RESET;
    }
  }
  else if (MB_Int == MB_INT_CM0_CORE)
  {
    if (IS_BIT_SET(SYSCFG0->MB_M0ToM33_INT, SYSCFG0_MAILBOX_M02M33_INTSTS_SUB))
    {
      status = SET;
    }
    else
    {
      status = RESET;
    }
  }

#endif /* V32F20XXX_CM33_CORE1 */

#if defined (V32F20XXX_CM0_CORE)

  if (MB_Int == MB_INT_CM33_CORE0)
  {
    if (IS_BIT_SET(SYSCFG1->MB_M33ToM0_STS, SYSCFG1_MB_M332M0_STS_MAIN))
    {
      status = SET;
    }
    else
    {
      status = RESET;
    }
  }
  else if (MB_Int == MB_INT_CM33_CORE1)
  {
    if (IS_BIT_SET(SYSCFG1->MB_M33ToM0_STS, SYSCFG1_MB_M332M0_STS_SUB))
    {
      status = SET;
    }
    else
    {
      status = RESET;
    }
  }

#endif /* V32F20XXX_CM0_CORE */

  return status;
}

/*********************************** END OF FILE ******************************/
