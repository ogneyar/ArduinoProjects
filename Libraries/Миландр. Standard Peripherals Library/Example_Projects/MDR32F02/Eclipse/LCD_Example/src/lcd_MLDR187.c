/**
  ******************************************************************************
  * @file    lcd_MDR32F9Qx.c
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    22/11/2020
  * @brief   This file provides all the LCD driver functions for MLDR187
  *          evaluation boards.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* Private macro -------------------------------------------------------------*/
#define WAIT_BUSY           WhileStatus(LCD_BUSY_Msk)
#define WAIT_RESET          WhileStatus(LCD_RESET_Msk)
#define WAIT_ON             WhileStatus(LCD_ONOFF_Msk)

/* Private variables ---------------------------------------------------------*/
LCD_Crystal CurrentCrystal = LCD_CRYSTAL1;  /* Currently selected crystal */
LCD_Method LCD_CurrentMethod;               /* Current display method    */


/* Private function prototypes -----------------------------------------------*/
static uint32_t GetStatus(void);
static void WhileStatus(uint32_t status);
static void Pause(void);

/* Functions -----------------------------------------------------------------*/
/*******************************************************************************
* Function Name  : LCDClock
* Description    : Gating data.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCDClock(void)
{
    Pause();
    PORT_SetReset(LCD_CLOCK_PORT, LCD_CLOCK_PIN, SET);
    Pause();
    PORT_SetReset(LCD_CLOCK_PORT, LCD_CLOCK_PIN, RESET);
}

/*******************************************************************************
* Function Name  : ResetLCD
* Description    : Resets the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ResetLCD(void)
{
    PORT_SetReset(LCD_RESET_PORT, LCD_RESET_PIN, RESET);
    Pause();
    PORT_SetReset(LCD_RESET_PORT, LCD_RESET_PIN, SET);
}

/*******************************************************************************
* Function Name  : SetCrystal
* Description    : Sets the current LCD crystal.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SetCrystal(LCD_Crystal num)
{
    PORT_SetReset(LCD_CRYSTAL_PORT, LCD_CRYSTAL_PINs, RESET);
    PORT_SetReset(LCD_CRYSTAL_PORT, ((num + 1) << LCD_CRYSTAL_POS), SET);
    LCDClock();
    CurrentCrystal = num;
}

/*******************************************************************************
* Function Name  : WriteLCD_Cmd
* Description    : Writes command to the current LCD crystal.
* Input          : LCD command
* Output         : None
* Return         : None
*******************************************************************************/
void WriteLCD_Cmd(uint8_t val)
{
    uint16_t portdata;
    
    /* Switch LCD to the command mode */
    PORT_SetReset(LCD_CMD_DATA_PORT, LCD_CMD_DATA_PIN, RESET);
    /* Switch LCD to the data input mode */
    PORT_SetReset(LCD_RD_WR_PORT, LCD_RD_WR_PIN, RESET);
    
    /* Switch LCD_DATA_PORT to the data output mode */
    LCD_DATA_PORT->OE |= LCD_DATA_BUS_8;
    
    portdata = PORT_Read(LCD_DATA_PORT) & (~LCD_DATA_BUS_8);
    portdata |= val << LCD_DATA_PORT_Pos;
    PORT_Write(LCD_DATA_PORT, portdata);
    
    LCDClock();
    
    /* Switch LCD_DATA_PORT to the data input mode */
    LCD_DATA_PORT->OE &= ~LCD_DATA_BUS_8;
    
    /* Switch LCD to the data output mode */
    PORT_SetReset(LCD_RD_WR_PORT, LCD_RD_WR_PIN, SET);
}

/*******************************************************************************
* Function Name  : WriteLCD_Data
* Description    : Writes data to the current LCD crystal.
* Input          : Data
* Output         : None
* Return         : None
*******************************************************************************/
void WriteLCD_Data(uint8_t val)
{
    uint16_t portdata;
    
    /* Switch LCD to the data mode */
    PORT_SetReset(LCD_CMD_DATA_PORT, LCD_CMD_DATA_PIN, SET);
    /* Switch LCD to the data input mode */
    PORT_SetReset(LCD_RD_WR_PORT, LCD_RD_WR_PIN, RESET);
    
    /* Switch LCD_DATA_PORT to the data output mode */
    LCD_DATA_PORT->OE |= LCD_DATA_BUS_8;
    
    portdata = PORT_Read(LCD_DATA_PORT) & (~LCD_DATA_BUS_8);
    portdata |= val << LCD_DATA_PORT_Pos;
    PORT_Write(LCD_DATA_PORT, portdata);
    
    LCDClock();
    
    /* Switch LCD_DATA_PORT to the data input mode */
    LCD_DATA_PORT->OE &= ~LCD_DATA_BUS_8;
    
    /* Switch LCD to the data output mode */
    PORT_SetReset(LCD_RD_WR_PORT, LCD_RD_WR_PIN, SET);
}

/*******************************************************************************
* Function Name  : ReadLCD_Cmd
* Description    : Reads command from the current LCD crystal.
* Input          : None
* Output         : None
* Return         : LCD command
*******************************************************************************/
uint8_t ReadLCD_Cmd(void)
{
    uint32_t ret;
    
    /* Switch LCD to the command mode */
    PORT_SetReset(LCD_CMD_DATA_PORT, LCD_CMD_DATA_PIN, RESET);
    Pause();
    PORT_SetReset(LCD_CLOCK_PORT, LCD_CLOCK_PIN, SET);
    Pause();
    Pause();
    ret = (PORT_Read(LCD_DATA_PORT) & LCD_DATA_BUS_8) >> LCD_DATA_PORT_Pos;
    PORT_SetReset(LCD_CLOCK_PORT, LCD_CLOCK_PIN, RESET);
    
    return ret;
}

