
#include "MDR32F9Q2I.h"
#include "main.h"

static uint32_t sys_tick_flag = 0;

void GpioInit(void);
void ClockInit(void);
void SysTick_Handler(void);

int main (void)
{
	GpioInit();
	ClockInit();
	
	// divider
	SysTick->LOAD |= 48000000 -1; // 48000 - 1  this 1KHz // 48000000 -1  this 1Hz
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	NVIC_EnableIRQ(SysTick_IRQn);
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
		
	while(1) 
	{
		if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
		//if (sys_tick_flag) {
			MDR_PORTB->RXTX ^= LED_HL1;
			MDR_PORTB->RXTX ^= LED_HL2;	
			MDR_PORTC->RXTX ^= LED_HL3;
		}
	}
	
}


void GpioInit(void){
	MDR_RST_CLK->PER_CLOCK |= PORTB_CLK | PORTC_CLK | PORTD_CLK;
	
	MDR_PORTB->ANALOG |= LED_HL1 | LED_HL2;
	MDR_PORTB->OE |= LED_HL1 | LED_HL2; 
	MDR_PORTB->PWR |= (0x2<<(PB1*2)) | (0x2<<(PB2*2)); // 10 - middle
	
	MDR_PORTC->ANALOG |= LED_HL3;
	MDR_PORTC->OE |= LED_HL3; 
	MDR_PORTC->PWR |= (0x2<<(PC2*2)); // 10 - middle
	
	MDR_PORTD->ANALOG |= BTN_USR;
	
	MDR_PORTB->RXTX |= LED_HL1;
	MDR_PORTB->RXTX &= ~(uint32_t)LED_HL2;	
	MDR_PORTC->RXTX |= LED_HL3;
}	

void ClockInit(void) {
	// switching on an external generator 
	MDR_RST_CLK->HS_CONTROL |= RST_CLK_HS_CONTROL_HSE_ON; // (1<<0)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY)); // (1<<2)
	
	// switching CPU_C1 on HSE
	MDR_RST_CLK->CPU_CLOCK |= 0x2<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos; // 0x3 - 0b11 - HSE/2  // 0x2 - 0b10 - HSE
	// switching HCLK on CPU_C3
	MDR_RST_CLK->CPU_CLOCK |= 0x1<<RST_CLK_CPU_CLOCK_HCLK_SEL_Pos; // (1<<0)
	
	// PLLCPUo = PLLCPUi * (PLLCPUMUL+1)  -  (3-1) multiplication by three times
	MDR_RST_CLK->PLL_CONTROL |= (3-1)<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos; // (2<<8) or (0b0010<<8) or 0b001000000000 or 0x0200 or (2<<0x100) or (1<<0x200) or (1<<9)
	
	// run module PLL
	MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_ON; // (1<<2)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY));
	
	// include line CPU_C2 on PLL
	MDR_RST_CLK->CPU_CLOCK |= RST_CLK_CPU_CLOCK_CPU_C2_SEL;
}

void SysTick_Handler(void) {
	sys_tick_flag = 1;
}

