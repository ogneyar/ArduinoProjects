#include <MDR32FxQI_port.h>
#include <MDR32FxQI_rst_clk.h>

//      Определения
#define LED_PERIOD      1000000

#define LED_PORT_CLK    RST_CLK_PCLK_PORTD
#define LED_PORT        MDR_PORTD
#define LED_PORT_PIN    PORT_Pin_7

//  Прототип функции задержки, реализованной ниже
void Delay(int waitTicks);

//  Точка входа, отсюда начинается исполнение программы
int main()
{
    // Заводим структуру конфигурации вывода(-ов) порта GPIO
    PORT_InitTypeDef GPIOInitStruct;

    //  Включаем тактирование порта LED_PORT_CLK
    RST_CLK_PCLKcmd (LED_PORT_CLK, ENABLE);

    //  Инициализируем структуру конфигурации вывода(-ов) порта значениями по умолчанию
    PORT_StructInit(&GPIOInitStruct);

    //  Изменяем значения по умолчанию на необходимые нам настройки
    GPIOInitStruct.PORT_Pin   = LED_PORT_PIN;
    GPIOInitStruct.PORT_OE    = PORT_OE_OUT;
    GPIOInitStruct.PORT_SPEED = PORT_SPEED_SLOW;
    GPIOInitStruct.PORT_MODE  = PORT_MODE_DIGITAL;

    //  Применяем заполненную нами структуру для LED_PORT
    PORT_Init(LED_PORT, &GPIOInitStruct);

    //  Запускаем бесконечный цикл обработки - Основной цикл	
    while (1)
    {
        // Считываем состояние вывода LED_PORT_PIN
        // Если на выводе логический "0", то выставляем вывод в логическую "1"
        if (PORT_ReadInputDataBit (LED_PORT, LED_PORT_PIN) == 0)
        {
            PORT_SetBits(LED_PORT, LED_PORT_PIN); // LED
        }

        //  Задержка
        Delay(LED_PERIOD);

        // Считываем состояние вывода LED_PORT_PIN
        // Если на выводе = "1", то выставляем "0"
        if (PORT_ReadInputDataBit (LED_PORT, LED_PORT_PIN) == 1)
        {
            PORT_ResetBits(LED_PORT, LED_PORT_PIN);
        };

        //  Задержка
        Delay(LED_PERIOD);
    }
}

//  Простейшая функция задержки
void Delay(int waitTicks)
{
    volatile int i;
    for (i = 0; i < waitTicks; i++)
    {
        __NOP();
    }
}

