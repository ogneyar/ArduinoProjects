
#ifndef __MDR_main__
#define __MDR_main__

#include "MDR32F9Q2I.h"
#include <stdint.h>
#include <stdbool.h>

#define PB1 1
#define PB2 2
#define PC0 0
#define PC1 1
#define PC2 2
#define PD5 5
#define LED_HL1 (1<<PB1) // red
#define LED_HL2 (1<<PB2) // green
#define LED_HL3 (1<<PC2) // blue
#define BTN_USR (1<<PD5) // blue
#define SCL1 (1<<PC0) // i2c clock
#define SDA1 (1<<PC1) // i2c data
#define DMA_CLK (1<<5)
#define UART1_CLK (1<<6)
#define UART2_CLK (1<<7)
#define SPI1_CLK (1<<8)
#define I2C1_CLK (1<<10)
#define TIMER1_CLK (1<<14)
#define TIMER2_CLK (1<<15)
#define TIMER3_CLK (1<<16)
#define ADC1_CLK (1<<17)
#define DAC1_CLK (1<<18)
#define COMP_CLK (1<<19)
#define SPI2_CLK (1<<20)
#define PORTA_CLK (1<<21)
#define PORTB_CLK (1<<22)
#define PORTC_CLK (1<<23)
#define PORTD_CLK (1<<24)
#define PORTE_CLK (1<<25)
#define PORTF_CLK (1<<29)

#define PORT_FUNC_ALTER 2 // 0b10

#define PORT_SPEED_MIDDLE 1 // 0b01
#define PORT_SPEED_FAST 2 // 0b10
#define PORT_SPEED_MAXFAST 3 // 0b11


void SysTick_Init(void);
void SystemClock_Init(void);
void PllInit(unsigned int pll_mul);
void GPIO_Init(void);
void Delay_us(uint32_t Microseconds);
void Delay_ms(uint32_t Milliseconds);
void SysTick_Handler(void);

void I2C_Init(void);
void I2C_start(void);
void I2C_send_byte(uint8_t byte);
uint8_t I2C_read_byte(void);
void I2C_stop(void);

void Display_Init(void);
void Disp_Write_Byte(uint8_t mode, uint8_t data);
void Disp_Write_Array(void);
void Screen_Clear(void);
void Screen_Update(void);
void Lines_Screen_Pixels(void);
void Full_Screen_Pixels(void);
void Test_Screen(void);


#endif

