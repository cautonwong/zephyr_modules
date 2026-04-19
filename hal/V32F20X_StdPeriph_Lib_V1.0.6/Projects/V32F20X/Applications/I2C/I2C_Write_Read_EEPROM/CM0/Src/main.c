/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c_ee.h"

/* Private functions ---------------------------------------------------------*/

uint8_t I2c_Buf_Write[I2C_TRANSFER_SIZE];
uint8_t I2c_Buf_Read[I2C_TRANSFER_SIZE] = {0};
uint8_t I2C_Test(void);

extern uint8_t EE_State;
extern uint16_t EEPROM_SubAddress;
static __IO uint32_t nTxNum; /* Transmited data number */
static __IO uint32_t nRxNum; /* Received data number */

void I2C0_IRQHandler(void)
{
  /* I2C Transmit handler */
  /*- I2C_INT_TX_ABORT ------*/
  /*- When TX_ABOPT occurs, I2C bus automatically generate STOP signal */
  if(SET == I2C_GetINTStatus(EEPROM_I2C, I2C_INT_TX_ABORT))
  {
    if(SET == I2C_GetTransmitAbortStatus(EEPROM_I2C, I2C_7B_ADDR_NOACK))
    {
      I2C_ClearINTStatus(EEPROM_I2C, I2C_INT_TX_ABORT);
      if(EE_State == EE_Normal)
      {
        printf("NOACK for 7-bit address by slave!\r\n");
      }
      /* EE_State == EE_Crossing_Page */
      else
      {
        I2C_SendCmdDataFrame(EEPROM_I2C, I2C_CMD_READ_RESTART, 0x00);
      }
    }
    if(SET == I2C_GetTransmitAbortStatus(EEPROM_I2C, I2C_TXDATA_NOACK))
    {
      I2C_ClearINTStatus(EEPROM_I2C, I2C_INT_TX_ABORT);
      printf("NOACK for Transmitted data by addressed slave!\r\n");
    }
  }
}
  
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* V32F20xxx CM0 core STD library initialization:
       - HCLK 48 MHz, be configured be CM33 core0
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Low Level Initialization
     */
  STD_Init(48000000UL);
  
  BSP_Printf_Init();
  
  printf("Hello World!\r\n");
  
  printf("This is an I2C peripheral (AT24C512) read and write test routine \r\n");
  
  /* I2C AT24C512 init*/
  I2C_EE_Init();

  printf("I2C_EE_Init success\r\n");
  
  if(I2C_Test() == 1)
  {
     printf("Read and write Test Succeed!");
  }
  else
  {
     printf("Read and write Test Failed!");
  }
  
  while(1)
  {
  }
}

/**
  * @brief  Initialize the Low level.
  * @retval None
  */
void STD_lowInit(void)
{
  /* nothing to do */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the STD error return state */
  while(1)
  {
  }
}

/**
  * @brief  I2C(AT24C512) read write test
  * @param 
  * @retval 
  */
uint8_t I2C_Test(void)
{
  u16 i;

  EEPROM_INFO("Data written :");

  for ( i=0; i<=I2C_TRANSFER_SIZE; i++ )
  {   
    I2c_Buf_Write[i] = i+2;
  }

  /* write data to EEPROM */
  I2C_EE_BufferWrite( I2c_Buf_Write, EEPROM_SubAddress, I2C_TRANSFER_SIZE);
  
  EEPROM_INFO("Written successfully!");
   
  EEPROM_INFO("Data read :");
   
  /* read data from EEPROM to I2c_Buf_Read */
  I2C_EE_BufferRead(I2c_Buf_Read, EEPROM_SubAddress, I2C_TRANSFER_SIZE);
   
  /* disable abort interrupt */
  I2C_INTConfig(EEPROM_I2C, I2C_INT_TX_ABORT, DISABLE);
  NVIC_DisableIRQ(I2C14_IRQn);
  I2C_Cmd(EEPROM_I2C, DISABLE);

  for (i=0; i<I2C_TRANSFER_SIZE; i++)
  {  
    if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
    {
      printf("0x%02X ", I2c_Buf_Read[i]);
      EEPROM_ERROR("Error: I2C EEPROM write and read data are inconsistent!");
      return 0;
    }
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)    
        printf("\n\r");
    
  }
  EEPROM_INFO("I2C (AT24C512) read and write test successfully!");
  return 1;
}


#ifdef  ASSERT_ENABLED
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_errhandler error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_errhandler error line source number
  * @retval None
  */
void assert_errhandler(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*********************************** END OF FILE ******************************/
