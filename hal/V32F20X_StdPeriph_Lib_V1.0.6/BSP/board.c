/**
  ******************************************************************************
  * @file    board.c 
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-10-12
  * @brief   1. Set of firmware functions to manage Leds
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "board.h"
#include "lib_uart.h"
#include "lib_clk.h"
#include "lib_gpio.h"
#include "lib_syscfg.h"

GPIO_Type* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};

GPIO_Type* BUTTON_PORT[BUTTONn] = {BUTTON1_GPIO_PORT, BUTTON2_GPIO_PORT}; 
const uint16_t BUTTON_PIN[BUTTONn] = {BUTTON1_PIN, BUTTON2_PIN}; 

/**
  * @brief  Configures print UART.
  */
__weak void BSP_Printf_Init(void)
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
{
  uint32_t uart_clk;
  GPIO_InitType GPIO_InitStruct;
  UART_InitType UART_InitStruct;

  /*Configure UART7 PA2-TX PA3-RX pin*/
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF7_FC7_TXD_SCL_MISO);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF7_FC7_RXD_SDA_MOSI);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 ;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  SYSCFG0_FlexcommClockConfig(FLEXCOMM7, SYSCFG0_FC_CLKSRC_RCH, 1);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_FC7, ENABLE);
  SYSCFG0_Periph1Reset(SYSCFG0_Periph1Reset_FC7);
  SYSCFG0_FlexcommModeConfig(FLEXCOMM7, SYSCFG0_FC_UART);

  uart_clk = CLK_GetFlexcommClockFreq(FLEXCOMM7);
  
  UART_DeInit(UART7);
  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.Baudrate = 115200;
  UART_InitStruct.SerialClock = uart_clk;
  UART_InitStruct.DataLength = UART_DATALEN_8B;
  UART_InitStruct.Parity  = UART_PARITY_NONE;
  UART_InitStruct.StopBit = UART_STOPBIT_1;
  UART_Init(UART7, &UART_InitStruct);
}
#else
{
  uint32_t uart_clk;
  GPIO_InitType GPIO_InitStruct;
  UART_InitType UART_InitStruct;
  
  /*Configure UART19 TX pin*/
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF14_UART19_TX);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF14_UART19_RX);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_UART19, ENABLE);
  SYSCFG1_PeriphReset(SYSCFG1_Periph1Clock_UART19);

  uart_clk = CLK_GetUART14_19ClockFreq(UART19);

  UART_DeInit(UART19);
  UART_StructInit(&UART_InitStruct);
  UART_InitStruct.Baudrate = 115200;
  UART_InitStruct.SerialClock = uart_clk;
  UART_InitStruct.DataLength = UART_DATALEN_8B;
  UART_InitStruct.Parity  = UART_PARITY_NONE;
  UART_InitStruct.StopBit = UART_STOPBIT_1;
  UART_Init(UART19, &UART_InitStruct);
  SYSCFG1_UARTPinsCmd(UART19, ENABLE); 
}
#endif

/**
  * @brief  Retargets the C library printf function to the UART.
  * @param  None
  * @retval None
  */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 for Keil*/
  #define PUTCHAR_PROTOTYPE __WEAK int fputc(int ch, FILE *f)
#elif defined (__GNUC__)    /*For GCC*/
  #include <unistd.h>

  int _write(int32_t fd, char* ptr, int32_t len)
  {
    uint32_t i;

    if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
      i = 0UL;
      while (i < len)
      {
  #if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
        UART_SendData(UART7, ptr[i++]);
        while(UART_GetFlag(UART7, UART_FLAG_TXE) == RESET);
  #else
        UART_SendData(UART19, ptr[i++]);
        while(UART_GetFlag(UART19, UART_FLAG_TXE) == RESET);
  #endif
      }
    }
    return len;
  }
#else         /*For IAR*/
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#ifdef PUTCHAR_PROTOTYPE
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
#if defined (V32F20XXX_CM33_CORE0) || defined (V32F20XXX_CM33_CORE1)
  /* e.g. write a character to the USART33_7 and Loop until the end of transmission */
  UART_SendData(UART7, ch);
  while(UART_GetFlag(UART7, UART_FLAG_TXE) == RESET);
#else
  /* e.g. write a character to the USART0_5 and Loop until the end of transmission */
  UART_SendData(UART19, ch);
  while(UART_GetFlag(UART19, UART_FLAG_TXE) == RESET);
#endif

  return ch;
}
#endif

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg  LED1
  *     @arg  LED2
  *     @arg  LED3
  */
void BSP_LED_Init(Led_Type Led)
{
  GPIO_InitType  GPIO_InitStruct;
    
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  
  GPIO_WriteBit(GPIO_PORT[Led], GPIO_PIN[Led], SET);
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStruct);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED2
  */
void BSP_LED_On(Led_Type Led)
{
  GPIO_WriteBit(GPIO_PORT[Led], GPIO_PIN[Led], RESET);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg  LED1
  *     @arg  LED2
  *     @arg  LED3
  */
void BSP_LED_Off(Led_Type Led)
{
  GPIO_WriteBit(GPIO_PORT[Led], GPIO_PIN[Led], SET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg  LED1
  *     @arg  LED2
  *     @arg  LED3 
  */
void BSP_LED_Toggle(Led_Type Led)
{
  GPIO_ToggleBits(GPIO_PORT[Led], GPIO_PIN[Led]);
}

/**
  * @brief  Configures Button GPIO.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be one of following parameters:
  *     @arg  BUTTON1
  *     @arg  BUTTON2
  */
void BSP_PB_Init(Button_Type Button)
{
  GPIO_InitType GPIO_InitStruct;

  /* Configure Button pin as input */
  GPIO_InitStruct.GPIO_Pin = BUTTON_PIN[Button];
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);  
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:
  *     @arg  BUTTON1
  *     @arg  BUTTON2 
  * @retval The Button status (DOWN, UP)
  *
  */
Button_Status BSP_PB_GetState(Button_Type Button)
{
  return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/*********************************** END OF FILE ******************************/
