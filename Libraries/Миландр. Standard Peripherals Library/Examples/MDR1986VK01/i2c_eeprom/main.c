/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V1.1.0
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
#include "i2c.h"
#include "i2c_eeprom.h"

#include <string.h>
#include <stdlib.h>

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup i2c_eeprom i2c_eeprom
 *  @{
 */

#define I2C_TEST_SIZE   32

void ClockInit()
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;

    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[0], PLL_CLK_HSE0, CPU_CLK );
//    CLK_PllState( &MDR_CLK->PLL[0], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[0] ) )
//        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[2], PLL_CLK_HSE0, 50000000 );
//    CLK_PllState( &MDR_CLK->PLL[2], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[2] ) )
//        while(1){}

    CLK_SetSystemClock( MAX_CLK_HSE0 );
}

int main()
{
    uint8_t ucI2cTestData[ I2C_TEST_SIZE ], ucI2cTestDataRead[ I2C_TEST_SIZE ];
    uint8_t i;
    
    ClockInit();
    
    InitI2c( 400000 );
    
    for( i = 0; i < I2C_TEST_SIZE; i++ )
        ucI2cTestData[ i ] = rand() & 0xFF;
    
    I2C_Mem_RwData( 48, ucI2cTestData, I2C_TEST_SIZE, EEPROM_WRITE );
    I2C_Mem_RwData( 48, ucI2cTestDataRead, I2C_TEST_SIZE, EEPROM_READ );
    
    if( !memcmp( ucI2cTestData, ucI2cTestDataRead, I2C_TEST_SIZE ) )
    {
        __NOP();
    }
    else
    {
        __NOP();
    }
    
    while(1)
    {
    
    }
    
}

/** @} */ /* End of group i2c_eeprom */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


