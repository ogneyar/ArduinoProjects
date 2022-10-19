/**
  ******************************************************************************
  * @file    lcd.h
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    22/11/2020
  * @brief   This file contains all the functions prototypes for the LCD driver.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  */

#ifndef __LCD_H_
#define __LCD_H_

/* Includes ------------------------------------------------------------------*/
#include <MLDR187.h>
#include <MLDR187_gpio.h>
#include <MLDR187_rst_clk.h>

/* LCD Exported Types --------------------------------------------------------*/
/* LCD crystal numbers */
typedef enum
{
    LCD_CRYSTAL1    = 0,
    LCD_CRYSTAL2    = 1,
    LCD_BOTH        = 2,
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

/* LCD Exported defines ------------------------------------------------------*/
/* number of LCD crystal*/
#define NUM_LCD_CRYSTALS        2

/* LCD status flags */
#define LCD_BUSY_Pos      7
#define LCD_BUSY_Msk      (uint32_t)(1 << LCD_BUSY_Pos)

#define LCD_ONOFF_Pos     5
#define LCD_ONOFF_Msk     (uint32_t)(1 << LCD_ONOFF_Pos)

#define LCD_RESET_Pos     4
#define LCD_RESET_Msk     (uint32_t)(1 << LCD_RESET_Pos)

#define LCD_DATA_PORT_Pos       6

/* LCD Data Port */
#define LCD_DATA_PORT      MDR_PORTB
#define LCD_DATA_BUS_8     (PORT_Pin_6 | PORT_Pin_7 | PORT_Pin_8| PORT_Pin_9 | \
                            PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12 | PORT_Pin_13)

/* LCD crystals control */
#define LCD_CRYSTAL_PINs        (PORT_Pin_4 | PORT_Pin_5)
#define LCD_CRYSTAL_POS         4
#define LCD_CRYSTAL_PORT        MDR_PORTB

/* LCD command/data switching */
#define LCD_CMD_DATA_PIN        (PORT_Pin_2)
#define LCD_CMD_DATA_PORT       MDR_PORTB

/* LCD read/write switching */
#define LCD_RD_WR_PIN           (PORT_Pin_14)
#define LCD_RD_WR_PORT          MDR_PORTB

/* LCD CLOCK signal control */
#define LCD_CLOCK_PIN           (PORT_Pin_3)
#define LCD_CLOCK_PORT          MDR_PORTB

/* LCD RESET signal control */
#define LCD_RESET_PIN           (PORT_Pin_4)
#define LCD_RESET_PORT          MDR_PORTA

/* LCD screen resolution (in pixels) */
#define MAX_X       127
#define MAX_Y       63

/* LCD Exported Macros -------------------------------------------------------*/
/* Specific LCD control commands */
#define LCD_ON                      WriteLCD_Cmd(0x3F)
#define LCD_OFF                     WriteLCD_Cmd(0x3E)
#define LCD_START_LINE(x)           WriteLCD_Cmd(0xC0 | x)
#define LCD_SET_PAGE(x)             WriteLCD_Cmd(0xB8 | x)
#define LCD_SET_ADDRESS(x)          WriteLCD_Cmd(0x40 | x)


/* LCD Exported variables ----------------------------------------------------*/
extern LCD_Crystal CurrentCrystal;  /* Currently selected crystal */
extern LCD_Method LCD_CurrentMethod;    /* Current display method    */

/* LCD Exported functions ----------------------------------------------------*/
void ResetLCD(void);
void SetCrystal(LCD_Crystal num);
void WriteLCD_Cmd(uint8_t val);
void WriteLCD_Data(uint8_t val);
uint8_t ReadLCD_Cmd(void);
uint8_t ReadLCD_Data(void);
void LCD_INIT(void);
void LCD_CLS(void);
void LCD_PUT_PICT(uint8_t x, uint8_t y, uint8_t SizeX, uint8_t SizeY, const uint8_t* pict);
void LCD_PUTS(uint8_t x, uint8_t y, const uint8_t* str);


#endif /* __LCD_H_ */

