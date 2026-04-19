/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "udp_test.h"
#include "lwip_comm.h"
#include "delay.h"
#include "tcp_server_test.h"
#include "lan8720.h"
#include "board.h"


#define TEST_INIT_TASK_STK_SIZE            (640+128)
#define TEST_INIT_TASK_PRI                 (configMAX_PRIORITIES - 1)
#define TEST_INIT_TASK_NAME                "test_init"

osThreadId_t testInitHandle;
const osThreadAttr_t testInit_attributes = {
  .name = TEST_INIT_TASK_NAME,
  .priority = (osPriority_t) (TEST_INIT_TASK_PRI),
  .stack_size = TEST_INIT_TASK_STK_SIZE
};


static void SystemClock_Config(void);
static void Error_Handler(void);


static void test_init_task(void *pdata)
{
  uint8_t flag = 0;
  uint32_t timeOut;
  uint32_t len = 0;

  for( ; ; )
  { 
    while(lwip_comm_init()) //lwip
    {
      delay_ms(1200);
    }

    SysTick_Config(CLK_GetHCLK0Freq() / 1000); 
    NVIC_SetPriority(SysTick_IRQn, 1);

    NVIC_SetPriority(MAC0_SBD_IRQn, 4); 
    NVIC_EnableIRQ(MAC0_SBD_IRQn);

    NVIC_SetPriority(MAC1_SBD_IRQn, 4); 
    NVIC_EnableIRQ(MAC1_SBD_IRQn);

    udp_task_create();
    tcp_task_create();
    vTaskDelete(testInitHandle);
  }

  osThreadExit();
}

void test_init_task_create(void)
{
  testInitHandle = osThreadNew(test_init_task, NULL, &testInit_attributes); 
}




/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
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

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_3);

  BSP_Printf_Init();

  /* Init scheduler */
  osKernelInitialize();

  test_init_task_create();
  
  printf("Task create success\r\n");
  
  /* Start scheduler */
  osKernelStart();    

  while (1)
  {
  }
}




/**
  * @brief  AHB and APB Clock Configuration
  *         The Bus Clock is configured as follows :
  *            HCLK0    = RCH 48 MHz
  *            PCLK0    = RCH
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
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_ON;
  CLK_OscInitStruct.PLL0.PLL0_Source = CLK_PLL0SOURCE_RCH_DIV4;
  CLK_OscInitStruct.PLL0.PLL0_1stN   = CLK_PLL0_1stN_2;
  CLK_OscInitStruct.PLL0.PLL0_2rdN   = 24;
  CLK_OscInitStruct.PLL0.PLL0_M      = 2;
  CLK_OscInitStruct.PLL1.PLL1_State = CLK_PLL1_NONE;
  if (CLK_OscConfig(&CLK_OscInitStruct) != STD_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select RCH as AHB and APB clock */
  CLK_InitStruct.BusClock = CLK_BUSCLOCK0 |\
                            CLK_BUSCLOCK1;
  CLK_InitStruct.AHBCLKSource = CLK_AHBCLKSOURCE_RCH;
  CLK_InitStruct.AHBCLKDivider = 2U;
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
