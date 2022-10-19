/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V1.3.0
 * @date    07/04/2022
 * @brief   Main program body.
 ******************************************************************************
 * <br><br>
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"
#include "adc.h"            // For ANABG macros
#include "sdio.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup sdio sdio
 *  @{
 */

#define CPU_CLK        160E6 // 160 МГц

PORT_InitTypeDef PortSDIO;
FATFS       FatFs __attribute__ ((aligned(1024)));        // File system object for each logical drive
FATFS       *fs;
DWORD       free_clust;
uint32_t    size_total, size_free;
FIL         LogFile;

char        buffer_wr[100], buffer_rd[100];
FRESULT     res;
UINT        bw, br;

void vError(FRESULT error);
void ClockInit(void);

int main()
{
    ClockInit();
    
    MDR_CLK->SDIO_CLK =  (uint32_t)CLK_SOURCE_MAX_CLK << 28 | CLK_ENABLE | 1; // SDIO_CLK = MAX_CLK/(1+1)
    SDIO_PORT->KEY = 0x8555AAA1;
    
    PORT_StructInit(&PortSDIO);
    PortSDIO.PORT_SOE     = PORT_SOE_OUT;
    PortSDIO.PORT_SFUNC   = PORT_SFUNC_1;
    PortSDIO.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    PortSDIO.PORT_SPWR    = PORT_SPWR_10;
    PortSDIO.PORT_Pin     = SDIO_DAT0_PIN | SDIO_DAT1_PIN | SDIO_DAT2_PIN |
                            SDIO_DAT3_PIN | SDIO_CMD_PIN  | SDIO_CLK_PIN;
    PORT_Init(SDIO_PORT, &PortSDIO);
    
    NVIC_EnableIRQ((IRQn_Type)51);  // DMA0
    NVIC_EnableIRQ((IRQn_Type)52);  // DMA1
    NVIC_EnableIRQ((IRQn_Type)216); // SDIO

    /* Mount the default drive */
    if((res = f_mount(&FatFs, "", 0)) != FR_OK)
        vError(res);
    
    /* Get volume information and free clusters of default drive */
    if((res = f_getfree("", &free_clust, &fs)) != FR_OK)
        vError(res);
    
    size_total = (fs->n_fatent - 2) * (fs->csize / 2);
    size_free = free_clust * (fs->csize / 2);
    
    /* Create file on default drive */
    if((res = f_open(&LogFile, "SDCard.txt", FA_CREATE_ALWAYS | FA_WRITE)) != FR_OK)
        vError(res);
    
    /* Write data to the text file */
    sprintf(buffer_wr, "TEST LOG FILE\r\n\nTotal size = %d byte \r\nFree size = %d byte", size_total, size_free);
    res = f_write(&LogFile, buffer_wr, strlen(buffer_wr), &bw);
    
    if((bw == 0) || (res != FR_OK))
        vError(res);
    
    /* Close the open file */
    f_close(&LogFile);
    
    /* Open the text file with read access */
    if((res = f_open(&LogFile, "SDCard.txt", FA_READ)) != FR_OK)
        vError(res);
    
    /* Read data from the text file */
    res = f_read(&LogFile, buffer_rd, sizeof(buffer_rd), &br);

    if((br == 0) || (res != FR_OK))
        vError(res);
    
    /* Close the open file */
    f_close(&LogFile);

    /* Unmount the default drive */
    f_mount(NULL, "", 0);
    while(1){}
}

void vError(FRESULT error)
{
    __IO FRESULT error_type = error;
    while(1);
}

void ClockInit(void)
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;
    
    MDR_COMP0->ANABG_CTRL = ANABG_IREFEN | ANABG_BGEN | 
                            ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );

    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        while(1){}

    CLK_SetPllClk( &MDR_CLK->PLL[0], PLL_CLK_HSE0, CPU_CLK );
    CLK_PllState( &MDR_CLK->PLL[0], ENABLE );
    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[0] ) )
        while(1){}
    
    // Setting Flash Access Time
    MDR_FLASH->KEY = 0x8555AAA1;
    MDR_FLASH->CNTR = ((32 / (1E9/CPU_CLK)) + 1); // WAITCYCLE = (Trd_flash / Tcpu_clk) + 1
    MDR_FLASH->KEY  = 0x00000000;

    CLK_SetSystemClock( MAX_CLK_PLL0 );

    SystemCoreClockUpdate();
}

/** @} */ /* End of group sdio */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


