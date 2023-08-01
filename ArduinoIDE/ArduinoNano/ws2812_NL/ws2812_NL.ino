
// LGT8F328

#define NUMLEDS 1
#define STRIP_PIN 3 // PD3

typedef uint32_t ws2812_color_t;

// переменные
unsigned long ledPrevious = 0;
unsigned long pixelPrevious = 0;
int ledInterval = 500; 
int pixelInterval = 1000;
uint8_t step = 1;
uint8_t  ws2812_bright = 10, ws2812_showBright = 10;    
volatile uint8_t *ws2812_dat_port, *ws2812_dat_ddr;
volatile uint8_t *ws2812_clk_port, *ws2812_clk_ddr;
uint8_t ws2812_dat_mask;
uint8_t ws2812_clk_mask;
uint8_t ws2812_mask_h,  ws2812_mask_l;
uint8_t ws2812_sregSave = SREG;
int ws2812_oneLedMax = 30; // oneLedMax = (ток ленты с одним горящим) - (ток выключенной ленты)
int ws2812_oneLedIdle = 660; // oneLedIdle = (ток выключенной ленты) / (количество ледов)
ws2812_color_t ws2812_leds[NUMLEDS];
    

// функции
void ws2812_init(int8_t);
void ws2812_setBrightness(uint8_t newBright);
void ws2812_set(int n, ws2812_color_t color);
void ws2812_show(void);
void ws2812_setOne(ws2812_color_t color);
void ws2812_send(ws2812_color_t color);
void ws2812_sendRaw(byte data);
uint8_t getRed(ws2812_color_t color);
uint8_t getGreen(ws2812_color_t color);
uint8_t getBlue(ws2812_color_t color);


void setup() {
  ws2812_init(STRIP_PIN);
  DDRB |= (1 << 5); // PB5
}


void loop() {
  unsigned long currentMillis = millis();
  
  if((currentMillis - ledPrevious) >= ledInterval) { 
    ledPrevious = currentMillis;    
    PORTB ^= (1 << 5);
  }
  
  if(currentMillis - pixelPrevious >= pixelInterval) {
    pixelPrevious = currentMillis;

    switch(step) {
      case 1:
        ws2812_setOne(0xffffff);  // цвет белый
      break;
      case 2:
        ws2812_setOne(0xff0000);  // цвет зелёный
      break;
      case 3:      
        ws2812_setOne(0x00ff00);  // цвет красный
      break;
      case 4:
        ws2812_setOne(0x0000ff);  // цвет синий
      break;
      default: break;
    }

    step++;
    if (step > 4) step = 1;
  }    
}

void ws2812_init(int8_t ws2812_pin = 3) {
  ws2812_dat_mask = digitalPinToBitMask(ws2812_pin);
  ws2812_dat_port = portOutputRegister(digitalPinToPort(ws2812_pin));
  ws2812_dat_ddr = portModeRegister(digitalPinToPort(ws2812_pin));
  *ws2812_dat_ddr |= ws2812_dat_mask; // DDRx |= (1 << y);
}

void ws2812_setBrightness(uint8_t newBright) {
  ws2812_bright = newBright;
}

void ws2812_set(int n, ws2812_color_t color) {
  ws2812_leds[n] = color;
}

void ws2812_show() {
  ws2812_mask_h = ws2812_dat_mask | *ws2812_dat_port;
  ws2812_mask_l = ~ws2812_dat_mask & *ws2812_dat_port;
  ws2812_showBright = ws2812_bright;
  for (int i = 0; i < NUMLEDS; i++) ws2812_send(ws2812_leds[i]);
}

void ws2812_setOne(ws2812_color_t color) {
  ws2812_leds[0] = color;
  ws2812_show();
}

void ws2812_send(ws2812_color_t color) {
  uint8_t data[3];
  // достаём три цвета
  data[0] = contrast(getRed(color), ws2812_showBright);
  data[1] = contrast(getGreen(color), ws2812_showBright);
  data[2] = contrast(getBlue(color), ws2812_showBright);      
  // отключаем прерывания на время передачи данных
  ws2812_sregSave = SREG;
  cli();
  // отправляем RGB
  for (uint8_t i = 0; i < 3; i++) ws2812_sendRaw(data[i]);
  // возвращаем прерывания        
  SREG = ws2812_sregSave;
}

void ws2812_sendRaw(byte data) {
    asm volatile
    (
        "LDI r19, 8      	    \n\t"     // Загружаем в счетчик циклов 8
        "_LOOP_START_%=:      \n\t"     // Начало основного цикла
        "ST X, %[SET_H]       \n\t"     // Устанавливаем на выходе HIGH
#if(F_CPU == 32000000UL) 
            "RJMP .+0             \n\t"			// (LGT8 32MHZ) два дополнительных NOP
#endif 
        "SBRS %[DATA], 7      \n\t"     // Если текущий бит установлен - пропуск след. инстр.
        "ST X, %[SET_L]       \n\t"     // Устанавливаем на выходе LOW
        "LSL  %[DATA]         \n\t"     // Двигаем данные влево на один бит
        //-----------------------------------------------------------------------------------------
#if(F_CPU > 8000000UL)
#if(F_CPU == 32000000UL)        	  	      // (LGT8) delay 29 тактов, 9 цикла по 3CK + загрузка 1CK + NOP  
        "LDI r20, 9    		    \n\t"
#elif(F_CPU == 16000000UL)        	  	    // delay 8 тактов, 2 цикла по 3CK + загрузка 1CK + NOP
        "LDI r20, 3    		    \n\t"
#endif
        "_DELAY_LOOP_%=:      \n\t"     // Цикл задержки
        "DEC r20       		    \n\t"     // 1CK декремент
        "BRNE _DELAY_LOOP_%=  \n\t"     // 2CK переход
#endif
        "NOP                   \n\t"    // 1CK NOP
        //-----------------------------------------------------------------------------------------
        "ST X, %[SET_L]        \n\t"    // Устанавливаем на выходе LOW
        "DEC r19               \n\t"    // Декремент счетчика циклов
        "BRNE  _LOOP_START_%=  \n\t"    // Переход на новый цикл, если счетчик не иссяк
        ::[DATA] "r" (data), [SET_H] "r" (ws2812_mask_h), [SET_L] "r" (ws2812_mask_l), "x" (ws2812_dat_port)
        :"r19","r20"
    );
}
        
// получение красного цвета
uint8_t getRed(ws2812_color_t color) {
  return ( ( color >> 16 ) & 0xff );
}
// получение зелёного цвета
uint8_t getGreen(ws2812_color_t color) {
  return ( ( color >> 8 ) & 0xff );
}
// получение синего цвета
uint8_t getBlue(ws2812_color_t color) {
  return ( ( color >> 0 ) & 0xff );
}
// уменьшение яркости
uint8_t contrast(uint8_t one_color, uint8_t brightness) {
  return ( ( (uint16_t)one_color * ( brightness + 1) ) >> 8 );
}

