/**
  ******************************************************************************
  * @file    sdio.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   SDIO header file for demo board.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  ******************************************************************************
  * FILE sdio.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SDIO_H
#define __SDIO_H

/* Includes ------------------------------------------------------------------*/
#include "ff.h"
#include "diskio.h"   /* Declarations of low level disk I/O functions */
#include "sdio_sd.h"
#include "MDR1986VK01_sdio.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_SDIO BSP_SDIO
  * @{
  */

/** @defgroup BSP_SDIO_Private_Defines SDIO Private Defines
  * @{
  */

#define SDIO_PORT                    MDR_PORTB

#define SDIO_DAT2_PIN                PORT_Pin_15
#define SDIO_DAT3_PIN                PORT_Pin_27
#define SDIO_CMD_PIN                 PORT_Pin_12
#define SDIO_CLK_PIN                 PORT_Pin_11
#define SDIO_DAT0_PIN                PORT_Pin_24
#define SDIO_DAT1_PIN                PORT_Pin_25

/** @} */ /* End of group BSP_SDIO_Private_Defines */

/** @defgroup BSP_SDIO_Exported_Types BSP_SDIO Exported Types
  * @{
  */

static uint8_t rc_str[20][22] =
{
    {"OK"},
    {"DISK_ERR"},
    {"INT_ERR"},
    {"NOT_READY"},
    {"NO_FILE"},
    {"NO_PATH"},
    {"INVALID_NAME"},
    {"DENIED"},
    {"EXIST"},
    {"INVALID_OBJECT"},
    {"WRITE_PROTECTED"},
    {"INVALID_DRIVE"},
    {"NOT_ENABLED"},
    {"NO_FILE_SYSTEM"},
    {"MKFS_ABORTED"},
    {"TIMEOUT"},
    {"LOCKED"},
    {"NOT_ENOUGH_CORE"},
    {"TOO_MANY_OPEN_FILES"}
};

static uint8_t ft[5][6] =
{
    {"none "},
    {"FAT12"},
    {"FAT16"},
    {"FAT32"},
    {"exFAT"}
};

/** @} */ /* End of group BSP_SDIO_Exported_Types */

/** @defgroup BSP_SDIO_Exported_Functions BSP_SDIO Exported Functions
  * @{
  */

//static void Int_2_Str(uint32_t var_Int, uint8_t* var_Str)
//{
//  uint8_t i;
//  var_Str[0] = ( var_Int / 1000000000);\
//    var_Int = var_Int - var_Str[0] * 1000000000;
//  var_Str[1] = ( var_Int / 100000000);
//    var_Int = var_Int - var_Str[1] * 100000000;
//  var_Str[2] = ( var_Int / 10000000);
//    var_Int = var_Int - var_Str[2] * 10000000;
//  var_Str[3] = ( var_Int / 1000000);
//    var_Int = var_Int - var_Str[3] * 1000000;
//  var_Str[4] = ( var_Int / 100000);
//    var_Int = var_Int - var_Str[4] * 100000;
//  var_Str[5] = ( var_Int / 10000);
//    var_Int = var_Int - var_Str[5] * 10000;
//  var_Str[6] = ( var_Int / 1000);
//    var_Int = var_Int - var_Str[6] * 1000;
//  var_Str[7] = ( var_Int / 100);
//    var_Int = var_Int - var_Str[7] * 100;
//  var_Str[8] = ( var_Int / 10);
//    var_Int = var_Int - var_Str[8] * 10;
//  var_Str[9] = ( var_Int % 10);
//
//    for (i=0; i<10; i++)
//        var_Str[i] = var_Str[i]  + 0x30;
//}

/** @} */ /* End of group BSP_SDIO_Exported_Functions */

/** @} */ /* End of group BSP_SDIO */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __SDIO_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE sdio.h */


