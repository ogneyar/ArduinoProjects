/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Main program body.
 *********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 touchkey detection routine:
 This example demonstrates channel 2 (PA2), which is a Touchkey application.

*/

#include "debug.h"

/*********************************************************************
 * @fn      Touch_Key_Init
 *
 * @brief   Initializes Touch Key collection.
 *
 * @return  none
 */
void Adc_Init( void )
{
    ADC_InitTypeDef ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1, ENABLE );
    RCC_ADCCLKConfig( RCC_PCLK2_Div8 );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init( GPIOA, &GPIO_InitStructure );

    ADC_DeInit( ADC1 );
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init( ADC1, &ADC_InitStructure );

    ADC_Cmd( ADC1, ENABLE );

    ADC_ResetCalibration( ADC1 );
    while( ADC_GetResetCalibrationStatus( ADC1 ) );
    ADC_StartCalibration( ADC1 );
    while( ADC_GetCalibrationStatus( ADC1 ) );

    ADC1->CTLR1 |= 0x01000000;   //Enable Touch Key
}

/*********************************************************************
 * @fn      Touch_Key_Adc
 *
 * @brief   Returns ADCx conversion result data.
 *
 * @param   ch - ADC channel.
 *            ADC_Channel_0 - ADC Channel0 selected.
 *            ADC_Channel_1 - ADC Channel1 selected.
 *            ADC_Channel_2 - ADC Channel2 selected.
 *            ADC_Channel_3 - ADC Channel3 selected.
 *            ADC_Channel_4 - ADC Channel4 selected.
 *            ADC_Channel_5 - ADC Channel5 selected.
 *            ADC_Channel_6 - ADC Channel6 selected.
 *            ADC_Channel_7 - ADC Channel7 selected.
 *            ADC_Channel_8 - ADC Channel8 selected.
 *            ADC_Channel_9 - ADC Channel9 selected.
 *            ADC_Channel_10 - ADC Channel10 selected.
 *            ADC_Channel_11 - ADC Channel11 selected.
 *            ADC_Channel_12 - ADC Channel12 selected.
 *            ADC_Channel_13 - ADC Channel13 selected.
 *            ADC_Channel_14 - ADC Channel14 selected.
 *            ADC_Channel_15 - ADC Channel15 selected.
 *
 * @return  val - The Data conversion value.
 */
u16 Touch_Key_Adc( u8 ch )
{
    u16 val;

    //Set Charging or Discharge Time
    ADC1->IDATAR1 = 0x30;    //Discharge Time
    ADC_RegularChannelConfig( ADC1, ch, 1, ADC_SampleTime_13Cycles5 );	//Charging Time

    ADC1->RDATAR = 0x00;     //Write Value, Start Samping
    while( !ADC_GetFlagStatus( ADC1, ADC_FLAG_EOC ) );

    val = ADC_GetConversionValue( ADC1 );

    return val;
}

/*********************************************************************
 * @fn      Get_Adc_Average
 *
 * @brief   Returns ADCx conversion result average data.
 *
 * @param   ch - ADC channel.
 *            ADC_Channel_0 - ADC Channel0 selected.
 *            ADC_Channel_1 - ADC Channel1 selected.
 *            ADC_Channel_2 - ADC Channel2 selected.
 *            ADC_Channel_3 - ADC Channel3 selected.
 *            ADC_Channel_4 - ADC Channel4 selected.
 *            ADC_Channel_5 - ADC Channel5 selected.
 *            ADC_Channel_6 - ADC Channel6 selected.
 *            ADC_Channel_7 - ADC Channel7 selected.
 *            ADC_Channel_8 - ADC Channel8 selected.
 *            ADC_Channel_9 - ADC Channel9 selected.
 *            ADC_Channel_10 - ADC Channel10 selected.
 *            ADC_Channel_11 - ADC Channel11 selected.
 *            ADC_Channel_12 - ADC Channel12 selected.
 *            ADC_Channel_13 - ADC Channel13 selected.
 *            ADC_Channel_14 - ADC Channel14 selected.
 *            ADC_Channel_15 - ADC Channel15 selected.
 *
 * @return  val - The Data conversion value.
 */
u16 Get_Adc_Average( u8 ch, u8 times )
{
    u32 temp_val = 0;
    u8 t;
    u16 val;

    for( t = 0; t < times; t++ )
    {
        temp_val += Touch_Key_Adc( ch );
    }

    val = temp_val / times;

    return val;
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main( void )
{
    u16 ADC_val;

    Delay_Init();
    USART_Printf_Init( 115200 );
    printf( "SystemClk:%d\r\n", SystemCoreClock );

    Adc_Init();

    while( 1 )
    {
        ADC_val = Get_Adc_Average( ADC_Channel_2, 10 );  //Channel 2
        printf( "TouchKey:%04d\r\n", ADC_val );
        Delay_Ms( 2 );
    }
}

