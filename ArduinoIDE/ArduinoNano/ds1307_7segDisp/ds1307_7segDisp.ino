
// Nano

#define CLK 4
#define DIO 5
// #define DS1307_ADDRESS	0x86

#include <GyverTM1637.h>
GyverTM1637 disp(CLK, DIO); 
#include <RTClib.h>
RTC_DS1307 rtc;

// char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

uint8_t flag = 1; 

uint8_t digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6f};// символы с 0 по 9

void display(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3);


void setup () {  
  disp.clear();
  disp.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
  display(7,7,7,7); 

  Serial.begin(57600);
  while (!Serial);
  Serial.println("Serial start...");

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    display(0,0,0,0); 
    while (1) ;    
  }
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    display(1,1,1,1);
  }else {
    display(1,2,3,4);
  }
  
  //  DS1307_OFF, DS1307_ON, DS1307_SquareWave1HZ, DS1307_SquareWave4kHz, DS1307_SquareWave8kHz, DS1307_SquareWave32kHz
  rtc.writeSqwPinMode(DS1307_OFF);
}

void loop () {   
  DateTime now = rtc.now();
  uint8_t hour = now.hour();
  uint8_t minute = now.minute();
  uint8_t second = now.second();

  display(hour/10,hour%10,minute/10,minute%10);
  // display(minute/10,minute%10,second/10,second%10);
  
	disp.point(flag); // показать точки
  flag = !flag;  
  
  _delay_ms(1000);
  
  Serial.print(hour, DEC);
  Serial.print(':');
  Serial.print(minute, DEC);
  Serial.print(':');
  Serial.print(second, DEC);
  Serial.println();
}


void display(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3) {
  disp.displayByte(digit[n0], digit[n1], digit[n2], digit[n3]);
}


