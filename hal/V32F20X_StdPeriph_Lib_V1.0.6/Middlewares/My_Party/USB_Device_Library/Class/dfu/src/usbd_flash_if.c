/**
  * @file    usbd_flash_if.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2021-09-26
  * @brief   Specific media access Layer for internal flash.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usbd_flash_if.h"
#include "usbd_dfu_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
uint16_t FLASH_If_Init(void);
uint16_t FLASH_If_Erase (uint32_t Add);
uint16_t FLASH_If_Write (uint32_t Add, uint32_t Len);
uint8_t *FLASH_If_Read  (uint32_t Add, uint32_t Len);
uint16_t FLASH_If_DeInit(void);
uint16_t FLASH_If_CheckAdd(uint32_t Add);


/* Private variables ---------------------------------------------------------*/
DFU_MAL_Prop_TypeDef DFU_Flash_cb =
  {
    FLASH_IF_STRING,
    FLASH_If_Init,
    FLASH_If_DeInit,
    FLASH_If_Erase,
    FLASH_If_Write,
    FLASH_If_Read,
    FLASH_If_CheckAdd,
    50, /* Erase Time in ms */
    50  /* Programming Time in ms */
  };

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  FLASH_If_Init
  *         Memory initialization routine.
  * @param  None
  * @retval MAL_OK if operation is successful, MAL_FAIL else.
  */
uint16_t FLASH_If_Init(void)
{
  return MAL_OK;
}

/**
  * @brief  FLASH_If_DeInit
  *         Memory deinitialization routine.
  * @param  None
  * @retval MAL_OK if operation is successful, MAL_FAIL else.
  */
uint16_t FLASH_If_DeInit(void)
{
  return MAL_OK;
}

/*******************************************************************************
* Function Name  : FLASH_If_Erase
* Description    : Erase sector
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t FLASH_If_Erase(uint32_t Add)
{
  FLASH_PageErase(FLASHA, Add);
  
  return MAL_OK;
}

/**
  * @brief  FLASH_If_Write
  *         Memory write routine.
  * @param  Add: Address to be written to.
  * @param  Len: Number of data to be written (in bytes).
  * @retval MAL_OK if operation is successful, MAL_FAIL else.
  */
uint16_t FLASH_If_Write(uint32_t Add, uint32_t Len)
{
  FLASH_ProgramByte(FLASHA, Add, MAL_Buffer, Len);
  
  return MAL_OK;
}

/**
  * @brief  FLASH_If_Read
  *         Memory read routine.
  * @param  Add: Address to be read from.
  * @param  Len: Number of data to be read (in bytes).
  * @retval Pointer to the physical address where data should be read.
  */
uint8_t *FLASH_If_Read (uint32_t Add, uint32_t Len)
{
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  uint32_t idx = 0;
  for (idx = 0; idx < Len; idx += 4)
  {
    *(uint32_t*)(MAL_Buffer + idx) = *(uint32_t *)(Add + idx);
  }
  return (uint8_t*)(MAL_Buffer);
#else  
  return  (uint8_t *)(Add);
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
}

/**
  * @brief  FLASH_If_CheckAdd
  *         Check if the address is an allowed address for this memory.
  * @param  Add: Address to be checked.
  * @param  Len: Number of data to be read (in bytes).
  * @retval MAL_OK if the address is allowed, MAL_FAIL else.
  */
uint16_t FLASH_If_CheckAdd(uint32_t Add)
{
  if ((Add >= FLASH_START_ADD) && (Add < FLASH_END_ADD))
  {
    return MAL_OK;
  }
  else
  {
    return MAL_FAIL;
  }
}
/*********************************** END OF FILE ******************************/
