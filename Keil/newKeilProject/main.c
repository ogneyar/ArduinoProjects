
#include "MDR32F9x.h"

#define PB1 1
#define PB2 2
#define PC2 2
#define LED_HL1 (1<<PB1) // red
#define LED_HL2 (1<<PB2) // green
#define LED_HL3 (1<<PC2) // blue
#define PORTB_CLK (1<<22)
#define PORTC_CLK (1<<23)
#define PORTD_CLK (1<<24)

//static uint16_t i;

void GPIO_Init(void);

void GPIO_Init(void){
	MDR_RST_CLK->PER_CLOCK |= PORTB_CLK | PORTC_CLK;
	
	MDR_PORTB->OE |= LED_HL1 | LED_HL2; 
	MDR_PORTB->ANALOG |= LED_HL1 | LED_HL2;
	MDR_PORTB->PWR |= (0x1<<(PB1*2)) | (0x1<<(PB2*2)); // 01 - lower
	
	MDR_PORTC->OE |= LED_HL3; 
	MDR_PORTC->ANALOG |= LED_HL3;
	MDR_PORTC->PWR |= (0x1<<(PC2*2)); // 01 - lower
	
	MDR_PORTB->RXTX |= LED_HL1;
	MDR_PORTB->RXTX |= LED_HL2;	
	MDR_PORTC->RXTX |= LED_HL3;
}	

int main (void)
{

	GPIO_Init();
		
	while(1) 
	{
		/*MDR_PORTB->RXTX &= ~(unsigned int)LED_VD5; 
		for(i=0; i<10000; i++) __asm("nop");
		MDR_PORTB->RXTX |= (unsigned int)LED_VD5; 
		for(i=0; i<10000; i++) __asm("nop");*/
	}
	
}
