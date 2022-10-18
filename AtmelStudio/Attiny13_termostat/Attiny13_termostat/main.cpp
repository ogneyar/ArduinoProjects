#include "main.h"



int main(void)
{
	//переменные для температуры
	uint16_t temp=0;
	uint16_t n1=0;
	uint16_t n2;
	//------------------------------
		
	DDRB|=(1<<PB2); // ПИН реле
	
	
	uint16_t t_max=eeprom_read_word((uint16_t*)15);
	uint16_t t_min=eeprom_read_word((uint16_t*)17);
		
	adc_setup();// настройка ацп
	

	t_max=change(t_max,0x76);
	t_min=change(t_min,0x38);
	eeprom_write_word((uint16_t*)15,t_max);
	eeprom_write_word((uint16_t*)17,t_min);
	
	

// 		

	
	DT_init12();
		
    while (1) 
    {
		temp=dt_check();
		n1=temp>>1;
		n2=temp>>3;
		temp=n1+n2;
		if (temp>=t_max)
		{
			PORTB&=~(1<<PB2);
		}
		if (temp<=t_min)
		{
			PORTB|=(1<<PB2);
		}
		indication(temp, 0x63);
    }
}

