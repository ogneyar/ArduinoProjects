
#include "main.h"


static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_ms = 0;
static volatile uint32_t Timeout_counter_ms = 0;

void SysTick_Init(void);
void SystemClock_72MHz(void);
void GPIO_Init(void);
void Delay_ms(uint32_t Milliseconds);
void SysTick_Handler(void);

void SPI1_Init(void);
bool SPI_Transmit_8BIT(SPI_TypeDef* SPI, uint8_t* data, uint16_t Size_data, uint32_t Timeout_ms);
bool SPI_Transmit_16BIT(SPI_TypeDef* SPI, uint16_t* data, uint16_t Size_data, uint32_t Timeout_ms);
bool SPI_Receive_8BIT(SPI_TypeDef* SPI, uint8_t* data, uint16_t Size_data, uint32_t Timeout_ms);
bool SPI_Receive_16BIT(SPI_TypeDef* SPI, uint16_t* data, uint16_t Size_data, uint32_t Timeout_ms);

void display_init(void);
void screen_clear(void);
void screen_clear_CENTER(void);
void screen_clear_CENTER_mini(void);
void screen_update(void);
void disp_write(uint8_t mode, uint8_t* data, uint16_t length);
void test_screen(void);

//static uint8_t spi_tx_buffer[6] = { 4, 8, 15, 16, 23, 42 };
//static uint8_t spi_rx_buffer[6] = {0,};


static uint8_t commandSend = 0;
static uint8_t dataSend = 1;

static uint8_t scr_buffer[SCREEN_BUFFER_LENGTH] = {0};

static uint8_t scr_col_row[] = {
	0x21, // column
  0, 		// begin
  127, 	// end
	0x22, // row
  0, 		// begin
	7, 		// end
};

static uint8_t scr_col_row_CENTER[] = {
	0x21, // column
  31, 		// begin
  95, 	// end
	0x22, // row
  2, 		// begin
	5, 		// end
};

static uint8_t scr_col_row_CENTER_mini[] = {
	0x21, // column
  47, 		// begin
  79, 	// end
	0x22, // row
  3, 		// begin
	4, 		// end
};

static uint8_t ssd1306_128x64_init[] = {
	OLED_DISPLAY_OFF,
  OLED_CLOCKDIV,
	0x80,    // value
	OLED_CHARGEPUMP,
	0x14,    // value
	OLED_ADDRESSING_MODE,
	OLED_VERTICAL,
	OLED_NORMAL_H,
	OLED_NORMAL_V,
	OLED_CONTRAST,
	0x7F,    // value
	OLED_SETVCOMDETECT,
	0x40,     // value
	OLED_NORMALDISPLAY,
	OLED_DISPLAY_ON,
	
	OLED_SETCOMPINS,
	OLED_HEIGHT_64,
	
	OLED_SETMULTIPLEX,
	OLED_64,
};


	
// main function
int main(void)
{	
	/* SysTick timer settings */
	SysTick_Init();
	
	/* Configure the system clock */
  SystemClock_72MHz();

  /* Initialize all configured peripherals */
	GPIO_Init();
	
	
	SPI1_Init();	
	
	
  display_init();

	
  test_screen();
	
	
	
	while (1) {
		GPIOC->BSRR |= GPIO_BSRR_BS13;
		Delay_ms(500);
		GPIOC->BSRR |= GPIO_BSRR_BR13;
		Delay_ms(500);
	}
	
}



void display_init(void) 
{	
	NSS_OFF; // CS - pull up

	RES_OFF; // RST - pull up
	Delay_ms(1);
	RES_ON; // RST - pull down
	Delay_ms(10);
	RES_OFF;
	
	disp_write(commandSend, ssd1306_128x64_init, sizeof ssd1306_128x64_init); 
}


void screen_clear(void) 
{
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0;
	screen_update();
}


