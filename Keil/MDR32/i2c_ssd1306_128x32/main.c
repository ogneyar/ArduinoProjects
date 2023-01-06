
#include "main.h"

#define SCREEN_BUFFER_LENGTH 512 // 512 * 8 or 128 * 32


static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_us = 0; // microseconds
static volatile uint32_t Delay_counter_ms = 0; // milliseconds
static volatile uint32_t Delay_counter_ms_100 = 100;
static volatile uint32_t Timeout_counter_us = 0;
static volatile uint32_t Timeout_counter_ms = 0;
static volatile uint32_t Timeout_counter_ms_100 = 100;

const static uint8_t address = 0x3c;
static uint8_t addressWrite = (address<<1);
//static uint8_t addressRead = (address<<1) | 1;
static uint8_t command = 0x00; // or 0x80 
static uint8_t dataByte = 0x40;
static uint8_t dataArray = 0xc0;

static uint8_t scr_buffer[0];// = { 0, }; // 


static const uint8_t ssd1306_128x32_init[] = {
  0xAE, // Выключить дисплей 
  0xD5, // Настройка частоты обновления дисплея 
  0x80, ///+----- делитель 0-F/ 0 - деление на 1 //+------ частота генератора. по умочанию 0x80 
  0xA8, // Установить multiplex ratio 
    0x1F, // 1/64 duty (значение по умолчанию), 0x1F - 128x32, 0x3F - 128x64 
  0xD3, // Смещение дисплея (offset) 
  0x00, // Нет смещения 
  0x40, // Начала строки начала разверки 0x40 с начала RAM 
  0x8D, // Управление внутреним преобразователем 
  0x14, // 0x10 - отключить (VCC подается извне) 0x14 - запустить внутрений DC/DC 
  0x20, // Режим автоматической адресации 
  0x00, // 0-по горизонтали с переходом на новую страницу (строку) // 1 - по вертикали с переходом на новую строку // 2 - только по выбранной странице без перехода 
  0xA1, // Режим разверки по странице (по X) // A1 - нормальный режим (слева/направо) A0 - обратный (справа/налево) 
  0xC8, // Режим сканирования озу дисплея // для изменения системы координат // С0 - снизу/верх (начало нижний левый угол) // С8 - сверху/вниз (начало верний левый угол) 
  0xDA, // Аппаратная конфигурация COM 
    0x02, // 0x02 - 128x32, 0x12 - 128x64 
  0x81, // Установка яркости дисплея 
  0x8F, // 0x8F..0xCF контраст
  0xD9, // Настройка фаз DC/DC преоразователя, HIGH: 0xD9, LOW: 0xEF
  0xF1, // 0x22 - VCC подается извне / 0xF1 для внутренего 
  0xDB, // Установка уровня VcomH 
  0x40, // Влияет на яркость дисплея 0x00..0x70 
  0xA4, // Режим нормальный 
  0xA6, // 0xA6 - нет инверсии, 0xA7 - инверсия дисплея 
  0xAF // Дисплей включен
};
	
	
// main function
int main(void)
{
	/* SysTick timer settings */
	SysTick_Init();
	
	/* Configure the system clock */
	SystemClock_Init();

	/* Initialize all configured peripherals */
	GPIO_Init();
	
	/* Initialize I2C */
	I2C_Init();	
	
	//Delay_ms(10);
	
	/* Initialize SSD1306 */
  Display_Init();
		
	
  Test_Screen();
	
	
  while (1)
  {
		
		if (!Timeout_counter_ms) {
			//
			Timeout_counter_ms = 10;
		}
		
		if (!Delay_counter_ms) {
			MDR_PORTB->RXTX ^= LED_HL1;
			MDR_PORTB->RXTX ^= LED_HL2;	
			MDR_PORTC->RXTX ^= LED_HL3;
			Delay_counter_ms = 100;
		}
		
  }
	
}


