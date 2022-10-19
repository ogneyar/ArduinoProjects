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
#include "demoboard.h"
#include "adcsync.h"
#include "pwm.h"


#include <string.h>
#include <stdlib.h>
#include <math.h>

/** @addtogroup  __MDR1986VK01_StdPeriph_Examples MDR1986VK01 StdPeriph Examples
 *  @{
 */

/** @addtogroup __MDR1986VK01_EVALBOARD MDR1986VK01 Demo Board
 *  @{
 */

/** @addtogroup pwm_sync_adc pwm_sync_adc
 *  @{
 */

#define PWM_COUNTER             1000

uint32_t ulClkFreq;
uint32_t adcSampleRate;


ADC_CH_TypeDef adcCh;
PWM_Conf_TypeDef pwmCnf;
PORT_InitTypeDef Port;
PORT_InitTypeDef MarkerPort;


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

//    CLK_SetPllClk( &MDR_CLK->PLL[0], PLL_CLK_HSE0, 50000000 );
//    CLK_PllState( &MDR_CLK->PLL[0], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[0] ) )
//        while(1){}

//    CLK_SetPllClk( &MDR_CLK->PLL[2], PLL_CLK_HSE0, 50000000 );
//    CLK_PllState( &MDR_CLK->PLL[2], ENABLE );
//    if( !CLK_PLLWaitReady( &MDR_CLK->PLL[2] ) )
//        while(1){}

    //CLK_SetSystemClock( MAX_CLK_PLL0 );
    CLK_SetSystemClock( MAX_CLK_HSE0 );
    
}

static void vShifterInit( void )
{
    PORT_InitTypeDef ShifterPort;
    PORT_StructInit( &ShifterPort );

    MDR_PORTA->KEY = 0x8555AAA1;

    ShifterPort.PORT_Pin     = PORT_Pin_31;
    ShifterPort.PORT_SOE     = PORT_SOE_OUT;
		ShifterPort.PORT_SFUNC   = PORT_SFUNC_PORT;
		ShifterPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    ShifterPort.PORT_SPWR    = PORT_SPWR_10;

    PORT_Init( MDR_PORTA, &ShifterPort );

    BUF_OE_OFF;
}

