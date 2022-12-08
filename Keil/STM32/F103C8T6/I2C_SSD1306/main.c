
#include "main.h"

#define SCREEN_BUFFER_LENGTH 512 // 512 * 8 or 128 * 32

static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_ms = 0;
static volatile uint32_t Timeout_counter_ms = 0;

static uint8_t address = 0x3c;
//static uint8_t addressWrite = 0x78; // address << 1 | 0x00
//static uint8_t addressRead = 0x79; // address << 1 | 0x01
static uint8_t command = 0x00; // or 0x80 
static uint8_t dataByte = 0x40;
//static uint8_t dataArray = 0xc0;
static uint8_t scr_buffer[] = {0};


void SysTick_Init(void);
void SystemClock_72MHz(void);
void GPIO_Init(void);
void Delay_ms(uint32_t Milliseconds);
void SysTick_Handler(void);

void I2C_Reset(I2C_TypeDef *I2C);
void I2C_Init(I2C_TypeDef *I2C);
bool I2C_start(I2C_TypeDef *I2C, uint32_t Timeout_ms);
bool I2C_send_address(I2C_TypeDef *I2C, uint8_t byte, uint32_t Timeout_ms);
bool I2C_send_byte(I2C_TypeDef *I2C, uint8_t byte, uint32_t Timeout_ms);
void I2C_stop(I2C_TypeDef *I2C);
	
bool disp_write(uint8_t mode, uint8_t data);
void display_init(void);
void screen_clear(void);
void screen_update(void);
void test_screen(void);


static const unsigned char ssd1306_128x32_init[] = {
  0xAE, 0xD5, 0x80, 
	0xA8, // multiplex ratio 
  0x1F, // 0x1F - 128x32, 0x3F - 128x64 
  0xD3, // offset 
  0x00, 0x40, 0x8D, 0x14, 0x20, 0x00, 0xA1, 0xC8, 0xDA,
  0x02, // 0x02 - 128x32, 0x12 - 128x64 
  0x81,
  0x8F, // 0x8F..0xCF contrast
  0xD9, // HIGH: 0xD9, LOW: 0xEF
  0xF1, 0xDB,
  0x40, // backlight 0x00..0x70 
  0xA4,
  0xA6, // 0xA6 - no inversion, 0xA7 - inversion
  0xAF
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
	
	I2C_Init(I2C1);	
	Delay_ms(1000);
	
  display_init();
  
  screen_clear();
  screen_update();

  Delay_ms(1000);

  test_screen();
		
	
  while (1)
  {
		GPIOC->BSRR |= GPIO_BSRR_BS13;
		Delay_ms(500);
		GPIOC->BSRR |= GPIO_BSRR_BR13;
		Delay_ms(500);
  }
	
}


/* SysTick timer settings */
void SysTick_Init(void) {	
	SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
	SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk);
	SET_BIT(SysTick->LOAD, 71999);
	SET_BIT(SysTick->VAL, 71999);
	SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);
}


/* Configure the system clock */
void SystemClock_72MHz(void) {		
	SET_BIT(RCC->CR, RCC_CR_HSION);
	while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET) ;
	while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET) ;
	SET_BIT(RCC->CR, RCC_CR_CSSON);
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	RCC->CFGR |= RCC_CFGR_SWS_PLL;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	FLASH->ACR |= FLASH_ACR_LATENCY_2;
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBE);
	SET_BIT(FLASH->ACR, FLASH_ACR_PRFTBS);
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
	RCC->CFGR |= RCC_CFGR_PLLMULL9;
	MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO, RCC_CFGR_MCO_PLL);
	SET_BIT(RCC->CR, RCC_CR_PLLON);
	while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);
}


/* Initialize all configured peripherals */
void GPIO_Init(void) {
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN);
	GPIOC->CRH &= ~GPIO_CRH_CNF13; 
	GPIOC->CRH |= GPIO_CRH_MODE13;	
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


void I2C_Reset(I2C_TypeDef *I2C) {
	SET_BIT(I2C->CR1, I2C_CR1_SWRST); //: I2C Peripheral not under reset
	while (READ_BIT(I2C->CR1, I2C_CR1_SWRST) == 0) ;
	CLEAR_BIT(I2C->CR1, I2C_CR1_SWRST); //: I2C Peripheral not under reset
	while (READ_BIT(I2C->CR1, I2C_CR1_SWRST)) ;
}

void I2C_Init(I2C_TypeDef *I2C) {
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN); // IO port B clock enabled
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN); // alternate function enabled
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN); // i2c clock enabled
	//PB7 SDA (I2C Data I/O) Alternate function open drain
	SET_BIT(GPIOB->CRL, GPIO_CRL_CNF7); // 0b11 //Alternate function open drain
	SET_BIT(GPIOB->CRL, GPIO_CRL_MODE7); // 0b11 //Maximum output speed 50 MHz
	//PB6 SCL (I2C clock) Alternate function open drain
	SET_BIT(GPIOB->CRL, GPIO_CRL_CNF6); // 0b11 //Alternate function open drain
	SET_BIT(GPIOB->CRL, GPIO_CRL_MODE6); // 0b11 //Maximum output speed 50 MHz
	// 26.6 I2C registers(Reference Manual page 772)
	I2C_Reset(I2C);
	SET_BIT(I2C->CR2, I2C_CR2_FREQ_5 | I2C_CR2_FREQ_2); // 0x24 - 36 // f PCLK1 = 36 MHz
	I2C->OAR1 = 0;
	I2C->OAR2 = 0;
	//CLEAR_BIT(I2C1->CCR, I2C_CCR_FS); //Standard mode I2C
	SET_BIT(I2C->CCR, I2C_CCR_FS); //Fast mode I2C
	//CLEAR_BIT(I2C->CCR, I2C_CCR_DUTY); //Fm mode tlow/thigh = 2/1
	SET_BIT(I2C->CCR, I2C_CCR_DUTY); //Fm mode tlow/thigh = 16/9 (see CCR)
	//MODIFY_REG(I2C->CCR, I2C_CCR_CCR, 180); // Sm mode
	MODIFY_REG(I2C->CCR, I2C_CCR_CCR, 30); // Fm mode. DUTY 0.  (2 / 1)
	//MODIFY_REG(I2C->CCR, I2C_CCR_CCR, 4); // Fm mode. DUTY 1. (9 / 16)
	//MODIFY_REG(I2C->TRISE, I2C_TRISE_TRISE, 37); // Sm mode
	MODIFY_REG(I2C->TRISE, I2C_TRISE_TRISE, 12); // Fm mode
	SET_BIT(I2C->CR1, I2C_CR1_PE); //I2C1 enable
}

