
#include "main.h"


static bool PA1_Pin_state;
static bool PB0_Pin_state;

static volatile uint32_t counter_0 = 0;
static volatile uint32_t counter_1 = 0;

static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_ms = 0;

void SysTick_Init(void);
void SystemClock_72MHz(void);
void GPIO_Init(void);
void Delay_ms(uint32_t Milliseconds);
void SysTick_Handler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void Interrupt_Init(void);
	
	
// main function
int main(void)
{	
	/* SysTick timer settings */
	SysTick_Init();
	
	/* Configure the system clock */
  SystemClock_72MHz();

  /* Initialize all configured peripherals */
	GPIO_Init();
	
	/* Interrupt enable */
	Interrupt_Init();

  while (1)
  {
		//PA1_Pin_state = GPIOA->IDR & GPIO_IDR_IDR1;
		PA1_Pin_state = READ_BIT(GPIOA->IDR, GPIO_IDR_IDR1);
		//PB0_Pin_state = GPIOB->IDR & GPIO_IDR_IDR0;
		PB0_Pin_state = READ_BIT(GPIOB->IDR, GPIO_IDR_IDR0);
		
		if (PB0_Pin_state) {
			SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS13);
		}else {
			SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR13);
		}
			
		Delay_ms(100);
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
	
/* Port configuration register high (GPIOx_CRH) (x=A..G) */
	// CNFy[1:0]: Port x configuration bits (y= 8 .. 15)
	GPIOC->CRH &= ~GPIO_CRH_CNF13; // 00: General purpose output push-pull (PC13)
	// MODEy[1:0]: Port x mode bits (y= 8 .. 15)
	GPIOC->CRH |= GPIO_CRH_MODE13; // 11: Maximum output speed 50 MHz
/* ----------------------------------------------------- */
	
	// PA1 - input
/* APB2 peripheral clock enable register (RCC_APB2ENR) */
	// IOPAEN: IO port A clock enable
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN); // 1: IO port A clock enabled
/* --------------------------------------------------- */	
	
/* Port configuration register low (GPIOx_CRL) (x=A..G) */	
	// CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
	GPIOA->CRL |= GPIO_CRL_CNF1_0; // 01: Floating input (reset state) (PA1)	
	// MODEy[1:0]: Port x mode bits (y= 0 .. 7)
	GPIOA->CRL &= ~GPIO_CRL_MODE1; // 00: Input mode (reset state)
/* ----------------------------------------------------- */
	
	// PB0 - input pull up
/* APB2 peripheral clock enable register (RCC_APB2ENR) */	
	// IOPBEN: IO port B clock enable
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPBEN); // 1: IO port B clock enabled
/* --------------------------------------------------- */	
	
/* Port configuration register low (GPIOx_CRL) (x=A..G) */	
	// CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
	GPIOB->CRL |= GPIO_CRL_CNF1_1; // 10: Input with pull-up / pull-down (PB0)	
	// MODEy[1:0]: Port x mode bits (y= 0 .. 7)
	GPIOB->CRL &= ~GPIO_CRL_MODE1; // 00: Input mode (reset state)
/* ----------------------------------------------------- */
	GPIOB->BSRR |= GPIO_BSRR_BS0; // pull up
	//GPIOB->BSRR |= GPIO_BSRR_BR0; // pull down
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

void EXTI0_IRQHandler(void) {
	// Pending register (EXTI_PR)
	SET_BIT(EXTI->PR, EXTI_PR_PR0);
	counter_0++;
}

void EXTI1_IRQHandler(void) {
	// Pending register (EXTI_PR)
	SET_BIT(EXTI->PR, EXTI_PR_PR1);
	counter_1++;
}


void Interrupt_Init(void) {
/* APB2 peripheral clock enable register (RCC_APB2ENR) */
	// AFIOEN: Alternate function IO clock enable
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN); // Alternate Functions
/* --------------------------------------------------- */
	
/* External interrupt configuration register 1 (AFIO_EXTICR1) */
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB; // EXTI0, PB0
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI1_PA; // EXTI1, PA1
/* ---------------------------------------------------------- */
	
/* Interrupt mask register (EXTI_IMR) */
	// MRx: Interrupt Mask on line x
	EXTI->IMR |= EXTI_IMR_MR0; // enable interrupt on EXTI0
	EXTI->IMR |= EXTI_IMR_MR1; // enable interrupt on EXTI1
/* ---------------------------------- */
	
/* Rising trigger selection register (EXTI_RTSR) */
	EXTI->RTSR |= EXTI_RTSR_TR0;  // EXTI0, PB0 Rising on
	EXTI->FTSR &= ~EXTI_FTSR_TR0; // EXTI0, PB0 Falling off
	EXTI->RTSR |= EXTI_RTSR_TR1;  // EXTI1, PA1 Rising on
	EXTI->FTSR |= EXTI_FTSR_TR1;  // EXTI1, PA1 Falling on
/* --------------------------------------------- */

	// interrupt enable EXTI0
	NVIC_EnableIRQ(EXTI0_IRQn);
	// interrupt enable EXTI1
	NVIC_EnableIRQ(EXTI1_IRQn);
}
