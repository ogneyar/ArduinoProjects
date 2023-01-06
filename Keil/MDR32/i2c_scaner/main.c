
#include "main.h"

static volatile uint32_t SysTimer_ms = 0;
static volatile uint32_t Delay_counter_ms = 0;
static volatile uint32_t Timeout_counter_ms = 0;

void SysTick_Init(void);
void SystemClock_Init(void);
void PllInit(unsigned int pll_mul);
void GPIO_Init(void);
void Delay_ms(uint32_t Milliseconds);
void SysTick_Handler(void);

//void I2C_Reset();
void MDR_I2C_Init(void);
void I2C_start(void);
void I2C_send_byte(uint8_t byte);
uint8_t I2C_get_byte(void);
void I2C_stop(void);

//bool I2C_Adress_Device_Scan(uint8_t Adress_Device, uint32_t Timeout_ms);
	
static bool flag_I2C_Adress_Device_ACK;

const static uint8_t address = 0x78;
static uint8_t address_command = (address<<1);
static uint8_t address_data = (address<<1) | 1;
static uint8_t data = 0x55;
static uint8_t command = 0xAA;
	
	
// main function
int main(void)
{	
	/* SysTick timer settings */
	SysTick_Init();
	
	/* Configure the system clock */
	SystemClock_Init();

	/* Initialize all configured peripherals */
	GPIO_Init();
	
	
	MDR_I2C_Init();	
	
	Delay_ms(100);
	
	I2C_start();
	I2C_send_byte(address_command);
	I2C_send_byte(command);
	I2C_stop();
			
	
	//flag_I2C_Adress_Device_ACK = I2C_Adress_Device_Scan(I2C1, 0x3c, 100);
	
	Delay_ms(500);
	
	
  while (1)
  {
		
		if (!Timeout_counter_ms) {
			I2C_start();
			I2C_send_byte(address_data);
			I2C_send_byte(data);
			I2C_stop();
			Timeout_counter_ms = 10;
		}
		
		if (!Delay_counter_ms) {
			MDR_PORTB->RXTX ^= LED_HL1;
			MDR_PORTB->RXTX ^= LED_HL2;	
			MDR_PORTC->RXTX ^= LED_HL3;
			if (flag_I2C_Adress_Device_ACK) Delay_counter_ms = 1000;
			else Delay_counter_ms = 100;
			
		}
  }
	
}


/* SysTick timer settings */
void SysTick_Init(void) {	
	
	// divider (SysTick 24 bit) max 16 777 216
	SysTick->LOAD |= 80000 - 1; //  this 1KHz clock, if FCPU = 80MHz // 16000 - 1; //  this 1KHz clock, if FCPU = 16MHz // 72000 - 1; //  this 1KHz clock, if FCPU = 72MHz
	
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
	MDR_RST_CLK->PLL_CONTROL |= (pll_mul-1)<<RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos; // pll_mul * 8MHz
	
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
	//MDR_PORTC->RXTX |= LED_HL3;
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

/*
void I2C_Reset(I2C_TypeDef *I2C) {
	//26.6.1 I2C Control register 1 (I2C_CR1) (page 772)
	SET_BIT(I2C->CR1, I2C_CR1_SWRST); //: I2C Peripheral not under reset
	while (READ_BIT(I2C->CR1, I2C_CR1_SWRST) == 0) ;
	CLEAR_BIT(I2C->CR1, I2C_CR1_SWRST); //: I2C Peripheral not under reset
	while (READ_BIT(I2C->CR1, I2C_CR1_SWRST)) ;
}*/

void MDR_I2C_Init() {
    MDR_RST_CLK->PER_CLOCK |= PORTC_CLK;
    MDR_PORTC->FUNC &= ~(PORT_FUNC_MODE0_Msk | PORT_FUNC_MODE1_Msk);
    MDR_PORTC->FUNC |= (PORT_FUNC_ALTER << PORT_FUNC_MODE0_Pos
                     | PORT_FUNC_ALTER << PORT_FUNC_MODE1_Pos);
    MDR_PORTC->ANALOG |= SCL1 | SDA1;
    MDR_PORTC->PWR |= (PORT_SPEED_MIDDLE << PORT_PWR0_Pos
                    | PORT_SPEED_MIDDLE << PORT_PWR1_Pos);

    MDR_RST_CLK->PER_CLOCK |= I2C1_CLK;
    MDR_I2C->PRL = 150; // Fscl = HCLK/(5*(DIV+1))    Fscl = 100KHz  (HCLK = 72MHz   => DIV = 143)  or  (HCLK = 80MHz   => DIV = 159)  or  (HCLK = 16MHz   => DIV = 45)
    MDR_I2C->PRH = 0;
    MDR_I2C->CTR |= (1 << I2C_CTR_EN_I2C_Pos) // enable I2C
                 |  (0 << I2C_CTR_EN_INT_Pos) // disable interrupt
                 |  (0 << I2C_CTR_S_I2C_Pos); // speed I2C (0 - after 400KHz, 1 - after 1MHz)
}

// START
void I2C_start() {	
	MDR_I2C->CMD |= I2C_CMD_START;
}

// SEND BYTE
void I2C_send_byte(uint8_t byte) {
	
	MDR_I2C->TXD = byte;
	
	MDR_I2C->CMD |= I2C_CMD_WR;
	
	while (MDR_I2C->STA & I2C_STA_TR_PROG) ;
	
}

// GET BYTE
uint8_t I2C_get_byte() {
	
	MDR_I2C->CMD |= I2C_CMD_RD;
		
	while (MDR_I2C->STA & I2C_STA_TR_PROG) ;
	
	return (uint8_t)MDR_I2C->RXD;
}

// STOP
void I2C_stop() {
	MDR_I2C->CMD |= I2C_CMD_STOP;
}

// I2C SCANER
/*
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

*/



