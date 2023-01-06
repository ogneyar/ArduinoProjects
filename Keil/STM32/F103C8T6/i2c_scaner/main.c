
#include "main.h"

static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_ms = 0;
static volatile uint32_t Timeout_counter_ms = 0;

void SysTick_Init(void);
void SystemClock_72MHz(void);
void GPIO_Init(void);
void Delay_ms(uint32_t Milliseconds);
void SysTick_Handler(void);

void I2C_Reset(I2C_TypeDef *I2C);
void I2C_Init(I2C_TypeDef *I2C);
bool I2C_start(I2C_TypeDef *I2C, uint32_t Timeout_ms);
bool I2C_send_byte(I2C_TypeDef *I2C, uint8_t byte, uint32_t Timeout_ms);
void I2C_stop(I2C_TypeDef *I2C);

bool I2C_Adress_Device_Scan(I2C_TypeDef *I2C, uint8_t Adress_Device, uint32_t Timeout_ms);
	
static bool flag_I2C_Adress_Device_ACK;

	
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
	
	flag_I2C_Adress_Device_ACK = I2C_Adress_Device_Scan(I2C1, 0x3c, 100);
	
  while (1)
  {
		GPIOC->BSRR |= GPIO_BSRR_BS13;
		GPIOB->BSRR |= GPIO_BSRR_BS2; // signal for WeAct board
		if (flag_I2C_Adress_Device_ACK) Delay_ms(1000);
		else Delay_ms(100);
		GPIOC->BSRR |= GPIO_BSRR_BR13;
		GPIOB->BSRR |= GPIO_BSRR_BR2; // signal for WeAct board
		if (flag_I2C_Adress_Device_ACK) Delay_ms(1000);
		else Delay_ms(100);
  }
	
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