/*******************************************************************************
* Function Name  : ReadLCD_Data
* Description    : Reads data from the current LCD crystal.
* Input          : None
* Output         : None
* Return         : LCD data
*******************************************************************************/
uint8_t ReadLCD_Data()
{
    uint32_t ret;
    
    /* Switch LCD to the data mode */
    PORT_SetReset(LCD_CMD_DATA_PORT, LCD_CMD_DATA_PIN, SET);
    Pause();
    LCDClock();              /* Dummy reading is necessary to get correct data */
    Pause();
    PORT_SetReset(LCD_CLOCK_PORT, LCD_CLOCK_PIN, SET);
    Pause();
    Pause();
    ret = (PORT_Read(LCD_DATA_PORT) & LCD_DATA_BUS_8) >> LCD_DATA_PORT_Pos;
    PORT_SetReset(LCD_CLOCK_PORT, LCD_CLOCK_PIN, RESET);
    
    return ret;
}

/*******************************************************************************
* Function Name  : LCD_INIT
* Description    : Initializes all LCD crystals.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_INIT(void)
{
    static PORT_InitTypeDef        PORT_InitStructure;
    uint32_t crystal;
    
    RST_CLK_EnablePeripheralClock(RST_CLK_PORTA, RST_CLK_Div1);
    RST_CLK_EnablePeripheralClock(RST_CLK_PORTB, RST_CLK_Div1);
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_FAST_2mA;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(LCD_RESET_PORT, LCD_RESET_PIN, &PORT_InitStructure);
    PORT_SetReset(LCD_RESET_PORT, LCD_RESET_PIN, RESET);  
    
    PORT_Init(LCD_DATA_PORT, (LCD_DATA_BUS_8 | LCD_CRYSTAL_PINs | LCD_CMD_DATA_PIN | \
        LCD_RD_WR_PIN | LCD_CLOCK_PIN), &PORT_InitStructure);
    
    ResetLCD();
    Pause();
/*
    SetCrystal(LCD_BOTH);
    LCD_ON;
    LCD_START_LINE(0);
    LCD_SET_PAGE(0);
    LCD_SET_ADDRESS(0);
*/
    for (crystal = LCD_CRYSTAL1; crystal < NUM_LCD_CRYSTALS; crystal++)
    {
		SetCrystal((LCD_Crystal)crystal);
		WAIT_BUSY;
		LCD_ON;
		WAIT_ON;
		LCD_START_LINE(0);
    }
}

/*******************************************************************************
* Function Name  : LCD_CLS
* Description    : Clears LCD screen.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CLS(void)
{
    uint32_t i, j, crystal;
    
    for (crystal = LCD_CRYSTAL1; crystal < NUM_LCD_CRYSTALS; crystal++)
    {
        SetCrystal((LCD_Crystal)crystal);
        WAIT_BUSY;
        //    LCD_OFF;
        LCD_SET_ADDRESS(0);
        for (i = 0; i < 8; i++)
        {
            LCD_SET_PAGE(i);
            for (j = 0; j < 64; j++)
            {
                WriteLCD_Data(0x00);
            }
        }
        //    LCD_ON;
    }
}

/*******************************************************************************
* Function Name  : LCD_PutPixel
* Description    : Outputs one pixel to the given screen coordinates.
* Input          : x - x-coordinate
*                : y - y-coordinate
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PutPixel(uint32_t x, uint32_t y)
{
    uint32_t shifted, page;
    uint32_t data;
    
    if ((x>MAX_X)|(y>MAX_Y))
    {
        return;
    }
    
    SetCrystal((LCD_Crystal)(x/64));
    x %= 64;
    
    page = y/8;
    shifted = (1 << (y%8));
    LCD_SET_PAGE(page);
    LCD_SET_ADDRESS(x);
    data = ReadLCD_Data();
    switch (LCD_CurrentMethod)
    {
		case MET_OR :   data |= shifted;    break;
		case MET_XOR :  data ^= shifted;    break;
		case MET_AND :  data &= ~shifted;  	break;
    }
    LCD_SET_ADDRESS(x);
    WriteLCD_Data(data);
}

/*******************************************************************************
* Function Name  : GetStatus
* Description    : Returns the current LCD status.
* Input          : None
* Output         : None
* Return         : LCD status
*******************************************************************************/
static uint32_t GetStatus(void)
{
    uint32_t ret;
    
    ret = ReadLCD_Cmd();
    return ret;
}

/*******************************************************************************
* Function Name  : WhileStatus
* Description    : Wait until the specific LCD status changes.
* Input          : LCD status. This parameter can be one of the following
*                : values: LCD_BUSY, LCD_ONOFF, LCD_RESET.
* Output         : None
* Return         : None
*******************************************************************************/
static void WhileStatus(uint32_t status)
{
    
    uint32_t stat;
    for (stat = GetStatus(); (stat & status) != 0; stat = GetStatus())
    {
    }
}

/*******************************************************************************
* Function Name  : Pause
* Description    : Delay for approx. 15*3 CPU clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void Pause(void)
{
    volatile uint32_t i;
    
    for (i = 15; i > 0; i--);
}

