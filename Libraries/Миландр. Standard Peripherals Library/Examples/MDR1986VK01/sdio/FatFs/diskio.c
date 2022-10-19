/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "sdio_sd.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = RES_OK;

	if (SD_Detect() != SD_PRESENT)
		stat |= STA_NODISK;
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
    
 	/* Supports only single drive */
	if (pdrv)
	{
		return STA_NOINIT;
	}
	/*-------------------------- SD Init ----------------------------- */
	stat = SD_Init();
	if (stat==SD_OK )
	{
		return RES_OK;
	}

    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
    DRESULT res  = RES_OK;

    SDTransferState state;
    SD_Error volatile errorstatus;

    if ( SD_Detect( ) != SD_PRESENT)
        return RES_NOTRDY;

    if ( count == 0)
        return RES_PARERR;

    if((DWORD)buff & 0x3) // Array is not aligned, read with CPU
    {
        errorstatus = SD_ReadMultiBlocks ( buff, sector*512ULL, 512, count );
        if (errorstatus != SD_OK)
            return RES_ERROR;
    }
    else                  // Array is aligned, read with DMA
    {
        errorstatus = SD_ReadMultiBlocks_DMA ( buff, sector*512ULL, 512, count );
        if (errorstatus != SD_OK)
            return RES_ERROR;
        
        errorstatus = SD_WaitReadOperation ( );
        if (errorstatus != SD_OK)
            return RES_ERROR;
    }

    while ( 1 )
    {
        state = SD_GetStatus ( );
        if ( state == SD_TRANSFER_OK )
            break;
    }
    
    return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
    SDTransferState state;

    volatile SD_Error errorstatus;

    if ( SD_Detect() != SD_PRESENT )
        return RES_NOTRDY;

    if ( count == 0)
        return RES_PARERR;

    if((DWORD)buff & 0x3) // Array is not aligned, write with CPU
    {
        errorstatus = SD_WriteMultiBlocks ( (uint8_t *)buff, sector*512ULL, 512, count );
        if (errorstatus != SD_OK)
            return RES_ERROR;
    }
    else                  // Array is aligned, write with DMA
    {
        errorstatus = SD_WriteMultiBlocks_DMA ( (uint8_t *)buff, sector*512ULL, 512, count );
        if (errorstatus != SD_OK)
            return RES_ERROR;
    
        errorstatus = SD_WaitWriteOperation ( );
        if (errorstatus != SD_OK)
            return RES_ERROR;
    }

    while ( 1 )
    {
        state = SD_GetStatus ( );
        if ( state == SD_TRANSFER_OK )
            break;
    }

    return RES_OK;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
    DRESULT res = RES_ERROR;
    SD_CardInfo CardInfo;

    switch (cmd)
    {
        /* Make sure that no pending write process */
        case CTRL_SYNC :
        res = RES_OK;
        break;

    /* Get number of sectors on the disk (DWORD) */
    case GET_SECTOR_COUNT :
        SD_GetCardInfo(&CardInfo);
        *(DWORD*)buff = CardInfo.CardCapacity / 512UL;
        res = RES_OK;
        break;

    /* Get R/W sector size (WORD) */
    case GET_SECTOR_SIZE :
        SD_GetCardInfo(&CardInfo);
        *(WORD*)buff = CardInfo.CardBlockSize;
        res = RES_OK;
        break;

    /* Get erase block size in unit of sector (DWORD) */
    case GET_BLOCK_SIZE :
        SD_GetCardInfo(&CardInfo);
        *(DWORD*)buff = CardInfo.CardBlockSize;
        res = RES_OK;
        break;

    default:
        res = RES_PARERR;
    }

    return res;
}


