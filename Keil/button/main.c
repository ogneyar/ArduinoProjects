
#include "MDR32F9x.h"

#define PB1 1
#define PB2 2
#define PC2 2
#define PD5 5
#define LED_HL1 (1<<PB1) // red
#define LED_HL2 (1<<PB2) // green
#define LED_HL3 (1<<PC2) // blue
#define BTN_USR (1<<PD5) // blue
#define PORTB_CLK (1<<22)
#define PORTC_CLK (1<<23)
#define PORTD_CLK (1<<24)

void GPIO_Init(void);


int main (void)
{
	
	uint16_t intervalRising = 250;//500;//1000; 
	uint16_t intervalFalling = 0;
	
	uint16_t i;

	GPIO_Init();
		
	while(1) 
	{
		if (!(MDR_PORTD->RXTX & BTN_USR)) intervalRising = 100;
		else intervalRising = 500;
						
		while(intervalRising) {			
			MDR_PORTB->RXTX |= LED_HL1;
			MDR_PORTB->RXTX |= LED_HL2;	
			MDR_PORTC->RXTX |= LED_HL3;
			
			for(i=0; i<intervalFalling; i++) __asm("nop");
			
			MDR_PORTB->RXTX &= ~(unsigned int)LED_HL1;
			MDR_PORTB->RXTX &= ~(unsigned int)LED_HL2;	
			MDR_PORTC->RXTX &= ~(unsigned int)LED_HL3;
			
			for(i=0; i<intervalRising; i++) __asm("nop");

			intervalRising--;
			intervalFalling++;    
		}
		
		while(intervalFalling) {    			
			MDR_PORTB->RXTX |= LED_HL1;
			MDR_PORTB->RXTX |= LED_HL2;	
			MDR_PORTC->RXTX |= LED_HL3;
			
			for(i=0; i<intervalFalling; i++) __asm("nop");
			
			MDR_PORTB->RXTX &= ~(unsigned int)LED_HL1;
			MDR_PORTB->RXTX &= ~(unsigned int)LED_HL2;	
			MDR_PORTC->RXTX &= ~(unsigned int)LED_HL3;
			
			for(i=0; i<intervalRising; i++) __asm("nop");
				
			intervalRising++;
			intervalFalling--;
		}
	}
	
}


void GPIO_Init(void){
	MDR_RST_CLK->PER_CLOCK |= PORTB_CLK | PORTC_CLK | PORTD_CLK;
	
	MDR_PORTB->ANALOG |= LED_HL1 | LED_HL2;
	MDR_PORTB->OE |= LED_HL1 | LED_HL2; 
	MDR_PORTB->PWR |= (0x1<<(PB1*2)) | (0x1<<(PB2*2)); // 01 - lower
	
	MDR_PORTC->ANALOG |= LED_HL3;
	MDR_PORTC->OE |= LED_HL3; 
	MDR_PORTC->PWR |= (0x1<<(PC2*2)); // 01 - lower
	
	MDR_PORTD->ANALOG |= BTN_USR;
	
	MDR_PORTB->RXTX |= LED_HL1;
	MDR_PORTB->RXTX |= LED_HL2;	
	MDR_PORTC->RXTX |= LED_HL3;
}	

