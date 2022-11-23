
#include "main.h"

static volatile uint32_t Counter_ADC = 0;

static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_ms = 0;

void SysTick_Init(void);
void SystemClock_72MHz(void);
void GPIO_Init(void);
void Delay_ms(uint32_t Milliseconds);
void SysTick_Handler(void);
void ADC1_2_IRQHandler(void);
	
	
	
// main function
int main(void)
{	
	/* SysTick timer settings */
	SysTick_Init();
	
	/* Configure the system clock */
  SystemClock_72MHz();

  /* Initialize all configured peripherals */
	GPIO_Init();
	
	
	// setting ADC
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN); // ADC1 clock enable
		
	// 11.12.2 ADC control register 1 (ADC_CR1) (page 238
	//SET_BIT(ADC1->CR1, ADC_CR1_EOCIE); // EOCIE: Interrupt enable for EOC // 1: EOC interrupt enabled
	//CLEAR_BIT(ADC1->CR1, ADC_CR1_AWDIE); // AWDIE: Analog watchdog interrupt enable // 0: Analog watchdog interrupt disabled
	//CLEAR_BIT(ADC1->CR1, ADC_CR1_JEOCIE); // JEOCIE: Interrupt enable for injected channels // 0: JEOC interrupt disabled
	SET_BIT(ADC1->CR1, ADC_CR1_JEOCIE); // SCAN: Scan mode // 1: Scan mode enabled
	//CLEAR_BIT(ADC1->CR1, ADC_CR1_AWDSGL); // AWDSGL: Enable the watchdog on a single channel in scan mode // 0: Analog watchdog enabled on all channels
	//CLEAR_BIT(ADC1->CR1, ADC_CR1_JAUTO); // JAUTO: Automatic Injected Group conversion // 0: Automatic injected group conversion disabled
	//CLEAR_BIT(ADC1->CR1, ADC_CR1_DISCEN); // DISCEN: Discontinuous mode on regular channels (0: Discontinuous mode on regular channels disabled)
	//CLEAR_BIT(ADC1->CR1, ADC_CR1_JDISCEN); // JDISCEN: Discontinuous mode on injected channels (0: Discontinuous mode on injected channels disabled)
	MODIFY_REG(ADC1->CR1, ADC_CR1_DUALMOD, ADC_CR1_DUALMOD_1 | ADC_CR1_DUALMOD_2); // DUALMOD[3:0]: Dual mode selection (0110: Regular simultaneous mode only)
	//CLEAR_BIT(ADC1->CR1, ADC_CR1_JAWDEN); // JAWDEN: Analog watchdog enable on injected channels (0: Analog watchdog disabled on injected channels)
	//CLEAR_BIT(ADC1->CR1, ADC_CR1_AWDEN); // AWDEN: Analog watchdog enable on regular channels (0: Analog watchdog disabled on regular channels)
	
	
	// 11.12.3 ADC control register 2 (ADC_CR2)
	SET_BIT(ADC1->CR2, ADC_CR2_ADON); // ADON: A/D converter ON / OFF (1: Enable ADC and to start conversion)	
	
	// run conversion automatically (continuously)
	SET_BIT(ADC1->CR2, ADC_CR2_CONT); // CONT: Continuous conversion (1: Continuous conversion mode)
	
	SET_BIT(ADC1->CR2, ADC_CR2_CAL); // CAL: A/D Calibration (1: Enable calibration)
	while(READ_BIT(ADC1->CR2, ADC_CR2_CAL) == SET) __asm__("nop"); // waiting for calibration to stop
	Delay_ms(1);
	SET_BIT(ADC1->CR2, ADC_CR2_DMA); // DMA: Direct memory access mode (1: DMA mode enabled)
	//CLEAR_BIT(ADC1->CR2, ADC_CR2_ALIGN); // ALIGN: Data alignment (0: Right Alignment)
	SET_BIT(ADC1->CR2, ADC_CR2_EXTSEL); // EXTSEL[2:0]: External event select for regular group (111: SWSTART)
	//CLEAR_BIT(ADC1->CR2, ADC_CR2_EXTTRIG); // EXTTRIG: External trigger conversion mode for regular channels (0: Conversion on external event disabled)
	
	// run conversion manually (if automatically conversion off)
	//SET_BIT(ADC1->CR2, ADC_CR2_SWSTART); // SWSTART: Start conversion of regular channels (1: Starts conversion of regular channels)
	
	SET_BIT(ADC1->CR2, ADC_CR2_TSVREFE); // TSVREFE: Temperature sensor and VREFINT enable (1: Temperature sensor and VREFINT channel enabled)
	
	
	// 11.12.4 ADC sample time register 1 (ADC_SMPR2) (page245)
	SET_BIT(ADC1->SMPR2, ADC_SMPR2_SMP0); // 111: 239.5 cycles
	SET_BIT(ADC1->SMPR2, ADC_SMPR2_SMP1); // 111: 239.5 cycles
	// 11.12.4 ADC sample time register 1 (ADC_SMPR1) (page244)
	SET_BIT(ADC1->SMPR1, ADC_SMPR1_SMP17); // 111: 239.5 cycles
	
	
	// 11.12.9 ADC regular sequence register 1 (ADC_SQR1) (page247)
	MODIFY_REG(ADC1->SQR1, ADC_SQR1_L, ADC_SQR1_L_0); // L[3:0]: Regular channel sequence length (0001: 2 conversions)
	
	
	// 11.12.11 ADC regular sequence register 3 (ADC_SQR3) (page249)
	MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ1, 0x00000000); // hz
	MODIFY_REG(ADC1->SQR3, ADC_SQR3_SQ2, ADC_SQR3_SQ2_0 | ADC_SQR3_SQ2_4); // hz
	
	// if EOCIE interrupt enable
	//NVIC_EnableIRQ(ADC1_2_IRQn);
	
	
	
  while (1)
  {
		GPIOC->BSRR |= GPIO_BSRR_BS13;
		Delay_ms(300);
		GPIOC->BSRR |= GPIO_BSRR_BR13;
		Delay_ms(300);
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
	
	// APB2 peripheral clock enable register (RCC_APB2ENR)
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN); // enable clock port A
	// 9.2.1 Port configuration register low (GPIOx_CRL) (x=A..G)
	// PA0 - input
	GPIOA->CRL &= ~GPIO_CRL_CNF0; // 00: Analog mode
	GPIOA->CRL &= ~GPIO_CRL_MODE0; // 00: Input mode (reset state)
	// PA1 - input
	GPIOA->CRL &= ~GPIO_CRL_CNF1; // 00: Analog mode
	GPIOA->CRL &= ~GPIO_CRL_MODE1; // 00: Input mode (reset state)
	
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
}


void ADC1_2_IRQHandler(void) {
	Counter_ADC++;
	
	// 11.12.1 ADC status register (ADC_SR)
	if (READ_BIT(ADC1->SR, ADC_SR_EOC)) { // Bit 1 EOC: End of conversion
		ADC1->DR; // read 
	}
	
}

