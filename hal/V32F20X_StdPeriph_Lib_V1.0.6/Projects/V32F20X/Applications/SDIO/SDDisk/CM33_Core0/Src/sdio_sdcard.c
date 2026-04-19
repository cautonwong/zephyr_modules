/**
  * @file    sdio.sdcard.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   sdcard program body.
******************************************************************************/

#include "sdio_sdcard.h"
#include "lib_sdio.h"
#include "string.h"
/* Private macro -------------------------------------------------------------*/
/** 
  * @brief  SDIO Static flags, TimeOut, FIFO Address  
  */
#define NULL 0
#define SDIO_STATIC_FLAGS               ((uint32_t)0xFFFFFFFF)  //0x07FF41FF
#define SDIO_CMD0TIMEOUT                ((uint32_t)0x00010000)

/** 
  * @brief  Mask for errors Card Status R1 (OCR Register) 
  */
#define SD_OCR_ADDR_OUT_OF_RANGE        ((uint32_t)0x80000000)
#define SD_OCR_ADDR_MISALIGNED          ((uint32_t)0x40000000)
#define SD_OCR_BLOCK_LEN_ERR            ((uint32_t)0x20000000)
#define SD_OCR_ERASE_SEQ_ERR            ((uint32_t)0x10000000)
#define SD_OCR_BAD_ERASE_PARAM          ((uint32_t)0x08000000)
#define SD_OCR_WRITE_PROT_VIOLATION     ((uint32_t)0x04000000)
#define SD_OCR_LOCK_UNLOCK_FAILED       ((uint32_t)0x01000000)
#define SD_OCR_COM_CRC_FAILED           ((uint32_t)0x00800000)
#define SD_OCR_ILLEGAL_CMD              ((uint32_t)0x00400000)
#define SD_OCR_CARD_ECC_FAILED          ((uint32_t)0x00200000)
#define SD_OCR_CC_ERROR                 ((uint32_t)0x00100000)
#define SD_OCR_GENERAL_UNKNOWN_ERROR    ((uint32_t)0x00080000)
#define SD_OCR_STREAM_READ_UNDERRUN     ((uint32_t)0x00040000)
#define SD_OCR_STREAM_WRITE_OVERRUN     ((uint32_t)0x00020000)
#define SD_OCR_CID_CSD_OVERWRIETE       ((uint32_t)0x00010000)
#define SD_OCR_WP_ERASE_SKIP            ((uint32_t)0x00008000)
#define SD_OCR_CARD_ECC_DISABLED        ((uint32_t)0x00004000)
#define SD_OCR_ERASE_RESET              ((uint32_t)0x00002000)
#define SD_OCR_AKE_SEQ_ERROR            ((uint32_t)0x00000008)
#define SD_OCR_ERRORBITS                ((uint32_t)0xFDFFE008)

/** 
  * @brief  Masks for R6 Response 
  */
#define SD_R6_GENERAL_UNKNOWN_ERROR     ((uint32_t)0x00002000)
#define SD_R6_ILLEGAL_CMD               ((uint32_t)0x00004000)
#define SD_R6_COM_CRC_FAILED            ((uint32_t)0x00008000)

#define SD_VOLTAGE_WINDOW_SD            ((uint32_t)0x80100000)
#define SD_HIGH_CAPACITY                ((uint32_t)0x40000000)
#define SD_STD_CAPACITY                 ((uint32_t)0x00000000)
#define SD_CHECK_PATTERN                ((uint32_t)0x000001AA)

//#define SD_MAX_VOLT_TRIAL               ((uint32_t)0x0000FFFF)
#define SD_MAX_VOLT_TRIAL               ((uint32_t)0x0000002F)
#define SD_ALLZERO                      ((uint32_t)0x00000000)

#define SD_WIDE_BUS_SUPPORT             ((uint32_t)0x00040000)
#define SD_SINGLE_BUS_SUPPORT           ((uint32_t)0x00010000)
#define SD_CARD_LOCKED                  ((uint32_t)0x02000000)

#define SD_DATATIMEOUT                  ((uint32_t)0xFFFFFFFF)
#define SD_0TO7BITS                     ((uint32_t)0x000000FF)
#define SD_8TO15BITS                    ((uint32_t)0x0000FF00)
#define SD_16TO23BITS                   ((uint32_t)0x00FF0000)
#define SD_24TO31BITS                   ((uint32_t)0xFF000000)
#define SD_MAX_DATA_LENGTH              ((uint32_t)0x01FFFFFF)

#define SD_HALFFIFO                     ((uint32_t)0x00000008)
#define SD_HALFFIFOBYTES                ((uint32_t)0x00000020)

/** 
  * @brief  Command Class Supported 
  */
#define SD_CCCC_LOCK_UNLOCK             ((uint32_t)0x00000080)
#define SD_CCCC_WRITE_PROT              ((uint32_t)0x00000040)
#define SD_CCCC_ERASE                   ((uint32_t)0x00000020)

/** 
  * @brief  Following commands are SD Card Specific commands.
  *         SDIO_APP_CMD should be sent before sending these commands. 
  */
#define SDIO_SEND_IF_COND               ((uint32_t)0x00000008)

/* Private variables ---------------------------------------------------------*/
static uint32_t CardType =  SDIO_STD_CAPACITY_SD_CARD_V1_1;	//The type of memory card first initializes it into a 1.1 protocol card
static uint32_t CSD_Tab[4], CID_Tab[4], RCA = 0;//Storage CSD, DID, register and card relative address
static uint8_t SDSTATUS_Tab[16]; //The memory card status is part of the CSR
__IO uint32_t StopCondition = 0; //The logo used to stop the card operation
__IO SD_Error TransferError = SD_OK; //Used for memory card errors, initialization to normal state
__IO uint32_t TransferEnd = 0;	   //Used to sign for the end of the transmission, call in the interrupt service function
SD_CardInfo SDCardInfo;	  //Used for the information of the memory card


/*The structural body for SDIO initialization*/
SDIO_InitType SDIO_InitStructure;
SDIO_CMDInitType SDIO_CmdInitStructure;
SDIO_DATAInitType SDIO_DataInitStructure;   

/* Private function prototypes -----------------------------------------------*/
static SD_Error CmdError(SDIO_TypeDef *SDIOx);
static SD_Error CmdResp1Error(SDIO_TypeDef *SDIOx,uint8_t cmd);
static SD_Error CmdResp7Error(SDIO_TypeDef *SDIOx);
static SD_Error CmdResp3Error(SDIO_TypeDef *SDIOx);
static SD_Error CmdResp2Error(SDIO_TypeDef *SDIOx);
static SD_Error CmdResp6Error(SDIO_TypeDef *SDIOx,uint8_t cmd, uint16_t *prca);
static SD_Error SDEnWideBus(SDIO_TypeDef *SDIOx,FunctionalState NewState);
static SD_Error IsCardProgramming(SDIO_TypeDef *SDIOx, uint8_t *pstatus);

static void GPIO_Configuration(SDIO_TypeDef *SDIOx);
static uint32_t SD_DMAEndOfTransferStatus(SDIO_TypeDef *SDIOx);
static void SD_DMA_RxConfig(SDIO_TypeDef *SDIOx,uint32_t *BufferDST, uint32_t BufferSize);
static void SD_DMA_TxConfig(SDIO_TypeDef *SDIOx,uint32_t *BufferSRC, uint32_t BufferSize, uint32_t Block);

uint8_t convert_from_bytes_to_power_of_two(uint16_t NumberOfBytes);
extern void SDIODelay_ms(uint32_t n);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Deinitializes the SDIOx GPIO.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval None
  */
void SD_DeInit(SDIO_TypeDef *SDIOx)
{
  GPIO_InitType  GPIO_InitStructure;
  
  /*!< Disable SDIO Clock */
  SDIO_ClockCmd(SDIOx,DISABLE);
  
  /*!< Set Power State to OFF */

  /*!< DeInitializes the SDIO peripheral */
  SDIO_DeInit(SDIOx);
  
  if(SDIOx == SDIO0)
  {
    /*!< Disable the SDIO AHB Clock */
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO0,DISABLE);

    /*!< Configure PC08, PC09, PC10, PC11, PC12 pin*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*!< Configure PD02 CMD line */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
  }
  else if(SDIOx == SDIO1)
  {
    /*!< Disable the SDIO AHB Clock */
    SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO1,DISABLE);

    /*!< Configure PF00~PF03 pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /*!< Configure PI10~PI11 CMD line */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_Init(GPIOI, &GPIO_InitStructure);
  }
}

/**
  * @brief  Gets the SDIO_FLAG_DMA flag is set or not.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval SET or RESET
  */
uint32_t SD_DMAEndOfTransferStatus(SDIO_TypeDef *SDIOx)
{
  return (uint32_t)SDIO_GetFlagStatus(SDIOx,SDIO_FLAG_DMA); 
}

/**
  * @brief  DMA send data request.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @param  BufferSRC: Pointing to data
  * @param  BufferSize: Data size
  * @param  Block: Block size
  * @retval None
  */
