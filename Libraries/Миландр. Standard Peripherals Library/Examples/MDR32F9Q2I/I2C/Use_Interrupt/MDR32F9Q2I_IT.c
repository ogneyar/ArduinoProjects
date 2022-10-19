/**
  ******************************************************************************
  * @file    MDR32F9Q2I_IT.c
  * @author  Milandr Application Team
  * @version V2.0.0
  * @date    03/08/2021
  * @brief   Main Interrupt Service Routines.
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
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Q2I_IT.h"
#include "MDR32FxQI_i2c.h"

/* Private variables ---------------------------------------------------------*/
extern uint32_t i2c_flag;
extern uint32_t tran_dat;

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : I2C_IRQHandler
* Description    : This function handles I2C global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_IRQHandler(void)
{
    if (I2C_GetITStatus() == SET)
    {
        I2C_ClearITPendingBit();
        i2c_flag = SET;

        if (I2C_GetFlagStatus(I2C_FLAG_BUS_BUSY) == SET)
        {
            tran_dat++;
        }
        else
        {
            tran_dat = 0;
        }
    }
}

/******************* (C) COPYRIGHT 2022 Milandr *******************************/

/* END OF FILE MDR32F9Q2I_IT.c */



