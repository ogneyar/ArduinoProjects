
// Uno

#include <stdint.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

//#include <Wire.h>
#include "defines.h"
#include "structs.h"

void error_led(void){
    DDRB |= 32;//make sure led is output
    while (1){//wait for reset
        PORTB ^= 32;// toggle led
        _delay_ms(100);
    }
}
 
void twiStart(void){
    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);//send start
    while (!(TWCR & (1 << TWINT)));//wait for start to be transmitted
    if ((TWSR & 0xF8) != TW_START) error_led();
}

void twiStop(void){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);//send stop // | (0<<TWIE)  
}
 
void twiWriteByte(uint8_t DATA, uint8_t type){
    TWDR = DATA;
    TWCR = _BV(TWINT) | _BV(TWEN);
    while (!(TWCR & (1 << TWINT))) {}
    if ((TWSR & 0xF8) != type) error_led();
}
 
void twiAddr(uint8_t addr, uint8_t typeTWI) {
    TWDR = addr;//send address
    TWCR = _BV(TWINT) | _BV(TWEN); // | (1<<TWIE)   /* clear interrupt to start transmission */
    while ((TWCR & _BV(TWINT)) == 0); /* wait for transmission */
    if ((TWSR & 0xF8) != typeTWI) error_led();
}
 
void writeReg(uint8_t reg, uint8_t dat){
    //send start condition
    twiStart();
    twiAddr(camAddr_WR, TW_MT_SLA_ACK);
    twiWriteByte(reg, TW_MT_DATA_ACK);
    twiWriteByte(dat, TW_MT_DATA_ACK);
    twiStop();
//    Wire.beginTransmission(camAddr_WR);
//    Wire.write(reg);
//    Wire.write(dat);
//    Wire.endTransmission();
    _delay_ms(1);
}
 
static uint8_t twiRd(uint8_t nack){
  if (nack){
    TWCR = _BV(TWINT) | _BV(TWEN);
    while ((TWCR & _BV(TWINT)) == 0); /* wait for transmission */
    if ((TWSR & 0xF8) != TW_MR_DATA_NACK) error_led();
    return TWDR;
  }
  else{
    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
    while ((TWCR & _BV(TWINT)) == 0); /* wait for transmission */
    if ((TWSR & 0xF8) != TW_MR_DATA_ACK) error_led();
    return TWDR;
  }
}
 
uint8_t rdReg(uint8_t reg){
    uint8_t dat;
    twiStart();
    twiAddr(camAddr_WR, TW_MT_SLA_ACK);
    twiWriteByte(reg, TW_MT_DATA_ACK);
    twiStop();
//    Wire.beginTransmission(camAddr_WR);
//    Wire.write(reg);
//    Wire.endTransmission();
    _delay_ms(1);
    twiStart();
    twiAddr(camAddr_RD, TW_MR_SLA_ACK);
    dat = twiRd(1);
    twiStop();
//    Wire.requestFrom(camAddr_RD, 1);
//    while(!Wire.available());
//    dat = Wire.read();
    _delay_ms(1);
    return dat;
}
 
void wrSensorRegs8_8(const struct regval_list reglist[]){
    uint8_t reg_addr, reg_val;
    const struct regval_list *next = reglist;
    while ((reg_addr != 0xff) | (reg_val != 0xff)){
        reg_addr = pgm_read_byte(&next->reg_num);
        reg_val = pgm_read_byte(&next->value);
        writeReg(reg_addr, reg_val);
        next++;
    }
}
 
void setColor(void){
    wrSensorRegs8_8(yuv422_ov7670);
    // wrSensorRegs8_8(qvga_ov7670);
}
 
void setResolution(void){
    writeReg(REG_COM3, 4); // REG_COM3 enable scaling
    wrSensorRegs8_8(qvga_ov7670);
}
 
void camInit(void){
    writeReg(0x12, 0x80);
    _delay_ms(100);
    wrSensorRegs8_8(ov7670_default_regs);
    writeReg(REG_COM10, 32);//PCLK does not toggle on HBLANK.
}
 
void arduinoUnoInit(void) {
    cli();//disable interrupts
  
    /* Setup the 8mhz PWM clock
    * This will be on pin 11*/
    DDRB |= (1 << 3);//pin 11
    ASSR &= ~(_BV(EXCLK) | _BV(AS2));
    TCCR2A = (1 << COM2A0) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << WGM22) | (1 << CS20);
    OCR2A = 0;//(F_CPU)/(2*(X+1))
    DDRC &= ~15;//low d0-d3 camera
    DDRD &= ~252;//d7-d4 and interrupt pins
    _delay_ms(3000);
  
    //set up twi for 100khz
    TWSR &= ~3;//disable prescaler for TWI
    TWBR = 72;//set to 100khz
//    Wire.begin();
  
    //enable serial
    UBRR0H = 0;
    UBRR0L = 1;//0 = 2M baud rate. 1 = 1M baud. 3 = 0.5M. 7 = 250k 207 is 9600 baud rate.
    UCSR0A |= 2;//double speed aysnc
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);//Enable receiver and transmitter
    UCSR0C = 6;//async 1 stop bit 8bit char no parity bits
//    Serial.begin(1000000);
}
 
void StringPgm(const char * str){
  do{
      while (!(UCSR0A & (1 << UDRE0)));//wait for byte to transmit
      UDR0 = pgm_read_byte_near(str);
      while (!(UCSR0A & (1 << UDRE0)));//wait for byte to transmit
  } while (pgm_read_byte_near(++str));
}
 
static void captureImg(uint16_t wg, uint16_t hg){
  uint16_t y, x;
 
  StringPgm(PSTR("*RDY*"));
 
  while (!(PIND & 8));//wait for high
  while ((PIND & 8));//wait for low
 
    y = hg;
  while (y--){
        x = wg;
      //while (!(PIND & 256));//wait for high
    while (x--){
      while ((PIND & 4));//wait for low
            UDR0 = (PINC & 15) | (PIND & 240);
          while (!(UCSR0A & (1 << UDRE0)));//wait for byte to transmit
      while (!(PIND & 4));//wait for high
      while ((PIND & 4));//wait for low
      while (!(PIND & 4));//wait for high
    }
    //  while ((PIND & 256));//wait for low
  }
    _delay_ms(100);
}
 
void setup(){
    arduinoUnoInit();
    camInit();
    setResolution();
    setColor();
    writeReg(0x11, 12); //Earlier it had the value:writeReg(0x11, 12); New version works better for me :) !!!!
}
 
void loop(){
    captureImg(320, 240);
}
