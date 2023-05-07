
#ifndef _TFT_DEFINES_H_
#define _TFT_DEFINES_H_

// #define __DEBUG 1

#ifndef F_CPU
  #ifdef __SAMD21G18A__
    #define F_CPU 48000000UL
  #else
    #define F_CPU 16000000UL
  #endif
#endif

#define TFTLCD_DELAY 0xFFFF
#define TFTLCD_DELAY8 0xFF

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#if 0
#elif defined(__AVR_ATmega328P__)       //regular UNO shield on UNO

  #define RD_PORT PORTC
  #define RD_PIN  0
  #define WR_PORT PORTC
  #define WR_PIN  1
  #define CD_PORT PORTC
  #define CD_PIN  2
  #define CS_PORT PORTC
  #define CS_PIN  3
  #define RESET_PORT PORTC
  #define RESET_PIN  4

// ifdef USE_OPENSMART_SHIELD_PINOUT
  #define write_8(x) {                          \
      PORTD = (PORTD & B00101111) | ((x) & B11010000); \
      PORTB = (PORTB & B11010000) | ((x) & B00101111);}    
  #define read_8() (PIND & B11010000) | (PINB & B00101111)    
  #define setWriteDir() { DDRD |=  B11010000; DDRB |=  B00101111; }
  #define setReadDir()  { DDRD &= ~B11010000; DDRB &= ~B00101111; }
  
  #define write8(x)     { write_8(x); WR_STROBE; }
  #define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }

  #define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
  #define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

  #define PIN_LOW(p, b)        (p) &= ~(1<<(b))
  #define PIN_HIGH(p, b)       (p) |= (1<<(b))
  #define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))
// ---------------------------------

#elif (defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__))       //regular UNO shield on MEGA2560

  #define RD_PORT PORTF
  #define RD_PIN  0
  #define WR_PORT PORTF
  #define WR_PIN  1
  #define CD_PORT PORTF
  #define CD_PIN  2
  #define CS_PORT PORTF
  #define CS_PIN  3
  #define RESET_PORT PORTF
  #define RESET_PIN  4

// ifdef USE_OPENSMART_SHIELD_PINOUT
  #define write_8(x) {                                              \
    PORTH = (PORTH&B10000111)|(((x)&B11000000)>>3)|(((x)&B00000011)<<5); \
    PORTB = (PORTB&B01001111)|(((x)&B00101100)<<2);                      \
    PORTG = (PORTG&B11011111)|(((x)&B00010000)<<1);}
  #define read_8()(                                      \ 
  	((PINH & B00011000) << 3) | ((PINB & B10110000) >> 2) | \
  	((PING & B00100000) >> 1) | ((PINH & B01100000) >> 5) )
  #define setWriteDir() {                                   \
    DDRH |=  B01111000; DDRB |=  B10110000; DDRG |=  B00100000; }
  #define setReadDir()  {                                   \
    DDRH &= ~B01111000; DDRB &= ~B10110000; DDRG &= ~B00100000; }
    
  #define write8(x)     { write_8(x); WR_STROBE; }
  #define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }

  #define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
  #define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

  #define PIN_LOW(p, b)        (p) &= ~(1<<(b))
  #define PIN_HIGH(p, b)       (p) |= (1<<(b))
  #define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))
// ---------------------------------

