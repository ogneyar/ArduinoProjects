
// LGT8F328

// MCP4725 12ти битный, значения принимает от 0 до 4095

#include<Wire.h>                   // библиотека для работы с протоколом I2C  

#define MCP4725 0x60              //устанавливаем для MCP4725 адрес 0x61, для своего АЦП вы можете использовать свой адрес
 
unsigned int adc;
byte buffer[3];        


void setup() {
  Wire.begin();                    //старт связи по протоколу I2C
  Serial.begin(9600);  
  Serial.println("CIRCUIT DIGEST");   
  Serial.println("Arduino");  
  Serial.println("DAC with MCP4725");  
}
void loop() 
{
  buffer[0] = 0b01000000;            //записываем в buffer0 контрольный байт (010-Sets in Write mode)
  adc = analogRead(A0) * 4;          //считываем аналоговое значение с контакта A0, преобразуем его в цифровое значение в диапазоне (0-1023) и умножаем его на 4 чтобы преобразовать его к диапазону (0-4096)
  // 5v из usb = 4,5v
  float ipvolt = (4.5/4096.0)* adc;  //формула для расчета значения напряжения (A0)
  buffer[1] = adc >> 4;              //записываем наиболее значимые биты
  buffer[2] = adc << 4;              //записываем наименее значимые биты
  
  unsigned int analogread = analogRead(A1)*4 ; //считываем аналоговое напряжение с контакта A1
  // 5v из usb = 4,5v
  float opvolt = (4.5/4096.0)* analogread; // формула для расчета значения напряжения (A1)
  
  Wire.beginTransmission(MCP4725);         //присоединяемся к шине I2C с MCP4725 с адресом 0x61
  
  Wire.write(buffer[0]);            //передаем контрольный байт с помощью протокола I2C 
  Wire.write(buffer[1]);            //передаем наиболее значимые биты с помощью протокола I2C 
  Wire.write(buffer[2]);            // передаем наименее значимые биты с помощью протокола I2C
  
  Wire.endTransmission();           //окончание передачи

  Serial.print("A IP: ");
  Serial.println(adc);                   // выводим на экран значение с выхода АЦП контакта A0
  
  Serial.print("V: ");                  // выводим на экран значение напряжения на контакте A0
  Serial.println(ipvolt);
  
  Serial.print("D OP: ");
  Serial.println(analogread);             // выводим на экран значение с контакта A1 (с ЦАП)
  
  Serial.print("V: ");
  Serial.println(opvolt);                 // выводим на экран значение напряжения на контакте A1 (From DAC)
   
  delay(500);
}
