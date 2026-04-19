/**
  ******************************************************************************
  * @file    system_target.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   system source file.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "target.h"

#define NVR_REGINFOCOUNT1        (0x80400)
#define NVR_REGINFOBAKOFFSET     (0x100)

/**
  * @brief  Setup the microcontroller system
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  uint32_t i, Count, Value, Address, Checksum;
  
  Count = *(__IO uint32_t *)NVR_REGINFOCOUNT1;
  Checksum = Count;
  Checksum = ~Checksum;
  if(Checksum != *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + 4))
  {
    Count = *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + NVR_REGINFOBAKOFFSET);
    Checksum = Count;
    Checksum = ~Checksum;
    if(Checksum != *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + NVR_REGINFOBAKOFFSET + 4))
    {
      while(1);
    }
  }
  
  for(i=0; i<Count; i++)
  {
    Address = *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + 8+ i*12);
    Value = *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + 12 + i*12);
    Checksum = Address + Value;
    Checksum = ~Checksum;
    if(Checksum != *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + 16 + i*12))
    {
      Address = *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + NVR_REGINFOBAKOFFSET + 8 + i*12);
      Value = *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + NVR_REGINFOBAKOFFSET + 12 + i*12);
      Checksum = Address + Value;
      Checksum = ~Checksum;
      if(Checksum != *(__IO uint32_t *)(NVR_REGINFOCOUNT1 + NVR_REGINFOBAKOFFSET + 16 + i*12))
      {
        while(1);
      }
    }
    if((Address>=0x40014800) && (Address<=0x40015000))
    {
      RTC_WriteRegisters(Address, &Value, 1);
    }
    else
    {
      *(__IO uint32_t *)(Address) = Value;
    }
  }
}

/**
  * @brief  Initializes registers.
  * @param  None
  * @retval None
  */
void SystemUpdate(void)
{
 
}


/*********************************** END OF FILE ******************************/
