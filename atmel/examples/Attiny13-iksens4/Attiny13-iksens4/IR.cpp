#include "main.h"
#include "IR.h"



void IR_ini(void) {
	// –ежим —“—  38 к√ц дл€ 9.6ћгц
	//частота сигнала=F_CPU / 2*делитель*(1+OCR0A)

	
	GIMSK|=(1<<PCIE); // пинчандже вкл.
	PCMSK|=(1<<PCINT1); // PCINT0 ака PB1 вкл.
	
	TCCR0A |=(1<<WGM01); // –ежим CTC, сброс при совпадении
	//TCCR0A |= (1<<COM0A0); // —осто€ние вывода OC0A мен€етс€ на противоположное при равенстве регистров TCNT0 и OCR0A.
	TCCR0B |= (1<<CS00);  // без делител€
	OCR0A = 126; // регистр сравнени€
	
	TIMSK0 |= (1<< OCIE0A);// прерывание по совпадению оцра
	
	DDRB|=(1<<TX); // пин передатчика
	DDRB&=~(1<<RX); // пин приемника

}

//--------- отправка »  ----------------------
void IRR_0 (void) {
	TCCR0A |= (1<<COM0A0);
	_delay_us(100);
	TCCR0A &=~(1<<COM0A0);
	_delay_us(500);
}

void IRR_1(void) {
	TCCR0A |= (1<<COM0A0);
	_delay_us(500);
	TCCR0A &=~(1<<COM0A0);
	_delay_us(500);
}


void IRR_code(uint8_t code) {
	uint8_t a,i;
	a=1; // 0b0000001
	for (i=0; i<8; i++)
	{
		if ((code&a)==0) {
			IRR_0();	//ноль
			}  else {
			IRR_1(); //единица
		}
		a=a<<1;
	}
}
//-------------------------------------------


// статус сенсора
uint8_t status(uint8_t cod, uint8_t null)
{
	static uint8_t COUNT_ok; // счетчик отражений
	static uint8_t COUNT_er; // счетчик не отражений
	if (null) // обнул€шка статиков
	{
		COUNT_er=0;
		COUNT_ok=0;
		return 0;
	}
	
	if (cod!=IR_CODE)
	{
		if (COUNT_er<OTR_OFF) { COUNT_er++;}
		} else {
		if (COUNT_ok<OTR_ON) {COUNT_ok++; COUNT_er=0;}
	}
	
	if (COUNT_er==OTR_OFF)
	{
		COUNT_ok=0;
		COUNT_er=0;
	}
	
	if (COUNT_ok==OTR_ON)
	{
		return 1;
	}
	
	return 0;
}
//-----------------------------------------------------------------------------------------------------------

//--------------Ёмул€ци€ отправки »  кода----------------------
void IR_0 (void) {
	PORTB|=(1<<TX);
	_delay_us(100);
	PORTB&=~(1<<TX);
	_delay_us(500);
}

void IR_1(void) {
	PORTB|=(1<<TX);
	_delay_us(500);
	PORTB&=~(1<<TX);
	_delay_us(500);
}


void IR_code(uint8_t code) {
	uint8_t a,i;
	a=1; // 0b0000001
	for (i=0; i<8; i++)
	{
		if ((code&a)==0) {
			IR_0();	//ноль
			}  else {
			IR_1(); //единица
		}
		a=a<<1;
	}
}
//----------------------------------------------------