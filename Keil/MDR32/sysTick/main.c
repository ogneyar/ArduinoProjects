
#include "MDR32F9Q2I.h"
#include "main.h"

static uint32_t sys_tick_flag = 0;

void GpioInit(void);
void ClockInit_8MHz_ext(void);
void PllInit(unsigned int);
void SysTick_Handler(void);


int main (void)
{
	GpioInit();
	ClockInit_8MHz_ext();
	PllInit(2); // pll_mul = 2
	
	// divider (SysTick 24 bit) max 16 777 216
	SysTick->LOAD |= 16000000 -1; // 16000 - 1  this 1KHz // 16000000 -1  this 1Hz
	
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	NVIC_EnableIRQ(SysTick_IRQn);
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
		
	while(1) 
	{
		//if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) {
		if (sys_tick_flag) {
			MDR_PORTB->RXTX ^= LED_HL1;
			MDR_PORTB->RXTX ^= LED_HL2;	
			MDR_PORTC->RXTX ^= LED_HL3;
			sys_tick_flag = 0;
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

void ClockInit_8MHz_ext(void) {
	// switching on an external generator 
	MDR_RST_CLK->HS_CONTROL |= RST_CLK_HS_CONTROL_HSE_ON; // (1<<0)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY)); // (1<<2)
	
	// switching CPU_C1 on HSE (external 16MHz without divide)
	//MDR_RST_CLK->CPU_CLOCK |= 0x2<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos; // 0x2 - 0b10 - HSE (16MHz)
	// switching CPU_C1 on HSE (external 16MHz / 2)
	MDR_RST_CLK->CPU_CLOCK |= 0x3<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos; // 0x3 - 0b11 - HSE/2 (8MHz)
	// switching HCLK on CPU_C3 (include external clock)
	MDR_RST_CLK->CPU_CLOCK |= 0x1<<RST_CLK_CPU_CLOCK_HCLK_SEL_Pos; // (1<<0)

}

void PllInit(unsigned int pll_mul) {	
	// PLLCPUo = PLLCPUi * (PLLCPUMUL+1)  -  (pll_mul-1) multiplication by pll_mul
	MDR_RST_CLK->PLL_CONTROL |= (pll_mul-1)<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos; // pll_mul * 8MHz
	
	// run module PLL
	MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_ON; // (1<<2)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY));
	
	//MDR_EEPROM->CMD |= 3<<EEPROM_CMD_DELAY_Pos; // 3 - after 100MHz // 4 - after 125MHz // 7 - after 200MHz 
	
	// include line CPU_C2 on PLL
	MDR_RST_CLK->CPU_CLOCK |= RST_CLK_CPU_CLOCK_CPU_C2_SEL;
}

void SysTick_Handler(void) {
	sys_tick_flag = 1;
}

