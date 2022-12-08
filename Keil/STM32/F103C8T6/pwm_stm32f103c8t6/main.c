
#include "main.h"

static volatile uint32_t Counter = 0;

static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_ms = 0;

void SysTick_Init(void);
void SystemClock_72MHz(void);
void GPIO_Init(void);
void Delay_ms(uint32_t Milliseconds);
void SysTick_Handler(void);
void TIM3_IRQHandler(void);
	
	
// main function
int main(void)
{	
	/* SysTick timer settings */
	SysTick_Init();
	
	/* Configure the system clock */
  SystemClock_72MHz();

  /* Initialize all configured peripherals */
	GPIO_Init();
	
	// setting timer (page 48)
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN); // enable clock timer 3
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN); // enable clock alternate function
	
	// 15.4.1 TIMx control register 1 (TIMx_CR1) (page 404)
	CLEAR_BIT(TIM3->CR1, TIM_CR1_UDIS); // UDIS: Update disable // 0: UEV enabled.
	CLEAR_BIT(TIM3->CR1, TIM_CR1_URS); // URS: Update request source // 0: Any of the following events generate an update interrupt or DMA request if enabled.
	CLEAR_BIT(TIM3->CR1, TIM_CR1_OPM); // OPM: One-pulse mode // 0: Counter is not stopped at update event
	CLEAR_BIT(TIM3->CR1, TIM_CR1_DIR); // DIR: Direction // 0: Counter used as upcounter
	TIM3->CR1 &= ~TIM_CR1_CMS; // CMS: Center-aligned mode selection // 00: Edge-aligned mode
	SET_BIT(TIM3->CR1, TIM_CR1_ARPE); // ARPE: Auto-reload preload enable // 1: TIMx_ARR register is buffered
	TIM3->CR1 &= ~TIM_CR1_CKD; // CKD: Clock division // 00: tDTS = tCK_INT
	
	// 15.4.4 TIMx DMA/Interrupt enable register (TIMx_DIER) (page 409)
	SET_BIT(TIM3->DIER, TIM_DIER_UIE); // UIE: Update interrupt enable // 1: Update interrupt enabled.
	
	//TIM3->PSC = 7200 - 1; // 72 MHz / 7200 = 10 000 Hz
	//TIM3->ARR = 10000 - 1; // 10 000 Hz / 10 000 = 1 Hz
	TIM3->PSC = 720 - 1; // 72 MHz / 720 = 100 000 Hz
	TIM3->ARR = 100 - 1; // 100 000 Hz / 100 = 1 000 Hz
	
	NVIC_EnableIRQ(TIM3_IRQn); // enable interrupt timer 3
	// start timer
	SET_BIT(TIM3->CR1, TIM_CR1_CEN); // CEN: Counter enable // 1: Counter enabled
		
		
	
	// setting PWM	(channel 1)
	// 15.4.7 TIMx capture/compare mode register 1 (TIMx_CCMR1)
	CLEAR_BIT(TIM3->CCMR1, TIM_CCMR1_CC1S); // CC1S: Capture/Compare 1 selection // 00: CC1 channel is configured as output.
	CLEAR_BIT(TIM3->CCMR1, TIM_CCMR1_OC1FE); // OC1FE: Output compare 1 fast enable // 0: fast mode disable
	SET_BIT(TIM3->CCMR1, TIM_CCMR1_OC1PE); // OC1PE: Output compare 1 preload enable
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // OC1M: Output compare 1 mode // 110: PWM mode 1
	CLEAR_BIT(TIM3->CCMR1, TIM_CCMR1_OC1CE); // OC1CE: Output compare 1 clear enable
	
	// setting PWM	(channel 2)
	// 15.4.7 TIMx capture/compare mode register 1 (TIMx_CCMR1)
	CLEAR_BIT(TIM3->CCMR1, TIM_CCMR1_CC2S); // CC2S: Capture/Compare 1 selection // 00: CC1 channel is configured as output.
	CLEAR_BIT(TIM3->CCMR1, TIM_CCMR1_OC2FE); // OC2FE: Output compare 1 fast enable // 0: fast mode disable
	SET_BIT(TIM3->CCMR1, TIM_CCMR1_OC2PE); // OC2PE: Output compare 1 preload enable
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; // OC2M: Output compare 1 mode // 110: PWM mode 1
	CLEAR_BIT(TIM3->CCMR1, TIM_CCMR1_OC2CE); // OC2CE: Output compare 1 clear enable
	
	// run pwm
	// 15.4.9 TIMx capture/compare enable register (TIMx_CCER)
	SET_BIT(TIM3->CCER, TIM_CCER_CC1E); // CC1E: Capture/Compare 1 output enable
	SET_BIT(TIM3->CCER, TIM_CCER_CC1P); // CC1P: Capture/Compare 1 output polarity // 1: OC1 active low.
	
	SET_BIT(TIM3->CCER, TIM_CCER_CC2E); // CC2E: Capture/Compare 1 output enable
	CLEAR_BIT(TIM3->CCER, TIM_CCER_CC2P); // CC2P: Capture/Compare 1 output polarity // 0: OC1 active high.
	
	//TIM3->CCR1 = 5000 - 1; // middle 1 Hz
	//TIM3->CCR1 = 5 - 1; // middle 1 KHz
	TIM3->CCR1 = 1;
	
	
  while (1)
  {
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
	// PA6 - out
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN); // enable clock port A
	GPIOA->CRL |= GPIO_CRL_CNF6_1; // 0x10: push-pull
	GPIOA->CRL |= GPIO_CRL_MODE6; // 0x11: Maximum output speed 50 MHz
	
	// PA7 - out
	GPIOA->CRL |= GPIO_CRL_CNF7_1; // 0x10: push-pull
	GPIOA->CRL |= GPIO_CRL_MODE7; // 0x11: Maximum output speed 50 MHz
	
	// PC13 - out
/* APB2 peripheral clock enable register (RCC_APB2ENR) */
	// IOPCEN: IO port C clock enable
	//SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPCEN); // 1: IO port C clock enabled
/* --------------------------------------------------- */	
	
/* Port configuration register high (GPIOx_CRH) (x=A..G) */
	// CNFy[1:0]: Port x configuration bits (y= 8 .. 15)
	//GPIOC->CRH &= ~GPIO_CRH_CNF13; // 00: General purpose output push-pull (PC13)
	// MODEy[1:0]: Port x mode bits (y= 8 .. 15)
	//GPIOC->CRH |= GPIO_CRH_MODE13; // 11: Maximum output speed 50 MHz
/* ----------------------------------------------------- */
	
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


void TIM3_IRQHandler(void) {
	CLEAR_BIT(TIM3->SR, TIM_SR_UIF); // reset flag interrupt
	Counter++;
	/*
	if (Counter > 1000) {
		Counter = 0;
		if (TIM3->CCR1 > 99) TIM3->CCR1 = 1;
		else TIM3->CCR1 = TIM3->CCR1 + 1;
	}
	*/
}