void screen_clear_CENTER(void) 
{	
  for(uint16_t i = 0; i < 256; i++) scr_buffer[i] = 0;	
	disp_write(commandSend, scr_col_row_CENTER, sizeof scr_col_row_CENTER); 	
	disp_write(dataSend, scr_buffer, 256);
}

void screen_clear_CENTER_mini(void) 
{	
  for(uint16_t i = 0; i < 64; i++) scr_buffer[i] = 0xff;	
	disp_write(commandSend, scr_col_row_CENTER_mini, sizeof scr_col_row_CENTER_mini); 	
	disp_write(dataSend, scr_buffer, 64);
}

void screen_update(void) 
{
  disp_write(commandSend, scr_col_row, sizeof scr_col_row); 	
	disp_write(dataSend, scr_buffer, sizeof scr_buffer);
}


void disp_write(uint8_t mode, uint8_t* data, uint16_t length) // 1 - data, 0 - command
{
  if(mode == commandSend) DC_COMA;
  else DC_DATA;
			
  NSS_ON;
  SPI_Transmit_8BIT(SPI1, data, length, 100);
  NSS_OFF;
}



void test_screen(void) {
  screen_clear();
	
  Delay_ms(1000);
	
  uint8_t flag = 0xff;
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) {
    scr_buffer[i] = flag;
    if (flag) flag = 0x00;
    else flag = 0xff;
  }
  screen_update();
  
  Delay_ms(1000);
	
  screen_clear();
  
  Delay_ms(100);
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0xff;
  screen_update();
	
  Delay_ms(1000);
	
	screen_clear_CENTER();
	
  Delay_ms(1000);
	
	screen_clear_CENTER_mini();
}








/* SysTick timer settings */
void SysTick_Init(void) {	
/* SysTick control and status register (STK_CTRL) */
	// ENABLE: Counter enable
	CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); // 0: Counter disabled
	// TICKINT: SysTick exception request enable
	SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk); // 1: Counting down to zero to asserts the SysTick exception request.
	// CLKSOURCE: Clock source selection
	SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk); // 1: Processor clock (AHB)
/* ---------------------------------------------- */
	
/* SysTick reload value register (STK_LOAD) */
	// RELOAD[23:0]: RELOAD value
	SET_BIT(SysTick->LOAD, 71999); // The RELOAD value can be any value in the range 0x00000001-0x00FFFFFF.
/* ---------------------------------------- */
	
/* SysTick current value register (STK_VAL) */
	// CURRENT[23:0]: Current counter value
	SET_BIT(SysTick->VAL, 71999); // The VAL register contains the current value of the SysTick counter.
/* ---------------------------------------- */
	
/* SysTick control and status register (STK_CTRL) */
	// ENABLE: Counter enable
	SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); //  1: Counter enabled
/* ---------------------------------------------- */
}


/* Configure the system clock */
void SystemClock_72MHz(void) {			
/* Clock control register (RCC_CR) */	
	// HSION: Internal high-speed clock enable
	SET_BIT(RCC->CR, RCC_CR_HSION); // internal 8 MHz RC oscillator ON
	// HSIRDY: Internal high-speed clock ready flag
	while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET); // 1: internal 8 MHz RC oscillator ready
	// HSEON: External high-speed clock enable
	SET_BIT(RCC->CR, RCC_CR_HSEON); // HSE oscillator ON
	// HSERDY: External high-speed clock ready flag
	while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET) ; // 1: HSE oscillator ready
	// HSEBYP: External high-speed clock bypass
	CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP); // 0: external 4-16 MHz oscillator not bypassed
	// CSSON: Clock security system enable
	SET_BIT(RCC->CR, RCC_CR_CSSON); // 1: Clock detector ON (Clock detector ON if the HSE oscillator is ready , OFF if not).
/* -------------------------------- */	

/* Clock configuration register (RCC_CFGR) */
	// SW: System clock switch
	RCC->CFGR |= RCC_CFGR_SW_PLL; // 10: PLL selected as system clock
	// SWS: System clock switch status
	RCC->CFGR |= RCC_CFGR_SWS_PLL; // 10: PLL used as system clock
	// HPRE: AHB prescaler
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // 0000: SYSCLK not divided
/* --------------------------------------- */

