/**
  ******************************************************************************
  * @file    text.h
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    22/11/2020
  * @brief   This file contains all the functions prototypes for the symbol
  *          and text output to LCD.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEXT_H
#define __TEXT_H

/* Includes ------------------------------------------------------------------*/
#include "font_defs.h"

/* LCD Text Exported defines -------------------------------------------------*/
#define DefaultFontWidth                 6
#define DefaultFontHeight                8

/* LCD lines */
#define Interline               2
#define LineMessage1            DefaultFontHeight + 4
#define LineMessage2            LineMessage1 + DefaultFontHeight + Interline
#define LineMessage3            LineMessage2 + DefaultFontHeight + Interline
#define LineMessage4            LineMessage3 + DefaultFontHeight + Interline
#define LineMessage5            LineMessage4 + DefaultFontHeight + Interline

/* LCD Text Exported Types ---------------------------------------------------*/
/* Styles */
typedef enum
{
    StyleSimple,
    StyleBlink,
    StyleFlipFlop,
    StyleVibratory
}TextStyle;


/* LCD Text Exported Macros --------------------------------------------------*/
/* Macro for calculation of an address of symbol description structure in the
 * symbol description table. Gets symbol code and font description address,
 * returns symbol description address. */
#define Get_Char_Data_Addr(ch)    \
  (CurrentFont)->pData + (ch) * (CurrentFont)->Width * ((((CurrentFont)->Height % 8) != 0) ? (1 + (CurrentFont)->Height / 8) : ((CurrentFont)->Height / 8))

/* LCD Text Exported variables -----------------------------------------------*/
extern sFONT *CurrentFont;      /* Selected font (used for symbol output) */

/* LCD Text Exported functions -----------------------------------------------*/
void LCD_PUT_PICT(uint8_t x, uint8_t y, uint8_t SizeX, uint8_t SizeY, const uint8_t* pict); /* Pictere to screen output */
void LCD_PUT_BYTE(uint8_t x, uint8_t y, uint8_t data); /* Byte to screen output */
void LCD_PUTC(uint8_t x, uint8_t y, uint8_t ch); /* Output symbols to screen using current font */
void LCD_PUTS(uint8_t x, uint8_t y, const uint8_t* str);

#endif /*__TEXT_H*/


