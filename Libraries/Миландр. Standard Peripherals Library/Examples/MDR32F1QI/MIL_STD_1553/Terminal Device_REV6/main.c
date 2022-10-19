/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team - Dyachkov Petr
  * @version V2.0.2
  * @date    21/09/2021
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
  * <h2><center>&copy; COPYRIGHT 2022 Milandr </center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F1QI.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_MDR32F1QI_6 MIL_STD_1553 Terminal Device for MDR32F1QI rev. 6 Evaluation Board
  * @{
  */

/* Private define ------------------------------------------------------------*/


#define CONTROL_MODE 0x03E0
#define SUBADDRESS   0x03E0
#define TRM_nRCV     0x0400

/*
If you uncomment string <#define USE_HARDWARE_ADDRESS> then the address of Terminal Device gets from PORTF[8:4] and flags in Status Word gets from PORTF[12:9],
else the Terminal address gets from ADDR_OU, and flags in Status Word gets from trouble_OU_0, trouble_user_2, busy_user_3, s_request_8

Terminal address bits:
PF[4] - Terminal address 0,
PF[5] - Terminal address 1,
PF[6] - Terminal address 2,
PF[7] - Terminal address 3,
PF[8] - Terminal address 4,

Terminal address parity bit:
PF[13] - Terminal address parity bit

Flags in Status Word:
PF[9]     - Busy
PF[10] - Terminal Flag
PF[11] - Subsystem Flag
PF[12] - Serice Request
*/
//#define USE_HARDWARE_ADDRESS

/* if you use 5559in13, you must uncomment next string, and comment #define __5559IN67 */
#define __5559IN13

/* if you use 5559in67, you must uncomment next string, and comment #define __5559IN13 */
//#define __5559IN67

#define __DEBUG__

/* Private variables ---------------------------------------------------------*/
int ADDR_OU;
int ADDR_OU_old;

uint32_t SW1;               //Status Word 1

uint32_t block_tf;          //flag of property "defect terminal" (masked 0 bit in Status Word, if reset (0)).
uint32_t trouble_OU_0;      //0 bit in Status Word 1 (Terminal Flag)
uint32_t trouble_user_2;    //2 bit in Status Word 1 (Subsystem Flag)
uint32_t busy_user_3;       //3 bit in Status Word 1 (Busy)
uint32_t s_request_8;       //8 bit in Status Word 1 (Service Request)


int bits;
int bits_old;
int old_prty;

uint32_t flag_test_6137 = 1;
uint32_t active_channel = 0;

#ifdef USE_HARDWARE_ADDRESS
/**
  * @brief  Function for check new terminal address at parity.
  * @param  newAddress - new terminal addr ess in range 0 - 30
  * @param  parity     - parity bit (odd)
  * @retval 0 - parity OK
            1 - parity ERROR
  */
uint32_t CheckTermAddress(uint32_t newAddress, uint32_t parity)
{
    uint32_t i, res = 0;
    
    for(i = 0; i < 5; i++)
    {
        res += ((newAddress >> i) & 1);
    }
    if((res & 1) != parity)    return 0;    //parity OK
    else                       return 1;    //parity ERROR

}
#endif    //USE_HARDWARE_ADDRESS

/**
  * @brief  MIL_STD_15531 Interrupt Handler
  * @param  None
  * @retval None
  */
void  MIL_STD_1553B1_IRQHandler(void)
{
    uint32_t i, j, Control_Mode, _Status_, _CommandWord1_;

    _CommandWord1_ = MDR_MIL_STD_15531->CommandWord1;   //save Command Word
    _Status_ = MDR_MIL_STD_15531->STATUS;
    MDR_MIL_STD_15531->STATUS = 0;
    
#ifdef __DEBUG__
    MDR_PORTD->SETTX = 1 << 7;
    
    if((_Status_ & MIL_STD_1553_STATUS_ERR) != 0)       //ERROR interrupt occure
    {
        MDR_PORTD->SETTX = 2 << 7;
    }
#endif    //__DEBUG__
    
    if((_Status_ & MIL_STD_1553_STATUS_VALMESS) != 0)   //VALMESS interrupt occure
    {
        /*-----------------------------------*/
        /*--- Cyclic subaddress operation ---*/
        /*-----------------------------------*/
        if(((_CommandWord1_ & TRM_nRCV) == 0)    &&
           ((_CommandWord1_ & CONTROL_MODE) != CONTROL_MODE) &&
           ((_CommandWord1_ & CONTROL_MODE) != 0))
        {
            if((_CommandWord1_ & SUBADDRESS) == (30 << 5))  //if 30 subaddress (subadderss for wraparound data)
            {
                Control_Mode = _CommandWord1_ & 0x1F;
                if(Control_Mode == 0)
                {
                    Control_Mode = 32;
                }
                for(j = 0; j < Control_Mode; j++)
                {
                    i = MDR_MIL_STD_15531->SubAddr[30].Data[j];
                    MDR_MIL_STD_15531->SubAddr[30].Data[j] = i;
                }
            }
        }
    }

#ifdef __DEBUG__
    MDR_PORTD->CLRTX = 0x0F << 7;
#endif    //__DEBUG__

}
/*--------------------------------------------------------------*/
/*---------- MIL_STD_15531 Interrupt Handler Complete ----------*/
/*--------------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t i, p, j;
    
    /***************************/
    /* Configuration MCU Clock */
    /***************************/
    MDR_RST_CLK->PER_CLOCK &= ((1 << 4)|(1 << 27));           //Disable all peripherial clocks signals without RST_CLK and BKP
    MDR_RST_CLK->PER_CLOCK |= (1 << 4)|(1 << 3)|(1 << 27);    //Enable clocks of EEPROM_CNTRL, RST_CLK, BKP

    if((MDR_BKP->REG_0F & (3 << 22)) != 3)    //if HSI not ready or power off, wait or power on HSI
    {
        if((MDR_BKP->REG_0F & (1 << 22)) == 0){
            MDR_BKP->REG_0F |= (1 << 22);    //power on HSI, if it disable
        }
        while((MDR_BKP->REG_0F & (1 << 23)) == 0);  //wait until HSI not ready
    }
    
    MDR_RST_CLK->CPU_CLOCK = 0;
    MDR_RST_CLK->PLL_CONTROL = 0;
    MDR_RST_CLK->HS_CONTROL = 1;    //HSE power on, oscillator mode (default: HSE = 8 MHz for eval kit)
    while((MDR_RST_CLK->CLOCK_STATUS & (1 << 2)) == 0); //wait until HSE not ready
    
    i = 1000;
    while(i-- > 0){}
    
    MDR_RST_CLK->PER_CLOCK |= (1 << 3); //Enable clock of EEPROM_CNTRL
    MDR_RST_CLK->CPU_CLOCK = 2;         //CPU_C1 = 2 (sourse of CPU_C1 frequency is HSE generator)
    MDR_EEPROM->CMD = 5 << 3;           //delay = 5, max clock of core must be below 150 MHz        
    MDR_BKP->REG_0E |= 0x3F;            //write 7 in fields LOW and SelectRI (for working frequency more then 80 MHz)
    MDR_RST_CLK->PLL_CONTROL = (9 << 8)|(1 << 2);    //PLL frequency 80 MHz

    MDR_RST_CLK->PER_CLOCK &= ~(1 << 3);    //Disable clock of EEPROM_CNTRL

    while((MDR_RST_CLK->CLOCK_STATUS & (1 << 1)) == 0); //wait until PLL not ready
    MDR_RST_CLK->CPU_CLOCK = 0x106;    //PLL is source of core frequency (80 MHz)

    MDR_RST_CLK->PER_CLOCK |= (1 << 29)|(1 << 23)|(1 << 24)|(1 << 25)|(1 << 9);    //Enable clocks of PortF, PortC, PortD, PortE, Mil_Std_1553_1

    /***************************/
    /* Configuration MCU Ports */
    /***************************/
    MDR_PORTC->ANALOG = (7 << 13);
    MDR_PORTC->FUNC = (0x15 << 26);

    //MDR_PORTD->ANALOG = 0x7F;
    MDR_PORTD->FUNC = 0x1555;
    MDR_PORTD->PWR = (3 << 2)|(3 << 4)|(3 << 6)|(3 << 8)|(3 << 10)|(3 << 12);

#ifdef __DEBUG__
    MDR_PORTD->RXTX = 0;
    MDR_PORTD->ANALOG |= 0xFF << 7;
    MDR_PORTD->OE = 0xFF << 7;
    MDR_PORTD->PWR |= 0xAAAA << 14;
#endif    //__DEBUG__

#ifdef USE_HARDWARE_ADDRESS
    MDR_PORTF->FUNC = 0;
    MDR_PORTF->ANALOG = (0x3FF << 4);
    MDR_PORTF->OE = 0;
    MDR_PORTF->PULL    = ((0x3FF << 4) << 16);    //Enable Pull up of PortF[13:4]
#endif    //USE_HARDWARE_ADDRESS

    MDR_PORTE->FUNC = 0;    //port
    MDR_PORTE->OE = 0;        //input
    MDR_PORTE->ANALOG = 1 << 8;    //digital
    MDR_PORTE->PULL = 0;        //pull off

    /********************************/
    /* Configuration MIL_STD_1553_1 */
    /********************************/
    MDR_RST_CLK->ETH_CLOCK = 0x02000100;    //Enable clock of Mil_Std_1553_1, reference clock of Mil_Std_1553_1 is HCLK/2 = 40 MHz

#ifdef USE_HARDWARE_ADDRESS
    i = MDR_PORTF->RXTX;

    j = ((i >> 4) & 0x1F);    //read new terminal address
    p = ((i >> 13) & 1);        //read address parity bit
    old_prty = p;
    if(CheckTermAddress(j, p) == 0)    ADDR_OU = j;     // valid address
    else                               ADDR_OU = -1;    // unvalid address

    trouble_OU_0 = ((i >> 10) & 1);
    trouble_user_2 = ((i >> 11) & 1);
    busy_user_3 = ((i >> 9) & 1);
    s_request_8 = ((i >> 12) & 1);

#else
    ADDR_OU = 1;

    trouble_OU_0 = 0;
    trouble_user_2 = 0;
    busy_user_3 = 0;
    s_request_8 = 0;
#endif    //USE_HARDWARE_ADDRESS

    ADDR_OU_old = ADDR_OU;

    bits = trouble_OU_0 | (trouble_user_2 << 2) | (busy_user_3 << 3) | (s_request_8 << 8);
    bits_old = bits;

    MDR_MIL_STD_15531->CONTROL = 0x00000000;
    MDR_MIL_STD_15531->INTEN = 0x00000004;      //Enable interrupts of events: VALMESS

#ifdef     __DEBUG__
    MDR_MIL_STD_15531->INTEN = 0x0000000C;      //Enable interrupts of events: VALMESS, ERROR
#endif    //__DEBUG__

    SW1 = (ADDR_OU << 11)|(bits);
    MDR_MIL_STD_15531->StatusWord1 = SW1;       //write Status Word

    block_tf = 0xFFFFFFFF;

    MDR_MIL_STD_15531->ModeData = 0x000055AA;   //Mode Word 
    
    if((ADDR_OU >= 0)&&(ADDR_OU < 31))    //check for unvalid terminal address
    {
#ifdef __5559IN13
        /*                           RT_HW    | ENFILTER| ERR bit | DIV[6:0] |   RTA[4:0]   |  TRB   |  TRA   | RTMODE  */
        MDR_MIL_STD_15531->CONTROL = (1 << 23)|(1 << 20)|(0 << 18)|(40 << 11)|(ADDR_OU << 6)|(1 << 5)|(1 << 4)|(2 << 2);    //settings for MIL_STD_1553 PHY 5559IN13
#endif    //__5559IN13

#ifdef __5559IN67
        /*                           RT_HW    |INVTR bit| RERR bit| DIV[6:0] |   RTA[4:0]   |  TRB   |  TRA   | RTMODE  */
        MDR_MIL_STD_15531->CONTROL = (1 << 23)|(1 << 19)|(0 << 18)|(40 << 11)|(ADDR_OU << 6)|(1 << 5)|(1 << 4)|(2 << 2);    //settings for MIL_STD_1553 PHY 5559IN67
#endif    //__5559IN67
    }
    else
    {
#ifdef __5559IN13
        /*                           RT_HW    | ENFILTER| RERR bit| DIV[6:0] |   RTA[4:0]   |  TRB   |  TRA   | RTMODE  */
        MDR_MIL_STD_15531->CONTROL = (1 << 23)|(1 << 20)|(0 << 18)|(40 << 11)|(      0 << 6)|(1 << 5)|(1 << 4)|(2 << 2)|1;    //settings for MIL_STD_1553 PHY 5559IN13, controller of MIL_STD_1553 in reset
#endif    //__5559IN13
        
#ifdef    __5559IN67
        /*                           RT_HW    |INVTR bit| RERR bit| DIV[6:0] |   RTA[4:0]   |  TRB   |  TRA   | RTMODE  */
        MDR_MIL_STD_15531->CONTROL = (1 << 23)|(1 << 19)|(0 << 18)|(40 << 11)|(      0 << 6)|(1 << 5)|(1 << 4)|(2 << 2)|1;    //settings for MIL_STD_1553 PHY 5559IN67, controller of MIL_STD_1553 in reset
        
#endif    //__5559IN67
    }
    
    for(i = 0; i < 32; i++)
    {
        for(p = 0; p < 32; p++)
        {
            MDR_MIL_STD_15531->SubAddr[i].Data[p] = (((uint8_t)i) << 8)|((uint8_t)p);
        }
    }

    MDR_PORTD->ANALOG = 0x7F;

    NVIC_EnableIRQ(MIL_STD_1553B1_IRQn);
    
    /*-------------------------------*/
    /*---------- Main Loop ----------*/
    /*-------------------------------*/

    while(1)
    {
#ifdef USE_HARDWARE_ADDRESS
        i = MDR_PORTF->RXTX;
        j = ((i >> 4) & 0x1F);    // read new terminal address
        p = ((i >> 13) & 1);      // read address parity bit
#else 
        j = (ADDR_OU & 0x1F);
#endif    //USE_HARDWARE_ADDRESS



#ifdef USE_HARDWARE_ADDRESS
        if((ADDR_OU_old != j)||(old_prty != p))
        {
            i = CheckTermAddress(j, p);
            old_prty = p;
#else
        if(ADDR_OU_old != j)
        {
#endif    //USE_HARDWARE_ADDRESS
            while((MDR_MIL_STD_15531->STATUS & 1) == 0){}    //wait while MIL_STD_15531 is transmitting a data
#ifdef USE_HARDWARE_ADDRESS
            if((i == 0)&&(j != 0x1F))
            {
                i = MDR_MIL_STD_15531->CONTROL;
                i = (i & (~((0x1F << 6) | 1))) | (j << 6);    //Set new Terminal Address and set normal state (not reset)
                MDR_MIL_STD_15531->CONTROL = i;
                ADDR_OU_old = ADDR_OU = j;
            }
#else
            if(j != 0x1F)
            {
                i = MDR_MIL_STD_15531->CONTROL;
                i = (i & (~((0x1F << 6) | 1))) | (j << 6);    //Set new Terminal Address and set normal state (not reset)
                MDR_MIL_STD_15531->CONTROL = i;
                ADDR_OU_old = ADDR_OU = j;
            }
#endif    //USE_HARDWARE_ADDRESS
            else
            {
                MDR_MIL_STD_15531->CONTROL |= 1;    //reset MIL_STD_1553 controller
                ADDR_OU_old = j;
            }
        }
        
#ifdef USE_HARDWARE_ADDRESS
        i = MDR_PORTF->RXTX;
        trouble_OU_0 = ((i >> 10) & 1);
        trouble_user_2 = ((i >> 11) & 1);
        busy_user_3 = ((i >> 9) & 1);
        s_request_8 = ((i >> 12) & 1);
#endif    //USE_HARDWARE_ADDRESS

        bits = trouble_OU_0|(trouble_user_2 << 2)|(busy_user_3 << 3)|(s_request_8 << 8);
    
        if(bits != bits_old)
        {    
            bits_old = bits;
            while((MDR_MIL_STD_15531->STATUS & 1) == 0){}    //wait while MIL_STD_15531 is transmitting a data
            SW1 = (SW1 & 0xFEF2)|trouble_OU_0|(trouble_user_2 << 2)|(busy_user_3 << 3)|(s_request_8 << 8);
            MDR_MIL_STD_15531->StatusWord1 = SW1;
        }
    }
}

/**
  * @brief  Reports the source file name, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the source file name and line number.
       Ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    /* User can add his own implementation to report the source file name, line number and
       expression text.
       Ex: printf("Wrong parameters value (%s): file %s on line %d\r\n", expr, file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group MIL_STD_1553_MDR32F1QI_6 */

/** @} */ /* End of group __MDR32F1QI_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE main.c */