/* Flash access control register (FLASH_ACR) */
	// LATENCY: Latency
	FLASH->ACR |= FLASH_ACR_LATENCY_2; // 010: Two wait states, if 48 MHz < SYSCLK <= 72 MHz
	// PRFTBE: Prefetch buffer enable
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE); //1: Prefetch is enabled
	// PRFTBS: Prefetch buffer status
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBS); //1: Prefetch buffer is enabled
/* ----------------------------------------- */

/* Clock configuration register (RCC_CFGR) */
	// PPRE1: APB low-speed prescaler (APB1)
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // 100: HCLK divided by 2
	// PPRE2: APB high-speed prescaler (APB2)
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; //000: HCLK not divided
	// ADCPRE: ADC prescaler
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // 10: PCLK2 divided by 6 // 72/6 = 12Mhz (< 14 ok)
	// PLLSRC: PLL entry clock source
	SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC); // 1: HSE oscillator clock selected as PLL input clock
	// PLLXTPRE: HSE divider for PLL entry
	CLEAR_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE); // 0: HSE clock not divided
	// PLLMUL: PLL multiplication factor
	RCC->CFGR |= RCC_CFGR_PLLMULL9; // 0111: PLL input clock x 9 (8*9 = 72)
	// USBPRE: USB prescaler
	CLEAR_BIT(RCC->CFGR, RCC_CFGR_USBPRE); // 0: PLL clock is divided by 1.5 (72 / 1.5 = 48 MHz)
	// MCO: Microcontroller clock output
	//SET_BIT(RCC->CFGR, RCC_CFGR_MCO_PLL); // 111: PLL clock divided by 2 selected
	MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, RCC_CFGR_MCO_PLL); // MODIFY_REG(REG, Msk, Data);
/* --------------------------------------- */

/* Clock control register (RCC_CR) */	
	// PLLON: PLL enable
	SET_BIT(RCC->CR, RCC_CR_PLLON); // 1: PLL ON
	// PLLRDY: PLL clock ready flag
	while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET); // 1: PLL locked
/* -------------------------------- */	
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {
	// PC13 - out
/* APB2 peripheral clock enable register (RCC_APB2ENR) */
	// IOPCEN: IO port C clock enable
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN); // 1: IO port C clock enabled
/* --------------------------------------------------- */	
	
/* 9.2.1 Port configuration register high (GPIOx_CRH) (x=A..G) */
	// CNFy[1:0]: Port x configuration bits (y= 8 .. 15)
	GPIOC->CRH &= ~GPIO_CRH_CNF13; // 00: General purpose output push-pull (PC13)
	// MODEy[1:0]: Port x mode bits (y= 8 .. 15)
	GPIOC->CRH |= GPIO_CRH_MODE13; // 11: Maximum output speed 50 MHz
/* ----------------------------------------------------- */		
		
	// PB2 - out
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN); // 1: IO port B clock enabled
	GPIOB->CRL &= ~GPIO_CRL_CNF2; // 00: General purpose output push-pull (PB2)
	GPIOB->CRL |= GPIO_CRL_MODE2; // 11: Maximum output speed 50 MHz
}


void Delay_ms(uint32_t Milliseconds) {
	Delay_counter_ms = Milliseconds;
	while (Delay_counter_ms != 0) ;
}


void SysTick_Handler(void) {
	SysTimer_ms++;	
	if (Delay_counter_ms) {
		Delay_counter_ms--;
	}		
	if (Timeout_counter_ms) {
		Timeout_counter_ms--;
	}	
}



