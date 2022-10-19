/**
 ******************************************************************************
 * @file    main.c
 * @author  Milandr Application Team
 * @version V1.1.0
 * @date    14/04/2022
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
#include "MDR1986VK01_dma.h"
#include "eth.h"


#include <string.h>
#include <stdlib.h>

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup eth_icmp eth_icmp
 *  @{
 */

#define CPU_CLK             50000000

#define ANABG_IREFEN        (1 << 0)
#define ANABG_BFEN(x)       ((x & 0x3F) << 1)
#define ANABG_BGEN          (1 << 7)
#define ANABG_BFEXT(x)      ((x & 0xF) << 8)
#define ANABG_SWMODE(x)     ((x & 0x3F) << 12)
#define ANABG_EXTMODE       (1 << 18)
#define ANABG_IRECMODE      (1 << 19)
#define ANABG_VRECMODE      (1 << 20)
#define ANABG_ZMODE         (1 << 21)

#define ETH_BUFFER_SIZE     ((uint32_t)0x8000)

uint32_t ulOldIp = 1;

// PortA
#define YelLed              18
#define GrLed               17

#define PCLK_EN_PORTA       13

#define ETH_BUF             0x21008000

typedef struct
{
    unsigned short Data[288];
    unsigned short Counter;
    unsigned short Status;
} _Rec_Frame;

typedef struct
{
    unsigned char Data[1600];
    unsigned short Length;
    unsigned short Status;
    unsigned short Address;
    unsigned char Remote_IP[4];
    unsigned char Remote_MAC[6];

#if PRINTSTATUSON
    unsigned int CounterTxPacket;
    unsigned int CounterRxPacket;
#endif //PRINTSTATUSON

} _ethernet_packet;
__attribute__ ((aligned (4)))
_Rec_Frame Frame;

const uint16_t MyMAC[3] = {0x3412, 0x7856, 0xBC9A};
const uint16_t MyIPAddress[2] = {0xA8C0, 0x5701};

int Read_Packet(_ethernet_packet*);
uint16_t CheckSum_IP(void);
uint16_t CheckSum_ICMP(uint16_t size);
void Answear_ARP(void);
void Answear_ICMP(void);
void ClkCfg(void);
//void ETH_DeInit(MDR_ETH_TypeDef * ETHERNETx );
void EthCfg(MDR_ETH_TypeDef * ETHERNETx);
void LedsSetup(void);


void PacketAnaliser(void);
void MACReset(void);
void ClearMemory(void);

#if PRINTSTATUSON
    void Request_Status(_ethernet_packet*);
#endif //PRINTSTATUSON

_ethernet_packet Packet;
unsigned short Temp, TypeOfProtocol;
unsigned char My_IP[4], My_MAC[6];
unsigned char Receive_IP[4];
unsigned char ICMP_Packet[1500];
unsigned char RF_OK=0;
unsigned char XF_OK=0;


void ClockInit()
{
    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK =  0xFFFFFFFF;
    MDR_CLK->PER1_CLK =  0xFFFFFFFF;
    
    MDR_COMP0->ANABG_CTRL= ANABG_IREFEN | ANABG_BGEN | 
                     ANABG_BFEN( 0x3F ) | ANABG_SWMODE( 0x3F );

    MDR_BKP->KEY = 0x8555AAA1;

    CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
    if( !CLK_XSEWaitReady( CLK_HSE0 ) )
        while(1){}

    CLK_SetPllClk( &MDR_CLK->PLL[0], PLL_CLK_HSE0, CPU_CLK );
    CLK_PllState( &MDR_CLK->PLL[0], ENABLE );
    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[0] ) )
        while(1){}

    CLK_SetPllClk( &MDR_CLK->PLL[2], PLL_CLK_HSE0, 50000000 );
    CLK_PllState( &MDR_CLK->PLL[2], ENABLE );
    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[2] ) )
        while(1){}

    //CLK_SetSystemClock( MAX_CLK_HSE0 );
    CLK_SetSystemClock( MAX_CLK_PLL0 );
}