#elif defined(__SAMD21G18A__)   //regular UNO shield on ZERO or M0_PRO

  #include "sam.h"

  // configure macros for the control pins
  #define RD_PORT PORT->Group[0]
  #define RD_PIN  2
  #define WR_PORT PORT->Group[1]
  #define WR_PIN  8  
  #define CD_PORT PORT->Group[1]
  #define CD_PIN  9
  #define CS_PORT PORT->Group[0]
  #define CS_PIN  4
  #define RESET_PORT PORT->Group[0]
  #define RESET_PIN  5
  // configure macros for data bus
  #define DMASK 0x003701C0 // 0000 0000 0011 0111 0000 0001 1100 0000
  // 6 7 18 16 8 17 20 21 - очерёдность битов 0 1 2 3 4 5 6 7
  #define write_8(x) {\ 
      PORT->Group[0].OUTCLR.reg = DMASK;\
      PORT->Group[0].OUTSET.reg = ( ((x) & 0x01) << 6)\
                                  |(((x) & 0x02) << 7)\
                                  |(((x) & 0x04) << 18)\
                                  |(((x) & 0x08) << 16)\
                                  |(((x) & 0x10) << 8)\
                                  |(((x) & 0x20) << 17)\
                                  |(((x) & 0x40) << 20)\
                                  |(((x) & 0x80) << 21);\
                      }
  #define read_8() ( ( (PORT->Group[0].IN.reg >> 6)  & 0x01) \
                    | ((PORT->Group[0].IN.reg >> 7)  & 0x02) \
                    | ((PORT->Group[0].IN.reg >> 18) & 0x04) \
                    | ((PORT->Group[0].IN.reg >> 16) & 0x08) \
                    | ((PORT->Group[0].IN.reg >> 8)  & 0x10) \
                    | ((PORT->Group[0].IN.reg >> 17) & 0x20) \
                    | ((PORT->Group[0].IN.reg >> 20) & 0x40) \
                    | ((PORT->Group[0].IN.reg >> 21) & 0x80) ) ) 


  #define setWriteDir() { PORT->Group[0].DIRSET.reg = DMASK; \
                      PORT->Group[0].WRCONFIG.reg = (DMASK & 0xFFFF) | (0<<22) | (1<<28) | (1<<30); \
                      PORT->Group[0].WRCONFIG.reg = (DMASK>>16) | (0<<22) | (1<<28) | (1<<30) | (1<<31); \
                          }
  #define setReadDir()  { PORT->Group[0].DIRCLR.reg = DMASK; \
                      PORT->Group[0].WRCONFIG.reg = (DMASK & 0xFFFF) | (1<<17) | (1<<28) | (1<<30); \
                      PORT->Group[0].WRCONFIG.reg = (DMASK>>16) | (1<<17) | (1<<28) | (1<<30) | (1<<31); \
                          }
  #define write8(x)     { write_8(x); WR_STROBE; }
  #define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }
  #define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
  #define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }
  // Shield Control macros.
  #define PIN_LOW(port, pin)    (port).OUTCLR.reg |= (1<<(pin))
  #define PIN_HIGH(port, pin)   (port).OUTSET.reg |= (1<<(pin))
  #define PIN_OUTPUT(port, pin) (port).DIR.reg |= (1<<(pin))

#endif


#define wait_ms(ms)  delay(ms)
#define MIPI_DCS_REV1   (1<<0)
#define AUTO_READINC    (1<<1)
#define READ_BGR        (1<<2)
#define READ_LOWHIGH    (1<<3)
#define READ_24BITS     (1<<4)
#define XSA_XEA_16BIT   (1<<5)
#define READ_NODUMMY    (1<<6)
#define INVERT_GS       (1<<8)
#define INVERT_SS       (1<<9)
#define MV_AXIS         (1<<10)
#define INVERT_RGB      (1<<11)
#define REV_SCREEN      (1<<12)
#define FLIP_VERT       (1<<13)
#define FLIP_HORIZ      (1<<14)

#define RD_ACTIVE  PIN_LOW(RD_PORT, RD_PIN)
#define RD_IDLE    PIN_HIGH(RD_PORT, RD_PIN)
#define RD_OUTPUT  PIN_OUTPUT(RD_PORT, RD_PIN)
#define WR_ACTIVE  PIN_LOW(WR_PORT, WR_PIN)
#define WR_IDLE    PIN_HIGH(WR_PORT, WR_PIN)
#define WR_OUTPUT  PIN_OUTPUT(WR_PORT, WR_PIN)
#define CD_COMMAND PIN_LOW(CD_PORT, CD_PIN)
#define CD_DATA    PIN_HIGH(CD_PORT, CD_PIN)
#define CD_OUTPUT  PIN_OUTPUT(CD_PORT, CD_PIN)
#define CS_ACTIVE  PIN_LOW(CS_PORT, CS_PIN)
#define CS_IDLE    PIN_HIGH(CS_PORT, CS_PIN)
#define CS_OUTPUT  PIN_OUTPUT(CS_PORT, CS_PIN)
#define RESET_ACTIVE  PIN_LOW(RESET_PORT, RESET_PIN)
#define RESET_IDLE    PIN_HIGH(RESET_PORT, RESET_PIN)
#define RESET_OUTPUT  PIN_OUTPUT(RESET_PORT, RESET_PIN)

 // General macros.   IOCLR registers are 1 cycle when optimised.
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }       //PWLW=TWRL=50ns
#define RD_STROBE RD_IDLE, RD_ACTIVE, RD_ACTIVE, RD_ACTIVE      //PWLR=TRDL=150ns, tDDR=100ns

#define CTL_INIT()   { RD_OUTPUT; WR_OUTPUT; CD_OUTPUT; CS_OUTPUT; }

#define WriteCmd(x)  { CD_COMMAND; write16(x); }
#define WriteData(x) { CD_DATA; write16(x); }


#endif /* _TFT_DEFINES_H_ */
