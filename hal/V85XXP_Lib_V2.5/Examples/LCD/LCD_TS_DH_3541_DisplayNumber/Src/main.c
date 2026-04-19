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

#define Const_LCDRAMLen 17

uint8_t guc_LCDRAM[Const_LCDRAMLen];

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



void LCD_Clean()
{
  int i;
  for( i=0;i<40;i++)
    LCD->FB[i] =0x00;
}


#define     number9H     1
#define     number9L     0
#define     number8H     3
#define     number8L     2
#define     number7H     5
#define     number7L     4
#define     number6H     7
#define     number6L     6
#define     number5H     9
#define     number5L     8
#define     number4H     11
#define     number4L     10
#define     number3H     13
#define     number3L     12
#define     number2H     15
#define     number2L     14

const uint8_t  NumAddr[16] = {number9H,number9L,number8H,number8L,number7H,number7L,number6H,number6L,number5H,
                          number5L,number4H,number4L,number3H,number3L,number2H,number2L};


#define NUM1B    BIT4
#define NUM1G    BIT5
#define NUM1C    BIT6

#define NUM1A    BIT4
#define NUM1F    BIT5
#define NUM1E    BIT6
#define NUM1D    BIT7

                          
const uint8_t  NUMTABLE_1L[]=
{
  NUM1B+NUM1C,                        //0
  NUM1B+NUM1C,                        //1
  NUM1G+NUM1B,                        //2
  NUM1B+NUM1G+NUM1C,                  //3
  NUM1B+NUM1C+NUM1G,                  //4
  NUM1G+NUM1C,                        //5
  NUM1G+NUM1C,                        //6
  NUM1B+NUM1C,                        //7
  NUM1G+NUM1B+NUM1C,                  //8
  NUM1B+NUM1G+NUM1C,                  //9

  NUM1G+NUM1B+NUM1C,                  //A
  NUM1C+NUM1G,                        //B
   0,                                 //C
  NUM1B+NUM1C+NUM1G,                  //D
  NUM1G,                              //E
  NUM1G,                              //F
};

const uint8_t  NUMTABLE_1H[]=
{
  NUM1A+NUM1E+NUM1F+NUM1D,            //0
  0,                                  //1
  NUM1D+NUM1E+NUM1A,                  //2
  NUM1D+NUM1A,                        //3
  NUM1F,                              //4
  NUM1D+NUM1F+NUM1A,                  //5
  NUM1D+NUM1E+NUM1F+NUM1A,            //6
  NUM1A,                              //7
  NUM1D+NUM1E+NUM1F+NUM1A,            //8
  NUM1A+NUM1D+NUM1F,                  //9

  NUM1E+NUM1F+NUM1A,                  //A
  NUM1D+NUM1E+NUM1F,                  //B
  NUM1A+NUM1D+NUM1E+NUM1F,            //C
  NUM1D+NUM1E,                        //D
  NUM1D+NUM1E+NUM1F+NUM1A,            //E
  NUM1E+NUM1F+NUM1A,                  //F
};

#define  N_Resd1H 0xf1
#define  N_Resd1L 0xf0

#define LCD_CHAR1H_G  (NUM1G)                       //'-'
#define LCD_CHAR1L_G  (0)                           //'-'
#define LCD_CHAR1H_L  (NUM1D+NUM1E+NUM1F)           //'L'
#define LCD_CHAR1L_L  (0)                           //'L'
#define LCD_CHAR1H_r  (NUM1E+NUM1G)                 //'r'
#define LCD_CHAR1L_r  (0)                           //'r'
#define LCD_CHAR1H_n  (NUM1E+NUM1G)                 //'n'
#define LCD_CHAR1L_n  (NUM1C)                       //'n'
#define LCD_CHAR1H_o  (NUM1D+NUM1E+NUM1G)           //'o'
#define LCD_CHAR1L_o  (NUM1C)                       //'o'
#define LCD_CHAR1H_C  (NUM1D+NUM1E+NUM1F)           //'C'
#define LCD_CHAR1L_C  (NUM1A)                       //'C'
#define LCD_CHAR1H_E  (NUM1D+NUM1E+NUM1F+NUM1G)     //'E'
#define LCD_CHAR1L_E  (NUM1A)                       //'E'


