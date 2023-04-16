
#define TFTLCD_DELAY 0xFFFF
#define WIDTH 240
#define HEIGHT 320

#define RGB565(r, g, b) ((((r)&0xF8) << 8) | (((g)&0xFC) << 3) | ((b) >> 3))

#define RGB565_BLACK RGB565(0, 0, 0)
#define RGB565_NAVY RGB565(0, 0, 123)
#define RGB565_DARKGREEN RGB565(0, 125, 0)
#define RGB565_DARKCYAN RGB565(0, 125, 123)
#define RGB565_MAROON RGB565(123, 0, 0)
#define RGB565_PURPLE RGB565(123, 0, 123)
#define RGB565_OLIVE RGB565(123, 125, 0)
#define RGB565_LIGHTGREY RGB565(198, 195, 198)
#define RGB565_DARKGREY RGB565(123, 125, 123)
#define RGB565_BLUE RGB565(0, 0, 255)
#define RGB565_GREEN RGB565(0, 255, 0)
#define RGB565_CYAN RGB565(0, 255, 255)
#define RGB565_RED RGB565(255, 0, 0)
#define RGB565_MAGENTA RGB565(255, 0, 255)
#define RGB565_YELLOW RGB565(255, 255, 0)
#define RGB565_WHITE RGB565(255, 255, 255)
#define RGB565_ORANGE RGB565(255, 165, 0)
#define RGB565_GREENYELLOW RGB565(173, 255, 41)
#define RGB565_PINK RGB565(255, 130, 198)

// #define	BLACK   0x0000
// #define	BLUE    0x001F
// #define	RED     0xF800
// #define	GREEN   0x07E0
// #define CYAN    0x07FF
// #define MAGENTA 0xF81F
// #define YELLOW  0xFFE0
// #define WHITE   0xFFFF

#define BLACK RGB565_BLACK
#define NAVY RGB565_NAVY
#define DARKGREEN RGB565_DARKGREEN
#define DARKCYAN RGB565_DARKCYAN
#define MAROON RGB565_MAROON
#define PURPLE RGB565_PURPLE
#define OLIVE RGB565_OLIVE
#define LIGHTGREY RGB565_LIGHTGREY
#define DARKGREY RGB565_DARKGREY
#define BLUE RGB565_BLUE
#define GREEN RGB565_GREEN
#define CYAN RGB565_CYAN
#define RED RGB565_RED
#define MAGENTA RGB565_MAGENTA
#define YELLOW RGB565_YELLOW
#define WHITE RGB565_WHITE
#define ORANGE RGB565_ORANGE
#define GREENYELLOW RGB565_GREENYELLOW
#define PINK RGB565_PINK


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


typedef struct {
  uint16_t bitmapOffset;
  uint8_t width;         ///< Bitmap dimensions in pixels
  uint8_t height;        ///< Bitmap dimensions in pixels
  uint8_t xAdvance;      ///< Distance to advance cursor (x axis)
  int8_t xOffset;        ///< X dist from cursor pos to UL corner
  int8_t yOffset;        ///< Y dist from cursor pos to UL corner
} GFXglyph;