void SD_DMA_TxConfig(SDIO_TypeDef *SDIOx,uint32_t *BufferSRC, uint32_t BufferSize,uint32_t Block)
{
  uint32_t tmpreg;

  SDIOx->ADDR = (uint32_t)BufferSRC;  //SDMA memory address
  SDIOx->BLOCK_COUNT = (uint32_t)BufferSize | Block<<16;
  SDIOx->CMD |= SDIO_CMD_BCE_EN;
}

/**
  * @brief  Initializes the SDIOx GPIO.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval None
  */
static void GPIO_Configuration(SDIO_TypeDef *SDIOx)
{
  GPIO_InitType GPIO_InitStructure;
  uint32_t temp;

  if(SDIOx == SDIO0)
  {
    // C8~C12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //GPIO_PuPd_NOPULL  GPIO_PuPd_UP
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; //CMD
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF12_SDIO0_D0);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF12_SDIO0_D1);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF12_SDIO0_D2);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF12_SDIO0_D3);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF12_SDIO0_CLK);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF12_SDIO0_CMD);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; //CD
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;  //CTRL
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_ResetBits(GPIOC,GPIO_Pin_1); //SD power on
  }
  else if(SDIOx == SDIO1)
  {
    // PF0~PF03 PI10 PI11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  //GPIO_PuPd_NOPULL  GPIO_PuPd_UP
    GPIO_Init(GPIOF, &GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11 ;
    GPIO_Init(GPIOI, &GPIO_InitStructure); 
    
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource0,GPIO_AF12_SDIO1_D0);
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource1,GPIO_AF12_SDIO1_D1);
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource2,GPIO_AF12_SDIO1_D2);
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource3,GPIO_AF12_SDIO1_CLK);
    GPIO_PinAFConfig(GPIOI,GPIO_PinSource10,GPIO_AF12_SDIO1_CMD);
    GPIO_PinAFConfig(GPIOI,GPIO_PinSource11,GPIO_AF12_SDIO1_D3);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ; //CD
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOI, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;  //CTRL
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOI, &GPIO_InitStructure);
    
    GPIO_ResetBits(GPIOI,GPIO_Pin_1); //SD power on
  }
}

/**
  * @brief  Initializes the SDIOx.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval None
  */
SD_Error SD_Init(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;
  
  /* Configura GPIO */
  GPIO_Configuration(SDIOx);

  SDIO_DeInit(SDIOx);  
  SDIO_VDD1Cmd(SDIOx, ENABLE); 
  SDIO_SetVDD1Voltage(SDIOx, SDIO_CTRL1_VDD1VOT_3_3V);
  SDIODelay_ms(300);

  SDIOx->CTRL2 = (0xE<<16)|(0x19<<8)|SDIO_CTRL2_ICE; 
  while((SDIOx->CTRL2 & BIT1) != BIT1);
  SDIOx->CTRL2 = (0xE<<16)|(0x19<<8)|BIT2|SDIO_CTRL2_ICE; 
  SDIOx->STATUS3_MASK = 0xFFFFFFFF;

  SDIO_SelectDevice(SDIOx,SDIO_DEVICE_SDCard);//SD Card in use

  errorstatus = SD_PowerON(SDIOx); 

  if (errorstatus != SD_OK)
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return(errorstatus);	
  }

  errorstatus = SD_InitializeCards(SDIOx); 

  if (errorstatus != SD_OK)	
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return(errorstatus);
  }

  /*!< Configure the SDIO peripheral 
  !< on STM32F2xx devices, SDIOCLK is fixed to 48MHz
  !< SDIOCLK = HCLK, SDIO_CK = HCLK/(2 + SDIO_TRANSFER_CLK_DIV) */    
  if (errorstatus == SD_OK)
  {
    /*----------------- Read CSD/CID MSD registers ------------------*/
    errorstatus = SD_GetCardInfo(SDIOx,&SDCardInfo);	 
  }

  if (errorstatus == SD_OK)
  {
    /*----------------- Select Card --------------------------------*/
    errorstatus = SD_SelectDeselect(SDIOx,(uint32_t) (SDCardInfo.RCA << 16));	
  }

  if (errorstatus == SD_OK)
  {
    errorstatus = SD_EnableWideBusOperation(SDIOx,SDIO_BusWide_4b);	//4bits
    if(errorstatus == SD_OK )
    {
      SDIO_InitStructure.ClockSource = SDIO_CLK_RCH;
      SDIO_InitStructure.ClockDiv = 0x2;
      SDIO_InitStructure.BusWide = SDIO_BusWide_4b;
      SDIO_InitStructure.Mode = SDIO_MODE_SD;
      SDIO_Init(SDIOx,&SDIO_InitStructure);
    }
  }  

  return(errorstatus);
}

/**
  * @brief  Gets the cuurent sd card data transfer status.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval SDTransferState: Data Transfer state.
  *   This value can be: 
  *        - SD_TRANSFER_OK: No data transfer is acting
  *        - SD_TRANSFER_BUSY: Data transfer is acting
  */
SDTransferState SD_GetStatus(SDIO_TypeDef *SDIOx)
{
  SDCardState cardstate =  SD_CARD_TRANSFER;

  cardstate = SD_GetState(SDIOx);
  
  if (cardstate == SD_CARD_TRANSFER)
  {
    return(SD_TRANSFER_OK);
  }
  else if(cardstate == SD_CARD_ERROR)
  {
    return (SD_TRANSFER_ERROR);
  }
  else
  {
    return(SD_TRANSFER_BUSY);
  }
}

/**
  * @brief  Returns the current card's state.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval SDCardState: SD Card Error or SD Card Current State.
  */
SDCardState SD_GetState(SDIO_TypeDef *SDIOx)
{
  uint32_t resp1 = 0;   

    if (SD_SendStatus(SDIOx,&resp1) != SD_OK)
    {
      return SD_CARD_ERROR;
    }
    else
    {
      return (SDCardState)((resp1 >> 9) & 0x0F);
    } 
}

/**
  * @brief  Power on SDIO.
  * @param  SDIOx: where x can be 0 to 1 to select the SDIO peripheral.
  * @retval SDCardState: SD Card Error or SD Card Current State.
  */
SD_Error SD_PowerON(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;
  uint32_t response = 0, count = 0, validvoltage = 0;
  uint32_t SDType = SD_STD_CAPACITY;
  uint32_t i;

  /*!< Power ON Sequence -----------------------------------------------------*/
  /*!< Configure the SDIO peripheral */
  /*!< SDIOCLK = HCLK, SDIO_CK = HCLK/(2 + SDIO_INIT_CLK_DIV) */
  /*!< on STM32F2xx devices, SDIOCLK is fixed to 48MHz */
  /*!< SDIO_CK for initialization should not exceed 400 KHz */ 
    SDIO_InitStructure.ClockSource = SDIO_CLK_RCH;
    SDIO_InitStructure.ClockDiv = 0x19;
    SDIO_InitStructure.BusWide = SDIO_BusWide_1b;
    SDIO_InitStructure.Mode = SDIO_MODE_SD;
    SDIO_Init(SDIOx,&SDIO_InitStructure);
  
  /*!< CMD0: GO_IDLE_STATE ---------------------------------------------------*/
  /*!< No CMD response required */
    SDIO_CmdInitStructure.CmdIndex = SD_CMD_GO_IDLE_STATE;  //cmd0
  SDIO_CmdInitStructure.Argument = 0;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_No; 
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  errorstatus = CmdError(SDIOx);
  if (errorstatus != SD_OK)	
  {
    /*!< CMD Response TimeOut (wait for CMDSENT flag) */
    return(errorstatus);
  }

  /*!< CMD8: SEND_IF_COND ----------------------------------------------------*/
  /*!< Send CMD8 to verify SD card interface operating condition */
  /*!< Argument: - [31:12]: Reserved (shall be set to '0')
               - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
               - [7:0]: Check Pattern (recommended 0xAA) */
  /*!< CMD Response: R7 */
  SDIO_CmdInitStructure.CmdIndex = SDIO_SEND_IF_COND;  //cmd8
  SDIO_CmdInitStructure.Argument = SD_CHECK_PATTERN;  
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;  //r7
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
  for(i=0;i<6000;i++)//
  {

  }   

  errorstatus = CmdResp7Error(SDIOx); 

  if (errorstatus == SD_OK)	
  {
    CardType = SDIO_STD_CAPACITY_SD_CARD_V2_0; 
  }
  else
  {
    /*!< CMD55 */	  
    SDIO_CmdInitStructure.Argument = 0x00;  
    SDIO_CmdInitStructure.CmdIndex = SD_CMD_APP_CMD;  //cmd8
    SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
    SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
    SDIO_CmdInitStructure.Response = SDIO_Response_Short;  ///r1
    SDIO_CmdInitStructure.DataMode = SDIO_CMD;
    SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);		
    errorstatus = CmdResp1Error(SDIOx,SD_CMD_APP_CMD);
  }
  /*!< CMD55 */		

  SDIO_CmdInitStructure.Argument = 0x00; 
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_APP_CMD;  //cmd8
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;  ///r1
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);		
  for(i=0;i<50000;i++)//
  {

  }
  errorstatus = CmdResp1Error(SDIOx,SD_CMD_APP_CMD);	

  /*!< If errorstatus is Command TimeOut, it is a MMC card */
  /*!< If errorstatus is SD_OK it is a SD card: SD card 2.0 (voltage range mismatch)
     or SD card 1.x */
  if (errorstatus == SD_OK)	
  {
    /*!< SD CARD */
    /*!< Send ACMD41 SD_APP_OP_COND with Argument 0x80100000 */
    while ((!validvoltage) && (count < SD_MAX_VOLT_TRIAL))
    {	 
      /*!< SEND CMD55 APP_CMD with RCA as 0 */
      SDIO_CmdInitStructure.Argument = 0x00;  
      SDIO_CmdInitStructure.CmdIndex = SD_CMD_APP_CMD;  //CMD55
      SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
      SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
      SDIO_CmdInitStructure.Response = SDIO_Response_Short;  ///r1
      SDIO_CmdInitStructure.DataMode = SDIO_CMD;
      SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);				
      
      errorstatus = CmdResp1Error(SDIOx,SD_CMD_APP_CMD); 

      if (errorstatus != SD_OK)
      {
        return(errorstatus);
      }
      SDIO_CmdInitStructure.Argument = SD_VOLTAGE_WINDOW_SD | SDType;	
      SDIO_CmdInitStructure.Argument = 0x40ff8000;
      SDIO_CmdInitStructure.CmdIndex = SD_CMD_SD_APP_OP_COND;  //CMD41
      SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
      SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
      SDIO_CmdInitStructure.Response = SDIO_Response_Short;  //r3
      SDIO_CmdInitStructure.DataMode = SDIO_CMD;
      SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);	

      for(i=0;i<50000;i++)//
      {

      }
      errorstatus = CmdResp3Error(SDIOx);
      if (errorstatus != SD_OK)
      {
        return(errorstatus);  
      }
      response = SDIO_GetResponse(SDIOx,SDIO_RESP1);	
      validvoltage = (((response >> 31) == 1) ? 1 : 0);
      count++;			 
    }
    if (count >= SD_MAX_VOLT_TRIAL)	
    {
      errorstatus = SD_INVALID_VOLTRANGE;	
      return(errorstatus);
    }

    if (response &= SD_HIGH_CAPACITY) 
    {
      CardType = SDIO_HIGH_CAPACITY_SD_CARD;  
    }

  }/*!< else MMC Card */

  return(errorstatus);		
}

