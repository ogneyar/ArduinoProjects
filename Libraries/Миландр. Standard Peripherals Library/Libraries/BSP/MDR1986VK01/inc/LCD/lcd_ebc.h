/**
  ******************************************************************************
  * @file    lcd_ebc.h
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    17/03/2022
  * @brief   LCD header file for demo board.
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
  * FILE lcd_ebc.h
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_ebc.h"
#include "MDR1986VK01_port.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSB_LCD_EBC BSB LCD EBC
  * @{
  */

/** @defgroup BSB_LCD_EBC_Exported_Types BSP LCD EBC Exported Types
  * @{
  */

#define LCD_RES_0           MDR_PORTB->CRXTX = 1<<10
#define LCD_RES_1           MDR_PORTB->SRXTX = 1<<10

/* LCD crystal ports */
typedef struct
{
    uint32_t Data;
    uint32_t Cmd;
}LCD_Ports;

#define LCD_DATA(x)         (*((volatile uint32_t*)CrystalPorts[x].Data))
#define LCD_CMD(x)          (*((volatile uint32_t*)CrystalPorts[x].Cmd))

/* LCD crystal numbers */
typedef enum
{
    LCD_CRYSTAL1    = 0,
    LCD_CRYSTAL2    = 1,
    NUM_LCD_CRYSTALS
}LCD_Crystal;

/* Bit and byte output methods */
typedef enum
{
    MET_OR          = 0,
    MET_XOR         = 1,
    MET_NOT_OR      = 2,
    MET_NOT_XOR     = 3,
    MET_AND         = 4,
    NUM_LCD_METHOD
}LCD_Method;

/* LCD status flags */
#define LCD_BUSY_Pos        7
#define LCD_BUSY_Msk        (uint32_t)(1 << LCD_BUSY_Pos)

#define LCD_ONOFF_Pos       5
#define LCD_ONOFF_Msk       (uint32_t)(1 << LCD_ONOFF_Pos)

#define LCD_RESET_Pos       4
#define LCD_RESET_Msk       (uint32_t)(1 << LCD_RESET_Pos)

/* LCD Data Port */
#define LCD_DATA_PORT       MDR_PORTC

#define LCD_DATA_BUS_8      (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | \
                             PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7)


/* LCD screen resolution (in pixels) */
#define MAX_X               127
#define MAX_Y               63

/* Specific LCD control commands */
#define LCD_ON              vLcdWriteCmd(0x3F)
#define LCD_OFF             vLcdWriteCmd(0x3E)
#define LCD_START_LINE(x)   vLcdWriteCmd(0xC0 | x)
#define LCD_SET_PAGE(x)     vLcdWriteCmd(0xB8 | x)
#define LCD_SET_ADDRESS(x)  vLcdWriteCmd(0x40 | x)

extern const LCD_Ports CrystalPorts[NUM_LCD_CRYSTALS];

/** @} */ /* End of group BSB_LCD_EBC_Exported_Types */

/** @defgroup BSB_LCD_EBC_Exported_Functions BSP LCD EBC Exported Functions
  * @{
  */

/* Display context */
extern LCD_Crystal CurrentCrystal;  /*!< Currently selected crystal */
extern LCD_Method CurrentMethod;    /*!< Current display method    */

void vLcdReset( void );
void vLcdSetCrystal( LCD_Crystal num );
void vLcdWriteCmd( uint32_t val );
void vLcdWriteData( uint32_t val );
uint32_t ulLcdReadCmd( void );
uint32_t ulLcdReadData( void );
void vLcdInit(void);
void vLcdClear(void);

/** @} */ /* End of group BSB_LCD_EBC_Exported_Functions */

/** @} */ /* End of group BSB_LCD_EBC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __LCD_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE lcd_ebc.h */
