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
#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_canfd.h"
#include "MDR1986VK01_clk.h"
#include "tinymt32.h"

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup canfd_transceive canfd_transceive
 *  @{
 */

void ProgramDelay (uint32_t value) // 2097151 max
{
  //Init systick
  SysTick->LOAD = value*8;
  SysTick->CTRL = 0x5; //CLKSOURCE = HCLK,Enable
  SysTick->LOAD = 0;
  while((SysTick->CTRL&1<<16)!=1<<16);
  SysTick->CTRL = 0x0; //Disable
}

void delay_us(void)
{
    volatile int j;	
    for(j=0;j<30;j++)
    __NOP();
}

void vErrorHandler( void )
{
    while( 1 );
}

#define ANABG_IREFEN                (1 << 0)
#define ANABG_BFEN(x)               ((x & 0x3F) << 1)
#define ANABG_BGEN                  (1 << 7) 
#define ANABG_BFEXT(x)              ((x & 0xF) << 8)
#define ANABG_SWMODE(x)             ((x & 0x3F) << 12)
#define ANABG_EXTMODE               (1 << 18)
#define ANABG_IRECMODE              (1 << 19)
#define ANABG_VRECMODE              (1 << 20)
#define ANABG_ZMODE                 (1 << 21)

#define N_IRQ            210


// Test configuration
#define MDR_CANFDx       MDR_CANFD0
volatile int32_t  NumMsg = -1;

volatile uint32_t       Errors  = 0;
volatile uint32_t       delay   = 0;
uint8_t                 i,j;
uint16_t                QNum    = 0;
uint16_t                SlotNum = 0;

// Structures
CanfdInitCfg_t          InitCfg;
CanFdUserMsg_t          Msg;
CanFdStatus_t           Status = OK;

tinymt32_t tinymt;

int main(void)
{
    uint32_t st;
    int i;
    
    NVIC->ISER[N_IRQ/32]=(1<<(N_IRQ%32));
    
    tinymt.mat1 = 0x8f7011ee;
    tinymt.mat2 = 0xfc78ff1f;
    tinymt.tmat = 0x3793fdff;
    tinymt32_init(&tinymt, 42);
    
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK = 0xFFFFFFFF;
    MDR_CLK->PER1_CLK = 0xFFFFFFFF;
    
    MDR_BKP->KEY     = 0x8555AAA1;
    MDR_PORTA->KEY   = 0x8555AAA1;
    MDR_PORTB->KEY   = 0x8555AAA1;
    MDR_PORTC->KEY   = 0x8555AAA1;
    
    MDR_COMP0->ANABG_CTRL= ANABG_IREFEN | ANABG_BGEN | ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );
    
    PORT_InitTypeDef p;
    PORT_StructInit( &p );
    p.PORT_SOE     = PORT_SOE_OUT;
    p.PORT_SFUNC   = PORT_SFUNC_9;
    p.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    p.PORT_SPWR    = PORT_SPWR_10;
    
    p.PORT_Pin     = PORT_Pin_26; // TX_CANFD
    PORT_Init( MDR_PORTC, &p );  
    
    p.PORT_Pin     = PORT_Pin_27; // RX_CANFD
    PORT_Init( MDR_PORTC, &p );
    
    p.PORT_SFUNC   = PORT_SFUNC_PORT;
    p.PORT_Pin     = PORT_Pin_19; // STBY_CANFD
    PORT_Init( MDR_PORTC, &p );  
    PORT_ResetBits ( MDR_PORTC, 1<<19 );
    
    p.PORT_SFUNC   = PORT_SFUNC_1;
    p.PORT_Pin     = PORT_Pin_19; // TRACECLK
    PORT_Init( MDR_PORTA, &p );  
    
    
    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        vErrorHandler();
    
    CLK_SetPllClk( &MDR_CLK->PLL[0], PLL_CLK_HSE0, 80000000 );
    
    CLK_PllState( &MDR_CLK->PLL[0], ENABLE );
    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[0] ) )
        vErrorHandler();
    
    MDR_CLK->MAX_CLK = MAX_CLK_PLL0;
    
    MDR_CLK->CANFD_CLK = (5<<28)|(1<<16); // PLL0
    
    /*****MLDR124 - CAN-FD Initialization*****/
    CanFdCreateDefaultCfg( &InitCfg );
    
    InitCfg.PropSeg  = 1;
    
    // 80E6/32/(3+2+5) = 250E3
    InitCfg.ClkDiv_N = 32-1;
    InitCfg.Seg1_n   = 3;
    InitCfg.Seg2_n   = 2;
    
    // 80E6/8/(3+2+2+2+1) = 1000E3
    InitCfg.ClkDiv_D = 8-1;
    InitCfg.Seg1_d   = 3; // (3+2)/(3+2+2+2+1) = 50%
    InitCfg.Seg2_d   = 2; 
    
    InitCfg.FdEn     = 1;
    InitCfg.RxQSize = 32;
    InitCfg.TxQSize = 96;
    
    CanFdInit(&InitCfg);
    
    MDR_CANFDx->MSK |= (1<<RXFRMCMPLT);
    
    /*****MLDR124 - CAN-FD Send Message*****/
    
    Msg.Dlc    = 2;
    Msg.Srr    = 1;
    Msg.Ide    = 0;
    Msg.Brs    = 1;
    Msg.Ssf    = 1;
    Msg.PType  = 1;

    for(i=0; i < NumMsg || NumMsg<0; i++) 
    {

        QNum    = 1;
        SlotNum = 1;

        Msg.BaseId = 0x123;
        Msg.ExtId  = 0x12345;

        Msg.Dlc = tinymt32_generate_uint32(&tinymt);
        Msg.Brs = tinymt32_generate_uint32(&tinymt);

        // allocate memory and check for valid pointer
        Msg.BytePtr= (uint8_t *) malloc( Dlc2Bytes(Msg.Dlc) );
        if( Msg.BytePtr == NULL ) {
            Errors++;
            goto exit;
        }

        //Msg.WordPtr= (uint32_t*) Msg.BytePtr;
        for(j=0; j < Dlc2Bytes(Msg.Dlc); j++) {
            //*(Msg.BytePtr+j) = 42+j;
            *(Msg.BytePtr+j) = tinymt32_generate_uint32(&tinymt);
        }
        
        //while (1);
        
        // Add msg to queue and de-allocate payload memory
        Status = CanFdSendMessage(&Msg, QNum, SlotNum);
        if( Status != OK) {
            Errors++;
        }
        free(Msg.BytePtr);

        do {
            for(delay=0; delay< 50; delay++) ;
            st = MDR_CANFDx->ST;
            } while ( ((st & (1<<TXFRMCMPLT)) == 0) && ((st & (1<<TXERR)) == 0)  && ((st & (1<<EAS)) == 0) );

    }

    exit:

    return 0;
    
    while (1) 
    {
        ProgramDelay(200000); 
        MDR_PORTC->RXTX = i++ << 16;
    }
}