SD_Error SD_InitializeCards(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;
  uint16_t rca = 0x01;

  if (SDIO_SECURE_DIGITAL_IO_CARD != CardType)
  {
    /*!< Send CMD2 ALL_SEND_CID */
    SDIO_CmdInitStructure.Argument = 0x00;   
    SDIO_CmdInitStructure.CmdIndex = SD_CMD_ALL_SEND_CID;  //CMD2
    SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
    SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
    SDIO_CmdInitStructure.Response = SDIO_Response_Long;  ///r1
    SDIO_CmdInitStructure.DataMode = SDIO_CMD;
    SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);		
    
    errorstatus = CmdResp2Error(SDIOx);

    if (SD_OK != errorstatus)
    {
      return(errorstatus);
    }

    CID_Tab[0] = SDIO_GetResponse(SDIOx,SDIO_RESP1);
    CID_Tab[1] = SDIO_GetResponse(SDIOx,SDIO_RESP2);
    CID_Tab[2] = SDIO_GetResponse(SDIOx,SDIO_RESP3);
    CID_Tab[3] = SDIO_GetResponse(SDIOx,SDIO_RESP4);
  }
    
  if ((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) ||  (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) ||  (SDIO_SECURE_DIGITAL_IO_COMBO_CARD == CardType)
      ||  (SDIO_HIGH_CAPACITY_SD_CARD == CardType))	
  {
    /*!< Send CMD3 SET_REL_ADDR with argument 0 */
    /*!< SD Card publishes its RCA. */
    SDIO_CmdInitStructure.Argument = 0x00;   //
    SDIO_CmdInitStructure.CmdIndex = SD_CMD_SET_REL_ADDR;  //CMD3
    SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
    SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
    SDIO_CmdInitStructure.Response = SDIO_Response_Short;  ///r1
    SDIO_CmdInitStructure.DataMode = SDIO_CMD;
    SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);		

    errorstatus = CmdResp6Error(SDIOx,SD_CMD_SET_REL_ADDR, &rca);

    if (SD_OK != errorstatus)
    {
      return(errorstatus);
    }
  }

  if (SDIO_SECURE_DIGITAL_IO_CARD != CardType)
  {
    RCA = rca;

    /*!< Send CMD9 SEND_CSD with argument as card's RCA */
    SDIO_CmdInitStructure.Argument = (uint32_t)(rca << 16);
    SDIO_CmdInitStructure.CmdIndex = SD_CMD_SEND_CSD;  //CMD9
    SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
    SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
    SDIO_CmdInitStructure.Response = SDIO_Response_Long;  ///r1
    SDIO_CmdInitStructure.DataMode = SDIO_CMD;
    SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);				
    
    errorstatus = CmdResp2Error(SDIOx);

    if (SD_OK != errorstatus)
    {
      return(errorstatus);
    }

    CSD_Tab[0] = SDIO_GetResponse(SDIOx,SDIO_RESP1);
    CSD_Tab[1] = SDIO_GetResponse(SDIOx,SDIO_RESP2);
    CSD_Tab[2] = SDIO_GetResponse(SDIOx,SDIO_RESP3);
    CSD_Tab[3] = SDIO_GetResponse(SDIOx,SDIO_RESP4);
  }

  errorstatus = SD_OK; /*!< All cards get intialized */

  return(errorstatus);
}

