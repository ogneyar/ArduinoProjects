
#include "MDR32F9Q2I.h"


int main(void)
{
	// switching on an external generator 
	MDR_RST_CLK->HS_CONTROL |= RST_CLK_HS_CONTROL_HSE_ON; // (1<<0)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY)); // (1<<2)
	
	// if 0x3 - 0b11 - HSE/2 (external 16MHz / 2 = 8MHz)
	// if 0x2 - 0b10 - HSE   (external 16MHz)
	MDR_RST_CLK->CPU_CLOCK |= 0x2<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos; // (1<<0) | (1<<1) or (0x3<<0) or 0x3
	
	MDR_RST_CLK->CPU_CLOCK |= 0x1<<RST_CLK_CPU_CLOCK_HCLK_SEL_Pos; // (1<<0)
	
	// PLLCPUo = PLLCPUi * (PLLCPUMUL+1)  -  (3-1) multiplication by three times
	MDR_RST_CLK->PLL_CONTROL |= (3-1)<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos; // 16 * 3 = 48MHz
	
	MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_ON; // (1<<2)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY));
	
	MDR_EEPROM->CMD |= 7<<EEPROM_CMD_DELAY_Pos; // (7<<3) or (0b111<<3) or (1<<3) | (1<<4) | (1<<5)
			
	// switching on PORTC & PORTD
	MDR_RST_CLK->PER_CLOCK |= (1<<23) | (1<<24);
	
	MDR_PORTD->ANALOG |= 0x20; // (1<<5) PD5
	MDR_PORTC->ANALOG |= 0x4; // (1<<2) PC2
	MDR_PORTC->OE 		|= 0x4; // (1<<2) PC2
	MDR_PORTC->PWR 		|= 0x1<<PORT_PWR2_Pos;//(0x1<<(PC2*2)); // 01 - lower
		
	volatile uint32_t wait = 0;
	static uint8_t flag = 0;
	static uint32_t pll_mul = 1;
	
	while(1)
	{
		wait++;
		//if (!wait) {
		if (wait == 1427<<5) {
			MDR_PORTC->RXTX ^= 0x4; // (1<<2) PC2
			wait = 0;
		}
		
		if (!(MDR_PORTD->RXTX & 0x20) && !flag) { // button pressed
			MDR_PORTC->RXTX &= ~(uint32_t)0x4;
			
			MDR_RST_CLK->CPU_CLOCK &= ~RST_CLK_CPU_CLOCK_CPU_C2_SEL; // (1<<2)
			
			pll_mul++;
			if (pll_mul > 15) pll_mul = 1;
			
			MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_RLD; // (1<<3)
			MDR_RST_CLK->PLL_CONTROL &= ~RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Msk;
			MDR_RST_CLK->PLL_CONTROL |= (pll_mul-1)<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos;
			MDR_RST_CLK->PLL_CONTROL &= ~RST_CLK_PLL_CONTROL_PLL_CPU_RLD; // (1<<3)
			
			while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY));
			
			MDR_RST_CLK->CPU_CLOCK |= RST_CLK_CPU_CLOCK_CPU_C2_SEL;
			flag = 1;
		}
		
		if ((MDR_PORTD->RXTX & 0x20) && flag) {
			flag = 0;
		}

	}
}