void SPI1_Init() {	
	/*Настройка GPIO*/
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN); //Включение альтернативных функций
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN); //Включение тактирования SPI1
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN); //Включение тактирования порта А
	/*Какие ножки:*/
	//PA2 - RES
	//PA3 - DC
	//PA4 - NSS
	//PA5 - SCK
	//PA6 - MISO
	//PA7 - MOSI
	
	//PA2 - RES
  MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE2, GPIO_CRL_MODE2_1); //Настройка GPIOA Pin 4 на выход со максимальной скоростью в 50 MHz
  MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF2, (0 << 11) | (0 << 12) /* (0b00 << GPIO_CRL_CNF4_Pos) */); //Настройка GPIOA Pin 4 на выход в режиме Push-Pull
	//PA3 - DC
  MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE3, GPIO_CRL_MODE3_1); //Настройка GPIOA Pin 4 на выход со максимальной скоростью в 50 MHz
  MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF3, (0 << 15) | (0 << 16) /* (0b00 << GPIO_CRL_CNF4_Pos) */); //Настройка GPIOA Pin 4 на выход в режиме Push-Pull
	//PA4 - NSS
  MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE4, GPIO_CRL_MODE4_1); //Настройка GPIOA Pin 4 на выход со максимальной скоростью в 50 MHz
  MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF4, (0 << 19) | (0 << 20) /* (0b00 << GPIO_CRL_CNF4_Pos) */); //Настройка GPIOA Pin 4 на выход в режиме Push-Pull
	//SCK - PA5:
	SET_BIT(GPIOA->CRL, GPIO_CRL_MODE5); // 0b11 - Maximum output speed 50 MHz
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF5, GPIO_CRL_CNF5_1); // 0b10 - Alternate Function output Push-pull
	//MISO - PA6:
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_MODE6, (0 << 25) | (0 << 26)/*(0b00 << GPIO_CRL_MODE6_Pos)*/); //Reserved
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF6, GPIO_CRL_CNF6_1); // 0b10 - Input pull-up
	SET_BIT(GPIOA->ODR, GPIO_ODR_ODR6); //Pull-Up
	//MOSI - PA7:
	SET_BIT(GPIOA->CRL, GPIO_CRL_MODE7); // 0b11 - Maximum output speed 50 MHz
	MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF7, GPIO_CRL_CNF7_1); // 0b10 - Alternate Function output Push-pull 	

	 /*SPI control register 1 (SPI_CR1) (not used in I2S mode)(см. п.п. 25.5.1 стр 742)*/
	/*
	 * Bits 5:3 BR[2:0]: Baud rate control
	 * 000: fPCLK/2
	 * 001: fPCLK/4
	 * 010: fPCLK/8
	 * 011: fPCLK/16
	 * 100: fPCLK/32
	 * 101: fPCLK/64
	 * 110: fPCLK/128
	 * 111: fPCLK/256
	 * */
	MODIFY_REG(SPI1->CR1, SPI_CR1_BR, (0 << 4) | (1 << 5) | (0 << 6) /*(0b100 << SPI_CR1_BR_Pos)*/); //fPCLK/8. 72000000/8 = 9 MBits/s
	// CLEAR_BIT(SPI1->CR1, SPI_CR1_CPOL); //Полярность 0
	// CLEAR_BIT(SPI1->CR1, SPI_CR1_CPHA); //Фаза 0
	// CLEAR_BIT(SPI1->CR1, SPI_CR1_DFF); //0: 8-bit data frame format is selected for transmission/reception
	// CLEAR_BIT(SPI1->CR1, SPI_CR1_LSBFIRST); //0: MSB transmitted first
	SET_BIT(SPI1->CR1, SPI_CR1_SSM); //1: Software slave management enabled
	SET_BIT(SPI1->CR1, SPI_CR1_SSI); //1: Software slave management enabled
	SET_BIT(SPI1->CR1, SPI_CR1_MSTR); //1: Master configuration
	// CLEAR_BIT(SPI1->CR1, SPI_CR1_BIDIMODE); //0: 2-line unidirectional data mode selected
	// CLEAR_BIT(SPI1->CR1, SPI_CR1_RXONLY); //0: full duplex

	SET_BIT(SPI1->CR1, SPI_CR1_SPE); //Включим SPI

	// CLEAR_BIT(SPI1->CR1, SPI_CR1_CRCEN); //0: CRC calculation disabled
	// CLEAR_BIT(SPI1->CR1, SPI_CR1_CRCNEXT); // 0: Data phase (no CRC phase) 

	/*SPI control register 2 (SPI_CR2) (см. п.п. 25.5.2 стр 744)*/
	// CLEAR_BIT(SPI1->CR2, SPI_CR2_RXDMAEN); //0: Rx buffer DMA disabled
	// CLEAR_BIT(SPI1->CR2, SPI_CR2_TXDMAEN); //0: Tx buffer DMA disabled
	// CLEAR_BIT(SPI1->CR2, SPI_CR2_SSOE); //0: SS output is disabled in master mode and the cell can work in multimaster configuration
	// CLEAR_BIT(SPI1->CR2, SPI_CR2_ERRIE); //0: Error interrupt is masked
	// CLEAR_BIT(SPI1->CR2, SPI_CR2_RXNEIE); //0: RXNE interrupt masked 
	// CLEAR_BIT(SPI1->CR2, SPI_CR2_TXEIE); //0: TXE interrupt masked 

	/*SPI_I2S configuration register (SPI_I2SCFGR) (см. п.п. 25.5.8 стр 748)*/
	// CLEAR_BIT(SPI1->I2SCFGR, SPI_I2SCFGR_I2SMOD); //т.к. на F103C6T6 нет I2S, его вырезали, а регистр оставили, нужно просто обнулить данный регистр. Тем самым включим режим SPI mode.

}



