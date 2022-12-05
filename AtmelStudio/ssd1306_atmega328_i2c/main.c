#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ssd1306.h"
#include "twi_driver.h"

volatile uint8_t m_sec, sec, min;
uint8_t lock, start_stop = 0;

// ���������� �� ��������� T1, ������ 0,1�
ISR(TIMER1_COMPA_vect)
{   
m_sec++;  // ����������� �������
if(m_sec >= 10)
{
sec++; // ����������� ������� 
m_sec = 0;
}
if(sec >= 60)
{
min++; // ����������� ������
m_sec = 0; sec = 0;
}
if(min >= 60) // ���� ������ ��� �������� ���
{
m_sec = 0; sec = 0; min = 0; 
}

}

int main(void)
{
// ��������� ������ �����/������
DDRC &= ~(1 << PC1)|(1 << PC0); // ����� ������
PORTC |= (1 << PC1)|(1 << PC0);

// ��������� ������� 1
OCR1A  = 3125; // ��� ������� 0,1 ��� � ������� ��������� ���������� 3125
// 8000000��/256/3125 = ���������� 10 ��� � �������
TCCR1B |= (1 << WGM12)|(1 << CS12); // ����� ���, �������� �� 256
TIMSK1 |= (1 << OCIE1A); // ���������� ���������� �� ��������� T1 

twi_init();
display_init(); // ������������� �������
screen_clear(); // ������� ������

sei(); // ��������� ��������� ����������

while(1)
{
if((PINC & (1 << PC0)) == 0 && lock) // ���� ������ ������
{
start_stop ^= 1; // ����������� ���������
lock = 0; // ����������
_delay_ms(10);
}	
if(PINC & (1 << PC0)) lock = 1; // ������� ����������

if(start_stop) 
{
TCCR1B |= (1 << WGM12)|(1 << CS12); // ��������� �1
}
else 
{
TCCR1A = 0x00; // ������������� T1
TCCR1B = 0x00;
TCNT1 = 0x0000;
}

if((PINC & (1 << PC1)) == 0 && start_stop == 0) // ���� ������ ������ � ���������� ����������
{
m_sec = 0; sec = 0; min = 0; // �������� ��� 
_delay_ms(10);
while((PINC & (1 << PC1)) == 0){} // ���� ���������� ������
}	

print_string_5x8(0,0,"����������"); // ������� ������
print_char_5x8(0,2, (min/10)%10 + '0'); // ������� ������
print_char_5x8(6,2, min%10 + '0');
print_char_5x8(12,2, ':');
print_char_5x8(18,2, (sec/10)%10 + '0');
print_char_5x8(24,2, sec%10+ '0');
print_char_5x8(30,2, ':');
print_char_5x8(36,2, m_sec%10+ '0');
screen_update(); // ��������� �����
_delay_ms(10);
}

}
