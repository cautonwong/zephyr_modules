/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private functions ---------------------------------------------------------*/
static uint32_t data_a[2] = { 0xFFFFFFFF, 0xFFFFFFFF };
static uint32_t data_b[2] = { 0x00000005, 0x80000000 };
static uint32_t data_o[2] = { 0 };

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
    
  /* Configure address */
  CRYPTO_AddressAConfig((uint32_t)&data_a[0]);
  CRYPTO_AddressBConfig((uint32_t)&data_b[0]);
  CRYPTO_AddressOConfig((uint32_t)&data_o[0]);
  
  /* Start operation */
  CRYPTO_StartAdd(CRYPT_LENGTH_64, CRYPT_STOPCPU);
  /* Waiting for operation done */
  CRYPTO_WaitForLastOperation();
  
  printf("Crypt addition 64 bit test\r\n");
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
