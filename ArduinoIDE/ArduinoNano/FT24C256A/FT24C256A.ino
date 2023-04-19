
// Nano, LGT8F328P

#include <Wire.h>    
 
#define disk1 0x50 // Адрес чипа 24LC256
 
void setup(void)
{
  Serial.begin(9600);
  Wire.begin();  
 
  unsigned int address = 0;
 
  writeEEPROM(disk1, address, 123);
  Serial.print(readEEPROM(disk1, address), DEC);
}
 
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));
  Wire.write((int)(eeaddress & 0xFF));
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}
 
byte readEEPROM(int deviceaddress, unsigned int eeaddress) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));
  Wire.write((int)(eeaddress & 0xFF));
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}
 
void loop()
{
}