bool SPI_Transmit_8BIT(SPI_TypeDef* SPI, uint8_t* data, uint16_t Size_data, uint32_t Timeout_ms) {
	//(см. Reference Manual стр. 712 Transmit-only procedure (BIDIMODE=0 RXONLY=0))
	if (!READ_BIT(SPI->SR, SPI_SR_BSY)) {
		//Проверим занятость шины
		SPI->DR = *(data); //Запишем первый элемент данных для отправки в регистр SPI_DR
		//(При этом очищается бит TXE)

		for (uint16_t i = 1; i < Size_data; i++) {
			Timeout_counter_ms = Timeout_ms;
			while (!READ_BIT(SPI->SR, SPI_SR_TXE)) {
				//Ждем, пока буфер на передачу не освободится
				if (!Timeout_counter_ms) {
					return false;
				}
			}
			SPI->DR = *(data + i); //Запишем следующий элемент данных.
		}
		Timeout_counter_ms = Timeout_ms;
		while (!READ_BIT(SPI->SR, SPI_SR_TXE)) {
			//После записи последнего элемента данных в регистр SPI_DR,
			//подождем, пока TXE станет равным 1.
			if (!Timeout_counter_ms) {
				return false;
			}
		}
		Timeout_counter_ms = Timeout_ms;
		while (READ_BIT(SPI->SR, SPI_SR_BSY)) {
			//Затем подождем, пока BSY станет равным 0.
			//Это указывает на то, что передача последних данных завершена.
			if (!Timeout_counter_ms) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
	//Примечание:
	//После передачи двух элементов данных в режиме "transmit-only mode" в регистре SPI_SR устанавливается флаг OVR, так как принятые данные никогда не считываются.
}


bool SPI_Transmit_16BIT(SPI_TypeDef* SPI, uint16_t* data, uint16_t Size_data, uint32_t Timeout_ms) {
	//(см. Reference Manual стр. 712 Transmit-only procedure (BIDIMODE=0 RXONLY=0))
	if (!READ_BIT(SPI->SR, SPI_SR_BSY)) {
		//Проверим занятость шины
		SPI->DR = *(data); //Запишем первый элемент данных для отправки в регистр SPI_DR
		//(При этом очищается бит TXE)

		for (uint16_t i = 1; i < Size_data; i++) {
			Timeout_counter_ms = Timeout_ms;
			while (!READ_BIT(SPI->SR, SPI_SR_TXE)) {
				//Ждем, пока буфер на передачу не освободится
				if (!Timeout_counter_ms) {
					return false;
				}
			}
			SPI->DR = *(data + i); //Запишем следующий элемент данных.
		}
		Timeout_counter_ms = Timeout_ms;
		while (!READ_BIT(SPI->SR, SPI_SR_TXE)) {
			//После записи последнего элемента данных в регистр SPI_DR,
			//подождем, пока TXE станет равным 1.
			if (!Timeout_counter_ms) {
				return false;
			}
		}
		Timeout_counter_ms = Timeout_ms;
		while (READ_BIT(SPI->SR, SPI_SR_BSY)) {
			//Затем подождем, пока BSY станет равным 0.
			//Это указывает на то, что передача последних данных завершена.
			if (!Timeout_counter_ms) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
	//Примечание:
	//После передачи двух элементов данных в режиме "transmit-only mode" в регистре SPI_SR устанавливается флаг OVR, так как принятые данные никогда не считываются.
}

//
bool SPI_Receive_8BIT(SPI_TypeDef* SPI, uint8_t* data, uint16_t Size_data, uint32_t Timeout_ms) {
	if (!READ_BIT(SPI->SR, SPI_SR_BSY)) {
		//Проверим занятость шины

		if (READ_BIT(SPI->SR, SPI_SR_OVR) || READ_BIT(SPI->SR, SPI_SR_RXNE)) {
			//Т.к. мы можем принимать данные в любой момент, например после режима "transmit-only mode"
			//то следует проверить статусы OVR и RXNE. Если хотя бы один из них установлен, 
			//то сбросим их при помощи чтения регистра DR.
			SPI->DR;
		}

		//Начнем прием данных
		for (uint16_t i = 0; i < Size_data; i++) {
			SPI->DR = 0; //Запустим тактирование, чтоб считать 8 бит
			Timeout_counter_ms = Timeout_ms;
			while (!READ_BIT(SPI->SR, SPI_SR_RXNE)) {
				//Ждем, пока буфер на прием не заполнится
				if (!Timeout_counter_ms) {
					return false;
				}
			}
			*(data + i) = SPI->DR; //Считываем данные
		}

		Timeout_counter_ms = Timeout_ms;
		while (READ_BIT(SPI->SR, SPI_SR_BSY)) {
			//Затем подождем, пока BSY станет равным 0.
			//Это указывает на то, что прием последних данных завершен.
			if (!Timeout_counter_ms) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}


//
bool SPI_Receive_16BIT(SPI_TypeDef* SPI, uint16_t* data, uint16_t Size_data, uint32_t Timeout_ms) {
	if (!READ_BIT(SPI->SR, SPI_SR_BSY)) {
		//Проверим занятость шины

		if (READ_BIT(SPI->SR, SPI_SR_OVR) || READ_BIT(SPI->SR, SPI_SR_RXNE)) {
			//Т.к. мы можем принимать данные в любой момент, например после режима "transmit-only mode"
			//то следует проверить статусы OVR и RXNE. Если хотя бы один из них установлен, 
			//то сбросим их при помощи чтения регистра DR.
			SPI->DR;
		}

		//Начнем прием данных
		for (uint16_t i = 0; i < Size_data; i++) {
			SPI->DR = 0; //Запустим тактирование, чтоб считать 16 бит
			Timeout_counter_ms = Timeout_ms;
			while (!READ_BIT(SPI->SR, SPI_SR_RXNE)) {
				//Ждем, пока буфер на прием не заполнится
				if (!Timeout_counter_ms) {
					return false;
				}
			}
			*(data + i) = SPI->DR; //Считываем данные
		}

		Timeout_counter_ms = Timeout_ms;
		while (READ_BIT(SPI->SR, SPI_SR_BSY)) {
			//Затем подождем, пока BSY станет равным 0.
			//Это указывает на то, что прием последних данных завершен.
			if (!Timeout_counter_ms) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}






