/**
  ******************************************************************************
  * @file    WDG_SoftReset/src/main.c
  * @author  Milandr Application Team
  * @version V1.0.0
  * @date    29/12/2021
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
#include "MLDR187_iwdg.h"
#include "MLDR187_wwdg.h"
#include "MLDR187_bkp.h"
#include "MLDR187_eeprom.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define	LED_PORT		MDR_PORTD
#define	LED_CLK_PORT	RST_CLK_PORTD
#define LED_1			PORT_Pin_0
#define LED_2			PORT_Pin_1
#define LED_3			PORT_Pin_2
#define LED_4			PORT_Pin_3

#define	BTN_PORT		MDR_PORTA
#define	BTN_CLK_PORT	RST_CLK_PORTA
#define BTN_DOWN		PORT_Pin_0
#define BTN_LEFT		PORT_Pin_1
#define BTN_RIGHT		PORT_Pin_2
#define BTN_UP			PORT_Pin_3

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint32_t DelayCnt = 0;

/* Private function prototypes -----------------------------------------------*/
void Setup_CPU_Clock(void);
void LedInit(void);
void ButtonInit(void);
void Delay(uint32_t wait_ticks);
void vError(void);
void IWDG_SoftReset(void);
void WWDG_SoftReset(void);
/* Private functions ---------------------------------------------------------*/

/* Main function */
int main()
{
	Setup_CPU_Clock();
	LedInit();
	ButtonInit();

    while (1)
    {
    	if(DelayCnt++ >= 20000)
    	{
            DelayCnt = 0;
            if (PORT_ReadPin(LED_PORT, LED_1) == 1)
                PORT_SetReset(LED_PORT, LED_1, RESET);
            else
                PORT_SetReset(LED_PORT, LED_1, SET);
    	}

        if (PORT_ReadPin(BTN_PORT, BTN_DOWN) == 0)
        {
        	/* Button debounce */
        	PORT_SetReset(LED_PORT, LED_2, RESET);
        	Delay(10000);
        	while(PORT_ReadPin(BTN_PORT, BTN_DOWN) == 0){}

        	/* IWDG Soft Reset */
        	IWDG_SoftReset();
        }

        if (PORT_ReadPin(BTN_PORT, BTN_UP) == 0)
        {
        	/* Button debounce */
        	PORT_SetReset(LED_PORT, LED_3, RESET);
        	Delay(10000);
        	while(PORT_ReadPin(BTN_PORT, BTN_UP) == 0){}

        	/* WWDG Soft Reset */
        	WWDG_SoftReset();
        }
    }
}

void IWDG_SoftReset(void)
{
	/* LSI Enable */
	RST_CLK_EnablePeripheralClock(RST_CLK_BKP, RST_CLK_Div1);
	if(BKP_GenState(bkpLsi) == DISABLE)
	{
		if(BKP_FreqGenCmd(bkpLsi, ENABLE, DISABLE) == DISABLE) // LSI EN for IWDG
			vError();
	}

	/* IWDG Enable - Reset after 2 ticks IWDG counter (~250 us)  */
	IWDG_SetupAndActivate(IWDG_PR_DIV_4, 0x1);

	/* Wait reset */
	while(1){}
}

void WWDG_SoftReset(void)
{
	/* WWDG Enable */
	WWDG_Init(RST_CLK_Div1, wwdgDiv_4096, 0x40, 0x7F, DISABLE);
	WWDG_EnableReset();

	/* Reloading counter outside window - Reset immediately */
	WWDG_SetNewCounter(0x7F);

	/* Wait reset */
	while(1){}
}

/* Frequencies setup */
void Setup_CPU_Clock(void)
{
	ErrorStatus erCode;
	RST_CLK_CpuSpeed_InitTypeDef    RST_CLK_CpuSpeed_InitStructure;

    MDR_RST_CLK->CPU_CLOCK &= RST_CLK_CPU_CLOCK_HCLKSEL_Msk;    // HCLK = HSI

    RST_CLK_EnablePeripheralClock(RST_CLK_EEPROM, RST_CLK_Div1);
    EEPROM_SetLatency(flashCoreSpeedUpTo60MHz);

    RST_CLK_CpuSpeed_InitStructure.hseState = RST_CLK_HseOscillator;
    RST_CLK_CpuSpeed_InitStructure.hseSpeed = 8000000;
    RST_CLK_CpuSpeed_InitStructure.cpuC1Src = RST_CLK_CpuC1SelHse;
    RST_CLK_CpuSpeed_InitStructure.pllState = RST_CLK_PllFromHse;
    RST_CLK_CpuSpeed_InitStructure.pllMult = 6;
    RST_CLK_CpuSpeed_InitStructure.cpuC2Src = RST_CLK_CpuC2SelPllCpu;
    RST_CLK_CpuSpeed_InitStructure.cpuC3Div = RST_CLK_Div1;
    RST_CLK_CpuSpeed_InitStructure.hclkSrc = RST_CLK_HclkSelCpuC3;
    erCode = RST_CLK_SetupCpuSpeed(&RST_CLK_CpuSpeed_InitStructure);
    if(erCode != SUCCESS)
    	vError();
    erCode = RST_CLK_SetupHsPeripheralClock(RST_CLK_Clk_PER1_C2, RST_CLK_ClkSrc_PLLCPU);
    if(erCode != SUCCESS)
        	vError();
}

void LedInit(void)
{
	PORT_InitTypeDef PORT_InitStructure;

	RST_CLK_EnablePeripheralClock(LED_CLK_PORT, RST_CLK_Div1);
	PORT_SetReset(LED_PORT, (LED_1 | LED_2 | LED_3 | LED_4), SET);

	PORT_StructInitDefault(&PORT_InitStructure);

    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW_4mA;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(LED_PORT, (LED_1 | LED_2 | LED_3 | LED_4), &PORT_InitStructure);

    // Blink Led

    PORT_SetReset(LED_PORT, (LED_1 | LED_2 | LED_3 | LED_4), RESET);
    Delay(500000);
    PORT_SetReset(LED_PORT, (LED_1 | LED_2 | LED_3 | LED_4), SET);
    Delay(500000);
}

void ButtonInit(void)
{
	PORT_InitTypeDef PORT_InitStructure;

	PORT_StructInitDefault(&PORT_InitStructure);

    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_PULL_DOWN   = PORT_PULL_DOWN_OFF;
    PORT_Init(BTN_PORT, (BTN_DOWN | BTN_LEFT | BTN_RIGHT | BTN_UP), &PORT_InitStructure);
}

void Delay(uint32_t wait_ticks)
{
    while(wait_ticks--)
	    asm("nop");
}

void vError(void)
{
	PORT_SetReset(LED_PORT, LED_4, RESET);
	Delay(500000);
	PORT_SetReset(LED_PORT, LED_4, SET);
	Delay(500000);
}