const GFXglyph fontGlyphs[] PROGMEM = {
  {0, 0, 0, 2, 0, 1},     // 0x20 ' '
  {0, 1, 5, 2, 0, -4},    // 0x21 '!'
  {1, 3, 2, 4, 0, -4},    // 0x22 '"'
  {2, 5, 5, 6, 0, -4},    // 0x23 '#'
  {6, 3, 6, 4, 0, -4},    // 0x24 '$'
  {9, 3, 5, 4, 0, -4},    // 0x25 '%'
  {11, 4, 5, 5, 0, -4},   // 0x26 '&'
  {14, 1, 2, 2, 0, -4},   // 0x27 '''
  {15, 2, 5, 3, 0, -4},   // 0x28 '('
  {17, 2, 5, 3, 0, -4},   // 0x29 ')'
  {19, 3, 3, 4, 0, -3},   // 0x2A '*'
  {21, 3, 3, 4, 0, -3},   // 0x2B '+'
  {23, 2, 2, 3, 0, 0},    // 0x2C ','
  {24, 3, 1, 4, 0, -2},   // 0x2D '-'
  {25, 1, 1, 2, 0, 0},    // 0x2E '.'
  {26, 3, 5, 4, 0, -4},   // 0x2F '/'
  {28, 3, 5, 4, 0, -4},   // 0x30 '0'
  {30, 2, 5, 3, 0, -4},   // 0x31 '1'
  {32, 3, 5, 4, 0, -4},   // 0x32 '2'
  {34, 3, 5, 4, 0, -4},   // 0x33 '3'
  {36, 3, 5, 4, 0, -4},   // 0x34 '4'
  {38, 3, 5, 4, 0, -4},   // 0x35 '5'
  {40, 3, 5, 4, 0, -4},   // 0x36 '6'
  {42, 3, 5, 4, 0, -4},   // 0x37 '7'
  {44, 3, 5, 4, 0, -4},   // 0x38 '8'
  {46, 3, 5, 4, 0, -4},   // 0x39 '9'
  {48, 1, 3, 2, 0, -3},   // 0x3A ':'
  {49, 2, 4, 3, 0, -3},   // 0x3B ';'
  {50, 2, 3, 3, 0, -3},   // 0x3C '<'
  {51, 3, 3, 4, 0, -3},   // 0x3D '='
  {53, 2, 3, 3, 0, -3},   // 0x3E '>'
  {54, 3, 5, 4, 0, -4},   // 0x3F '?'
  {56, 3, 5, 4, 0, -4},   // 0x40 '@'
  {58, 3, 5, 4, 0, -4},   // 0x41 'A'
  {60, 3, 5, 4, 0, -4},   // 0x42 'B'
  {62, 3, 5, 4, 0, -4},   // 0x43 'C'
  {64, 3, 5, 4, 0, -4},   // 0x44 'D'
  {66, 3, 5, 4, 0, -4},   // 0x45 'E'
  {68, 3, 5, 4, 0, -4},   // 0x46 'F'
  {70, 3, 5, 4, 0, -4},   // 0x47 'G'
  {72, 3, 5, 4, 0, -4},   // 0x48 'H'
  {74, 1, 5, 2, 0, -4},   // 0x49 'I'
  {75, 3, 5, 4, 0, -4},   // 0x4A 'J'
  {77, 3, 5, 4, 0, -4},   // 0x4B 'K'
  {79, 3, 5, 4, 0, -4},   // 0x4C 'L'
  {81, 5, 5, 6, 0, -4},   // 0x4D 'M'
  {85, 4, 5, 5, 0, -4},   // 0x4E 'N'
  {88, 3, 5, 4, 0, -4},   // 0x4F 'O'
  {90, 3, 5, 4, 0, -4},   // 0x50 'P'
  {92, 3, 6, 4, 0, -4},   // 0x51 'Q'
  {95, 3, 5, 4, 0, -4},   // 0x52 'R'
  {97, 3, 5, 4, 0, -4},   // 0x53 'S'
  {99, 3, 5, 4, 0, -4},   // 0x54 'T'
  {101, 3, 5, 4, 0, -4},  // 0x55 'U'
  {103, 3, 5, 4, 0, -4},  // 0x56 'V'
  {105, 5, 5, 6, 0, -4},  // 0x57 'W'
  {109, 3, 5, 4, 0, -4},  // 0x58 'X'
  {111, 3, 5, 4, 0, -4},  // 0x59 'Y'
  {113, 3, 5, 4, 0, -4},  // 0x5A 'Z'
  {115, 2, 5, 3, 0, -4},  // 0x5B '['
  {117, 3, 5, 4, 0, -4},  // 0x5C '\'
  {119, 2, 5, 3, 0, -4},  // 0x5D ']'
  {121, 3, 2, 4, 0, -4},  // 0x5E '^'
  {122, 4, 1, 4, 0, 1},   // 0x5F '_'
  {123, 2, 2, 3, 0, -4},  // 0x60 '`'
  {124, 3, 4, 4, 0, -3},  // 0x61 'a'
  {126, 3, 5, 4, 0, -4},  // 0x62 'b'
  {128, 3, 3, 4, 0, -2},  // 0x63 'c'
  {130, 3, 5, 4, 0, -4},  // 0x64 'd'
  {132, 3, 4, 4, 0, -3},  // 0x65 'e'
  {134, 2, 5, 3, 0, -4},  // 0x66 'f'
  {136, 3, 5, 4, 0, -3},  // 0x67 'g'
  {138, 3, 5, 4, 0, -4},  // 0x68 'h'
  {140, 1, 5, 2, 0, -4},  // 0x69 'i'
  {141, 2, 6, 3, 0, -4},  // 0x6A 'j'
  {143, 3, 5, 4, 0, -4},  // 0x6B 'k'
  {145, 2, 5, 3, 0, -4},  // 0x6C 'l'
  {147, 5, 3, 6, 0, -2},  // 0x6D 'm'
  {149, 3, 3, 4, 0, -2},  // 0x6E 'n'
  {151, 3, 3, 4, 0, -2},  // 0x6F 'o'
  {153, 3, 4, 4, 0, -2},  // 0x70 'p'
  {155, 3, 4, 4, 0, -2},  // 0x71 'q'
  {157, 2, 3, 3, 0, -2},  // 0x72 'r'
  {158, 3, 4, 4, 0, -3},  // 0x73 's'
  {160, 2, 5, 3, 0, -4},  // 0x74 't'
  {162, 3, 3, 4, 0, -2},  // 0x75 'u'
  {164, 3, 3, 4, 0, -2},  // 0x76 'v'
  {166, 5, 3, 6, 0, -2},  // 0x77 'w'
  {168, 3, 3, 4, 0, -2},  // 0x78 'x'
  {170, 3, 4, 4, 0, -2},  // 0x79 'y'
  {172, 3, 4, 4, 0, -3},  // 0x7A 'z'
  {174, 3, 5, 4, 0, -4},  // 0x7B '{'
  {176, 1, 6, 2, 0, -4},  // 0x7C '|'
  {177, 3, 5, 4, 0, -4},  // 0x7D '}'
  {179, 4, 2, 5, 0, -3}   // 0x7E '~'
};


