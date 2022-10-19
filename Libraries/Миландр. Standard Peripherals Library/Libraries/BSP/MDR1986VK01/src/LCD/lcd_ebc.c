/**
  ******************************************************************************
  * @file    lcd_ebc.c
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    17/03/2022
  * @brief   LCD source file for demo board.
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
  * FILE lcd_ebc.c
  */


/* Includes ------------------------------------------------------------------*/
#include "lcd_ebc.h"

#define EXTBUS_BASE         0x10000000
#define LCD_CRYSTAL1_OFFS   0x100
#define LCD_CRYSTAL2_OFFS   0x200

#define LCD_DATA_OFFS       0x2000

#define LCD_CRYSTAL1_CMD    EXTBUS_BASE + LCD_CRYSTAL1_OFFS
#define LCD_CRYSTAL2_CMD    EXTBUS_BASE + LCD_CRYSTAL2_OFFS
#define LCD_CRYSTAL1_DATA   EXTBUS_BASE + LCD_CRYSTAL1_OFFS + LCD_DATA_OFFS
#define LCD_CRYSTAL2_DATA   EXTBUS_BASE + LCD_CRYSTAL2_OFFS + LCD_DATA_OFFS

#define WAIT_BUSY           vLcdWhileStatus(LCD_BUSY_Msk)
#define WAIT_RESET          vLcdWhileStatus(LCD_RESET_Msk)
#define WAIT_ON             vLcdWhileStatus(LCD_ONOFF_Msk)

/* LCD ports */
const LCD_Ports CrystalPorts[NUM_LCD_CRYSTALS] =
{
  /* Crystal #1 */
  { LCD_CRYSTAL1_DATA,
    LCD_CRYSTAL1_CMD },
  /* Crystal #2 */
  { LCD_CRYSTAL2_DATA,
    LCD_CRYSTAL2_CMD }
};

/* Display context */
LCD_Crystal CurrentCrystal = LCD_CRYSTAL1;  /*!< Currently selected crystal */


/* Private function prototypes -----------------------------------------------*/
static uint32_t ulLcdGetStatus(void);
static void vLcdWhileStatus(uint32_t status);
static void vLcdPause(void);
static void vLcdInitPins( void );

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : vLcdReset
* Description    : Resets the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void vLcdReset(void)
{
  LCD_RES_1;
  LCD_RES_0;
  vLcdPause();
  LCD_RES_1;
  vLcdWhileStatus(LCD_BUSY_Msk | LCD_RESET_Msk);
}

/*******************************************************************************
* Function Name  : vLcdSetCrystal
* Description    : Sets the current LCD crystal.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void vLcdSetCrystal(LCD_Crystal num)
{
  CurrentCrystal = num;
}

/*******************************************************************************
* Function Name  : vLcdWriteCmd
* Description    : Writes command to the current LCD crystal.
* Input          : LCD command
* Output         : None
* Return         : None
*******************************************************************************/
void vLcdWriteCmd(uint32_t val)
{
  LCD_CMD(CurrentCrystal) = val;
  WAIT_BUSY;
}

/*******************************************************************************
* Function Name  : vLcdWriteData
* Description    : Writes data to the current LCD crystal.
* Input          : Data
* Output         : None
* Return         : None
*******************************************************************************/
void vLcdWriteData(uint32_t val)
{
  LCD_DATA(CurrentCrystal) = val;
  WAIT_BUSY;
}

/*******************************************************************************
* Function Name  : ulLcdReadCmd
* Description    : Reads command from the current LCD crystal.
* Input          : None
* Output         : None
* Return         : LCD command
*******************************************************************************/
uint32_t ulLcdReadCmd(void)
{
  volatile uint32_t addr = CrystalPorts[CurrentCrystal].Cmd;
  uint32_t ret = LCD_CMD(CurrentCrystal);

  return ret;
}

/*******************************************************************************
* Function Name  : ulLcdReadData
* Description    : Reads data from the current LCD crystal.
* Input          : None
* Output         : None
* Return         : LCD data
*******************************************************************************/
uint32_t ulLcdReadData()
{
  uint32_t ret;
  LCD_DATA(CurrentCrystal);     /* First reading is necessary to get correct data */
  WAIT_BUSY;
  ret = LCD_DATA(CurrentCrystal);
  WAIT_BUSY;
  return ret;
}