void I2C_Reset(I2C_TypeDef *I2C) {
	//26.6.1 I2C Control register 1 (I2C_CR1) (page 772)
	SET_BIT(I2C->CR1, I2C_CR1_SWRST); //: I2C Peripheral not under reset
	while (READ_BIT(I2C->CR1, I2C_CR1_SWRST) == 0) ;
	CLEAR_BIT(I2C->CR1, I2C_CR1_SWRST); //: I2C Peripheral not under reset
	while (READ_BIT(I2C->CR1, I2C_CR1_SWRST)) ;
	/* 
	Note: If this bit is reset while a communication is on going, the peripheral is disabled at the
				end of the current communication, when back to IDLE state.
				All bit resets due to PE=0 occur at the end of the communication.
				In master mode, this bit must not be reset before the end of the communication.
	*/
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
	
	// 26.6.1 I2C Control register 1 (I2C_CR1) (page 772)
	I2C_Reset(I2C);
	
	// CLEAR_BIT(I2C->CR1, I2C_CR1_ALERT); //Releases SMBA pin high.Alert Response Address Header followed by NACK
	// CLEAR_BIT(I2C->CR1, I2C_CR1_PEC); //No PEC transfer
	// CLEAR_BIT(I2C->CR1, I2C_CR1_POS); //ACK bit controls the (N)ACK of the current byte being received in the shift register
	// CLEAR_BIT(I2C->CR1, I2C_CR1_ACK); //No acknowledge returned
	// CLEAR_BIT(I2C->CR1, I2C_CR1_STOP); //No Stop generation
	// CLEAR_BIT(I2C->CR1, I2C_CR1_START); //No Start generation
	// CLEAR_BIT(I2C->CR1, I2C_CR1_NOSTRETCH); //Clock stretching enabled
	// CLEAR_BIT(I2C->CR1, I2C_CR1_ENGC); //General call disabled. Address 00h is NACKed.
	// CLEAR_BIT(I2C->CR1, I2C_CR1_ENPEC); //PEC calculation disabled
	// CLEAR_BIT(I2C->CR1, I2C_CR1_ENARP); //ARP disable
	// CLEAR_BIT(I2C->CR1, I2C_CR1_SMBTYPE); //SMBus Device
	// CLEAR_BIT(I2C->CR1, I2C_CR1_SMBUS); //I2C mode
	
	// 26.6.2 I2C Control register 2(I2C_CR2)(page 774)
	// CLEAR_BIT(I2C->CR2, I2C_CR2_LAST); //Next DMA EOT is not the last transfer
	// CLEAR_BIT(I2C->CR2, I2C_CR2_DMAEN); //DMA requests disabled
	// CLEAR_BIT(I2C->CR2, I2C_CR2_ITBUFEN); //TxE = 1 or RxNE = 1 does not generate any interrupt.
	// CLEAR_BIT(I2C->CR2, I2C_CR2_ITEVTEN); //Event interrupt disabled
	// CLEAR_BIT(I2C->CR2, I2C_CR2_ITERREN); //Error interrupt disabled
	SET_BIT(I2C->CR2, I2C_CR2_FREQ_5 | I2C_CR2_FREQ_2); // 0x24 - 36 // f PCLK1 = 36 MHz
	
	// 26.6.3 I2C Own address register 1(I2C_OAR1)(page 776)
	I2C->OAR1 = 0;
	// 26.6.4 I2C Own address register 2(I2C_OAR2)(page 776)
	I2C->OAR2 = 0;
	
	// 26.6.8 I2C Clock control register (I2C_CCR)(page 781)
	//CLEAR_BIT(I2C1->CCR, I2C_CCR_FS); //Standard mode I2C
	SET_BIT(I2C->CCR, I2C_CCR_FS); //Fast mode I2C

	CLEAR_BIT(I2C->CCR, I2C_CCR_DUTY); //Fm mode tlow/thigh = 2
	//SET_BIT(I2C->CCR, I2C_CCR_DUTY); //Fm mode tlow/thigh = 16/9 (see CCR)
	
	// CCR = APB2clock / 2 * 100 000 - from Standard mode I2C (36000000 / 2 * 100000) = 180
	//MODIFY_REG(I2C->CCR, I2C_CCR_CCR, 180); // Sm mode
	// CCR = APB2clock / 3 * 400 000 - from Fast mode I2C (36000000 / 3 * 400000) = 30
	MODIFY_REG(I2C->CCR, I2C_CCR_CCR, 30); // Fm mode. DUTY 0.  (2 / 1)
	// CCR = APB2clock / 25 * 400 000 - from Fast mode I2C (36000000 / 25 * 400000) = 3.6 = 4
	//MODIFY_REG(I2C->CCR, I2C_CCR_CCR, 4); // Fm mode. DUTY 1. (9 / 16)
	
	// 26.6.9 I2C TRISE register (I2C_TRISE)(page 782)
	// TRISE = (1000 ns / Tpclk ns) + 1 = 37  (Tpclk s = 1 / 36000000 s, Tpclk ns = 1000 / 36 ns)
	//MODIFY_REG(I2C->TRISE, I2C_TRISE_TRISE, 37); // Sm mode
	// TRISE = (300 ns / Tpclk ns) + 1 = 12  (Tpclk s = 1 / 36000000 s, Tpclk ns = 1000 / 36 ns)
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

// SEND BYTE
bool I2C_send_byte(I2C_TypeDef *I2C, uint8_t byte, uint32_t Timeout_ms) {
	I2C->SR1;
	I2C->DR = byte;
	
	Timeout_counter_ms = Timeout_ms;
	while ((READ_BIT(I2C->SR1, I2C_SR1_AF) == 0) && (READ_BIT(I2C->SR1, I2C_SR1_ADDR) == 0)) {
		if (!Timeout_counter_ms) return false;		
	}
	return true;
}

// STOP
void I2C_stop(I2C_TypeDef *I2C) {
	SET_BIT(I2C->CR1, I2C_CR1_STOP);
}

// I2C SCANER
bool I2C_Adress_Device_Scan(I2C_TypeDef *I2C, uint8_t Adress_Device, uint32_t Timeout_ms) {
	// if busy
	if (READ_BIT(I2C->SR2, I2C_SR2_BUSY)) {
		if ((READ_BIT(GPIOB->IDR, GPIO_IDR_IDR6)) && (READ_BIT(GPIOB->IDR, GPIO_IDR_IDR7))) {
			I2C_Reset(I2C);
			I2C_Init(I2C);
		} 		
		if (READ_BIT(I2C->SR2, I2C_SR2_MSL)) { // if status master
			SET_BIT(I2C->CR1, I2C_CR1_STOP); // then STOP
		} 
		
		if (I2C->CR1 != 1) { //if I2C error, restart I2C
			CLEAR_BIT(I2C->CR1, I2C_CR1_PE);
			SET_BIT(I2C->CR1, I2C_CR1_PE);
		}
		return false;	
	}
	
	if (! I2C_start(I2C1, Timeout_ms)) return false;
	
	if (! I2C_send_byte(I2C1, (uint8_t)(Adress_Device << 1), Timeout_ms)) return false;
	
	
	if (READ_BIT(I2C->SR1, I2C_SR1_ADDR)) {
		I2C_stop(I2C); // STOP
		// CLEAR ADDR
		I2C->SR1;
		I2C->SR2;
		return true;
	} 
	
	I2C_stop(I2C); // STOP
	CLEAR_BIT(I2C->SR1, I2C_SR1_AF); // CLEAR AF
	
	
	return false;	
}





