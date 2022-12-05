#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ssd1306.h"
#include "twi_driver.h"

volatile uint8_t m_sec, sec, min;
uint8_t lock, start_stop = 0;

// Прерывание по сравнению T1, отсчет 0,1с
ISR(TIMER1_COMPA_vect)
{   
m_sec++;  // Увеличиваем счётчик
if(m_sec >= 10)
{
sec++; // Увеличиваем секунды 
m_sec = 0;
}
if(sec >= 60)
{
min++; // Увеличиваем минуты
m_sec = 0; sec = 0;
}
if(min >= 60) // Если прошел час обнуляем все
{
m_sec = 0; sec = 0; min = 0; 
}

}

int main(void)
{
// Настройка портов ввода/вывода
DDRC &= ~(1 << PC1)|(1 << PC0); // Входы кнопок
PORTC |= (1 << PC1)|(1 << PC0);

// Настройка таймера 1
OCR1A  = 3125; // Для отсчёта 0,1 сек в регистр сравнения записываем 3125
// 8000000Гц/256/3125 = прерывание 10 раз в секунду
TCCR1B |= (1 << WGM12)|(1 << CS12); // Режим СТС, делитель на 256
TIMSK1 |= (1 << OCIE1A); // Разрешение прерывания по сравнению T1 

twi_init();
display_init(); // Инициализация дисплея
screen_clear(); // Очистка экрана

sei(); // Глобально разрешаем прерывания

while(1)
{
if((PINC & (1 << PC0)) == 0 && lock) // Если нажата кнопка
{
start_stop ^= 1; // Переключаем состояние
lock = 0; // Блокировка
_delay_ms(10);
}	
if(PINC & (1 << PC0)) lock = 1; // Снимаем блокировку

if(start_stop) 
{
TCCR1B |= (1 << WGM12)|(1 << CS12); // Запускаем Т1
}
else 
{
TCCR1A = 0x00; // Останавливаем T1
TCCR1B = 0x00;
TCNT1 = 0x0000;
}

if((PINC & (1 << PC1)) == 0 && start_stop == 0) // Если нажата кнопка и секундомер остановлен
{
m_sec = 0; sec = 0; min = 0; // Обнуляем все 
_delay_ms(10);
while((PINC & (1 << PC1)) == 0){} // Ждем отпускания кнопки
}	

print_string_5x8(0,0,"СЕКУНДОМЕР"); // Выводим строку
print_char_5x8(0,2, (min/10)%10 + '0'); // Выводим символ
print_char_5x8(6,2, min%10 + '0');
print_char_5x8(12,2, ':');
print_char_5x8(18,2, (sec/10)%10 + '0');
print_char_5x8(24,2, sec%10+ '0');
print_char_5x8(30,2, ':');
print_char_5x8(36,2, m_sec%10+ '0');
screen_update(); // Обновляем экран
_delay_ms(10);
}

}
