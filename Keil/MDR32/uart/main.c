
#include "main.h"


static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_us = 0; // microseconds
static volatile uint32_t Delay_counter_ms = 0; // milliseconds
static volatile uint32_t Delay_counter_ms_100 = 100;
static volatile uint32_t Timeout_counter_us = 0;
static volatile uint32_t Timeout_counter_ms = 0;
static volatile uint32_t Timeout_counter_ms_100 = 100;


	
// main function
int main(void)
{
	/* SysTick timer settings */
	SysTick_Init();
	
	/* Configure the system clock */
	SystemClock_Init();

	/* Initialize all configured peripherals */
	GPIO_Init();
	
	
	MDR_RST_CLK->PER_CLOCK |= UART2_CLK;
	
	
  while (1)
  {
		
		if (!Timeout_counter_ms) {
			//
			Timeout_counter_ms = 10;
		}
		
		if (!Delay_counter_ms) {
			MDR_PORTB->RXTX ^= LED_HL1;
			MDR_PORTB->RXTX ^= LED_HL2;	
			MDR_PORTC->RXTX ^= LED_HL3;
			Delay_counter_ms = 100;
		}
		
  }
	
}


/* SysTick timer settings */
void SysTick_Init(void) {	
	
	// divider (SysTick 24 bit) max 16 777 216
	SysTick->LOAD |= 800 - 1; // this 100KHz clock, if FCPU = 80MHz // 80000 - 1; //  this 1KHz clock, if FCPU = 80MHz // 16000 - 1; //  this 1KHz clock, if FCPU = 16MHz // 72000 - 1; //  this 1KHz clock, if FCPU = 72MHz
	
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	NVIC_EnableIRQ(SysTick_IRQn);
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


/* Configure the system clock */
void SystemClock_Init(void) {			
	// switching on an external generator 
	MDR_RST_CLK->HS_CONTROL |= RST_CLK_HS_CONTROL_HSE_ON; // (1<<0)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY)); // (1<<2)
	
	// switching CPU_C1 on HSE (external 16MHz without divide)
	MDR_RST_CLK->CPU_CLOCK |= 0x2<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos; // 0x2 - 0b10 - HSE (16MHz)
	// switching CPU_C1 on HSE (external 16MHz / 2)
	//MDR_RST_CLK->CPU_CLOCK |= 0x3<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos; // 0x3 - 0b11 - HSE/2 (8MHz)
	// switching HCLK on CPU_C3 (include external clock)
	MDR_RST_CLK->CPU_CLOCK |= 0x1<<RST_CLK_CPU_CLOCK_HCLK_SEL_Pos; // (1<<0)
	
	//PllInit(9); // 8MHz * 9 = 72MHz
	PllInit(5); // 16MHz * 5 = 80MHz
}


void PllInit(unsigned int pll_mul) {	
	// PLLCPUo = PLLCPUi * (PLLCPUMUL+1)  -  (pll_mul-1) multiplication by pll_mul
	MDR_RST_CLK->PLL_CONTROL |= (pll_mul-1)<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos; // pll_mul * FCPU_MHz
	
	// run module PLL
	MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_ON; // (1<<2)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY));
	
	//MDR_EEPROM->CMD |= 3<<EEPROM_CMD_DELAY_Pos; // 3 - after 100MHz // 4 - after 125MHz // 7 - after 200MHz 
	
	// include line CPU_C2 on PLL
	MDR_RST_CLK->CPU_CLOCK |= RST_CLK_CPU_CLOCK_CPU_C2_SEL;
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {	
	MDR_RST_CLK->PER_CLOCK |= PORTB_CLK | PORTC_CLK; // | PORTD_CLK
	
	MDR_PORTB->ANALOG |= LED_HL1 | LED_HL2;
	MDR_PORTB->OE |= LED_HL1 | LED_HL2; 
	MDR_PORTB->PWR |= (0x2<<(PB1*2)) | (0x2<<(PB2*2)); // 10 - middle
	
	MDR_PORTC->ANALOG |= LED_HL3;
	MDR_PORTC->OE |= LED_HL3; 
	MDR_PORTC->PWR |= (0x2<<(PC2*2)); // 10 - middle
	
	//MDR_PORTD->ANALOG |= BTN_USR;
	
	MDR_PORTB->RXTX |= LED_HL1;
	MDR_PORTB->RXTX &= ~(uint32_t)LED_HL2;	
	MDR_PORTC->RXTX |= LED_HL3;
	
}


void Delay_us(uint32_t Microseconds) {
	Delay_counter_us = Microseconds;
	while (Delay_counter_us != 0) ;
}


void Delay_ms(uint32_t Milliseconds) {
	Delay_counter_ms = Milliseconds;
	while (Delay_counter_ms != 0) ;
}



void SysTick_Handler(void) {
	SysTimer_ms++;	
	if (Delay_counter_us) {
		Delay_counter_us = Delay_counter_us - 10;
	}	
	if (Timeout_counter_us) {
		Timeout_counter_us = Timeout_counter_us - 10;
	}
	if (Delay_counter_ms) {
		if (Delay_counter_ms_100) {
			Delay_counter_ms_100--;
		}else {
			Delay_counter_ms--;
			Delay_counter_ms_100 = 100;
		}
	}	
	if (Timeout_counter_ms) {
		if (Timeout_counter_ms_100) {
			Timeout_counter_ms_100--;
		}else {
			Timeout_counter_ms--;
			Timeout_counter_ms_100 = 100;
		}
	}	
}

//
