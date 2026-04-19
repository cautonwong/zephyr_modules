/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/

#include "diskio.h"
#include "sdio_sdcard.h"
#include "SDIO.h"
#include "target.h"

#define BLOCK_SIZE            512 /* Block Size in Bytes */

extern SDTransferState SD_GetStatus(SDIO_TypeDef *SDIOx);
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	SD_Error  Status;
/*-------------------------- SD Init ----------------------------- */
	if (drv == Drv_SDIO0 )
    Status = SD_Init(SDIO0);
	if (drv == Drv_SDIO1 )
    Status = SD_Init(SDIO1);
	if (Status!=SD_OK )
	{
		return STA_NOINIT;
	}
	else
	{
		return RES_OK;
	}

}



/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..255) */
)
{
	uint8_t i;
	
	if (drv == Drv_SDIO0 )
	{
		if (count > 1)
		{
//			   SD_ReadMultiBlocks(SDIO0,buff, sector*BLOCK_SIZE, BLOCK_SIZE, count);
//		
//					/* Check if the Transfer is finished */
//				 SD_WaitReadOperation(SDIO0); 
//		
//				/* Wait until end of DMA transfer */
//				while(SD_GetStatus(SDIO0) != SD_TRANSFER_OK);
			for(i = 0;i < count;i++)
			{
				SD_ReadBlock(SDIO0,buff+i*BLOCK_SIZE, sector*BLOCK_SIZE+i*BLOCK_SIZE, BLOCK_SIZE);

					/* Check if the Transfer is finished */
				 SD_WaitReadOperation(SDIO0); 
		
				/* Wait until end of DMA transfer */
				while(SD_GetStatus(SDIO0) != SD_TRANSFER_OK);
			}

		}
		else
		{
			
				SD_ReadBlock(SDIO0,buff, sector*BLOCK_SIZE, BLOCK_SIZE);

					/* Check if the Transfer is finished */
				 SD_WaitReadOperation(SDIO0); 
		
				/* Wait until end of DMA transfer */
				while(SD_GetStatus(SDIO0) != SD_TRANSFER_OK);

		}
  }
	if (drv == Drv_SDIO1 )
	{
		if (count > 1)
		{
//			SD_ReadMultiBlocks(SDIO1,buff, sector*BLOCK_SIZE, BLOCK_SIZE, count);
//		
//					/* Check if the Transfer is finished */
//				 SD_WaitReadOperation(SDIO1);  
//		
//				/* Wait until end of DMA transfer */
//				while(SD_GetStatus(SDIO1) != SD_TRANSFER_OK);
			for(i = 0;i < count;i++)
			{
				SD_ReadBlock(SDIO1,buff+i*BLOCK_SIZE, sector*BLOCK_SIZE+i*BLOCK_SIZE, BLOCK_SIZE);

					/* Check if the Transfer is finished */
				 SD_WaitReadOperation(SDIO1); 
		
				/* Wait until end of DMA transfer */
				while(SD_GetStatus(SDIO1) != SD_TRANSFER_OK);
			}
		}
		else
		{
			
				SD_ReadBlock(SDIO1,buff, sector*BLOCK_SIZE, BLOCK_SIZE);

					/* Check if the Transfer is finished */
				 SD_WaitReadOperation(SDIO1);  
		
				/* Wait until end of DMA transfer */
				while(SD_GetStatus(SDIO1) != SD_TRANSFER_OK);

		}
  }
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..255) */
)
{
	uint8_t i;
	
  if(drv == Drv_SDIO0)
	{
		if (count > 1)
		{
//			SD_WriteMultiBlocks(SDIO0,(uint8_t *)buff, sector*BLOCK_SIZE, BLOCK_SIZE, count);
//			
//				/* Check if the Transfer is finished */
//				 SD_WaitWriteOperation(SDIO0);	   
//				while(SD_GetStatus(SDIO0) != SD_TRANSFER_OK);
			for(i = 0;i < count;i++)
			{
			SD_WriteBlock(SDIO0,(uint8_t *)buff+i*BLOCK_SIZE,sector*BLOCK_SIZE+i*BLOCK_SIZE, BLOCK_SIZE);
			
				/* Check if the Transfer is finished */
					SD_WaitWriteOperation(SDIO0);
				while(SD_GetStatus(SDIO0) != SD_TRANSFER_OK); 
			}
		}
		else
		{
			SD_WriteBlock(SDIO0,(uint8_t *)buff,sector*BLOCK_SIZE, BLOCK_SIZE);
			
				/* Check if the Transfer is finished */
					SD_WaitWriteOperation(SDIO0);
				while(SD_GetStatus(SDIO0) != SD_TRANSFER_OK); 
		}
  }
  if(drv == Drv_SDIO1)
	{
		if (count > 1)
		{
//			SD_WriteMultiBlocks(SDIO1,(uint8_t *)buff, sector*BLOCK_SIZE, BLOCK_SIZE, count);
//			
//				/* Check if the Transfer is finished */
//				 SD_WaitWriteOperation(SDIO1);
//				while(SD_GetStatus(SDIO1) != SD_TRANSFER_OK);
			for(i = 0;i < count;i++)
			{
			SD_WriteBlock(SDIO1,(uint8_t *)buff+i*BLOCK_SIZE,sector*BLOCK_SIZE+i*BLOCK_SIZE, BLOCK_SIZE);
			
				/* Check if the Transfer is finished */
					SD_WaitWriteOperation(SDIO1);
				while(SD_GetStatus(SDIO1) != SD_TRANSFER_OK); 
			}
		}
		else
		{
			SD_WriteBlock(SDIO1,(uint8_t *)buff,sector*BLOCK_SIZE, BLOCK_SIZE);
			
				/* Check if the Transfer is finished */
					SD_WaitWriteOperation(SDIO1);
				while(SD_GetStatus(SDIO1) != SD_TRANSFER_OK);
		}
  }
	return RES_OK;
}
#endif /* _READONLY */




/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	return RES_OK;
}
							 
/*-----------------------------------------------------------------------*/
/* Get current time                                                      */
/*-----------------------------------------------------------------------*/ 
DWORD get_fattime(void)
{

 	return 0;

} 
