/**
  ******************************************************************************
  * @file    misc.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   MISC library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "misc.h"
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
/**
  * @brief  Sets the priority grouping field (pre-emption priority and subpriority)
  *         using the required unlock sequence.
  * @param  PriorityGroup: The priority grouping bits length.
  *         This parameter can be one of the following values:
  *         @arg NVIC_PRIORITYGROUP_0: 0 bit  for pre-emption priority,
  *                                    3 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_1: 1 bit  for pre-emption priority,
  *                                    2 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_2: 2 bits for pre-emption priority,
  *                                    1 bits for subpriority
  *         @arg NVIC_PRIORITYGROUP_3: 3 bits for pre-emption priority,
  *                                    0 bit  for subpriority
  * @note   When the NVIC_PriorityGroup_0 is selected, IRQ pre-emption is no more possible.
  *         The pending IRQ priority will be managed only by the subpriority.
  * @retval None
  */
void NVIC_PriorityGroupConfig(uint32_t PriorityGroup)
{
  /* Check the parameters */
  assert_parameters(IS_NVIC_PRIORITY_GROUP(PriorityGroup));

  /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
  NVIC_SetPriorityGrouping(PriorityGroup);
}
#endif

/*********************************** END OF FILE ******************************/
