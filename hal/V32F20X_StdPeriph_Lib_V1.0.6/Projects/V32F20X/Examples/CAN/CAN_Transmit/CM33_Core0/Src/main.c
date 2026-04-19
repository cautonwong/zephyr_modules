/**
  * @file    main.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanTxMsg TxMessage;
CanRxMsg RxMessage;
uint32_t SystemCoreClock;
#define CAN0_PD0_PD1    1
#define CAN0_PB8_PB9    2
#define CAN1_PB5_PB6    3
#define CAN1_PB12_PB13  4
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void SYSCON_Configuration(void);
void CAN_GPIO_Configuration(uint8_t CANxIO);
void CAN_Configuration(CAN_Type* CANx);
void CAN_NVIC_Config(CAN_Type* CANx,uint8_t interrupt);
void CAN_transmit_data(CAN_Type* CANx);



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
  
  /* Configure the CM33/CM0 System clock to have a frequency of 48 MHz */
  SystemClock_Config();
  BSP_Printf_Init();
  SYSCON_Configuration();
	
  CAN_GPIO_Configuration(CAN0_PD0_PD1);
	CAN_GPIO_Configuration(CAN1_PB5_PB6);
	CAN_Configuration(CAN0);
	CAN_Configuration(CAN1);
	CAN_NVIC_Config(CAN0,CAN_INT_TI);
	CAN_NVIC_Config(CAN1,CAN_INT_RI);
	printf("Initial success.\r\n");
	CAN_transmit_data(CAN0);
  while(1)
  {

  }
}

void Print_CAN_data(CanTxMsg *msg)
{
  uint8_t i;
  if(msg->ID_Type == CAN_ID_STANDARD)
    printf("CAN ID:   0x%03X\r\n",msg->StdId);
  else
    printf("CAN ID:   0x%08X\r\n",msg->ExtId);
  printf("CAN RTR:  0x%X\r\n",msg->RTR);
  printf("CAN DLC:  0x%X\r\n",msg->DLC);
  printf("CAN DATA: ");
  for(i=0;i<msg->DLC;i++)
    printf("0x%X ",msg->Data[i]);
  printf("\r\n\r\n");

}
/**
 *	@brief  CAN GPIO Configiguration.Contain Mode,Speed and so on
 *	@param  CAN0_PD0_PD1 CAN0_PB8_PB9 CAN1_PB5_PB6 CAN1_PB12_PB13
 *	@retval None
 */
void CAN_GPIO_Configuration(uint8_t CANxIO)
{
	GPIO_InitType         GPIO_InitStruct;
  if(CANxIO==CAN0_PD0_PD1)
  {
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF9_CAN0_RX);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF9_CAN0_TX);
  }
	else if(CANxIO==CAN0_PB8_PB9)
  {
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF9_CAN0_RX);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF9_CAN0_TX);
  }
  else if(CANxIO==CAN1_PB5_PB6)
  {
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF9_CAN1_RX);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF9_CAN1_TX);
  }
	else if(CANxIO==CAN1_PB12_PB13)
  {
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF9_CAN1_RX);
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF9_CAN1_TX);
  }
	else;
}

/**
 *	@brief  CAN Configiguration.Contain Mode,Baudrate=500Kbps,Filter and so on
 *	@param  CAN0 CAN1
 *	@retval None
 */