int main()
{
    ClockInit();
    
    MDR_PORTA->KEY = 0x8555AAA1;
    MDR_PORTB->KEY = 0x8555AAA1;
    MDR_PORTC->KEY = 0x8555AAA1;
    MDR_PORTD->KEY = 0x8555AAA1;

    PORT_StructInit( &Port );
    PORT_StructInit( &MarkerPort );
    
    MarkerPort.PORT_Pin     = PORT_Pin_1;
    MarkerPort.PORT_SOE     = PORT_SOE_OUT;
    MarkerPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    MarkerPort.PORT_SPWR    = PORT_SPWR_10;

    PORT_Init( MDR_PORTB, &MarkerPort );
    
    /*
    PWM1_H - PB0  - 12 - MDR_PWM0
    PWM2_H - PB10 - 11 - MDR_PWM1
    PWM3_H - PC29 - 11 - MDR_PWM2
    */
    Port.PORT_Pin     = PORT_Pin_0 ;
    Port.PORT_SOE     = PORT_SOE_OUT;
	Port.PORT_SFUNC   = PORT_SFUNC_12;
	Port.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    Port.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( MDR_PORTB, &Port );
    
    Port.PORT_Pin     = PORT_Pin_10;
    Port.PORT_SFUNC   = PORT_SFUNC_11;
    PORT_Init( MDR_PORTB, &Port );
    
    Port.PORT_Pin     = PORT_Pin_29;
    Port.PORT_SFUNC   = PORT_SFUNC_11;
    PORT_Init( MDR_PORTC, &Port );
	
    ulClkFreq = CLK_GetSourceClk( CLK_SOURCE_MAX_CLK );
    
    AdcInitBg();
    
    AdcInitClk( MDR_ADC0, CLK_SOURCE_HSE0, 0 );
    AdcInitClk( MDR_ADC1, CLK_SOURCE_HSE0, 0 );
    AdcInitClk( MDR_ADC2, CLK_SOURCE_HSE0, 0 );
    
    adcSampleRate = AdcGetSampleRate( MDR_ADC1, 0 );
    
    AdcInitChStruct( &adcCh );
    adcCh.Adc0ConvChP[ 0 ] = ADC_CH6;
    adcCh.Adc0ConvChP[ 1 ] = ADC_CH0;
    adcCh.Adc0ConvCnt = 2;
    adcCh.Adc1ConvChP[ 0 ] = ADC_CH7;
    adcCh.Adc1ConvCnt = 1;   
    
    adcCh.Adc0ConvTrig = ADC10_EPWMxSOCA_1;
    AdcInit( MDR_ADC1, &adcCh ); 
    
    AdcInitChStruct( &adcCh ); 
    adcCh.Adc0ConvChP[ 0 ] = ADC_CH1;
    adcCh.Adc0ConvCnt = 1;
    
    adcCh.Adc0ConvTrig = ADC20_EPWMxSOCA_1;
    AdcInit( MDR_ADC2, &adcCh );


    PwmInitClk( MDR_PWM0, 0 );
    PwmInitClk( MDR_PWM1, 0 );
    PwmInitClk( MDR_PWM2, 0 );
    PwmInitClk( MDR_PWM3, 0 );
    
    PwmInitConfStruct( &pwmCnf );
    
    pwmCnf.ulPeriod = PWM_COUNTER;
    pwmCnf.ulPhase = 0;
    pwmCnf.ucCountMode = CTR_CNT_UP_DOWN;
    pwmCnf.ucSyncOutSelect = SYNCOSEL_CTR_ZERO;
    
    pwmCnf.xEventA[0].ucEventSel = EVENT_EQ_CMPA;
    pwmCnf.xEventA[0].ucActionInc = EVENT_ACT_SET;
    pwmCnf.xEventA[0].ucActionDec = EVENT_ACT_RESET;
    
    PwmInit( MDR_PWM0, &pwmCnf );
    
    pwmCnf.ucSyncOutSelect = SYNCOSEL_DIRECT;
    pwmCnf.eEnableSyncPhase = ENABLE;
    
    pwmCnf.eEnableSocA = ENABLE;
    pwmCnf.ucSocAEvent = ETSEL_EVENT_CTR_ZERO;
    
    PwmInit( MDR_PWM1, &pwmCnf );
  
    pwmCnf.eEnableSocA = DISABLE;
    pwmCnf.ucSocAEvent = ETSEL_EVENT_NONE;
    
    PwmInit( MDR_PWM2, &pwmCnf );
    
    pwmCnf.ulPeriod = PWM_COUNTER * 2;
    pwmCnf.ulPhase = 0;
    pwmCnf.ulCmpA = PWM_COUNTER * 2 - 200;
    pwmCnf.ucCountMode = CTR_CNT_UP;
    pwmCnf.ucSyncOutSelect = SYNCOSEL_CTR_ZERO;
    
    pwmCnf.eEnableIrq = ENABLE;
    pwmCnf.ucIrqEvent = ETSEL_EVENT_CTR_EQ_CMPA_INC;
    
    PwmInit( MDR_PWM3, &pwmCnf );
    
    MDR_PWM1->CMPA = PWM_COUNTER - 500;
    MDR_ADC1->INT_CTRL_ADC = 1 << 3;
    NVIC_SetPriority( ADC10_IRQn, 0 );
    NVIC_EnableIRQ( ADC10_IRQn );

    while( 1 )
    {
			PORT_ResetBits(MDR_PORTB, PORT_Pin_1);
			__NOP();
    }
	
}

void ADC01_IRQHandler( void )
{
	PORT_SetBits(MDR_PORTB, PORT_Pin_1);
  __NOP();
}

/** @} */ /* End of group pwm_sync_adc */

/** @} */ /* End of group __MDR1986VK01_EVALBOARD */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2022 Milandr *********/

/* END OF FILE main.c */


