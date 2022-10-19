/**
  ******************************************************************************
  * @file    i2c.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   I2C source file for demo board.
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
  * FILE i2c.c
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include "i2c_eeprom.h"
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_i2c.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_I2C BSP_I2C
  * @{
  */

/** @defgroup BSP_I2C_Private_Defines BSP_I2C Private Defines
  * @{
  */

void InitI2c( uint32_t speed )
{
    I2C_InitTypeDef I2C_InitStruct;
    PORT_InitTypeDef i2cPort;

    PORT_StructInit( &i2cPort );
    MDR_PORTA->KEY = 0x8555AAA1;
    MDR_PORTB->KEY = 0x8555AAA1;

    /* SCL, SDA */
    i2cPort.PORT_Pin     = PORT_Pin_30 | PORT_Pin_31;
    i2cPort.PORT_SOE     = PORT_SOE_OUT;
    i2cPort.PORT_SFUNC   = PORT_SFUNC_9;
    i2cPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    i2cPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( MDR_PORTB, &i2cPort );

    /* 
        F = HCLK / ( 5 * ( DIV + 1 ) )
        HCLK = SystemCoreClock

        DIV = HCLK / 5 * F - 1 
    */
    I2C_InitStruct.I2C_ClkDiv = SystemCoreClock / ( 5 * speed ) - 1;
    I2C_InitStruct.I2C_Speed = I2C_SPEED_UP_TO_400KHz;
    I2C_Init( &I2C_InitStruct );

    I2C_Cmd( ENABLE );
}

/**
    Writing an array of data to the memory of the i2c device within a page
*/
uint8_t I2C_Mem_Write( uint8_t devAddress, uint16_t memAddress, uint16_t memAddSize, uint8_t *pData, uint16_t size )
{
    uint32_t timeout = 0;

    /* Waiting for the release of the i2c bus */
    while( I2C_GetFlagStatus( I2C_FLAG_BUS_FREE ) != SET )
    {
        timeout++;
        if( timeout == MAX_I2C_TIMEOUT )
            return 0;
    }

    I2C_Send7bitAddress( devAddress, I2C_Direction_Transmitter );

    /* Waiting for the transfer to complete */
    while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};

    /* Device did not respond ACK */
    if( I2C_GetFlagStatus( I2C_FLAG_SLAVE_ACK ) != SET )
        goto i2c_stop;
    
    if( memAddSize == 2 )
    {
        I2C_SendByte( ( memAddress >> 8 ) & 0xFF );
        
        /* Waiting for the transfer to complete */
        while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};
    }
    
    I2C_SendByte( memAddress & 0xFF );

    /* Waiting for the transfer to complete */
    while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};
    
    /* Device did not respond ACK */
    if( I2C_GetFlagStatus( I2C_FLAG_SLAVE_ACK ) != SET )
        goto i2c_stop;    
    
    while( size )
    {
        I2C_SendByte( *pData++ );
        size--;

        /* Waiting for the transfer to complete */
        while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};
        
        /* Device did not respond ACK */
        if( I2C_GetFlagStatus( I2C_FLAG_SLAVE_ACK ) != SET )
            goto i2c_stop;   
    }
    
    I2C_SendSTOP();
    return 1; 
    
i2c_stop:
    I2C_SendSTOP();
    return 0;
}

/**
    Reading an array of data from the memory of the i2c device within a page
*/
uint8_t I2C_Mem_Read( uint8_t devAddress, uint16_t memAddress, uint16_t memAddSize, uint8_t *pData, uint16_t size )
{
    uint32_t timeout = 0;

    /* Waiting for the release of the i2c bus */
    while( I2C_GetFlagStatus( I2C_FLAG_BUS_FREE ) != SET )
    {
        timeout++;
        if( timeout == MAX_I2C_TIMEOUT )
            return 0;
    }

    I2C_Send7bitAddress( devAddress, I2C_Direction_Transmitter );

    /* Waiting for the transfer to complete */
    while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};

    /* Device did not respond ACK */
    if( I2C_GetFlagStatus( I2C_FLAG_SLAVE_ACK ) != SET )
        goto i2c_stop;
    
    if( memAddSize == 2 )
    {
        I2C_SendByte( ( memAddress >> 8 ) & 0xFF );
        while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};                        
    }
    
    I2C_SendByte( memAddress & 0xFF );
    while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};                            
    
    if( I2C_GetFlagStatus( I2C_FLAG_SLAVE_ACK ) != SET )                                
        goto i2c_stop;    
    
    I2C_Send7bitAddress( devAddress, I2C_Direction_Receiver );
    while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};  
    
    while( size )
    {
        /* Start receiving data */
        if( size == 1 )
            I2C_StartReceiveData( I2C_Send_to_Slave_NACK );                             
        else
            I2C_StartReceiveData( I2C_Send_to_Slave_ACK ); 
        while( I2C_GetFlagStatus( I2C_FLAG_nTRANS ) != SET ) {};  
        
        *pData++ = I2C_GetReceivedData();
        size--;
    }
    
    I2C_SendSTOP();
    return 1; 
    
i2c_stop:
    I2C_SendSTOP();
    return 0;
}

/** @} */ /* End of group BSP_I2C_Exported_Functions */

/** @} */ /* End of group BSP_I2C */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE i2c.с */