const uint8_t fontBitmaps[] PROGMEM = {
    0xE8, 0xB4, 0x57, 0xD5, 0xF5, 0x00, 0x4E, 0x3E, 0x80, 0xA5, 0x4A, 0x4A,
    0x5A, 0x50, 0xC0, 0x6A, 0x40, 0x95, 0x80, 0xAA, 0x80, 0x5D, 0x00, 0x60,
    0xE0, 0x80, 0x25, 0x48, 0x56, 0xD4, 0x75, 0x40, 0xC5, 0x4E, 0xC5, 0x1C,
    0x97, 0x92, 0xF3, 0x1C, 0x53, 0x54, 0xE5, 0x48, 0x55, 0x54, 0x55, 0x94,
    0xA0, 0x46, 0x64, 0xE3, 0x80, 0x98, 0xC5, 0x04, 0x56, 0xC6, 0x57, 0xDA,
    0xD7, 0x5C, 0x72, 0x46, 0xD6, 0xDC, 0xF3, 0xCE, 0xF3, 0x48, 0x72, 0xD4,
    0xB7, 0xDA, 0xF8, 0x24, 0xD4, 0xBB, 0x5A, 0x92, 0x4E, 0x8E, 0xEB, 0x58,
    0x80, 0x9D, 0xB9, 0x90, 0x56, 0xD4, 0xD7, 0x48, 0x56, 0xD4, 0x40, 0xD7,
    0x5A, 0x71, 0x1C, 0xE9, 0x24, 0xB6, 0xD4, 0xB6, 0xA4, 0x8C, 0x6B, 0x55,
    0x00, 0xB5, 0x5A, 0xB5, 0x24, 0xE5, 0x4E, 0xEA, 0xC0, 0x91, 0x12, 0xD5,
    0xC0, 0x54, 0xF0, 0x90, 0xC7, 0xF0, 0x93, 0x5E, 0x71, 0x80, 0x25, 0xDE,
    0x5E, 0x30, 0x6E, 0x80, 0x77, 0x9C, 0x93, 0x5A, 0xB8, 0x45, 0x60, 0x92,
    0xEA, 0xAA, 0x40, 0xD5, 0x6A, 0xD6, 0x80, 0x55, 0x00, 0xD7, 0x40, 0x75,
    0x90, 0xE8, 0x71, 0xE0, 0xBA, 0x40, 0xB5, 0x80, 0xB5, 0x00, 0x8D, 0x54,
    0xAA, 0x80, 0xAC, 0xE0, 0xE5, 0x70, 0x6A, 0x26, 0xFC, 0xC8, 0xAC, 0x5A
};

typedef struct {
  uint8_t *bitmap;  ///< Glyph bitmaps, concatenated
  GFXglyph *glyph;  ///< Glyph array
  uint16_t first;   ///< ASCII extents (first char)
  uint16_t last;    ///< ASCII extents (last char)
  uint8_t yAdvance; ///< Newline distance (y axis)
} GFXfont;

const GFXfont font PROGMEM = {
  (uint8_t *)fontBitmaps, (GFXglyph *)fontGlyphs, 0x20, 0x7E, 7
};


// #ifndef pgm_read_byte
// #define pgm_read_byte(addr) (*(const unsigned char *)(addr))
// #endif
// #ifndef pgm_read_word
// #define pgm_read_word(addr) (*(const unsigned short *)(addr))
// #endif
// #ifndef pgm_read_dword
// #define pgm_read_dword(addr) (*(const unsigned long *)(addr))
// #endif

#define pgm_read_pointer(addr) ((void *)pgm_read_dword(addr))


__inline GFXglyph *pgm_read_glyph_ptr(const GFXfont *gfxFont, uint8_t c)
{
  return &(((GFXglyph *)pgm_read_pointer(&gfxFont->glyph))[c]);
}

__inline uint8_t *pgm_read_bitmap_ptr(const GFXfont *gfxFont)
{
  return (uint8_t *)pgm_read_pointer(&gfxFont->bitmap);
}