SD_Error SD_GetCardInfo(SDIO_TypeDef *SDIOx,SD_CardInfo *cardinfo)
{
  SD_Error errorstatus = SD_OK;
  uint8_t tmp = 0;

  cardinfo->CardType = (uint8_t)CardType;
  cardinfo->RCA = (uint16_t)RCA;

  /*!< Byte 0 */
  tmp = (uint8_t)((CSD_Tab[0] & 0xFF000000) >> 24);
  cardinfo->SD_csd.CSDStruct = (tmp & 0xC0) >> 6;
  cardinfo->SD_csd.SysSpecVersion = (tmp & 0x3C) >> 2;
  cardinfo->SD_csd.Reserved1 = tmp & 0x03;

  /*!< Byte 1 */
  tmp = (uint8_t)((CSD_Tab[0] & 0x00FF0000) >> 16);
  cardinfo->SD_csd.TAAC = tmp;

  /*!< Byte 2 */
  tmp = (uint8_t)((CSD_Tab[0] & 0x0000FF00) >> 8);
  cardinfo->SD_csd.NSAC = tmp;

  /*!< Byte 3 */
  tmp = (uint8_t)(CSD_Tab[0] & 0x000000FF);
  cardinfo->SD_csd.MaxBusClkFrec = tmp;

  /*!< Byte 4 */
  tmp = (uint8_t)((CSD_Tab[1] & 0xFF000000) >> 24);
  cardinfo->SD_csd.CardComdClasses = tmp << 4;

  /*!< Byte 5 */
  tmp = (uint8_t)((CSD_Tab[1] & 0x00FF0000) >> 16);
  cardinfo->SD_csd.CardComdClasses |= (tmp & 0xF0) >> 4;
  cardinfo->SD_csd.RdBlockLen = tmp & 0x0F;

  /*!< Byte 6 */
  tmp = (uint8_t)((CSD_Tab[1] & 0x0000FF00) >> 8);
  cardinfo->SD_csd.PartBlockRead = (tmp & 0x80) >> 7;
  cardinfo->SD_csd.WrBlockMisalign = (tmp & 0x40) >> 6;
  cardinfo->SD_csd.RdBlockMisalign = (tmp & 0x20) >> 5;
  cardinfo->SD_csd.DSRImpl = (tmp & 0x10) >> 4;
  cardinfo->SD_csd.Reserved2 = 0; /*!< Reserved */

  if ((CardType == SDIO_STD_CAPACITY_SD_CARD_V1_1) || (CardType == SDIO_STD_CAPACITY_SD_CARD_V2_0))
  {
    cardinfo->SD_csd.DeviceSize = (tmp & 0x03) << 10;

    /*!< Byte 7 */
    tmp = (uint8_t)(CSD_Tab[1] & 0x000000FF);
    cardinfo->SD_csd.DeviceSize |= (tmp) << 2;

    /*!< Byte 8 */
    tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000) >> 24);
    cardinfo->SD_csd.DeviceSize |= (tmp & 0xC0) >> 6;

    cardinfo->SD_csd.MaxRdCurrentVDDMin = (tmp & 0x38) >> 3;
    cardinfo->SD_csd.MaxRdCurrentVDDMax = (tmp & 0x07);

    /*!< Byte 9 */
    tmp = (uint8_t)((CSD_Tab[2] & 0x00FF0000) >> 16);
    cardinfo->SD_csd.MaxWrCurrentVDDMin = (tmp & 0xE0) >> 5;
    cardinfo->SD_csd.MaxWrCurrentVDDMax = (tmp & 0x1C) >> 2;
    cardinfo->SD_csd.DeviceSizeMul = (tmp & 0x03) << 1;
    /*!< Byte 10 */
    tmp = (uint8_t)((CSD_Tab[2] & 0x0000FF00) >> 8);
    cardinfo->SD_csd.DeviceSizeMul |= (tmp & 0x80) >> 7;
    
    cardinfo->CardCapacity = (cardinfo->SD_csd.DeviceSize + 1) ;
    cardinfo->CardCapacity *= (1 << (cardinfo->SD_csd.DeviceSizeMul + 2));
    cardinfo->CardBlockSize = 1 << (cardinfo->SD_csd.RdBlockLen);
    cardinfo->CardCapacity *= cardinfo->CardBlockSize;
  }
  else if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)
  {
    /*!< Byte 7 */
    tmp = (uint8_t)(CSD_Tab[1] & 0x000000FF);
    cardinfo->SD_csd.DeviceSize = (tmp & 0x3F) << 16;

    /*!< Byte 8 */
    tmp = (uint8_t)((CSD_Tab[2] & 0xFF000000) >> 24);

    cardinfo->SD_csd.DeviceSize |= (tmp << 8);

    /*!< Byte 9 */
    tmp = (uint8_t)((CSD_Tab[2] & 0x00FF0000) >> 16);

    cardinfo->SD_csd.DeviceSize |= (tmp);

    /*!< Byte 10 */
    tmp = (uint8_t)((CSD_Tab[2] & 0x0000FF00) >> 8);
    
    cardinfo->CardCapacity = (cardinfo->SD_csd.DeviceSize + 1) * 512 * 1024;
    cardinfo->CardBlockSize = 512;    
  }


  cardinfo->SD_csd.EraseGrSize = (tmp & 0x40) >> 6;
  cardinfo->SD_csd.EraseGrMul = (tmp & 0x3F) << 1;

  /*!< Byte 11 */
  tmp = (uint8_t)(CSD_Tab[2] & 0x000000FF);
  cardinfo->SD_csd.EraseGrMul |= (tmp & 0x80) >> 7;
  cardinfo->SD_csd.WrProtectGrSize = (tmp & 0x7F);

  /*!< Byte 12 */
  tmp = (uint8_t)((CSD_Tab[3] & 0xFF000000) >> 24);
  cardinfo->SD_csd.WrProtectGrEnable = (tmp & 0x80) >> 7;
  cardinfo->SD_csd.ManDeflECC = (tmp & 0x60) >> 5;
  cardinfo->SD_csd.WrSpeedFact = (tmp & 0x1C) >> 2;
  cardinfo->SD_csd.MaxWrBlockLen = (tmp & 0x03) << 2;

  /*!< Byte 13 */
  tmp = (uint8_t)((CSD_Tab[3] & 0x00FF0000) >> 16);
  cardinfo->SD_csd.MaxWrBlockLen |= (tmp & 0xC0) >> 6;
  cardinfo->SD_csd.WriteBlockPaPartial = (tmp & 0x20) >> 5;
  cardinfo->SD_csd.Reserved3 = 0;
  cardinfo->SD_csd.ContentProtectAppli = (tmp & 0x01);

  /*!< Byte 14 */
  tmp = (uint8_t)((CSD_Tab[3] & 0x0000FF00) >> 8);
  cardinfo->SD_csd.FileFormatGrouop = (tmp & 0x80) >> 7;
  cardinfo->SD_csd.CopyFlag = (tmp & 0x40) >> 6;
  cardinfo->SD_csd.PermWrProtect = (tmp & 0x20) >> 5;
  cardinfo->SD_csd.TempWrProtect = (tmp & 0x10) >> 4;
  cardinfo->SD_csd.FileFormat = (tmp & 0x0C) >> 2;
  cardinfo->SD_csd.ECC = (tmp & 0x03);

  /*!< Byte 15 */
  tmp = (uint8_t)(CSD_Tab[3] & 0x000000FF);
  cardinfo->SD_csd.CSD_CRC = (tmp & 0xFE) >> 1;
  cardinfo->SD_csd.Reserved4 = 1;


  /*!< Byte 0 */
  tmp = (uint8_t)((CID_Tab[0] & 0xFF000000) >> 24);
  cardinfo->SD_cid.ManufacturerID = tmp;

  /*!< Byte 1 */
  tmp = (uint8_t)((CID_Tab[0] & 0x00FF0000) >> 16);
  cardinfo->SD_cid.OEM_AppliID = tmp << 8;

  /*!< Byte 2 */
  tmp = (uint8_t)((CID_Tab[0] & 0x000000FF00) >> 8);
  cardinfo->SD_cid.OEM_AppliID |= tmp;

  /*!< Byte 3 */
  tmp = (uint8_t)(CID_Tab[0] & 0x000000FF);
  cardinfo->SD_cid.ProdName1 = tmp << 24;

  /*!< Byte 4 */
  tmp = (uint8_t)((CID_Tab[1] & 0xFF000000) >> 24);
  cardinfo->SD_cid.ProdName1 |= tmp << 16;

  /*!< Byte 5 */
  tmp = (uint8_t)((CID_Tab[1] & 0x00FF0000) >> 16);
  cardinfo->SD_cid.ProdName1 |= tmp << 8;

  /*!< Byte 6 */
  tmp = (uint8_t)((CID_Tab[1] & 0x0000FF00) >> 8);
  cardinfo->SD_cid.ProdName1 |= tmp;

  /*!< Byte 7 */
  tmp = (uint8_t)(CID_Tab[1] & 0x000000FF);
  cardinfo->SD_cid.ProdName2 = tmp;

  /*!< Byte 8 */
  tmp = (uint8_t)((CID_Tab[2] & 0xFF000000) >> 24);
  cardinfo->SD_cid.ProdRev = tmp;

  /*!< Byte 9 */
  tmp = (uint8_t)((CID_Tab[2] & 0x00FF0000) >> 16);
  cardinfo->SD_cid.ProdSN = tmp << 24;

  /*!< Byte 10 */
  tmp = (uint8_t)((CID_Tab[2] & 0x0000FF00) >> 8);
  cardinfo->SD_cid.ProdSN |= tmp << 16;

  /*!< Byte 11 */
  tmp = (uint8_t)(CID_Tab[2] & 0x000000FF);
  cardinfo->SD_cid.ProdSN |= tmp << 8;

  /*!< Byte 12 */
  tmp = (uint8_t)((CID_Tab[3] & 0xFF000000) >> 24);
  cardinfo->SD_cid.ProdSN |= tmp;

  /*!< Byte 13 */
  tmp = (uint8_t)((CID_Tab[3] & 0x00FF0000) >> 16);
  cardinfo->SD_cid.Reserved1 |= (tmp & 0xF0) >> 4;
  cardinfo->SD_cid.ManufactDate = (tmp & 0x0F) << 8;

  /*!< Byte 14 */
  tmp = (uint8_t)((CID_Tab[3] & 0x0000FF00) >> 8);
  cardinfo->SD_cid.ManufactDate |= tmp;

  /*!< Byte 15 */
  tmp = (uint8_t)(CID_Tab[3] & 0x000000FF);
  cardinfo->SD_cid.CID_CRC = (tmp & 0xFE) >> 1;
  cardinfo->SD_cid.Reserved2 = 1;
  
  return(errorstatus);
}

