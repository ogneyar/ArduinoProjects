/**
  ******************************************************************************
  * @file    text.c
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    22/11/2020
  * @brief   This file provides all the functions for the symbol  and text
  *          output to LCD.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "lcd.h"
#include "text.h"

/* Private variables ---------------------------------------------------------*/

sFONT *CurrentFont = &Font_ASCII_6x8;   /* The selected font for text output */

/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
* Function Name  : LCD_PUT_PICT
* Description    : Prints the picture to the given screen coordinates.
* Input          : �  - x-coordinate
*                : y  - y-coordinate
*                : SizeX: - Number of Row  
*                : SizeY: - Number of Line
*                : pict - pointer to pict
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PUT_PICT(uint8_t x, uint8_t y, uint8_t SizeX, uint8_t SizeY, const uint8_t* pict)
{
    uint32_t i, j, line;
    
    line = SizeY / 8;
    if (CurrentFont->Height % 8)
    {
        line++;
    }
    
    for (j = 0; j < line; j++)
    {
        for( i = 0; i < SizeX; i++)
        {
            LCD_PUT_BYTE(x + i, y + j*8, pict[i + SizeX*j]);
        }
    }
    
}

/*******************************************************************************
* Function Name  : LCD_PUT_BYTE
* Description    : Outputs one byte to the given screen coordinates.
* Input          : �    - x-coordinate
*                : y    - y-coordinate
*                : data - byte to output
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PUT_BYTE(uint8_t x, uint8_t y, uint8_t data)
{
    uint32_t tmp_data, page, shift_num, shift_num_ex;
    
    if ((x>MAX_X)|(y>MAX_Y))
    {
        return;
    }
    
    /* Select crystal and x offset */
    SetCrystal((LCD_Crystal)(x/64));
    x %= 64;
    /* Determine first page and y offset */
    page = y/8;
    shift_num = y%8;
    shift_num_ex = 8 - shift_num;
    
    /* First page */
    
    /* Read current value */
    LCD_SET_PAGE(page);
    LCD_SET_ADDRESS(x);
    tmp_data = ReadLCD_Data();
    /* Write modified value */
    LCD_SET_PAGE(page);
    LCD_SET_ADDRESS(x);
    switch (LCD_CurrentMethod)
    {
    case MET_OR:
        WriteLCD_Data(tmp_data | (data << shift_num));
        break;
    case MET_XOR:
        WriteLCD_Data(tmp_data ^ (data << shift_num));
        break;
    case MET_NOT_OR:
        WriteLCD_Data(tmp_data | ((data ^ 0xFF) << shift_num));
        break;
    case MET_NOT_XOR:
        WriteLCD_Data(tmp_data ^ ((data ^ 0xFF) << shift_num));
        break;
    case MET_AND:
        WriteLCD_Data((tmp_data & (0xFF >> shift_num_ex)) | (data << shift_num));
        break;
    }
    
    /* Second page (if any) */
    if (shift_num > 0)
    {
        /* Read current value */
        LCD_SET_PAGE(page+1);
        LCD_SET_ADDRESS(x);
        tmp_data = ReadLCD_Data();
        /* Write modified value */
        LCD_SET_PAGE(page+1);
        LCD_SET_ADDRESS(x);
        switch (LCD_CurrentMethod)
        {
        case MET_OR:
            WriteLCD_Data(tmp_data | (data >> shift_num_ex));
            break;
        case MET_XOR:
            WriteLCD_Data(tmp_data ^ (data >> shift_num_ex));
            break;
        case MET_NOT_OR:
            WriteLCD_Data(tmp_data | ((data ^ 0xFF) >> shift_num_ex));
            break;
        case MET_NOT_XOR:
            WriteLCD_Data(tmp_data ^ ((data ^ 0xFF)>> shift_num_ex));
            break;
        case MET_AND:
            WriteLCD_Data((tmp_data & (0xFF << shift_num)) | (data >> shift_num_ex));
            break;
        }
    }
}

/*----------------- Printing of symbols and strings using current font -----------------*/

/*******************************************************************************
* Function Name  : LCD_PUTC
* Description    : Prints one symbol to the given screen coordinates.
* Input          : �  - x-coordinate
*                : y  - y-coordinate
*                : ch - symbol to print
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PUTC(uint8_t x, uint8_t y, uint8_t ch)
{
    uint32_t i, j, line;
    const uint8_t *sym;
    
    sym = Get_Char_Data_Addr(ch);
    line = CurrentFont->Height / 8;
    if (CurrentFont->Height % 8)
    {
        line++;
    }
    
    for (j = 0; j < line; j++)
    {
        for( i = 0; i < CurrentFont->Width; i++)
        {
            LCD_PUT_BYTE(x + i, y + j*8, sym[i + CurrentFont->Width*j]);
        }
    }
}

/*******************************************************************************
* Function Name  : LCD_PUTS
* Description    : Prints the string to the given screen coordinates.
* Input          : �  - x-coordinate
*                : y  - y-coordinate
*                : str - pointer to string
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PUTS(uint8_t x, uint8_t y, const uint8_t* str)
{
    uint32_t i;
    
    for (i=0; str[i]; i++)
    {
        LCD_PUTC(x + i*CurrentFont->Width, y, str[i]);
    }
}