// START
bool I2C_start(I2C_TypeDef *I2C, uint32_t Timeout_ms) {
	CLEAR_BIT(I2C->CR1, I2C_CR1_POS); // ACK  (N)ACK 
	SET_BIT(I2C->CR1, I2C_CR1_START); //? START
	
	Timeout_counter_ms = Timeout_ms;
	while (READ_BIT(I2C->SR1, I2C_SR1_SB) == 0) {
		// Start condition generated
		if (!Timeout_counter_ms) return false;
	} 
	return true;
}

// SEND ADDRESS
bool I2C_send_address(I2C_TypeDef *I2C, uint8_t byte, uint32_t Timeout_ms) {
	I2C->SR1;
	I2C->DR = byte;
	
	Timeout_counter_ms = Timeout_ms;
	while ((READ_BIT(I2C->SR1, I2C_SR1_AF) == 0) && (READ_BIT(I2C->SR1, I2C_SR1_ADDR) == 0)) {
		if (!Timeout_counter_ms) return false;		
	}
	return true;
}

// SEND BYTE
bool I2C_send_byte(I2C_TypeDef *I2C, uint8_t byte, uint32_t Timeout_ms) {	
	I2C->SR1;
	I2C->SR2;
	I2C->DR = byte;
	
	Timeout_counter_ms = Timeout_ms;
	while (READ_BIT(I2C->SR1, I2C_SR1_TXE) == 0) {				
		if ((READ_BIT(I2C->SR1, I2C_SR1_AF) == 1)) {
			I2C_stop(I2C1); // STOP
			return false;
		}
		if (!Timeout_counter_ms) return false;	
	} 
	
	return true;
}

// STOP
void I2C_stop(I2C_TypeDef *I2C) {
	SET_BIT(I2C->CR1, I2C_CR1_STOP);
	if ((READ_BIT(I2C->SR1, I2C_SR1_AF) == 1)) CLEAR_BIT(I2C->SR1, I2C_SR1_AF);
	else {
		// CLEAR ADDR
		I2C1->SR1;
		I2C1->SR2;
	}
}


bool disp_write(uint8_t mode, uint8_t data) { // 1 - data, 0 - command
  if(mode) mode = dataByte;
  else mode = command;
  // if busy
	if (READ_BIT(I2C1->SR2, I2C_SR2_BUSY)) {
		if ((READ_BIT(GPIOB->IDR, GPIO_IDR_IDR6)) && (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR7))) {
			I2C_Reset(I2C1);
			I2C_Init(I2C1);
		} 		
		if (READ_BIT(I2C1->SR2, I2C_SR2_MSL)) { // if status master
			SET_BIT(I2C1->CR1, I2C_CR1_STOP); // then STOP
		} 
		
		if (I2C1->CR1 != 1) { //if I2C error, restart I2C
			CLEAR_BIT(I2C1->CR1, I2C_CR1_PE);
			SET_BIT(I2C1->CR1, I2C_CR1_PE);
		}
		return false;	
	}
	
	
  if (! I2C_start(I2C1, 100)) return false;
	if (! I2C_send_address(I2C1, (uint8_t)(address << 1), 100)) return false;
	
	if (READ_BIT(I2C1->SR1, I2C_SR1_ADDR)) {		
		
		if (! I2C_send_byte(I2C1, mode, 100)) return false;
		if (! I2C_send_byte(I2C1, data, 100)) return false;
		
		I2C_stop(I2C1); // STOP
		
		return true;
	} 
	
	I2C_stop(I2C1); // STOP
	CLEAR_BIT(I2C1->SR1, I2C_SR1_AF); // CLEAR AF
	
	
	return false;	
}


void display_init(void) {
  for(uint8_t i = 0; i < sizeof ssd1306_128x32_init; i++) disp_write(0, ssd1306_128x32_init[i]);
}


void screen_clear(void) {
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0;
}


void screen_update(void) {
  disp_write(0,0x21); // column
  disp_write(0,0);    // begin
  disp_write(0,127);  // end
  
  disp_write(0,0x22); // row
  disp_write(0,0);    // begin
  disp_write(0,3);    // end
	
	for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) disp_write(1, scr_buffer[i]);
}


void test_screen(void) {
  uint8_t flag = 0xff;
  for(uint16_t i = 0; i < 1024; i++) {
    scr_buffer[i] = flag;
    if (flag) flag = 0x00;
    else flag = 0xff;
  }
  screen_update();
  
  Delay_ms(1000);
  screen_clear();
  screen_update();
  
  Delay_ms(1000);
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0xff;
  screen_update();
}