/**
  * @brief  Enables wide bus opeartion for the requeseted card if supported by 
  *         card.
  * @param  WideMode: Specifies the SD card wide bus mode. 
  *   This parameter can be one of the following values:
  *     @arg SDIO_BusWide_8b: 8-bit data transfer (Only for MMC)
  *     @arg SDIO_BusWide_4b: 4-bit data transfer
  *     @arg SDIO_BusWide_1b: 1-bit data transfer
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_GetCardStatus(SDIO_TypeDef *SDIOx,SD_CardStatus *cardstatus)
{
  SD_Error errorstatus = SD_OK;
  uint8_t tmp = 0;

  errorstatus = SD_SendSDStatus(SDIOx,(uint32_t *)SDSTATUS_Tab);

  if (errorstatus  != SD_OK)
  {
    return(errorstatus);
  }

  /*!< Byte 0 */
  tmp = (uint8_t)((SDSTATUS_Tab[0] & 0xC0) >> 6);
  cardstatus->DAT_BUS_WIDTH = tmp;

  /*!< Byte 0 */
  tmp = (uint8_t)((SDSTATUS_Tab[0] & 0x20) >> 5);
  cardstatus->SECURED_MODE = tmp;

  /*!< Byte 2 */
  tmp = (uint8_t)((SDSTATUS_Tab[2] & 0xFF));
  cardstatus->SD_CARD_TYPE = tmp << 8;

  /*!< Byte 3 */
  tmp = (uint8_t)((SDSTATUS_Tab[3] & 0xFF));
  cardstatus->SD_CARD_TYPE |= tmp;

  /*!< Byte 4 */
  tmp = (uint8_t)(SDSTATUS_Tab[4] & 0xFF);
  cardstatus->SIZE_OF_PROTECTED_AREA = tmp << 24;

  /*!< Byte 5 */
  tmp = (uint8_t)(SDSTATUS_Tab[5] & 0xFF);
  cardstatus->SIZE_OF_PROTECTED_AREA |= tmp << 16;

  /*!< Byte 6 */
  tmp = (uint8_t)(SDSTATUS_Tab[6] & 0xFF);
  cardstatus->SIZE_OF_PROTECTED_AREA |= tmp << 8;

  /*!< Byte 7 */
  tmp = (uint8_t)(SDSTATUS_Tab[7] & 0xFF);
  cardstatus->SIZE_OF_PROTECTED_AREA |= tmp;

  /*!< Byte 8 */
  tmp = (uint8_t)((SDSTATUS_Tab[8] & 0xFF));
  cardstatus->SPEED_CLASS = tmp;

  /*!< Byte 9 */
  tmp = (uint8_t)((SDSTATUS_Tab[9] & 0xFF));
  cardstatus->PERFORMANCE_MOVE = tmp;

  /*!< Byte 10 */
  tmp = (uint8_t)((SDSTATUS_Tab[10] & 0xF0) >> 4);
  cardstatus->AU_SIZE = tmp;

  /*!< Byte 11 */
  tmp = (uint8_t)(SDSTATUS_Tab[11] & 0xFF);
  cardstatus->ERASE_SIZE = tmp << 8;

  /*!< Byte 12 */
  tmp = (uint8_t)(SDSTATUS_Tab[12] & 0xFF);
  cardstatus->ERASE_SIZE |= tmp;

  /*!< Byte 13 */
  tmp = (uint8_t)((SDSTATUS_Tab[13] & 0xFC) >> 2);
  cardstatus->ERASE_TIMEOUT = tmp;

  /*!< Byte 13 */
  tmp = (uint8_t)((SDSTATUS_Tab[13] & 0x3));
  cardstatus->ERASE_OFFSET = tmp;
 
  return(errorstatus);
}

SD_Error SD_EnableWideBusOperation(SDIO_TypeDef *SDIOx,uint32_t WideMode)
{
  SD_Error errorstatus = SD_OK;

  /*!< MMC Card doesn't support this feature */
  if (SDIO_MULTIMEDIA_CARD == CardType)
  {
    errorstatus = SD_UNSUPPORTED_FEATURE;
    return(errorstatus);
  }
  else if ((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
  {														 
    if (SDIO_BusWide_8b == WideMode)   //2.0 sd
    {
      errorstatus = SD_UNSUPPORTED_FEATURE;
      return(errorstatus);
    }
    else if (SDIO_BusWide_4b == WideMode)
    {
      errorstatus = SDEnWideBus(SDIOx,ENABLE);
      if (SD_OK == errorstatus)
      {
        /*!< Configure the SDIO peripheral */
        SDIO_InitStructure.ClockSource = SDIO_CLK_RCH;
        SDIO_InitStructure.ClockDiv = 0;
        SDIO_InitStructure.BusWide = SDIO_BusWide_4b;
        SDIO_InitStructure.Mode = SDIO_MODE_SD;
        SDIO_Init(SDIO0,&SDIO_InitStructure);	
      }
    }
    else
    {
      errorstatus = SDEnWideBus(SDIOx,DISABLE);

      if (SD_OK == errorstatus)
      {
        /*!< Configure the SDIO peripheral */
        SDIO_InitStructure.ClockSource = SDIO_CLK_RCH;
        SDIO_InitStructure.ClockDiv = 0;
        SDIO_InitStructure.BusWide = SDIO_BusWide_1b;
        SDIO_InitStructure.Mode = SDIO_MODE_SD;
        SDIO_Init(SDIO0,&SDIO_InitStructure);		
      }
    }
  }

  return(errorstatus);
}


SD_Error SD_SelectDeselect(SDIO_TypeDef *SDIOx,uint32_t addr)
{
  SD_Error errorstatus = SD_OK;

  /*!< Send CMD7 SDIO_SEL_DESEL_CARD */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SEL_DESEL_CARD;
  SDIO_CmdInitStructure.Argument =  addr;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SEL_DESEL_CARD);

  return(errorstatus);
}


/**
  * @brief  Allows to read one block from a specified address in a card. The Data
  *         transfer can be managed by DMA mode or Polling mode. 
  * @note   This operation should be followed by two functions to check if the 
  *         DMA Controller and SD Card status.
  *          - SD_ReadWaitOperation(): this function insure that the DMA
  *            controller has finished all data transfer.
  *          - SD_GetStatus(): to check that the SD Card has finished the 
  *            data transfer and it is ready for data.            
  * @param  readbuff: pointer to the buffer that will contain the received data
  * @param  ReadAddr: Address from where data are to be read.  
  * @param  BlockSize: the SD card Data block size. The Block size should be 512.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_ReadBlock(SDIO_TypeDef *SDIOx,uint8_t *readbuff, uint32_t ReadAddr, uint16_t BlockSize)
{
  SD_Error errorstatus = SD_OK;
  volatile uint32_t tempreg;

  TransferError = SD_OK;
  TransferEnd = 0;	
  StopCondition = 0; 

  memset(readbuff,0,512);
  
  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)
  {
    BlockSize = 512;
    ReadAddr /= 512;
  }
    /*!< Set Block Size for Card cmd16*/
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SET_BLOCKLEN;
  SDIO_CmdInitStructure.Argument = (uint32_t) BlockSize;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SET_BLOCKLEN);

  if (SD_OK != errorstatus)
  {
    return(errorstatus);
  }
 /*********************************************************************************/

  /*!< Send CMD17 READ_SINGLE_BLOCK */
#if defined (SD_DMA_MODE) //SDMA

  SDIO_CmdInitStructure.CmdIndex = SD_CMD_READ_SINGLE_BLOCK;
  SDIO_CmdInitStructure.Argument = (uint32_t) ReadAddr;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_DATA;
  SDIO_CmdInitStructure.DataInit.BlockSize = BlockSize;

  SDIO_CmdInitStructure.DataInit.DMAMode = SDIO_SDMA;   // NODMA SDMA ADMA
  SDIO_CmdInitStructure.DataInit.SDMAAddr = (uint32_t)readbuff; 
  SDIO_CmdInitStructure.DataInit.SDMABufferBoundary = 0; 
  SDIO_CmdInitStructure.DataInit.BlockCount = 0;
  SDIO_CmdInitStructure.DataInit.BlockSize = BlockSize;
  SDIO_CmdInitStructure.DataInit.TransferDir = SDIO_DATA_Read;   //read or write
  SDIO_CmdInitStructure.DataInit.MultiSingleMode = SDIO_DATA_Single;  //Single-block or Multi-block

  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
#endif

  SDIO_ITConfig(SDIOx,SDIO_IT_TC, ENABLE); 
  if(SDIOx == SDIO0)
    NVIC_EnableIRQ(SDIO0_IRQn);
  if(SDIOx == SDIO1)
    NVIC_EnableIRQ(SDIO1_IRQn);

  return(errorstatus);
}