/* SysTick timer settings */
void SysTick_Init(void) {	
	
	// divider (SysTick 24 bit) max 16 777 216
	SysTick->LOAD |= 800 - 1; // this 100KHz clock, if FCPU = 80MHz // 80000 - 1; //  this 1KHz clock, if FCPU = 80MHz // 16000 - 1; //  this 1KHz clock, if FCPU = 16MHz // 72000 - 1; //  this 1KHz clock, if FCPU = 72MHz
	
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	NVIC_EnableIRQ(SysTick_IRQn);
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


/* Configure the system clock */
void SystemClock_Init(void) {			
	// switching on an external generator 
	MDR_RST_CLK->HS_CONTROL |= RST_CLK_HS_CONTROL_HSE_ON; // (1<<0)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_HSE_RDY)); // (1<<2)
	
	// switching CPU_C1 on HSE (external 16MHz without divide)
	MDR_RST_CLK->CPU_CLOCK |= 0x2<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos; // 0x2 - 0b10 - HSE (16MHz)
	// switching CPU_C1 on HSE (external 16MHz / 2)
	//MDR_RST_CLK->CPU_CLOCK |= 0x3<<RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos; // 0x3 - 0b11 - HSE/2 (8MHz)
	// switching HCLK on CPU_C3 (include external clock)
	MDR_RST_CLK->CPU_CLOCK |= 0x1<<RST_CLK_CPU_CLOCK_HCLK_SEL_Pos; // (1<<0)
	
	//PllInit(9); // 8MHz * 9 = 72MHz
	PllInit(5); // 16MHz * 5 = 80MHz
}


void PllInit(unsigned int pll_mul) {	
	// PLLCPUo = PLLCPUi * (PLLCPUMUL+1)  -  (pll_mul-1) multiplication by pll_mul
	MDR_RST_CLK->PLL_CONTROL |= (pll_mul-1)<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos; // pll_mul * FCPU_MHz
	
	// run module PLL
	MDR_RST_CLK->PLL_CONTROL |= RST_CLK_PLL_CONTROL_PLL_CPU_ON; // (1<<2)	
	while(!(MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY));
	
	//MDR_EEPROM->CMD |= 3<<EEPROM_CMD_DELAY_Pos; // 3 - after 100MHz // 4 - after 125MHz // 7 - after 200MHz 
	
	// include line CPU_C2 on PLL
	MDR_RST_CLK->CPU_CLOCK |= RST_CLK_CPU_CLOCK_CPU_C2_SEL;
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {	
	MDR_RST_CLK->PER_CLOCK |= PORTB_CLK | PORTC_CLK; // | PORTD_CLK
	
	MDR_PORTB->ANALOG |= LED_HL1 | LED_HL2;
	MDR_PORTB->OE |= LED_HL1 | LED_HL2; 
	MDR_PORTB->PWR |= (0x2<<(PB1*2)) | (0x2<<(PB2*2)); // 10 - middle
	
	MDR_PORTC->ANALOG |= LED_HL3;
	MDR_PORTC->OE |= LED_HL3; 
	MDR_PORTC->PWR |= (0x2<<(PC2*2)); // 10 - middle
	
	//MDR_PORTD->ANALOG |= BTN_USR;
	
	MDR_PORTB->RXTX |= LED_HL1;
	MDR_PORTB->RXTX &= ~(uint32_t)LED_HL2;	
	MDR_PORTC->RXTX |= LED_HL3;
	
}


void Delay_us(uint32_t Microseconds) {
	Delay_counter_us = Microseconds;
	while (Delay_counter_us != 0) ;
}


void Delay_ms(uint32_t Milliseconds) {
	Delay_counter_ms = Milliseconds;
	while (Delay_counter_ms != 0) ;
}



void SysTick_Handler(void) {
	SysTimer_ms++;	
	if (Delay_counter_us) {
		Delay_counter_us = Delay_counter_us - 10;
	}	
	if (Timeout_counter_us) {
		Timeout_counter_us = Timeout_counter_us - 10;
	}
	if (Delay_counter_ms) {
		if (Delay_counter_ms_100) {
			Delay_counter_ms_100--;
		}else {
			Delay_counter_ms--;
			Delay_counter_ms_100 = 100;
		}
	}	
	if (Timeout_counter_ms) {
		if (Timeout_counter_ms_100) {
			Timeout_counter_ms_100--;
		}else {
			Timeout_counter_ms--;
			Timeout_counter_ms_100 = 100;
		}
	}	
}

// инициализация I2C
void I2C_Init() {
    MDR_RST_CLK->PER_CLOCK |= PORTC_CLK;
    MDR_PORTC->FUNC &= ~(PORT_FUNC_MODE0_Msk | PORT_FUNC_MODE1_Msk);
    MDR_PORTC->FUNC |= (PORT_FUNC_ALTER << PORT_FUNC_MODE0_Pos
                     | PORT_FUNC_ALTER << PORT_FUNC_MODE1_Pos);
    MDR_PORTC->ANALOG |= SCL1 | SDA1;
    MDR_PORTC->PWR |= (PORT_SPEED_MIDDLE << PORT_PWR0_Pos
                    | PORT_SPEED_MIDDLE << PORT_PWR1_Pos);

    MDR_RST_CLK->PER_CLOCK |= I2C1_CLK;
    MDR_I2C->PRL = 15; // Fscl = HCLK/(5*(DIV+1))  Fscl = 1MHz  (HCLK = 80MHz   => DIV = 15)   ||  Fscl = 400KHz  (HCLK = 80MHz   => DIV = 39)   ||  Fscl = 100KHz  (HCLK = 72MHz   => DIV = 143)  or  (HCLK = 80MHz   => DIV = 159)  or  (HCLK = 16MHz   => DIV = 45)
    MDR_I2C->PRH = 0;
    MDR_I2C->CTR |= (1 << I2C_CTR_EN_I2C_Pos) // enable I2C
                 |  (0 << I2C_CTR_EN_INT_Pos) // disable interrupt
                 |  (0 << I2C_CTR_S_I2C_Pos); // speed I2C (0 - after 400KHz, 1 - after 1MHz)
}

// команда START
void I2C_start() {	
	MDR_I2C->CMD |= I2C_CMD_START;
}

// отправка байта
void I2C_send_byte(uint8_t byte) {
	MDR_I2C->TXD = byte;
	MDR_I2C->CMD |= I2C_CMD_WR;
	while (MDR_I2C->STA & I2C_STA_TR_PROG) ;
}

// чтение байта
uint8_t I2C_read_byte() {
	MDR_I2C->CMD |= I2C_CMD_RD;
	while (MDR_I2C->STA & I2C_STA_TR_PROG) ;
	return (uint8_t)MDR_I2C->RXD;
}

// команда STOP
void I2C_stop() {
	MDR_I2C->CMD |= I2C_CMD_STOP;
}



// Функция инициализации дисплея
void Display_Init(void) {
  for(uint8_t i = 0; i < (uint8_t)sizeof(ssd1306_128x32_init); i++) Disp_Write_Byte(0, ssd1306_128x32_init[i]);

	Delay_us(100000);
	MDR_PORTB->RXTX ^= LED_HL2;
	Delay_us(100000);
	MDR_PORTB->RXTX ^= LED_HL2;	
}


// Функция записи данных/команды в дисплей
void Disp_Write_Byte(uint8_t mode, uint8_t data) // Режим: 1-данные, 0-команда
{
  if(mode) mode = dataByte; // Режим данных
  else mode = command; 			// Режим команды
  
  I2C_start();
  I2C_send_byte(addressWrite); // команда на запись (7 бит адреса + 1 бит на запись/чтение )
  I2C_send_byte(mode);    // Control Byte - Command
  I2C_send_byte(data);    // payload
  I2C_stop();
	
	Delay_us(20);
}

// Функция записи массива данных из буфера в дисплей
void Disp_Write_Array() {
  I2C_start();
  I2C_send_byte(addressWrite); // команда на запись (7 бит адреса + 1 бит на запись/чтение )
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) {
    I2C_send_byte(dataArray); 		// Control Byte - Command
    I2C_send_byte(scr_buffer[i]); // payload
  }
  I2C_stop();    
}



// Функция очистки буфера дисплея
void Screen_Clear(void) {
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0;
  Screen_Update();
}

// Функция обновления дисплея
void Screen_Update(void) {
  Disp_Write_Byte(0,0x21); // Установка столбца
  Disp_Write_Byte(0,0);    // Начальный адрес
  Disp_Write_Byte(0,127);  // Конечный адрес
  
  Disp_Write_Byte(0,0x22); // Установка строки
  Disp_Write_Byte(0,0);    // Начальный адрес
  Disp_Write_Byte(0,3);    // Конечный адрес
	
  // Запись данных из буфера в дисплей
  //for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) Disp_Write_Byte(1, scr_buffer[i]);
  Disp_Write_Array();  
}

// Функция заполнения дисплея чередующимися пикселями
void Lines_Screen_Pixels(void) { 
  uint8_t flag = 0xff;
  for(uint16_t i = 0; i < 1024; i++) {
    scr_buffer[i] = flag;
    if (flag) flag = 0x00;
    else flag = 0xff;
  }
  Screen_Update();
}

// Функция вывода на дисплей всех пикселей
void Full_Screen_Pixels(void) {
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0xff;
  Screen_Update();
}

// Функция теста дисплея SSD1306
void Test_Screen(void) {
  Screen_Clear(); // очистка экрана
  Delay_ms(1000);
	Lines_Screen_Pixels(); // вывод чередующихя пикселей
  Delay_ms(1000);
  Screen_Clear(); // очистка экрана
  Delay_ms(1000);
  Full_Screen_Pixels(); // вывод на дисплей всех пикселей
}

//
