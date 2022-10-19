/**
  ******************************************************************************
  * @file    rtc.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   RTC header file for demo board.
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
  * FILE rtc.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H
#define __RTC_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_port.h"
#include "MDR1986VK01.h"
#include "MDR1986VK01_clk.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_RTC BSP_RTC
  * @{
  */

/** @defgroup BSP_RTC_Static_Functions BSP_RTC Static Functions
  * @{
  */

static void  RTC_ReadyWait()
{
    while( (MDR_BKP->RTC_CS_TMR0 | MDR_BKP->RTC_CS_TMR1 | MDR_BKP->RTC_CS_TMR2) & (1 << 6) )
    {
    }
}

/** @} */ /* End of group BSP_RTC_Static_Functions */

/** @defgroup BSP_RTC_Exported_Types BSP_RTC Exported Types
  * @{
  */

typedef struct
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
}tTime;

typedef struct
{
    uint8_t day;
    uint8_t month;
    uint16_t year;
}tDate;

/** @} */ /* End of group BSP_RTC_Exported_Types */

/** @defgroup BSP_RTC_Exported_Functions BSP_RTC Exported Functions
  * @{
  */

void InitRtc( void );

void setTime( tTime time );
void setDate( tDate date );

tDate roundDay( tDate date );

tTime getTime( void );
tDate getDate( void );

/** @} */ /* End of group BSP_RTC_Exported_Functions */

/** @} */ /* End of group BSP_RTC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __RTC_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE rtc.h */