/**
  * @brief  This function waits until the SDIO DMA data transfer is finished. 
  *         This function should be called after SDIO_ReadMultiBlocks() function
  *         to insure that all data sent by the card are already transferred by 
  *         the DMA controller.        
  * @param  None.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_WaitReadOperation(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;

  while ((SD_DMAEndOfTransferStatus(SDIOx) == RESET) && (TransferEnd == 0) && (TransferError == SD_OK))
  {}

  if (TransferError != SD_OK)
  {
    return(TransferError);
  }

  return(errorstatus);
}

/**
  * @brief  Allows to write one block starting from a specified address in a card.
  *         The Data transfer can be managed by DMA mode or Polling mode.
  * @note   This operation should be followed by two functions to check if the 
  *         DMA Controller and SD Card status.
  *          - SD_ReadWaitOperation(): this function insure that the DMA
  *            controller has finished all data transfer.
  *          - SD_GetStatus(): to check that the SD Card has finished the 
  *            data transfer and it is ready for data.      
  * @param  writebuff: pointer to the buffer that contain the data to be transferred.
  * @param  WriteAddr: Address from where data are to be read.   
  * @param  BlockSize: the SD card Data block size. The Block size should be 512.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_WriteBlock(SDIO_TypeDef *SDIOx,uint8_t *writebuff, uint32_t WriteAddr, uint16_t BlockSize)
{
  SD_Error errorstatus = SD_OK;
  uint32_t cardstatus = 0,count;

  TransferError = SD_OK;
  TransferEnd = 0;
  StopCondition = 0;
  
  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)
  {
    BlockSize = 512;
    WriteAddr /= 512;
  }

    /*!< Set Block Size for Card cmd16 */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SET_BLOCKLEN;
  SDIO_CmdInitStructure.Argument = (uint32_t)BlockSize;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SET_BLOCKLEN);

  if (SD_OK != errorstatus)
  {
    return(errorstatus);
  }
 /*********************************************************************************/
  
  /*!< Send CMD13 WRITE_SINGLE_BLOCK */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SEND_STATUS;
  SDIO_CmdInitStructure.Argument = RCA << 16; 
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SEND_STATUS);
  if (SD_OK != errorstatus)
  {
    return(errorstatus);
  }
  else
  {
    count = SD_MAX_VOLT_TRIAL;
    cardstatus = SDIO_GetResponse(SDIOx,SDIO_RESP1);
    while(((cardstatus&0x00000100)==0)&&(count>0)) 	
    {
      count--;
      SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
      errorstatus = CmdResp1Error(SDIOx,SD_CMD_SEND_STATUS);
      if (SD_OK != errorstatus)
      {
        return(errorstatus);
      }
      cardstatus = SDIO_GetResponse(SDIOx,SDIO_RESP1);
      
    }
    SDIO_ClearITStatus(SDIOx,SDIO_STATIC_FLAGS);
  }	
  /*!< In case of single data block transfer no need of stop command at all */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_WRITE_SINGLE_BLOCK;
  SDIO_CmdInitStructure.Argument = WriteAddr;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;

  SDIO_CmdInitStructure.DataMode = SDIO_DATA;
  SDIO_CmdInitStructure.DataInit.DMAMode = SDIO_SDMA;
  SDIO_CmdInitStructure.DataInit.SDMAAddr = (uint32_t)writebuff;
  SDIO_CmdInitStructure.DataInit.SDMABufferBoundary = 0;
  SDIO_CmdInitStructure.DataInit.BlockCount = 1;
  SDIO_CmdInitStructure.DataInit.BlockSize = 0x200;  //BlockSize
  SDIO_CmdInitStructure.DataInit.TransferDir = SDIO_DATA_Write;   //read or write
  SDIO_CmdInitStructure.DataInit.MultiSingleMode = SDIO_DATA_Single;  //Single-block or Multi-block

  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);  

  SDIO_ITConfig(SDIOx,SDIO_IT_TC, ENABLE);
  if(SDIOx == SDIO0)
    NVIC_EnableIRQ(SDIO0_IRQn);
  if(SDIOx == SDIO1)
    NVIC_EnableIRQ(SDIO1_IRQn);
  while((SDIOx->STATUS3 & BIT0) != 0)
  {;}

#if defined (SD_POLLING_MODE)  
  
  while((SDIO0->STATUS3 & BIT0) != 1)
  {;}
  errorstatus = CmdResp1Error(SDIOx,SD_CMD_WRITE_SINGLE_BLOCK);

  if (errorstatus != SD_OK)
  {
    return(errorstatus);
  }
#endif

  return(errorstatus);
}

/**
  * @brief  Allows to read blocks from a specified address  in a card.  The Data
  *         transfer can be managed by DMA mode or Polling mode. //?????
  * @note   This operation should be followed by two functions to check if the 
  *         DMA Controller and SD Card status.	   //dma????????????
  *          - SD_ReadWaitOperation(): this function insure that the DMA
  *            controller has finished all data transfer. 
  *          - SD_GetStatus(): to check that the SD Card has finished the 
  *            data transfer and it is ready for data.   
  * @param  readbuff: pointer to the buffer that will contain the received data.
  * @param  ReadAddr: Address from where data are to be read.
  * @param  BlockSize: the SD card Data block size. The Block size should be 512.
  * @param  NumberOfBlocks: number of blocks to be read.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_ReadMultiBlocks(SDIO_TypeDef *SDIOx,uint8_t *readbuff, uint32_t ReadAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  SD_Error errorstatus = SD_OK;
  TransferError = SD_OK;
  TransferEnd = 0;
  StopCondition = 1;

  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)//sdhc卡的地址以块为单位，每块512字节
  {
    BlockSize = 512;
    ReadAddr /= 512;
  }

  /*!< Set Block Size for Card，cmd16,若是sdsc卡，可以用来设置块大小，若是sdhc卡，块大小为512字节，不受cmd16影响 */
  SDIO_CmdInitStructure.Argument = (uint32_t) BlockSize;
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SET_BLOCKLEN;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;   //r1
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);	
  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SET_BLOCKLEN);

  if (SD_OK != errorstatus)
  {
    return(errorstatus);
  }
    
#if defined (SD_DMA_MODE) //SDMA

  SDIO_CmdInitStructure.CmdIndex = SD_CMD_READ_MULT_BLOCK;
  SDIO_CmdInitStructure.Argument = (uint32_t) ReadAddr;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_DATA;

  SDIO_CmdInitStructure.DataInit.DMAMode = SDIO_SDMA;   // NODMA SDMA ADMA
  SDIO_CmdInitStructure.DataInit.SDMAAddr = (uint32_t)readbuff; 
  SDIO_CmdInitStructure.DataInit.SDMABufferBoundary = 0; 
  SDIO_CmdInitStructure.DataInit.BlockCount = NumberOfBlocks;
  SDIO_CmdInitStructure.DataInit.BlockSize = BlockSize;
  SDIO_CmdInitStructure.DataInit.TransferDir = SDIO_DATA_Write;   //read or write
  SDIO_CmdInitStructure.DataInit.MultiSingleMode = SDIO_DATA_Multi;  //Single-block or Multi-block

  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
#endif

  SDIO_ITConfig(SDIOx,SDIO_IT_TC, ENABLE); 
  if(SDIOx == SDIO0)
    NVIC_EnableIRQ(SDIO0_IRQn);
  if(SDIOx == SDIO1)
    NVIC_EnableIRQ(SDIO1_IRQn);

  return(errorstatus);
}

/**
  * @brief  Allows to write blocks starting from a specified address in a card.
  *         The Data transfer can be managed by DMA mode only. 
  * @note   This operation should be followed by two functions to check if the 
  *         DMA Controller and SD Card status.
  *          - SD_ReadWaitOperation(): this function insure that the DMA
  *            controller has finished all data transfer.
  *          - SD_GetStatus(): to check that the SD Card has finished the 
  *            data transfer and it is ready for data.     
  * @param  WriteAddr: Address from where data are to be read.
  * @param  writebuff: pointer to the buffer that contain the data to be transferred.
  * @param  BlockSize: the SD card Data block size. The Block size should be 512.
  * @param  NumberOfBlocks: number of blocks to be written.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_WriteMultiBlocks(SDIO_TypeDef *SDIOx,uint8_t *writebuff, uint32_t WriteAddr, uint16_t BlockSize, uint32_t NumberOfBlocks)
{
  SD_Error errorstatus = SD_OK;
  __IO uint32_t count = 0;

  TransferError = SD_OK;
  TransferEnd = 0;
  StopCondition = 1;

  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)
  {
    BlockSize = 512;
    WriteAddr /= 512;
  }

    /*!< Set Block Size for Card cmd16 */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SET_BLOCKLEN;
  SDIO_CmdInitStructure.Argument = (uint32_t)BlockSize;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SET_BLOCKLEN);

  if (SD_OK != errorstatus)
  {
    return(errorstatus);
  }	
 /*********************************************************************************/

//  /*!< To improve performance  */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_APP_CMD;
  SDIO_CmdInitStructure.Argument = (uint32_t) (RCA << 16);
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SET_BLOCKLEN);

  if (SD_OK != errorstatus)
  {
    return(errorstatus);
  }

  /*!< To improve performance */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SET_BLOCK_COUNT;
  SDIO_CmdInitStructure.Argument = NumberOfBlocks;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SET_BLOCKLEN);

  if (SD_OK != errorstatus)
  {
    return(errorstatus);
  }


  /*!< Send CMD25 WRITE_MULT_BLOCK with argument data address */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_WRITE_MULT_BLOCK;
  SDIO_CmdInitStructure.Argument = WriteAddr;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;

  SDIO_CmdInitStructure.DataMode = SDIO_DATA;
  SDIO_CmdInitStructure.DataInit.DMAMode = SDIO_SDMA;
  SDIO_CmdInitStructure.DataInit.SDMAAddr = (uint32_t)writebuff;
  SDIO_CmdInitStructure.DataInit.SDMABufferBoundary = 0;
  SDIO_CmdInitStructure.DataInit.BlockCount = NumberOfBlocks;
  SDIO_CmdInitStructure.DataInit.BlockSize = 0x200;  // NumberOfBlocks * BlockSize;
  SDIO_CmdInitStructure.DataInit.TransferDir = SDIO_DATA_Write;   //read or write
  SDIO_CmdInitStructure.DataInit.MultiSingleMode = SDIO_DATA_Multi;  //Single-block or Multi-block

  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);  

  SDIO_ITConfig(SDIOx,SDIO_IT_TC|SDIO_IT_DMA, ENABLE);
  if(SDIOx == SDIO0)
    NVIC_EnableIRQ(SDIO0_IRQn);
  if(SDIOx == SDIO1)
    NVIC_EnableIRQ(SDIO1_IRQn);
  while((SDIOx->STATUS3 & BIT0) != 0)
  {;}
  return(errorstatus);
}

