//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef BUTTON
#define BUTTON


// ����, � ������� ���������� ������
#define TestButton_Port       GPIOB
#define TestButton_Pin        GPIO_Pin_13


// ��������� ������������� ���� GPIO ��� ����������� ������
void button_Init();
// ������� ������ ��������� ������
uint8_t button_GetState(void);
// ��������� �������� ������� (� ����������) ������
void button_WaitPress(void);

#endif