/**
  ******************************************************************************
  * @file    MDR1986VK01_ebc.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   This file contains all the functions prototypes for the EBC
  *          firmware library.
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
  * FILE MDR1986VK01_ebc.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VK01_EBC_H
#define __MDR1986VK01_EBC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"	
#include "MDR1986VK01_config.h"

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup  EBC EBC
  * @{
  */

/** @defgroup EBC_Exported_Types EBC Exported Types
  * @{
  */

/**
  * @brief  EBC Init structure definition
  */

typedef struct 
{
    FunctionalState RGN_ECCEN;
        
    uint32_t RGN_ECCMODE;
    
    uint32_t RGN_RDYWAIT;
    
    uint32_t RGN_MODE;
    
    uint32_t RGN_ROM;
    
    uint32_t RGN_CPOL;
    
    uint32_t RGN_WS_ACTIVE;
    
    uint32_t RGN_WS_SETUP;
    
    uint32_t RGN_WS_HOLD;
    
    uint32_t RGN_ECC8BIT;
    
    FunctionalState RGN_ENOCLK;
    
    uint32_t RGN_DIVOCLK;
}EBC_RGN_InitTypeDef;

#define RGN0                    0
#define RGN1			        1
#define RGN2			        2
#define RGN3			        3
#define RGN4			        4
#define RGN5			        5
#define RGN6			        6
#define RGN7			        7

#define EBC_RGNx_EN             ((uint32_t)0x00000001)

#define EBC_ECCMODE_PAR 		(uint32_t)(0x00);
#define EBC_ECCMODE_CON 		(uint32_t)(0x01);

#define EBC_RDYWAIT_NOWAIT 		(uint32_t)(0x00);
#define EBC_RDYWAIT_WAIT 		(uint32_t)(0x01);

#define EBC_MODE_32X_8ECC 		(uint32_t)(0x00);
#define EBC_MODE_16X 			(uint32_t)(0x01);
#define EBC_MODE_8X 			(uint32_t)(0x02);
#define EBC_MODE_32X_16ECC 		(uint32_t)(0x03);

#define EBC_ROM_RAM 			(uint32_t)(0x00);
#define EBC_ROM_ROM 			(uint32_t)(0x01);

#define EBC_CPOL_UP 			(uint32_t)(0x00);
#define EBC_CPOL_DOWN 			(uint32_t)(0x01);

#define EBC_ECC_16BIT 		    (uint32_t)(0x00);
#define EBC_ECC_8BIT 	        (uint32_t)(0x01);


/** @} */ /* End of group EBC_Exported_Types */



/** @defgroup EBC_Exported_Macros EBC Exported Macros
  * @{
  */

/** @} */ /* End of group EBC_Exported_Macros */

/** @defgroup EBC_Exported_Functions EBC Exported Functions
  * @{
  */
	
void EBC_RGNx_Init(uint32_t RGNx, const EBC_RGN_InitTypeDef* EBC_RGN_InitStruct);	
void EBC_RGNx_StructInit(EBC_RGN_InitTypeDef* EBC_RGN_InitStruct);
void EBC_RGNx_Cmd(uint32_t RGNx, FunctionalState NewState);

/** @} */ /* End of group EBC_Exported_Functions */

/** @} */ /* End of group EBC */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MDR1986VK01_EBC_H */

/******************* (C) COPYRIGHT 2022 Milandr *********************************
*
* END OF FILE MDR1986VK01_ebc.h */


