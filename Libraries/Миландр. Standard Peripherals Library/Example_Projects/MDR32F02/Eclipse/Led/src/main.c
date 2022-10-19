/**
  ******************************************************************************
  * @file    Led/src/main.c
  * @author  Milandr Application Team
  * @version V1.0.2
  * @date    21/12/2020
  * @brief   Main program body.
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187_lib.h"
#include "MLDR187.h"

#include "MLDR187_gpio.h"
#include "MLDR187_rst_clk.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define	LED_PORT		MDR_PORTD
#define	LED_PORT_CLK	RST_CLK_PORTD
#define LED_PIN_0		PORT_Pin_0
#define LED_PIN_1		PORT_Pin_1
#define LED_PIN_2		PORT_Pin_2
#define LED_PIN_3		PORT_Pin_3

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;

uint32_t DelayCnt = 0;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Main function */
int main()
{
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW_4mA;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(LED_PORT, (LED_PIN_0 | LED_PIN_1 | LED_PIN_2 | LED_PIN_3), &PORT_InitStructure);
    PORT_SetReset(LED_PORT, LED_PIN_0, SET);
    PORT_SetReset(LED_PORT, LED_PIN_1, SET);
    PORT_SetReset(LED_PORT, LED_PIN_2, SET);
    PORT_SetReset(LED_PORT, LED_PIN_3, SET);

    while (1)
    {
        if (DelayCnt++ >= 0x00010000)
        {
            DelayCnt = 0;
            if (PORT_ReadPin(LED_PORT, LED_PIN_0) != 0)
                PORT_SetReset(LED_PORT, LED_PIN_0, RESET);
            else
                PORT_SetReset(LED_PORT, LED_PIN_0, SET);
        }
    }
}