/*******************************************************************************
* Function Name  : vLcdInit
* Description    : Initializes all LCD crystals.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void vLcdInit(void)
{
  uint32_t crystal;
  EBC_RGN_InitTypeDef ebc;

  vLcdInitPins();

  EBC_RGNx_StructInit( &ebc );
  ebc.RGN_MODE = EBC_MODE_32X_8ECC;
  ebc.RGN_ROM = EBC_ROM_RAM;
  ebc.RGN_CPOL = EBC_CPOL_DOWN;
  ebc.RGN_WS_ACTIVE = 120;                                                               // 0 - 255
  ebc.RGN_WS_HOLD = 12;                                                                 // 0 - 15
  ebc.RGN_WS_SETUP = 12;                                                                // 0 - 15
  ebc.RGN_ENOCLK = DISABLE;
  ebc.RGN_DIVOCLK = 1;

  MDR_EBC->KEY = 0x8555AAA1;
  EBC_RGNx_Init( RGN0, &ebc );
  EBC_RGNx_Cmd( RGN0, ENABLE );

  vLcdReset();

  for (crystal = LCD_CRYSTAL1; crystal < NUM_LCD_CRYSTALS; crystal++)
  {
    vLcdSetCrystal((LCD_Crystal)crystal);
    WAIT_BUSY;
    LCD_ON;
    WAIT_ON;
    LCD_START_LINE(0);
  }

  vLcdClear();
}

/*******************************************************************************
* Function Name  : vLcdClear
* Description    : Clears the LCD screen.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void vLcdClear(void)
{
  uint32_t i, j, crystal;

  for (crystal = LCD_CRYSTAL1; crystal < NUM_LCD_CRYSTALS; crystal++)
  {
    vLcdSetCrystal((LCD_Crystal)crystal);
    WAIT_BUSY;
    LCD_OFF;
    LCD_SET_ADDRESS(0);
    for (i = 0; i < 8; i++)
    {
      LCD_SET_PAGE(i);
      for (j = 0; j < 64; j++)
      {
        vLcdWriteData(0x00);
      }
    }
    LCD_ON;
  }
}

/*******************************************************************************
* Function Name  : ulLcdGetStatus
* Description    : Returns the current LCD status.
* Input          : None
* Output         : None
* Return         : LCD status
*******************************************************************************/
static uint32_t ulLcdGetStatus(void)
{
  uint32_t ret;
  ret = ulLcdReadCmd();
  return ret;
}

/*******************************************************************************
* Function Name  : vLcdWhileStatus
* Description    : Wait until the specific LCD status changes.
* Input          : LCD status. This parameter can be one of the following
*                : values: LCD_BUSY, LCD_ONOFF, LCD_RESET.
* Output         : None
* Return         : None
*******************************************************************************/
static void vLcdWhileStatus(uint32_t status)
{

  uint32_t stat;
  for (stat = ulLcdGetStatus(); (stat & status) != 0; stat = ulLcdGetStatus())
  {
  }
}

/*******************************************************************************
* Function Name  : vLcdPause
* Description    : Delay for approx. 15*3 CPU clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void vLcdPause(void)
{
  volatile uint32_t i;

  for (i = 15; i > 0; i--);
}

static void vLcdInitPins( void )
{
    PORT_InitTypeDef lcdPort;

    PORT_StructInit( &lcdPort );

    MDR_PORTA->KEY = 0x8555AAA1;
    MDR_PORTB->KEY = 0x8555AAA1;
    MDR_PORTC->KEY = 0x8555AAA1;

    // D0 - D7
    lcdPort.PORT_Pin     = LCD_DATA_BUS_8;
    lcdPort.PORT_SOE     = PORT_SOE_OUT;
		lcdPort.PORT_SFUNC   = PORT_SFUNC_2;
		lcdPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    lcdPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( LCD_DATA_PORT, &lcdPort );

    // CLOCK - E
    lcdPort.PORT_Pin     = PORT_Pin_16;
    lcdPort.PORT_SFUNC   = PORT_SFUNC_2;
    PORT_Init( MDR_PORTB, &lcdPort );

    // PA18 - A0, PA22 - E2, PA23 - E1
    lcdPort.PORT_Pin     = PORT_Pin_18 | PORT_Pin_22 | PORT_Pin_23;
    lcdPort.PORT_SFUNC   = PORT_SFUNC_2;
    PORT_Init( MDR_PORTA, &lcdPort );

    // WE - R/W
    lcdPort.PORT_Pin     = PORT_Pin_14;
    lcdPort.PORT_SFUNC   = PORT_SFUNC_2;
    PORT_Init( MDR_PORTB, &lcdPort );

    // RES
    lcdPort.PORT_Pin     = PORT_Pin_10;
    lcdPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    PORT_Init( MDR_PORTB, &lcdPort );
}

/** @} */ /* End of group BSP_LCD_Exported_Functions */

/** @} */ /* End of group BSP_LCD */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE lcd_ebc.c */
