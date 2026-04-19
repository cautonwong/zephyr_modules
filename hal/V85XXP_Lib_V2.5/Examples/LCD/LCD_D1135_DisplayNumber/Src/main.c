/**
  * @file    main.c
  * @author  Application Team
  * @version V2.5.0
  * @date    2022-10-18
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

volatile unsigned char test_success;

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

#define lcd_a         0x08
#define lcd_b         0x04
#define lcd_c         0x02

#define lcd_d         0x10
#define lcd_e         0x20
#define lcd_g         0x40
#define lcd_f         0x80

void LCD_Clean()
{
  int i;
  for( i=0;i<40;i++)
    LCD->FB[i] =0x00;
}

uint32_t LCD_NTOF(uint32_t num1)
{
  switch (num1)
  {
  case 0: num1=lcd_a+lcd_b+lcd_c+lcd_d+lcd_e+lcd_f;  break;            
  case 1: num1=lcd_b+lcd_c; break;
  case 2: num1=lcd_a+lcd_b+lcd_g+lcd_e+lcd_d; break;
  case 3: num1=lcd_a+lcd_b+lcd_g+lcd_c+lcd_d; break;
  case 4: num1=lcd_f+lcd_g+lcd_b+lcd_c; break;
  case 5: num1=lcd_a+lcd_f+lcd_g+lcd_c+lcd_d; break;
  case 6: num1=lcd_a+lcd_f+lcd_e+lcd_d+lcd_c+lcd_g;break;
  case 7: num1=lcd_a+lcd_b+lcd_c; break;
  case 8: num1=lcd_a+lcd_b+lcd_c+lcd_d+lcd_e+lcd_f+lcd_g; break;
  case 9: num1=lcd_a+lcd_b+lcd_c+lcd_d+lcd_f+lcd_g; break;
  default: num1=lcd_d;
  }
  num1= ((num1&0xf0)<<4)+(num1&0x0f);
  return num1;
}

uint32_t  hextobcd(uint32_t num)
{ 
  int num_1,num_2,num_3,num_4,num_5,num_6,num_7,num_8;
  num_1=num%10;
  num_2=num%100/10;
  num_3=num%1000/100;
  num_4=num%10000/1000;
  num_5=num%100000/10000;
  num_6=num%1000000/100000;
  num_7=num%10000000/1000000;
  num_8=num%100000000/10000000;
  
  num=num_1+(num_2<<4)+(num_3<<8)+(num_4<<12)+ \
    (num_5<<16)+(num_6<<20)+(num_7<<24)+(num_8<<28);
  return num;
}


void LCD_Number(uint32_t num)
{
  uint32_t num1,num2,num3,num4,num5,num6,num7,num8;
  
  num=hextobcd(num);
  
  num1=(num>>28)&0xf;
  LCD->FB[5]=LCD_NTOF(num1); //seg20,seg21
  
  num2=(num>>24)&0xf;
  LCD->FB[3]=LCD_NTOF(num2)<<16;//seg14,seg15
  
  num3=(num>>20)&0xf;
  LCD->FB[6]=(LCD_NTOF(num3)&0xff00);   //seg25
  LCD->FB[6]|=(LCD_NTOF(num3)&0x00ff)<<16;   //seg26
  
  num4=(num>>16)&0xf;
  LCD->FB[6]|=(LCD_NTOF(num4)&0xff00)<<16;   //seg27
  LCD->FB[8]=(LCD_NTOF(num4)&0x00ff)<<16;   //seg34
  
  num5=(num>>12)&0xf;
  LCD->FB[11]=(LCD_NTOF(num5)&0xff00)<<16;   //seg47
  LCD->FB[12]=(LCD_NTOF(num5)&0x00ff)<<8;   //seg49
  
  num6=(num>>8)&0xf;
  LCD->FB[13]=(LCD_NTOF(num6)&0xff00)>>8;   //seg52
  LCD->FB[13]|=(LCD_NTOF(num6)&0x00ff)<<24;   //seg55
  
  num7=(num>>4)&0xf;
  LCD->FB[14]=(LCD_NTOF(num7)&0xff00)>>8;   //seg56
  LCD->FB[14]|=(LCD_NTOF(num7)&0x00ff)<<8;   //seg57

  num8=(num>>0)&0xf;
  LCD->FB[14]|=(LCD_NTOF(num8)&0xff00)<<8;   //seg58
  LCD->FB[14]|=(LCD_NTOF(num8)&0x00ff)<<24;   //seg59
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  LCD_InitType LCD_InitStruct;
  TMR_InitType TMR_InitStruct;
  LCD_IOInitType LCD_IOInitStruct;
  uint32_t tmp0, tmp1;
  uint16_t tmp2;
  uint32_t ticks_start;
  uint32_t i;

  test_success = 0;

  Clock_Init();
  Stdio_Init();
  
  /* LCD initialization, configure with default value */
  LCD_DeInit();
  LCD_StructInit(&LCD_InitStruct);
  /* Initialize the BKFILL member */  
  LCD_InitStruct.BKFILL = LCD_BKFILL_0;
  /* Initialize the Drv member */  
  LCD_InitStruct.Drv = LCD_DRV_300;
  /* Initialize the FBMODE member */  
  LCD_InitStruct.FBMODE = LCD_FBMODE_BUFA;
  /* Initialize the FRQ member */  
  LCD_InitStruct.FRQ = LCD_FRQ_512H;
  /* Initialize the SWPR member */  
  LCD_InitStruct.SWPR = 0;
  /* Initialize the Type member */  
  LCD_InitStruct.Type = LCD_TYPE_4COM;
  LCD_Init(&LCD_InitStruct);
  
  LCD_Clean();
  LCD->FB[3] =0X0f080000; 
  LCD->FB[5] =0X00000E06;
  LCD->FB[6] =0X0B000B00; 
  LCD->FB[11] =0X0B000000; 
  LCD->FB[12] =0X00000E00; 
  
  tmp0 = BIT0|BIT1|BIT2|BIT3|BIT8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15| \
         BIT20|BIT21|BIT22|BIT23|BIT24|BIT25|BIT26|BIT27;
  tmp1 = BIT2|BIT15|BIT17|BIT18|BIT19|BIT20|BIT23|BIT24|BIT25|BIT26|BIT27;
  tmp2 = 0;
  
  /* Enable LCD, configure LCD COMs and SEGs IO(disable I/O) */
  LCD_IOInitStruct.COMMode  = LCD_TYPE_4COM;
  LCD_IOInitStruct.SegCtrl0 = tmp0;
  LCD_IOInitStruct.SegCtrl1 = tmp1;
  LCD_IOInitStruct.SegCtrl2 = tmp2;
  LCD_Cmd(&LCD_IOInitStruct, ENABLE);
  
  TMR_DeInit(TMR0);
  TMR_InitStruct.ClockSource = TMR_CLKSRC_INTERNAL;
  TMR_InitStruct.EXTGT = TMR_EXTGT_DISABLE;
  TMR_InitStruct.Period = 0xFFFFFFFF;
  TMR_Init(TMR0, &TMR_InitStruct);
  /* Enable Timer0 */
  TMR_Cmd(TMR0, ENABLE);
  
  test_success = 1;
  
  while (1)
  {
    for (i=0; i<100; i++)
    {
      LCD_Number(i);
      
      WDT_Clear();
      
      /* Delay 200ms */
      ticks_start = TMR_GetCurrentValue(TMR0);
      while ((ticks_start - TMR_GetCurrentValue(TMR0)) < (13107200/5-1));
    }
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
