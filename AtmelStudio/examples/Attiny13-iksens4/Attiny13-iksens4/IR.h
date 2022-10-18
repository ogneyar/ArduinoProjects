#ifndef SIGNAL_H_
#define SIGNAL_H_


#define TX PB0 // пин частотного сигнала
#define RX PB1 // пин приемника

#define OTR_ON 3 // количество отражений для фиксации препятсвия
#define OTR_OFF 3 // количество не отражений для фиксации отсутствия препятствия

#define IR_CODE 170 // код для отправки

void IR_ini(void);
uint8_t status(uint8_t cod, uint8_t null);

// 
void IRR_0 (void);// нуль в эфир
void IRR_1(void); // 1 в эфир
void IRR_code(uint8_t code); // отправка 8 бит в эфир

// для протеуса
void IR_0 (void);
void IR_1(void);
void IR_code(uint8_t code);

#endif /* SIGNAL_H_ */