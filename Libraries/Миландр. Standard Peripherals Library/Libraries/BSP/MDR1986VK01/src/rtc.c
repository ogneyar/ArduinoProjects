/**
  ******************************************************************************
  * @file    rtc.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    14/04/2022
  * @brief   RTC source file for demo board.
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
  * FILE rtc.c
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_RTC BSP_RTC
  * @{
  */

/** @defgroup BSP_RTC_Exported_Functions BSP_RTC Exported Functions
  * @{
  */

void InitRtc( void )
{
    MDR_CLK->LSE.CLK = 0x00100000;
    while(! MDR_CLK->LSE.STAT & (1 << 20)){}

    MDR_BKP->REG_63_CLK0 |= 0x0000000A;//8
    MDR_BKP->REG_63_CLK1 |= 0x0000000A;
    MDR_BKP->REG_63_CLK2 |= 0x0000000A;
    while(! (MDR_BKP->REG_63_CLK0 & 1)){}

    //RTC_ReadyWait();
    MDR_BKP->REG_64_TMR0 = 0x00000401;//0x00000C01;
    MDR_BKP->REG_64_TMR1 = 0x00000401;
    MDR_BKP->REG_64_TMR2 = 0x00000401;
    //RTC_ReadyWait();
    MDR_BKP->RTC_PRL_TMR0 = RTC_PRESCALER_VALUE;
    //RTC_ReadyWait();
    MDR_BKP->RTC_PRL_TMR1 = RTC_PRESCALER_VALUE;
    //RTC_ReadyWait();
    MDR_BKP->RTC_PRL_TMR2 = RTC_PRESCALER_VALUE;

    //RTC_ReadyWait();
    MDR_BKP->REG_64_TMR0 |= (RTC_CalibratorValue & 0x3F) << 2;

    //RTC_ReadyWait();
    MDR_BKP->REG_64_TMR0 |= 0x00000800;//0x00000C01;

    //RTC_ReadyWait();
    MDR_BKP->RTC_CS_TMR0 |= 0x00000010;
    NVIC_EnableIRQ(BKP_IF_IRQn);
}


void setTime( tTime time )
{
    RTC_ReadyWait();
    MDR_BKP->REG_64_TMR0 &= ~0x00000800;
    uint32_t tmp = MDR_BKP->RTC_CNT_TMR0 / 3600 / 24;
    tmp = tmp*3600*24 + time.sec + 60*time.min + 3600*time.hour;

    RTC_ReadyWait();
    MDR_BKP->RTC_CNT_TMR0 = tmp;
    RTC_ReadyWait();
    MDR_BKP->RTC_CNT_TMR1 = tmp;
    RTC_ReadyWait();
    MDR_BKP->RTC_CNT_TMR2 = tmp;

    RTC_ReadyWait();
    MDR_BKP->REG_64_TMR0 |= 0x00000800;
    RTC_ReadyWait();
}


tDate roundDay( tDate date )
{
    if( (date.month == 1 || date.month == 3 || date.month == 5 ||
         date.month == 7 || date.month == 8 || date.month == 10 ||
         date.month == 12 ) && date.day > 31)
    {
        date.day = (date.day - 1) % 31 + 1;
    }
    if((date.month == 4 || date.month == 6 ||
        date.month == 9 || date.month == 11 ) && date.day > 30 )
        date.day = (date.day - 1) % 30 + 1;
    if( date.month == 2 )
    {
        if( (date.year % 4 == 0) && date.day > 29)
            date.day = (date.day - 1) % 29 + 1;
        if( (date.year % 4 != 0) && date.day > 28)
            date.day = (date.day - 1) % 28 + 1;
    }
    return date;
}


void setDate( tDate new_date )
{
    if((new_date.month == 4 || new_date.month == 6 ||
        new_date.month == 9 || new_date.month == 11 ) && new_date.day > 30 )
        new_date.day = 30;
    if( new_date.month == 2 )
    {
        if( (new_date.year % 4 == 0) && new_date.day > 29)
            new_date.day = 29;
        if( (new_date.year % 4 != 0) && new_date.day > 28)
            new_date.day = 28;
    }

    uint32_t days = 0;
    tDate date;
    date.day = 1;
    date.month = 1;
    date.year = 2016;
    while( !((date.day == new_date.day) &&
             (date.month == new_date.month) &&
             (date.year == new_date.year))  && date.year < 2101)
    {
        date.day++;
        days++;
        if( (date.month == 1 || date.month == 3 || date.month == 5 ||
             date.month == 7 || date.month == 8 || date.month == 10 ||
             date.month == 12 ) && date.day > 31)
        {
            date.day = 1;
            date.month++;
            if(date.month > 12)
            {
                date.month = 1;
                date.year++;
            }
        }
        if((date.month == 4 || date.month == 6 || date.month == 9 ||
             date.month == 11 ) && date.day > 30)
        {
            date.day = 1;
            date.month++;
        }
        if(date.month == 2)
        {
            if( (date.year % 4 == 0) && date.day > 29)
            {
                date.day = 1;
                date.month++;
            }
            if( (date.year % 4 != 0) && date.day > 28)
            {
                date.day = 1;
                date.month++;
            }
        }
    }

    RTC_ReadyWait();
    MDR_BKP->REG_64_TMR0 &= ~0x00000800;
    uint32_t tmp = MDR_BKP->RTC_CNT_TMR0 % (3600 * 24);
    tmp += days*3600*24;

    RTC_ReadyWait();
    MDR_BKP->RTC_CNT_TMR0 = tmp;
    RTC_ReadyWait();
    MDR_BKP->RTC_CNT_TMR1 = tmp;
    RTC_ReadyWait();
    MDR_BKP->RTC_CNT_TMR2 = tmp;

    RTC_ReadyWait();
    MDR_BKP->REG_64_TMR0 |= 0x00000800;
    RTC_ReadyWait();
}


uint32_t get_fattime( void )
{
    return 0;
}


tTime getTime()
{
    uint32_t tmp = MDR_BKP->RTC_CNT_TMR0;
    tTime time;
    time.sec = tmp % 60;
    time.min = (tmp / 60) % 60;
    time.hour = (tmp / 3600) % 24;

    return time;
}


tDate getDate()
{
    uint32_t tmp = MDR_BKP->RTC_CNT_TMR0 / 3600 / 24;
    tDate date;
    date.day = 1;
    date.month = 1;
    date.year = 2016;
    while(tmp--)
    {
        date.day++;
        if( (date.month == 1 || date.month == 3 || date.month == 5 ||
             date.month == 7 || date.month == 8 || date.month == 10 ||
             date.month == 12 ) && date.day > 31)
        {
            date.day = 1;
            date.month++;
            if(date.month > 12)
            {
                date.month = 1;
                date.year++;
            }
        }
        if((date.month == 4 || date.month == 6 || date.month == 9 ||
             date.month == 11 ) && date.day > 30)
        {
            date.day = 1;
            date.month++;
        }
        if(date.month == 2)
        {
            if( (date.year % 4 == 0) && date.day > 29)
            {
                date.day = 1;
                date.month++;
            }
            if( (date.year % 4 != 0) && date.day > 28)
            {
                date.day = 1;
                date.month++;
            }
        }
    }

    return date;
}


void BKP_IF_IRQHandler( void )
{
    
}

/** @} */ /* End of group BSP_RTC_Exported_Functions */

/** @} */ /* End of group BSP_RTC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE rtc.c */


