/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Clock_Init:
              - PLLL input clock    : External 32K crystal
              - PLLL frequency      : 26M
              - AHB Clock source    : PLLL
              - AHB Clock frequency : 26M (PLLL divided by 1)
              - APB Clock frequency : 13M (AHB Clock divided by 2)
  * @param  None
  * @retval None
  */
void Clock_Init(void)
{
  CLK_InitTypeDef CLK_Struct;

  CLK_Struct.ClockType = CLK_TYPE_AHBSRC \
                        |CLK_TYPE_PLLL   \
                        |CLK_TYPE_HCLK   \
                        |CLK_TYPE_PCLK;
  CLK_Struct.AHBSource      = CLK_AHBSEL_LSPLL;
  CLK_Struct.PLLL.Frequency = CLK_PLLL_26_2144MHz;
  CLK_Struct.PLLL.Source    = CLK_PLLLSRC_XTALL;
  CLK_Struct.PLLL.State     = CLK_PLLL_ON;
  CLK_Struct.HCLK.Divider   = 1;
  CLK_Struct.PCLK.Divider   = 2;
  CLK_ClockConfig(&CLK_Struct);
}

int test_ecdsa(void) 
{
  int i, c;
  uint8_t private[32] = {0};
  uint8_t public[64] = {0};
  uint8_t hash[32] = {0};
  uint8_t sig[64] = {0};

  const struct uECC_Curve_t * curves[5];
  int num_curves = 0;
#if uECC_SUPPORTS_secp160r1
  curves[num_curves++] = uECC_secp160r1();
#endif
#if uECC_SUPPORTS_secp192r1
  curves[num_curves++] = uECC_secp192r1();
#endif
#if uECC_SUPPORTS_secp224r1
  curves[num_curves++] = uECC_secp224r1();
#endif
#if uECC_SUPPORTS_secp256r1
  curves[num_curves++] = uECC_secp256r1();
#endif
#if uECC_SUPPORTS_secp256k1
  curves[num_curves++] = uECC_secp256k1();
#endif
    
  printf("Testing 256 signatures\r\n");
  for (c = 0; c < num_curves; ++c) 
  {
    for (i = 0; i < 1; ++i) {

    printf("uECC_make_key()\r\n");

    if (!uECC_make_key(public, private, curves[c])) 
    {
      printf("uECC_make_key() failed\r\n");
      return 1;
    }
    memcpy(hash, public, sizeof(hash));

    printf("uECC_sign()\r\n");
            
    if (!uECC_sign(private, hash, sizeof(hash), sig, curves[c])) 
    {
      printf("uECC_sign() failed\r\n");
      return 1;
    }

    printf("uECC_verify()\r\n");

    if (!uECC_verify(public, hash, sizeof(hash), sig, curves[c])) 
    {
      printf("uECC_verify() failed\r\n");
      return 1;
    }
  }
  printf("done\r\n");
}
    
    return 0;
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Clock initialization */
  Clock_Init();
  /* Print initialization */
  Stdio_Init();
  
  test_ecdsa();
  
  while (1)
  {
    WDT_Clear();
  }
}

#ifndef  ASSERT_NDEBUG
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