int main()
{
    ClockInit();
    
    InitEth( 50000000 );
    
    EthCfg(MDR_ETH0);
    
    // CfgDMA
    MDR_DMA->CTRL_BASE_PTR = 0x20001000;
    MDR_DMA->CHMUX[0] = 0x0;
    MDR_DMA->CONFIG |= (1 << 0); // Activate DMA
    
    while(1)
    {
        EthLoop();
        while(MDR_ETH0->R_HEAD != MDR_ETH0->R_TAIL)
        {
            Frame.Counter=ETH_ReceivedFrame((uint32_t*)&Frame, 100);
            PacketAnaliser();
        
        }
    }
}



uint16_t CheckSum_IP(void)
{
    unsigned long a, cs=0;
    for(a=0; a<10; a++)
    {
        if(a == 5) continue;
        else cs = cs + Frame.Data[7+a];
    }
    cs = (cs >> 16) + (cs & 0xFFFF);
    return (uint16_t)(~cs);
}


uint16_t CheckSum_ICMP(uint16_t size)
{
    unsigned long a, cs=0;
    for(a=0;a<size;a++)
    {
        if(a==1) continue;
        else cs+=Frame.Data[a+17];
    }
    cs=(cs>>16)+(cs&0xFFFF);
    return (uint16_t)(~cs);
}


void Answear_ARP(void)
{

    uint16_t Buf[24];
    Buf[0]=0x002A;
    Buf[1]=0x0000;
    Buf[2]=Frame.Data[3];           
    Buf[3]=Frame.Data[4];           
    Buf[4]=Frame.Data[5];           
    Buf[5]=MDR_ETH0->MAC_T;         
    Buf[6]=MDR_ETH0->MAC_M;         
    Buf[7]=MDR_ETH0->MAC_H;         
    Buf[8]=Frame.Data[6];           //type - ARP
    Buf[9]=Frame.Data[7];           //Hardware type - Ethernet
    Buf[10]=Frame.Data[8];          //Protocol type - IP
    Buf[11]=Frame.Data[9];          //Hardware size - 6; Protocol size - 4
    Buf[12]=0x0200;                 
    Buf[13]=MDR_ETH0->MAC_T;        //Sender MAC-address: 0A.1B.2C.3D.4E.5F
    Buf[14]=MDR_ETH0->MAC_M;        //Sender MAC-address: 0A.1B.2C.3D.4E.5F
    Buf[15]=MDR_ETH0->MAC_H;        //Sender MAC-address: 0A.1B.2C.3D.4E.5F
    Buf[16]=MyIPAddress[0];         //My_IP_Address[0];    //Sender IP-address: 192.168.1.87
    Buf[17]=MyIPAddress[1];         //My_IP_Address[1];    //Sender IP-address: 192.168.1.87
    Buf[18]=Frame.Data[3];          //Target MAC-address
    Buf[19]=Frame.Data[4];          //Target MAC-address
    Buf[20]=Frame.Data[5];          //Target MAC-address
    Buf[21]=Frame.Data[14];         //Target IP-address
    Buf[22]=Frame.Data[15];         //Target IP-address
    Buf[23]=0;
    
    ETH_SendFrame(MDR_ETH0, (uint32_t*) Buf, 42);
}