/**
  * @brief  This function waits until the SDIO DMA data transfer is finished. 
  *         This function should be called after SDIO_WriteBlock() and
  *         SDIO_WriteMultiBlocks() function to insure that all data sent by the 
  *         card are already transferred by the DMA controller.        
  * @param  None.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_WaitWriteOperation(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;

  while ((SD_DMAEndOfTransferStatus(SDIOx) == RESET) && (TransferEnd == 0) && (TransferError == SD_OK))
  {}

  if (TransferError != SD_OK)
  {
    return(TransferError);
  }

  /*!< Clear all the static flags */
  SDIO_ClearITStatus(SDIOx,SDIO_STATIC_FLAGS);

  return(errorstatus);
}

/**
  * @brief  Allows to erase memory area specified for the given card.
  * @param  sdiostartaddr: the start address.
  * @param  sdioendaddr: the end address.
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_Erase(SDIO_TypeDef *SDIOx,uint32_t sdiostartaddr, uint32_t sdioendaddr)
{
  SD_Error errorstatus = SD_OK;
  uint32_t delay = 0;
  __IO uint32_t maxdelay = 0;
  uint8_t cardstate = 0;

  /*!< Check if the card coomnd class supports erase command */
  if (((CSD_Tab[1] >> 20) & SD_CCCC_ERASE) == 0)
  {
    errorstatus = SD_REQUEST_NOT_APPLICABLE;
    return(errorstatus);
  }

  maxdelay = 5000;
  if (SDIO_GetResponse(SDIOx,SDIO_RESP1) & SD_CARD_LOCKED)
  {
    errorstatus = SD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  if (CardType == SDIO_HIGH_CAPACITY_SD_CARD)
  {
    sdiostartaddr /= 512;	  
    sdioendaddr /= 512;
  }
  
  /*!< According to sd-card spec 1.0 ERASE_GROUP_START (CMD32) and erase_group_end(CMD33) */
  if ((SDIO_STD_CAPACITY_SD_CARD_V1_1 == CardType) || (SDIO_STD_CAPACITY_SD_CARD_V2_0 == CardType) || (SDIO_HIGH_CAPACITY_SD_CARD == CardType))
  {
    /*!< Send CMD32 SD_ERASE_GRP_START with argument as addr  */
    SDIO_CmdInitStructure.CmdIndex = SD_CMD_SD_ERASE_GRP_START;
    SDIO_CmdInitStructure.Argument = sdiostartaddr;
    SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
    SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
    SDIO_CmdInitStructure.Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.DataMode = SDIO_CMD;
    SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
    
    errorstatus = CmdResp1Error(SDIOx,SD_CMD_SD_ERASE_GRP_START);
    if (errorstatus != SD_OK)
    {
      return(errorstatus);
    }

    /*!< Send CMD33 SD_ERASE_GRP_END with argument as addr  */
    SDIO_CmdInitStructure.CmdIndex = SD_CMD_SD_ERASE_GRP_END;
    SDIO_CmdInitStructure.Argument = sdioendaddr;
    SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
    SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
    SDIO_CmdInitStructure.Response = SDIO_Response_Short;
    SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
    
    errorstatus = CmdResp1Error(SDIOx,SD_CMD_SD_ERASE_GRP_END);
    if (errorstatus != SD_OK)
    {
      return(errorstatus);
    }
  }

  /*!< Send CMD38 ERASE */
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_ERASE;
  SDIO_CmdInitStructure.Argument = 0;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_ERASE);

  if (errorstatus != SD_OK)
  {
    return(errorstatus);
  }

  for (delay = 0; delay < maxdelay; delay++)
  {}

  /*!< Wait till the card is in programming state */
  errorstatus = IsCardProgramming(SDIOx,&cardstate);

  while ((errorstatus == SD_OK) && ((SD_CARD_PROGRAMMING == cardstate) || (SD_CARD_RECEIVING == cardstate)))
  {
    errorstatus = IsCardProgramming(SDIOx,&cardstate);
  }

  return(errorstatus);
}

/**
  * @brief  Returns the current card's status.
  * @param  pcardstatus: pointer to the buffer that will contain the SD card 
  *         status (Card Status register).
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_SendStatus(SDIO_TypeDef *SDIOx,uint32_t *pcardstatus)
{
  SD_Error errorstatus = SD_OK;

  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SEND_STATUS;
  SDIO_CmdInitStructure.Argument = (uint32_t) RCA << 16;
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_CmdInitStructure.DataMode = SDIO_CMD;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
  
  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SD_ERASE_GRP_END);
  if (errorstatus != SD_OK)
  {
    return(errorstatus);
  }

  *pcardstatus = SDIOx->RESP1;
  return(errorstatus);
}

/**
  * @brief  Returns the current SD card's status.
  * @param  psdstatus: pointer to the buffer that will contain the SD card status 
  *         (SD Status register).
  * @retval SD_Error: SD Card Error code.
  */
SD_Error SD_SendSDStatus(SDIO_TypeDef *SDIOx,uint32_t *psdstatus)
{
  SD_Error errorstatus = SD_OK;
  uint32_t count = 0;

  if (SDIO_GetResponse(SDIOx,SDIO_RESP1) & SD_CARD_LOCKED)
  {
    errorstatus = SD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  /*!< Set block size for card if it is not equal to current block size for card. */
  SDIO_CmdInitStructure.Argument = 64;
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SET_BLOCKLEN;  //CMD16
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;  ///r1
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);		

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_SET_BLOCKLEN);

  if (errorstatus != SD_OK)
  {
    return(errorstatus);
  }

  /*!< CMD55 */
  SDIO_CmdInitStructure.Argument = (uint32_t) RCA << 16;
  SDIO_CmdInitStructure.CmdIndex = SD_CMD_APP_CMD;  //CMD55
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;  //r1
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);		

  errorstatus = CmdResp1Error(SDIOx,SD_CMD_APP_CMD);

  if (errorstatus != SD_OK)
  {
    return(errorstatus);
  }
  if (errorstatus != SD_OK)
  {
    return(errorstatus);
  }

  return(errorstatus);
}

SD_Error SD_ProcessIRQSrc(SDIO_TypeDef *SDIOx)
{
  if (StopCondition == 1)
  {
    SDIO_CmdInitStructure.Argument = 0x00;   
    SDIO_CmdInitStructure.CmdIndex = SD_CMD_STOP_TRANSMISSION;  
    SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
    SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_CMD12;
    SDIO_CmdInitStructure.Response = SDIO_Response_Short;  //r1
    SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);		
    
    TransferError = CmdResp1Error(SDIOx,SD_CMD_STOP_TRANSMISSION);
  }
  else
  {
    TransferError = SD_OK;
  }
  SDIO_ClearITStatus(SDIOx,SDIO_STATIC_FLAGS);
  SDIO_ITConfig(SDIOx,SDIO_FLAG_TRANComplete, DISABLE);
  TransferEnd = 1;
  return(TransferError);
}

static SD_Error CmdError(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;
  uint32_t timeout;

  timeout = SDIO_CMD0TIMEOUT; /*!< 10000 */

  while ((timeout > 0) && (SDIO_GetFlagStatus(SDIOx,SDIO_FLAG_CMDSENT) == RESET))	
  {
    timeout--;
  }

  if (timeout == 0)
  {
    errorstatus = SD_CMD_RSP_TIMEOUT;
    return(errorstatus);
  }

  /*!< Clear all the static flags */
  SDIO_ClearITStatus(SDIOx,SDIO_STATIC_FLAGS);

  return(errorstatus);
}

static SD_Error CmdResp7Error(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;
  uint32_t status;
  uint32_t timeout = SDIO_CMD0TIMEOUT;

  status = SDIOx->STATUS3;
  /* Command response received (CRC check failed) Command response received (CRC check passed) Command response timeout */

  while (!(status & (SDIO_FLAG_CMDCRCERR | SDIO_FLAG_CMDSENT | SDIO_FLAG_CMDTIMEOUT)) && (timeout > 0))
  {
    timeout--;
    status = SDIOx->STATUS3;		  
  }
  //cmd8
  if ((timeout == 0) || (status & SDIO_FLAG_CMDTIMEOUT))
  {
    /*!< Card is not V2.0 complient or card does not support the set voltage range */
    errorstatus = SD_CMD_RSP_TIMEOUT;
    SDIO_ClearITStatus(SDIOx,SDIO_FLAG_CMDTIMEOUT);
    return(errorstatus);
  }

  if (status & SDIO_FLAG_CMDSENT)
  {
    /*!< Card is SD V2.0 compliant */
    errorstatus = SD_OK;
    SDIO_ClearITStatus(SDIOx,SDIO_FLAG_CMDSENT);
    return(errorstatus);
  }
  return(errorstatus);
}