void Disp_Numb(uint32_t data1, uint32_t type)
{
  uint8_t tmpdata, tmptype;
  uint8_t i;
  uint8_t tmpdisph,tmpdispl;
  uint8_t *p;
  uint8_t *q;

  for(i=0; i<8; i++)
  {
    tmpdata = (uint8_t)(data1 & 0x0F);        //Get the last digit
    tmptype = (uint8_t)(type & 0x0F);
    data1 >>= 4;                            //Right shift
    type >>= 4;

    tmpdisph = NUMTABLE_1H[tmpdata];         //Get high display code
    tmpdispl = NUMTABLE_1L[tmpdata];         //Get low display code

    //
    p = guc_LCDRAM + NumAddr[i*2];          //Digital display buffer
    q = guc_LCDRAM + NumAddr[i*2+1];        //Digital display buffer

    *p = 0;                          //Clear only digits
    *q = 0;                          //Clear only digits

    switch(tmptype)                         //type
    {
      case 0:
        *p |= tmpdisph;         //show number
        *q |= tmpdispl;         //show number
         break;
      
      case 1:
        *p |= LCD_CHAR1H_G;
        *q |= LCD_CHAR1L_G;      //show '-'
        break;
      
      case 2:                     //show 'L'
        *p |= LCD_CHAR1H_L;
        *q |= LCD_CHAR1L_L;
        break;
      
      case 3:                     //show 'r'
        *p |= LCD_CHAR1H_r;
        *q |= LCD_CHAR1L_r;
        break;
      
      case 4:                     //show 'n'
        *p |= LCD_CHAR1H_n;
        *q |= LCD_CHAR1L_n;
        break;
      
      case 5:                     //show 'o'
        *p |= LCD_CHAR1H_o;
        *q |= LCD_CHAR1L_o;
        break;
      
      case 6: 
        *p |= LCD_CHAR1H_E;
        *q |= LCD_CHAR1L_E;
        break;
      case 7: 
        *p |= LCD_CHAR1H_C;
        *q |= LCD_CHAR1L_C;
        break;
      
      case 0x0a:
        *p |= 0x00;             //clear
        *q |= 0x00;
         break;
      
      default:
        break;
    }
  }
}

void RefreshLCDRAM(uint8_t *p)
{
  LCD->FB[1] = (((uint32_t)(guc_LCDRAM[2]&0xff) << 24)  |\
               ((uint32_t)(guc_LCDRAM[1]&0xff) << 8)    |\
               ((uint32_t)(guc_LCDRAM[0]&0xff)));
  LCD->FB[2] = (((uint32_t)(guc_LCDRAM[4]&0xff) << 8)   |\
               ((uint32_t)(guc_LCDRAM[3]&0xff)));
  LCD->FB[6] = (((uint32_t)(guc_LCDRAM[6]&0xff) << 24)  |\
               ((uint32_t)(guc_LCDRAM[5]&0xff) << 16));
  LCD->FB[7] = (((uint32_t)(guc_LCDRAM[9]&0xff) << 24)  |\
               ((uint32_t)(guc_LCDRAM[8]&0xff) << 16)   |\
               ((uint32_t)(guc_LCDRAM[7]&0xff)));
  LCD->FB[8] = (((uint32_t)(guc_LCDRAM[13]&0xff) << 24) |\
               ((uint32_t)(guc_LCDRAM[12]&0xff) << 16)  |\
               ((uint32_t)(guc_LCDRAM[11]&0xff) << 8)   |\
               ((uint32_t)(guc_LCDRAM[10]&0xff) ));
  LCD->FB[9] = (((uint32_t)(guc_LCDRAM[16]&0xff) << 16) |\
               ((uint32_t)(guc_LCDRAM[15]&0xff) << 8)   |\
                (uint32_t)(guc_LCDRAM[14]&0xff));
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

  for(i=0; i<400000; i++)
  {
    __NOP();
  }
    
  LCD_StructInit(&LCD_InitStruct);
  /* Initialize the BKFILL member */  
  LCD_InitStruct.BKFILL = LCD_BKFILL_0;
  /* Initialize the Drv member */  
  LCD_InitStruct.Drv = LCD_DRV_600;
  /* Initialize the FBMODE member */  
  LCD_InitStruct.FBMODE = LCD_FBMODE_BUFA;
  /* Initialize the FRQ member */  
  LCD_InitStruct.FRQ = LCD_FRQ_256H;
  /* Initialize the SWPR member */  
  LCD_InitStruct.SWPR = 0;
  /* Initialize the Type member */  
  LCD_InitStruct.Type = LCD_TYPE_8COM;
  LCD_Init(&LCD_InitStruct);
  
  LCD_Clean();
  LCD->FB[3] =0X0f080000; 
  LCD->FB[5] =0X00000E06;
  LCD->FB[6] =0X0B000B00; 
  LCD->FB[11] =0X0B000000; 
  LCD->FB[12] =0X00000E00; 
  
  tmp0 = 0xDC0003B0;
  tmp1 = 0x0000007F;
  tmp2 = 0x00000000;
  
  /* Enable LCD, configure LCD COMs and SEGs IO(disable I/O) */
  LCD_IOInitStruct.COMMode  = LCD_TYPE_8COM;
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
    for (i=000; i<200; i++)
    {
      Disp_Numb(0x12345678+i, 0x00000000);
      RefreshLCDRAM(guc_LCDRAM);
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