void CANFD_IRQHandler(void) 
{

    uint32_t ST_temp;
    uint32_t RXQCTRL_temp;
    uint8_t  i;


    ST_temp = MDR_CANFDx->ST;
    // Check that transmittion complete
    if( (ST_temp & (1<<RXFRMCMPLT) ) != 0 ) {
        if( SlotNum < 32 ) {
            RXQCTRL_temp = MDR_CANFDx->RXQCTRL[0];
        } else {
            RXQCTRL_temp = MDR_CANFDx->RXQCTRL[1];
        }
        if( (RXQCTRL_temp & (1<<SlotNum)) == 0 ){
            Errors++;
        }

        Status = CanFdReadMessage(&Msg, 0, SlotNum);
    }

    // Check there are no errors
    if( (ST_temp & (1<<DLCERR) ) == 1 ) {
        Errors++;
    }
    if( (ST_temp & (1<<TXERR) ) == 1 ) {
        Errors++;
    }
    if( (ST_temp & (1<<RXERR) ) == 1 ) {
        Errors++;
    }
    if( (ST_temp & (1<<BITERR) ) == 1 ) {
        Errors++;
    }
    if( (ST_temp & (1<<BITSTAFFERR) ) == 1 ) {
        Errors++;
    }
    if( (ST_temp & (1<<ACKERR) ) == 1 ) {
        Errors++;
    }
    if( (ST_temp & (1<<CRCERR) ) == 1 ) {
        Errors++;
    }
    if( (ST_temp & (1<<FRMERR) ) == 1 ) {
        Errors++;
    }
}

/** @} */ /* End of group canfd_transceive */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


