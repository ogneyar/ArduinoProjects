#include "config.h"
#include "UART.h"
#include "IR.h"


int main(void)
{



unsigned int IR_block=0;// ���������� ������ ����������� �� ��

uart_init(); // �������������� ����
IR_init(); // ���� ��

    while (1) 
    {
		
			
		if (!(IR_PIN & 1<<IR)) // ���� ������ 0 �������� ������ �������
		 { 
			IR_block = IR_read(); // ������ �������
			uart_print (IR_block); // ���������� � ����


		}

    }
}