void CAN_Configuration(CAN_Type* CANx)
{ 
	CAN_InitType CAN_InitStruct;
	CAN_FilterInitType CAN_FilterInitStruct;
  
  CAN_DeInit(CANx);
  CAN_InitStruct.CAN_Mode = CAN_MODE_NORMAL;
  CAN_InitStruct.CAN_Prescaler = 4;    //Baudrate=(SystemClock/2/CAN_Prescaler/(CAN_TSEG1+CAN_TSEG2+1))
  CAN_InitStruct.CAN_SJW = CAN_SJW_2TQ;//500000bps=(48000000/2/4/(8+3+1))
  CAN_InitStruct.CAN_TSEG1 = CAN_TSEG1_8TQ;
  CAN_InitStruct.CAN_TSEG2 = CAN_TSEG2_3TQ;
  CAN_InitStruct.CAN_OCR = CAN_OCRMODE_RESERVED;
  CAN_InitStruct.CAN_SAM = CAN_SAMPLING_3;
  CAN_InitStruct.CAN_EWLR = 96;
  CAN_Init(CANx,&CAN_InitStruct);
	
	CAN_FilterStructInit(&CAN_FilterInitStruct);
  CAN_FilterInitStruct.CAN_FilterIDMode = CAN_FILTER_ID_MODE_STD;
  CAN_FilterInitStruct.CAN_FilterAcceptMode = CAN_FILTER_ACCEPT_MODE_SINGLE;
  CAN_FilterInitStruct.CAN_FilterRTR = CAN_FILTER_RTR_DATA;
  CAN_FilterInitStruct.CAN_FilterRTRMsk = 1;
  CAN_FilterInitStruct.CAN_FilterStdID[0] = 0x755;
  CAN_FilterInitStruct.CAN_FilterStdIDMsk[0] = 0x0;
  CAN_FilterInitStruct.CAN_FilterData[0] = 0xFF;
  CAN_FilterInitStruct.CAN_FilterDataMsk[0] = 0xFF;
  CAN_FilterInitStruct.CAN_FilterExtID[0] = 0xFFFFFFFF;
  CAN_FilterInitStruct.CAN_FilterExtIDMsk[0] = 0xFFFFFFFF;
  CAN_FilterInit(CANx,&CAN_FilterInitStruct);
	
}

/**
 *	@brief  CAN NVIC Configiguration. Enable CAN NVIC,and Setting Priority
 *	@param  CANx: CAN0 CAN1  interrupt:CAN_INT_RI CAN_INT_TI...
 *	@retval None
 */
void CAN_NVIC_Config(CAN_Type* CANx,uint8_t interrupt)
{
	uint32_t group,priority;
	if(CANx==CAN0)
  {
		NVIC_DisableIRQ(CAN0_IRQn);
    CAN_INTConfig(CAN0,interrupt,ENABLE);
  	group = NVIC_GetPriorityGrouping();
	  priority = NVIC_EncodePriority(group,1,1);
	  NVIC_SetPriority(CAN0_IRQn, priority);
	  NVIC_EnableIRQ(CAN0_IRQn);
	}
	else if(CANx==CAN1)
	{
		NVIC_DisableIRQ(CAN1_IRQn);
    CAN_INTConfig(CAN1,interrupt,ENABLE);
  	group = NVIC_GetPriorityGrouping();
	  priority = NVIC_EncodePriority(group,1,1);
	  NVIC_SetPriority(CAN1_IRQn, priority);
	  NVIC_EnableIRQ(CAN1_IRQn);
	}
	else;
}

/**
 *	@brief  CAN transmit data.SID=0x755,Standard identifier,Data frame,data D0~D7 all 0xA5 
 *	@param  CAN0 CAN1
 *	@retval None
 */
void CAN_transmit_data(CAN_Type* CANx)
{
  uint8_t i,err=0;
	
	TxMessage.ID_Type = CAN_ID_STANDARD;
  TxMessage.StdId = 0x755;
  TxMessage.RTR = CAN_RTR_DATA;
  TxMessage.DLC = CAN_DLC_8;
  for(i=0;i<8;i++)
  {
    TxMessage.Data[i] = 0xA5;
  }

  printf("CAN Send DATA: \r\n");
  Print_CAN_data(&TxMessage);

  err = CAN_Transmit(CANx,&TxMessage);
  if(err)
  {
    printf("CAN Send data Error.%d\r\n",err);
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
  CLK_OscInitStruct.PLL0.PLL0_State = CLK_PLL0_NONE;
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
  SystemCoreClock = 48000000;

}


/**
  * @brief  Configures the different system clocks.
  * @param  None
  * @retval None
  */
void SYSCON_Configuration(void)
{
  /* Enable CAN0 CAN1 clocks */
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_CAN0, ENABLE);
  SYSCFG0_Periph1ClockCmd(SYSCFG0_Periph1Clock_CAN1, ENABLE);
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
