#ifndef SIGNAL_H_
#define SIGNAL_H_


#define TX PB0 // ��� ���������� �������
#define RX PB1 // ��� ���������

#define OTR_ON 3 // ���������� ��������� ��� �������� ����������
#define OTR_OFF 3 // ���������� �� ��������� ��� �������� ���������� �����������

#define IR_CODE 170 // ��� ��� ��������

void IR_ini(void);
uint8_t status(uint8_t cod, uint8_t null);

// 
void IRR_0 (void);// ���� � ����
void IRR_1(void); // 1 � ����
void IRR_code(uint8_t code); // �������� 8 ��� � ����

// ��� ��������
void IR_0 (void);
void IR_1(void);
void IR_code(uint8_t code);

#endif /* SIGNAL_H_ */