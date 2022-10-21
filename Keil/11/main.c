
#include "MDR32F9Q2I.h"

#include "MDR32FxQI_config.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_rst_clk.h"


#define ALL_PORTS_CLK (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | \
                       RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | \
                       RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF)

PORT_InitTypeDef PORT_InitStructure;


void Init_All_Ports(void)
{
    RST_CLK_PCLKcmd(ALL_PORTS_CLK, ENABLE);
	
    PORT_StructInit(&PORT_InitStructure);
    //PORT_Init(MDR_PORTA, &PORT_InitStructure);
    PORT_Init(MDR_PORTB, &PORT_InitStructure);
    //PORT_Init(MDR_PORTC, &PORT_InitStructure);
    PORT_Init(MDR_PORTD, &PORT_InitStructure);
    //PORT_Init(MDR_PORTE, &PORT_InitStructure);
    //PORT_Init(MDR_PORTF, &PORT_InitStructure);
	
    RST_CLK_PCLKcmd(ALL_PORTS_CLK, DISABLE);
}


int main(void)
{
	
    Init_All_Ports();

    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTD/* | RST_CLK_PCLK_PORTE*/, ENABLE);

    PORT_InitStructure.PORT_Pin   = (PORT_Pin_1 | PORT_Pin_2);
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTB, &PORT_InitStructure);
	
    PORT_InitStructure.PORT_Pin   = (PORT_Pin_5);
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTD, &PORT_InitStructure);

    /*PORT_InitStructure.PORT_Pin   = (PORT_Pin_3);
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;

    PORT_Init(MDR_PORTE, &PORT_InitStructure);*/


    while(1)
    {
        if (PORT_ReadInputDataBit(MDR_PORTB, PORT_Pin_5) == RESET)
        {
            PORT_SetBits(MDR_PORTC, PORT_Pin_1);
						PORT_ResetBits(MDR_PORTC, PORT_Pin_2);
        }
        else
        {
					  PORT_SetBits(MDR_PORTC, PORT_Pin_2);
            PORT_ResetBits(MDR_PORTC, PORT_Pin_1);
        }
    
        /*if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_3) == RESET)
        {
            PORT_SetBits(MDR_PORTC, PORT_Pin_1);
        }
        else
        {
            PORT_ResetBits(MDR_PORTC, PORT_Pin_1);
        }*/
    }
}


#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    while (1)
    {
    }
}
#endif

