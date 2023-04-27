#include "lcd.h"

#define E		2
#define RS		0

void write(uint8_t n){
	n|=(1<<E);
	pcf_write(n);
	n&=~(1<<E);
	pcf_write(n);
}


void send_byte(uint8_t byte, uint8_t tip){
	uint8_t data=0;
	if(tip) data|=(1<<RS); // если тип данные - на линии RS 1
	
	write(data|(byte&0xF0));// передача старшего полубайта
	write(data|(byte<<4));// передача младшего полубайта
}

// загрузка своих символов
void mychar(void){
	
	// массив с двум€ символами
	uint8_t simvol[16]={
		//  символ 1
		0x04,
		0x0E,
		0x04,
		0x1F,
		0x04,
		0x0A,
		0x11,
		0x00,
		// символ 2
		0x04,
		0x0E,
		0x15,
		0x0E,
		0x04,
		0x0A,
		0x0A,
		0x00
	};
	send_byte(64,0); // перейти в €чейку 0 CGRAM пам€ти
	
	// загрузить массив с символами в пам€ть CGRAM
	for (uint8_t i=0; i<16; i++)
	{
		send_byte(simvol[i], 1);
	}
	
	// перейти обратно в видео пам€ть
	lcd_pos(0,0);
}


void lcd_ini(void){
	
	//----------- магические действи€ инциализации----------------
	
	_delay_ms(40);// ждем 40 мс стабилизации питани€

	write(3<<4);
	_delay_ms(5);
	write(3<<4);
	_delay_us(150);
	write(3<<4);
	_delay_us(50);// минимальное врем€ выполнени€ команды
	write(2<<4);
	_delay_us(50);// минимальное врем€ выполнени€ команды
	
	// ---------------------- маги€ всЄ------------------------------
	
	// -----------команды инициализации--------------------
	
	send_byte(40,0);// команда Function Set 001_DL_N_F_X_X
	// DL 0/1 -4bit/8bit
	// N 0/1 -1/2 строки
	// F 0/1 -5x7/5x11 шрифт
	_delay_us(50);

	send_byte(12,0);// команда DISPLAY SWITCH 00001_D_C_B
	// D 0/1 - off/on display
	// C 0/1 - off/on cursor
	// B 0/1 - off/on blink
	
	_delay_us(50);
	
	send_byte(1,0);// команда очистка диспле€ (без параметров)
	_delay_ms(2);
	
	send_byte(6,0);// команда INPUT SET 000001_ID_S
	// ID 0/1 сдвиг влево/вправо
	// S 0/1 shift
	_delay_us(50);
	
	//--------------- команды всЄ ------------------------------------
	
	
	mychar();// загрузка своих символов

	//---------------маска индикации ----------------------------------
	lcd_str("count=");
	lcd_pos(1,2);
	lcd_str("HOLa Amigos!");
	// -----------маска всЄ----------------------------------------------
}


// вывод строки на индикацию
void lcd_str(char* str){
	uint8_t n=0;// счетчик 
	while(str[n])// пока н-ный символ не 0 работает цикл
	{
		send_byte(str[n],1);// выводим н-ный символна индикацию
		n++;// мен€ем номер символа 
	}
}

// смена активной €чейки видео пам€ти (позици€ курсора)
void lcd_pos(uint8_t line, uint8_t pos){
	uint8_t adress=(line*0x40+pos)|0x80;// вычисл€ем адрес и приводим значение в вид команды
	send_byte(adress,0);// отправка команды
	_delay_us(50);
}

// вывод 8 битного значени€ на индикацию
void lcd_num(uint8_t num, uint8_t line, uint8_t pos) {
	char buf[4];// буфер на 4 символа
	
	utoa(num, buf, 10);// конвертаци€ значени€ num в строку в массиве buf
	lcd_pos(line, pos);// смена позиции курсора 
	lcd_str("   ");// затираем три знакоместа пробелами
	lcd_pos(line, pos);//  смена позиции курсора 
	lcd_str(buf);// выводим строку
}

// анимаци€
void lcd_animation(void){
	static uint8_t status;
	lcd_pos(1,15);
	
	if (status)
	{
		send_byte(0,1);//  символ с кодом 0
		status=0;
	} 
	else
	{
		send_byte(1,1);// символ с кодом 1
		status=1;
	}
}