void Answear_ICMP(void)
{
    unsigned long a;
    __attribute__ ((aligned (4)))
    uint16_t buffer[288];
    uint16_t tmp;
    
    tmp = Frame.Counter-34-4;
    
    if((tmp&0x01)==1)
    {
        tmp=(tmp+1)>>1;
        Frame.Data[tmp+16]=Frame.Data[tmp+16]&0x00FF;
    }
    else tmp=tmp>>1;
        
        //-------Ethernet 2 Protocol---------
        buffer[0]=Frame.Counter-4;
        buffer[1]=0x0;
        
        buffer[2]=Frame.Data[3];
        buffer[3]=Frame.Data[4];
        buffer[4]=Frame.Data[5];
        
        buffer[5]=MDR_ETH0->MAC_T;
        buffer[6]=MDR_ETH0->MAC_M;
        buffer[7]=MDR_ETH0->MAC_H;
        
        buffer[8]=Frame.Data[6];
    
    //-------IP Protocol---------
    for(a=9;a<14;a++)
    {
        buffer[a]= Frame.Data[a-2];
    }
    //---------------------------
    buffer[14]=CheckSum_IP();
    buffer[15]=Frame.Data[15];//IP->DestinAddr[0];
    buffer[16]=Frame.Data[16];//IP->DestinAddr[1];
    buffer[17]=Frame.Data[13];//IP->SourceAddr[0];
    buffer[18]=Frame.Data[14];//IP->SourceAddr[1];
    
    //-------ICMP Protocol---------
    buffer[19]=0x0000;
    Frame.Data[17]=0x0000;
    //-----------------------------
    buffer[20]=CheckSum_ICMP(tmp);
    for(a=21;a<((tmp-2)+21);a++)
    {
        buffer[a]=Frame.Data[a-2];
    }
    
    ETH_SendFrame(MDR_ETH0, (uint32_t*) buffer, (tmp*2+34));

}


void PacketAnaliser(void)
{
    switch(Frame.Data[6])
    {
        case 0x0008:
            if((Frame.Data[15]==MyIPAddress[0])&&(Frame.Data[16]==MyIPAddress[1]))  
            {
                if(CheckSum_IP()==Frame.Data[12])
                {
                //--------------------ICMP-------------------
                    if((Frame.Data[11]&0xFF00)==0x0100)
                    {
                        if(Frame.Data[17]==0x0008)
                        {
                            Answear_ICMP();
                        }
                    }
                }
                //-------------------------------------------
            }
            break;
        case 0x0608:
            if((Frame.Data[19]==MyIPAddress[0])&&(Frame.Data[20]==MyIPAddress[1]))
            {
                Answear_ARP();
            }
            break;
    }
}


void MACReset()
{
    uint32_t treg;
    treg = 0x00030000;
    
    MDR_ETH0->G_CFG|=(treg & 0xFFFF0000);
    
    ClearMemory();
    
    MDR_ETH0->DILIMETR=0x4000;	
    
    MDR_ETH0->HASH0=0;
    MDR_ETH0->HASH1=0;
    MDR_ETH0->HASH2=0;
    MDR_ETH0->HASH3=0x8000;
    
    MDR_ETH0->IPG=0x0060;
    MDR_ETH0->PSC=0x0050;
    MDR_ETH0->BAG=0x0200;
    MDR_ETH0->JITTERWND=0x0005;
    MDR_ETH0->R_CFG=0x8406;
    MDR_ETH0->X_CFG=0x81FA;
    
    treg = 0x30030080;
    
    MDR_ETH0->G_CFG = (treg & 0xFFFFFFFF);
    
    MDR_ETH0->IMR=0;
    MDR_ETH0->IFR=0xFFFF;
    
    MDR_ETH0->R_HEAD=0x0000;
    MDR_ETH0->X_TAIL=0x1000;
    
    treg = 0xFFFCBFFF;
    
    MDR_ETH0->G_CFG&=(treg & 0xFFFFFFFF);
}

void ClearMemory()
{
    uint32_t Temp;
    uint32_t *ptr;
    ptr=(uint32_t*)0x21008000;
    for(Temp=0;Temp<8000;Temp++)
    {
        *ptr++=0;
    }
}

void EthCfg(MDR_ETH_TypeDef * ETHERNETx)
{
    ETHERNETx->MAC_T=MyMAC[0];
    ETHERNETx->MAC_M=MyMAC[1];
    ETHERNETx->MAC_H=MyMAC[2];
    
    // Start
    ETHERNETx->R_CFG |= (1<<15);
    ETHERNETx->X_CFG |= (1<<15);
}

/** @} */ /* End of group eth_icmp */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */

