/**
  ******************************************************************************
  * @file    lcd_ebc.h
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    17/03/2022
  * @brief   LCD header file for demo board.
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
  * FILE lcd_graph.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_GRAPH_H
#define __LCD_GRAPH_H

/* Includes ------------------------------------------------------------------*/
#include "lcd_ebc.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_LCD_GRAPH BSP LCD GRAPH
  * @{
  */

/** @defgroup BSP_LCD_GRAPH_Exported_Functions BSP LCD GRAPH Exported Functions
  * @{
  */

void vLcdPutPixel(uint32_t x, uint32_t y);
void vLcdPutLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void vLcdPutCircle(uint32_t xc, uint32_t yc, uint32_t r);

/** @} */ /* End of group BSP_LCD_GRAPH_Exported_Functions */

/** @} */ /* End of group BSP_LCD_GRAPH */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __LCD_GRAPH_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE lcd_graph.h */
