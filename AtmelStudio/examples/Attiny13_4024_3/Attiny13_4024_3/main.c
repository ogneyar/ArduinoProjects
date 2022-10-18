#include "main.h"

int main(void)
{
	cd4024_ini();
    while (1) 
    {
		cd4024_set(85);
		_delay_ms(1000);
		cd4024_set(42);
		_delay_ms(1000);
	}
}

