#include <MDR1986VK01.h>
#include <MDR1986VK01_port.h>

#define LedBlue  PORT_Pin_9
#define LedRed   PORT_Pin_13
#define LED_PORT MDR_PORTB

#define LED_DELAY       500000

void Delay(uint32_t waitTicks)
{
    volatile uint32_t i;
    for (i = 0; i < waitTicks; i++);
}

void LED_Show(uint32_t ledSel)
{
    PORT_SetBits(LED_PORT, ledSel);
    Delay(LED_DELAY);
    PORT_ResetBits(LED_PORT, ledSel);
}

int main(void)
{
    PORT_InitTypeDef LedPort;

    MDR_CLK->KEY = 0x8555AAA1;
    MDR_CLK->PER0_CLK |=  1<<14; // PORTB EN

    LED_PORT->KEY = 0x8555AAA1;
    PORT_DeInit(LED_PORT);

    PORT_StructInit( &LedPort );

    LedPort.PORT_Pin     = LedBlue | LedRed;
    LedPort.PORT_SOE     = PORT_SOE_OUT;
    LedPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    LedPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    LedPort.PORT_SPWR    = PORT_SPWR_300;

    PORT_Init( LED_PORT, &LedPort );

    while(1)
    {
        LED_Show(LedBlue);
        LED_Show(LedRed);
    }
}


