/**
  * @file    sdio.c
  * @author  Application Team
  * @version V1.0.0
  * @date    2020-09-27
  * @brief   Main program body.
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "SDIO.h"
#include "lib_sdio.h"
#include "sdio_sdcard.h"
#include "board.h"

/* Private functions ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/** 
  * @brief  SDIO Static flags, TimeOut, FIFO Address  
  */
#define NULL 0
#define SDIO_STATIC_FLAGS               ((uint32_t)0x000005FF)
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
#define TEST_LENGTH (512*2)

UINT br, bw;            // File R/W count
FATFS fs_sd0,fs_sd1;
FIL fnew;
char DISKPath[4];   /* SRAMDISK logical drive path */

extern __IO uint32_t nTick;
void SDIODelay_ms(uint32_t n)
{
  uint32_t Ticks_start;
  
  Ticks_start = nTick;
  while ((nTick - Ticks_start) < n);
}

void SD_WriteDisk(void)
{
  FRESULT res;
  uint32_t fsize,i;	
  uint8_t ReadBuff[TEST_LENGTH],WriteBuff[TEST_LENGTH],err = 0;

  for(i = 0;i < 512*2;i++)
  {
    if((i%10) == 0)
      WriteBuff[i] = '\n';
    else
      WriteBuff[i] = i%10 + '0';
  }

  SYSCFG0_Periph0ClockCmd(SYSCFG0_Periph0Clock_SDIO1,ENABLE);

  if(SD_Init(SDIO1) == SD_OK)
  {
    printf("InitSD success\r\n");
    res = f_mount(Drv_SDIO1, &fs_sd1);
    f_chdrive (Drv_SDIO1);   //Mount SD card
    res = f_open(&fnew, "txt1.txt", FA_WRITE|FA_READ|FA_OPEN_ALWAYS);		
    if ( res == FR_OK )
    {
      fsize = f_lseek(&fnew,f_size(&fnew));
      fsize = f_write(&fnew, WriteBuff, TEST_LENGTH, &bw);
      fsize = f_lseek(&fnew,f_size(&fnew)-TEST_LENGTH);
      fsize = f_read(&fnew, ReadBuff, TEST_LENGTH, &bw);
      f_close(&fnew);  
    }
    if ( res == FR_OK )
    {
      for(i = 0;i < 512;i++)
      {
        if(ReadBuff[i] != WriteBuff[i])
        {
          printf("Failed\r\n");
          err = 1;
        }
      }
      if(err == 0)
      {
        printf("Success\r\n");
      }
    }
  }
  else
  {
    printf("InitSD failed\r\n");
  }
}

/*********************************** END OF FILE ******************************/
