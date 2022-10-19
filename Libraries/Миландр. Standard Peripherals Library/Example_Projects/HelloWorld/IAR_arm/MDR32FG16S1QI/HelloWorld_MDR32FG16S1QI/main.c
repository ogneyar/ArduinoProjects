#include <MDR32FxQI_port.h>
#include <MDR32FxQI_rst_clk.h>

//      �����������
#define LED_PERIOD      500000

#define LED_PORT_CLK    RST_CLK_PCLK_PORTB
#define LED_PORT        MDR_PORTB
#define LED_PORT_PIN    PORT_Pin_11

//  �������� ������� ��������, ������������� ����
void Delay(int waitTicks);

//  ����� �����, ������ ���������� ���������� ���������
int main()
{
    // ������� ��������� ������������ ������(-��) ����� GPIO
    PORT_InitTypeDef GPIOInitStruct;

    //  �������� ������������ ����� LED_PORT_CLK
    RST_CLK_PCLKcmd (LED_PORT_CLK, ENABLE);

    //  �������������� ��������� ������������ ������(-��) ����� ���������� �� ���������
    PORT_StructInit(&GPIOInitStruct);

    //  �������� �������� �� ��������� �� ����������� ��� ���������
    GPIOInitStruct.PORT_Pin   = LED_PORT_PIN;
    GPIOInitStruct.PORT_OE    = PORT_OE_OUT;
    GPIOInitStruct.PORT_SPEED = PORT_SPEED_SLOW;
    GPIOInitStruct.PORT_MODE  = PORT_MODE_DIGITAL;

    //  ��������� ����������� ���� ��������� ��� LED_PORT
    PORT_Init(LED_PORT, &GPIOInitStruct);

    //  ��������� ����������� ���� ��������� - �������� ����
    while (1)
    {
        // ��������� ��������� ������ LED_PORT_PIN
        // ���� �� ������ ���������� "0", �� ���������� ����� � ���������� "1"
        if (PORT_ReadInputDataBit (LED_PORT, LED_PORT_PIN) == 0)
        {
            PORT_SetBits(LED_PORT, LED_PORT_PIN); // LED
        }

        //  ��������
        Delay(LED_PERIOD);

        // ��������� ��������� ������ LED_PORT_PIN
        // ���� �� ������ = "1", �� ���������� "0"
        if (PORT_ReadInputDataBit (LED_PORT, LED_PORT_PIN) == 1)
        {
            PORT_ResetBits(LED_PORT, LED_PORT_PIN);
        };

        //  ��������
        Delay(LED_PERIOD);
    }
}

//  ���������� ������� ��������
void Delay(int waitTicks)
{
    volatile int i;
    for (i = 0; i < waitTicks; i++)
    {
        __NOP();
    }
}


