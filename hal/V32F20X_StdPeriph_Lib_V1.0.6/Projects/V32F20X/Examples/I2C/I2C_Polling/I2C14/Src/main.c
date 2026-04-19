/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*******************************************************************************
I2C2 test mode
0:   None
1:   Master transmit
2:   Master recieve
3:   Slave  transmit
4:   Slave  recieve
5:   register transmit
6:   register recieve
*******************************************************************************/
unsigned char I2C_mode = 1;

unsigned char I2C_Send_Data[256];
unsigned char I2C_Reci_Data[256];
unsigned int  I2C_Reci_count = 0;

static void SystemClock_Config(void);

#define SAMPLE_I2C    I2C14

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t i = 0;
  GPIO_InitType GPIO_InitStructure;
  I2C_InitType  I2C_InitStruct;
  
  /* V32F20xxx CM33 core0 STD library initialization:
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Set NVIC Group Priority to 3
       - Low Level Initialization
     */
  STD_Init(CLK_GetHCLK0Freq());
  
  /* Configure the system System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  
  BSP_Printf_Init();
  
  printf("use I2C14 for test!\r\n");

  /* PH14 -> I2C0_0 SCL; PH15 -> I2C0_0 SDA*/
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource14, GPIO_AF14_I2C14_SCL);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource15, GPIO_AF14_I2C14_SDA);
  
  /* config I2C SCK */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
  
  /* config I2C SDA */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_15;
  GPIO_Init(GPIOH, &GPIO_InitStructure);
  
  SYSCFG1_Periph1ClockCmd(SYSCFG1_Periph1Clock_I2C14, ENABLE);
  SYSCFG1_PeriphReset(SYSCFG1_PeriphReset_I2C14);

  I2C_Cmd(SAMPLE_I2C,  DISABLE);
  
  I2C_DeInit(SAMPLE_I2C);
  I2C_StructInit(&I2C_InitStruct);
  I2C_InitStruct.SlaveAddress = 0xA0;
  I2C_InitStruct.OwnAddress = (0x50 >> 1);
  I2C_InitStruct.Restart = I2C_RESTART_ENABLE;
  
  printf("Prepare I2C14 data\r\n");
  for(i = 0; i< 500;i++)
  {
    __NOP();
  }
  
  for(i = 0; i < 256; i++)
  {
    I2C_Send_Data[i] = i;
  }
  
  if(I2C_mode == 1)
  {
    /**********************************************************
    I2C as master transmit 
    **********************************************************/
    I2C_InitStruct.Mode = I2C_MODE_MASTER;
    I2C_Init(SAMPLE_I2C, &I2C_InitStruct);
    
    /* waite for config */
    for(i = 0; i< 500;i++)
    {
      __NOP();
    }
    
    I2C_Cmd(SAMPLE_I2C, ENABLE);
    
    /* start send data */
    for(i = 0; i < 255; i++)
    {
      while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
      I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE, I2C_Send_Data[i]);
    }
    
    /* last data with stop */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE_STOP, I2C_Send_Data[i]);
        
    /* waite for idle */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_ACTIVE) == SET);
  }
  else if(I2C_mode == 2)
  {
    /**********************************************************
    I2C as master recieve 
    **********************************************************/
    I2C_InitStruct.Mode = I2C_MODE_MASTER;
    I2C_Init(SAMPLE_I2C, &I2C_InitStruct);
    
    /* waite for config */
    for(i = 0; i< 500;i++)
    {
      __NOP();
    }
    
    I2C_Cmd(SAMPLE_I2C, ENABLE);
    
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_READ, 0x00);
    /* start recieve 8 data */
    for(i = 0; i < 6; i++)
    {
      while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_RFNE) == RESET);
      I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_READ, 0x00);
      I2C_Reci_Data[I2C_Reci_count] = I2C_ReceiveData(SAMPLE_I2C);
      I2C_Reci_count += 1;
    }
    
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_RFNE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_READ_STOP, 0x00);
    I2C_Reci_Data[I2C_Reci_count] = I2C_ReceiveData(SAMPLE_I2C);
    I2C_Reci_count += 1;
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_RFNE) == RESET);
    I2C_Reci_Data[I2C_Reci_count] = I2C_ReceiveData(SAMPLE_I2C);
    I2C_Reci_count += 1;

    /* waite for idle */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_ACTIVE) == SET);
  }
  else if(I2C_mode == 3)
  {
    /**********************************************************
    I2C as slave transmit 
    **********************************************************/
    I2C_StructInit(&I2C_InitStruct);
    I2C_InitStruct.Mode = I2C_MODE_SLAVE;
    I2C_InitStruct.OwnAddress = (0x50 >> 1);
    I2C_Init(SAMPLE_I2C, &I2C_InitStruct);
    
    /* waite for config */
    for(i = 0; i< 500;i++)
    {
      __NOP();
    }
    
    I2C_Cmd(SAMPLE_I2C, ENABLE);
    
    /* start send data */
    for(i = 0; i < 5; i++)
    {
      while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_SLV_HOLD_TX_FIFO_EMPTY) == RESET);
      I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE, I2C_Send_Data[i]);
    }
        
    /* waite for idle */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_ACTIVE) == SET);  
  }
  else if(I2C_mode == 4)
  {
    /**********************************************************
    I2C as slave recieve
    **********************************************************/
    I2C_StructInit(&I2C_InitStruct);
    I2C_InitStruct.Mode = I2C_MODE_SLAVE;
    I2C_InitStruct.OwnAddress = (0x50 >> 1);
    I2C_Init(SAMPLE_I2C, &I2C_InitStruct);
    
    /* waite for config */
    for(i = 0; i< 500;i++)
    {
      __NOP();
    }
    
    I2C_Cmd(SAMPLE_I2C, ENABLE);
    
    /* start send data */
    while(1)
    {
      while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_RFNE) == RESET);
      I2C_Reci_Data[I2C_Reci_count] = I2C_ReceiveData(SAMPLE_I2C);
      I2C_Reci_count += 1;
      if(I2C_Reci_count >= 256)
      {
        I2C_Cmd(SAMPLE_I2C, DISABLE);  
        break;
      }
    }
        
    /* waite for idle */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_ACTIVE) == SET);  
  }
  else if(I2C_mode == 5)
  {
    /**********************************************************
    I2C as register transmit
    **********************************************************/
    I2C_InitStruct.Mode = I2C_MODE_MASTER;
    I2C_Init(SAMPLE_I2C, &I2C_InitStruct);
    
    /* waite for config */
    for(i = 0; i< 500;i++)
    {
      __NOP();
    }
    
    I2C_Cmd(SAMPLE_I2C, ENABLE);
    
    /* 16bits register addr */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE, 0x00);
    
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE, 0x00);
    
    /* start send data */
    for(i = 0; i < 127; i++)
    {
      while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
      I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE, I2C_Send_Data[i]+0x10);
    }
    
    /* last data with stop */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE_STOP, I2C_Send_Data[i]+0x10);
        
    /* waite for idle */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_ACTIVE) == SET);
  }
  else if(I2C_mode == 6)
  {
    /**********************************************************
    I2C as register transmit
    **********************************************************/
    I2C_InitStruct.Mode = I2C_MODE_MASTER;
    I2C_Init(SAMPLE_I2C, &I2C_InitStruct);
    
    /* waite for config */
    for(i = 0; i< 500;i++)
    {
      __NOP();
    }
    
    I2C_Cmd(SAMPLE_I2C, ENABLE);
    
    /* 16bits register addr */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE, 0x00);
    
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_WRITE, 0x00);
    
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_TFE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_READ_RESTART, 0x00);
    
    /* start recieve 8 data */
    for(i = 0; i < 126; i++)
    {
      while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_RFNE) == RESET);
      I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_READ, 0x00);
      I2C_Reci_Data[I2C_Reci_count] = I2C_ReceiveData(SAMPLE_I2C);
      I2C_Reci_count += 1;
    }
    
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_RFNE) == RESET);
    I2C_SendCmdDataFrame(SAMPLE_I2C, I2C_CMD_READ_STOP, 0x00);
    I2C_Reci_Data[I2C_Reci_count] = I2C_ReceiveData(SAMPLE_I2C);
    I2C_Reci_count += 1;
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_RFNE) == RESET);
    I2C_Reci_Data[I2C_Reci_count] = I2C_ReceiveData(SAMPLE_I2C);
    I2C_Reci_count += 1;

    /* waite for idle */
    while(I2C_GetFlag(SAMPLE_I2C, I2C_FLAG_ACTIVE) == SET);
  }
    
  I2C_Cmd(SAMPLE_I2C, DISABLE);  
  
  while(1)
  {

  }
}

/**
  * @brief  system AHB and APB Clock Configuration
  *         The Bus Clock is configured as follows :
  *            HCLK0     = RCH 48 MHz
  *            PCLK0     = RCH
  *            HCLK1     = RCH
  *            PCLK1     = RCH
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  CLK_OscInitType CLK_OscInitStruct = {0};
  CLK_InitType CLK_InitStruct = {0};
  
  /* RCH(48M) enabled */
  CLK_OscInitStruct.OscillatorType = CLK_OSCILLATORTYPE_RCH;
  CLK_OscInitStruct.RCHState = CLK_RCH_ON;
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_NONE;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_NONE;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select RCH as system AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0 |\
                            CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_RCH;
  CLK_InitStruct.AHBCLKDivider = 1U;
  CLK_InitStruct.APBCLKSource = CLK_APBCLKSOURCE_RCH;
  CLK_InitStruct.APBCLKDivider = 1U;
  if (CLK_Config(&CLK_InitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Update 1ms tick */
  if (STD_InitTick(CLK_GetHCLK0Freq(), TICK_INT_PRIORITY) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
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
