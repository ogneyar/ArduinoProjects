#include "MDR32F9x.h"

//#include "MDR32Fx.h"


#define LED_VD5 (1<<0) 
#define PORTB_CLK (1UL<<22)

static uint16_t i;

void GPIO_Init(void);

void GPIO_Init(void){
	MDR_RST_CLK->PER_CLOCK = PORTB_CLK;
	
	MDR_PORTB->OE = LED_VD5; 
	MDR_PORTB->FUNC = 0x00000000; 
	MDR_PORTB->ANALOG = 0x0000FFFF; 
	MDR_PORTB->PULL = (LED_VD5) << 16; 
	MDR_PORTB->PD = ~(uint32_t)(LED_VD5); 
	MDR_PORTB->PWR = 0x55555555; 
	MDR_PORTB->GFEN = 0; 
}	

int main (void)
{

	GPIO_Init();
	
	while(1) 
	{
		MDR_PORTB->RXTX &= ~(unsigned int)LED_VD5; 
		for(i=0; i<10000; i++) __asm("nop");
		MDR_PORTB->RXTX |= (unsigned int)LED_VD5; 
		for(i=0; i<10000; i++) __asm("nop");
	}
	
	//return 0;
	
}
