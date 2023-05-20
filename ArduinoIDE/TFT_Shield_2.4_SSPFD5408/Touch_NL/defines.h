
#define TFTLCD_DELAY 0xFFFF
#define WIDTH 240
#define HEIGHT 320


// #if defined(__AVR_ATmega2560__)
//   #define USING_16BIT_BUS 1
//   #define STROBE_16BIT {WR_ACTIVE; WR_IDLE;}
// #else
//   #define USING_16BIT_BUS 0
// #endif


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
// ---------------------------------

#endif

#define write8(x)     { write_8(x); WR_STROBE; }
#define write16(x)    { uint8_t h = (x)>>8, l = x; write8(h); write8(l); }

#define READ_8(dst)   { RD_STROBE; dst = read_8(); RD_IDLE; }
#define READ_16(dst)  { uint8_t hi; READ_8(hi); READ_8(dst); dst |= (hi << 8); }

#define PIN_LOW(p, b)        (p) &= ~(1<<(b))
#define PIN_HIGH(p, b)       (p) |= (1<<(b))
#define PIN_OUTPUT(p, b)     *(&p-1) |= (1<<(b))

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


static const uint16_t ILI9320_regValues[] PROGMEM = {
  0x00e5, 0x8000,
  0x0000, 0x0001,
  0x0001, 0x100,
  0x0002, 0x0700,
  0x0003, 0x1030,
  0x0004, 0x0000,
  0x0008, 0x0202,
  0x0009, 0x0000,
  0x000A, 0x0000,
  0x000C, 0x0000,
  0x000D, 0x0000,
  0x000F, 0x0000,
  //-----Power On sequence-----------------------
  0x0010, 0x0000,
  0x0011, 0x0007,
  0x0012, 0x0000,
  0x0013, 0x0000,
  TFTLCD_DELAY, 50,
  0x0010, 0x17B0,
  0x0011, 0x0007,
  TFTLCD_DELAY, 10,
  0x0012, 0x013A,
  TFTLCD_DELAY, 10,
  0x0013, 0x1A00,
  0x0029, 0x000c,
  TFTLCD_DELAY, 10,
  //-----Gamma control-----------------------
  0x0030, 0x0000,
  0x0031, 0x0505,
  0x0032, 0x0004,
  0x0035, 0x0006,
  0x0036, 0x0707,
  0x0037, 0x0105,
  0x0038, 0x0002,
  0x0039, 0x0707,
  0x003C, 0x0704,
  0x003D, 0x0807,
  //-----Set RAM area-----------------------
  0x0050, 0x0000,
  0x0051, 0x00EF,
  0x0052, 0x0000,
  0x0053, 0x013F,
  0x0060, 0xA700,     //GS=1
  0x0061, 0x0001,
  0x006A, 0x0000,
  0x0021, 0x0000,
  0x0020, 0x0000,
  //-----Partial Display Control------------
  0x0080, 0x0000,
  0x0081, 0x0000,
  0x0082, 0x0000,
  0x0083, 0x0000,
  0x0084, 0x0000,
  0x0085, 0x0000,
  //-----Panel Control----------------------
  0x0090, 0x0010,
  0x0092, 0x0000,
  0x0093, 0x0003,
  0x0095, 0x0110,
  0x0097, 0x0000,
  0x0098, 0x0000,
  //-----Display on-----------------------
  0x0007, 0x0173,
  TFTLCD_DELAY, 50,
};