static SD_Error CmdResp1Error(SDIO_TypeDef *SDIOx,uint8_t cmd) 
{  
  while (!(SDIOx->STATUS3 & (SDIO_FLAG_CMDCRCERR | SDIO_FLAG_CMDSENT | SDIO_FLAG_CMDTIMEOUT)))
  {
  }

  SDIO_ClearITStatus(SDIOx,SDIO_STATIC_FLAGS);

  return (SD_Error)(SDIOx->RESP1 &  SD_OCR_ERRORBITS);
}

static SD_Error CmdResp3Error(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;
  uint32_t status;

  status = SDIOx->STATUS3;	

  while (!(status & (SDIO_FLAG_CMDCRCERR | SDIO_FLAG_CMDSENT | SDIO_FLAG_CMDTIMEOUT)))
  {
    status =  SDIOx->STATUS3;
  }

  if (status & SDIO_FLAG_CMDTIMEOUT)
  {
    errorstatus = SD_CMD_RSP_TIMEOUT;
    SDIO_ClearITStatus(SDIOx,SDIO_FLAG_CMDTIMEOUT);
    return(errorstatus);
  }
  /*!< Clear all the static flags */
  SDIO_ClearITStatus(SDIOx,SDIO_STATIC_FLAGS);
  return(errorstatus);
}

static SD_Error CmdResp2Error(SDIO_TypeDef *SDIOx)
{
  SD_Error errorstatus = SD_OK;
  uint32_t status;

  status = SDIOx->STATUS3;	

  while (!(status & (SDIO_FLAG_CMDCRCERR | SDIO_FLAG_CMDSENT | SDIO_FLAG_CMDTIMEOUT)))
  {
    status = SDIOx->STATUS3;
  }

  if (status & SDIO_FLAG_CMDTIMEOUT)
  {
    errorstatus = SD_CMD_RSP_TIMEOUT;
    SDIO_ClearITStatus(SDIOx,SDIO_FLAG_CMDTIMEOUT);
    return(errorstatus);
  }
  else if (status & SDIO_FLAG_CMDCRCERR)
  {
    errorstatus = SD_CMD_CRC_FAIL;
    SDIO_ClearITStatus(SDIOx,SDIO_FLAG_CMDCRCERR);
    return(errorstatus);
  }

  /*!< Clear all the static flags */
  SDIO_ClearITStatus(SDIOx,SDIO_STATIC_FLAGS);

  return(errorstatus);
}

static SD_Error CmdResp6Error(SDIO_TypeDef *SDIOx,uint8_t cmd, uint16_t *prca)
{
  SD_Error errorstatus = SD_OK;
  uint32_t status;
  uint32_t response_r1;

  status = SDIOx->STATUS3;	
  while (!(status & (SDIO_FLAG_CMDCRCERR | SDIO_FLAG_CMDSENT | SDIO_FLAG_CMDTIMEOUT)))
  {
    status = SDIOx->STATUS3;
  }
  if (status & SDIO_FLAG_CMDTIMEOUT)
  {
    errorstatus = SD_CMD_RSP_TIMEOUT;
    SDIO_ClearITStatus(SDIOx,SDIO_FLAG_CMDTIMEOUT);
    return(errorstatus);
  }
  else if (status & SDIO_FLAG_CMDCRCERR)
  {
    errorstatus = SD_CMD_CRC_FAIL;
    SDIO_ClearITStatus(SDIOx,SDIO_FLAG_CMDCRCERR);
    return(errorstatus);
  }

  /*!< Check response received is of desired command */
  if (SDIO_GetCommandResponse(SDIOx) != 0)
  {
    errorstatus = SD_ILLEGAL_CMD;
    return(errorstatus);
  }

  /*!< Clear all the static flags */
  SDIO_ClearITStatus(SDIOx,SDIO_STATIC_FLAGS);

  /*!< We have received response, retrieve it.  */
  response_r1 = SDIO_GetResponse(SDIOx,SDIO_RESP1);

  if (SD_ALLZERO == (response_r1 & (SD_R6_GENERAL_UNKNOWN_ERROR | SD_R6_ILLEGAL_CMD | SD_R6_COM_CRC_FAILED)))
  {
    *prca = (uint16_t) (response_r1 >> 16);
    return(errorstatus);
  }

  if (response_r1 & SD_R6_GENERAL_UNKNOWN_ERROR)
  {
    return(SD_GENERAL_UNKNOWN_ERROR);
  }

  if (response_r1 & SD_R6_ILLEGAL_CMD)
  {
    return(SD_ILLEGAL_CMD);
  }

  if (response_r1 & SD_R6_COM_CRC_FAILED)
  {
    return(SD_COM_CRC_FAILED);
  }

  return(errorstatus);
}	   

static SD_Error SDEnWideBus(SDIO_TypeDef *SDIOx,FunctionalState NewState)
{
  SD_Error errorstatus = SD_OK;

  uint32_t scr[2] = {0, 0};

  if (SDIO_GetResponse(SDIOx,SDIO_RESP1) & SD_CARD_LOCKED) 
  {
    errorstatus = SD_LOCK_UNLOCK_FAILED;
    return(errorstatus);
  }

  /*!< If wide bus operation to be enabled */
  if (NewState == ENABLE)
  {
    /*!< If requested card supports wide bus operation */
//     if ((scr[1] & SD_WIDE_BUS_SUPPORT) != SD_ALLZERO)  
    {
      /*!< Send CMD55 APP_CMD with argument as card's RCA.*/
      SDIO_CmdInitStructure.CmdIndex = SD_CMD_APP_CMD;
      SDIO_CmdInitStructure.Argument = (uint32_t) RCA << 16;
      SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
      SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
      SDIO_CmdInitStructure.Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.DataMode = SDIO_CMD;
      SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

      errorstatus = CmdResp1Error(SDIOx,SD_CMD_APP_CMD);

      if (errorstatus != SD_OK)
      {
        return(errorstatus);
      }

      /*!< Send ACMD6 APP_CMD with argument as 2 for wide bus mode */
      SDIO_CmdInitStructure.CmdIndex = SD_CMD_APP_SD_SET_BUSWIDTH;
      SDIO_CmdInitStructure.Argument = 0x2;
      SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
      SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
      SDIO_CmdInitStructure.Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.DataMode = SDIO_CMD;
      SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

      errorstatus = CmdResp1Error(SDIOx,SD_CMD_APP_SD_SET_BUSWIDTH);

      if (errorstatus != SD_OK)
      {
        return(errorstatus);
      }
      return(errorstatus);
    }
  }   /*!< If wide bus operation to be disabled */
  else
  {
    /*!< If requested card supports 1 bit mode operation */
    if ((scr[1] & SD_SINGLE_BUS_SUPPORT) != SD_ALLZERO)
    {
      /*!< Send CMD55 APP_CMD with argument as card's RCA.*/
      SDIO_CmdInitStructure.CmdIndex = SD_CMD_APP_CMD;
      SDIO_CmdInitStructure.Argument = (uint32_t) RCA << 16;
      SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
      SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
      SDIO_CmdInitStructure.Response = SDIO_Response_Short;
      SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

      errorstatus = CmdResp1Error(SDIOx,SD_CMD_APP_CMD);

      if (errorstatus != SD_OK)
      {
        return(errorstatus);
      }

      /*!< Send ACMD6 APP_CMD with argument as 0 for single bus mode */
      SDIO_CmdInitStructure.CmdIndex =  SD_CMD_APP_SD_SET_BUSWIDTH;
      SDIO_CmdInitStructure.Argument =  0x00;
      SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
      SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
      SDIO_CmdInitStructure.Response = SDIO_Response_Short;
      SDIO_CmdInitStructure.DataMode = SDIO_CMD;
      SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);
      
      errorstatus = CmdResp1Error(SDIOx,SD_CMD_APP_SD_SET_BUSWIDTH);

      if (errorstatus != SD_OK)
      {
        return(errorstatus);
      }

      return(errorstatus);
    }
    else
    {
      errorstatus = SD_REQUEST_NOT_APPLICABLE;
      return(errorstatus);
    }
  }
}

static SD_Error IsCardProgramming(SDIO_TypeDef *SDIOx, uint8_t *pstatus)
{
  SD_Error errorstatus = SD_OK;
  __IO uint32_t respR1 = 0, status = 0;

  SDIO_CmdInitStructure.CmdIndex = SD_CMD_SEND_STATUS;
  SDIO_CmdInitStructure.Argument = (uint32_t) RCA << 16; 
  SDIO_CmdInitStructure.CmdType = CMDTYPE_Normal;
  SDIO_CmdInitStructure.CmdAuto = SDIO_CMDAUTO_No;
  SDIO_CmdInitStructure.Response = SDIO_Response_Short;
  SDIO_SendCommand(SDIOx,&SDIO_CmdInitStructure);

  return(errorstatus);
}

/*****************************END OF FILE*****************************/

