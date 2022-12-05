
// STM32F103C8T6

//#include <Wire.h>

//#define STM32F103C8T6

#include <U8glib.h>

//u8g_t u8g;
//u8g_dev_t u8g_dev_ssd1306_128x32_i2c;

//u8g_uint_t tx, ty;
//uint8_t is_begin = 0;

U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI 
//U8GLIB(&u8g_dev_ssd1306_128x32_i2c, U8G_I2C_OPT_NONE);
//U8GLIB(u8g_dev_t *dev, uint8_t options) { initI2C(dev, options); }
//initI2C(*u8g_dev_ssd1306_128x32_i2c, U8G_I2C_OPT_NONE);
//uint8_t U8GLIB::initI2C(u8g_dev_t *dev, uint8_t options){ prepare();  return u8g_InitI2C(&u8g, dev, options);}
//prepare();
//u8g_InitI2C(u8g, u8g_dev_ssd1306_128x32_i2c, U8G_I2C_OPT_NONE);


//uint8_t address = 0x3C;
//uint8_t command = 0x80;
//uint8_t data = 0xC0;
//uint8_t val = 0xAF; // 0xAF - display on


//static const uint8_t u8g_dev_ssd1306_128x32_adafruit3_init_seq[] PROGMEM = {
//  0xff, 0xd0, /* U8G_ESC_CS(0),*/        /* disable chip */
//  0xff, 0xe0, /* U8G_ESC_ADR(0),       /* instruction mode */
//  0xff, 0xc1, /* U8G_ESC_RST(1),    /* do reset low pulse with (1*16)+2 milliseconds */
//  0xff, 0xd1, /* U8G_ESC_CS(1),        /* enable chip */
//  0x0ae,        /* display off, sleep mode */
//  0x0d5, 0x080,     /* clock divide ratio (0x00=1) and oscillator frequency (0x8) */
//  0x0a8, 0x01f,     /* Feb 23, 2013: 128x32 OLED: 0x01f,  128x32 OLED 0x03f */
//  0x0d3, 0x000,     /*  */
//  0x040,        /* start line */
//  0x08d, 0x014,     /* [2] charge pump setting (p62): 0x014 enable, 0x010 disable */ 
//  0x020, 0x002,     /* com pin HW config, sequential com pin config (bit 4), disable left/right remap (bit 5), Feb 23, 2013: 128x32 OLED: 0x002,  128x32 OLED 0x012 */
//  0x0a1,        /* segment remap a0/a1*/
//  0x0c8,        /* c0: scan dir normal, c8: reverse */
//  0x0da, 0x002,     /* com pin HW config, sequential com pin config (bit 4), disable left/right remap (bit 5) */
//  0x081, 0x0cf,     /* [2] set contrast control */
//  0x0d9, 0x0f1,     /* [2] pre-charge period 0x022/f1*/
//  0x0db, 0x040,     /* vcomh deselect level */
//  0x02e,        /* 2012-05-27: Deactivate scroll */ 
//  0x0a4,        /* output ram to display */
//  0x0a6,        /* none inverted normal display mode */
//  0x0af,        /* display on */
//  0xff, 0xd0, /* U8G_ESC_CS(0),        /* disable chip */
//  0xff, 0xfe, /* U8G_ESC_END           /* end of sequence */
//};


//#define SDA_1 PB7
//#define SCL_1 PB6

//void lcd_ini(void) {
//    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS7); // set - 1
//    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS6); // set - 1
//}
//void lcd_start(void) {  
//    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR7); // reset - 0
//}

void setup(void) {
//  lcd_ini();
//  lcd_start();


  u8g.firstPage();
  //void firstPage(void) { cbegin(); u8g_FirstPage(&u8g); }
  //cbegin(); 
  //void cbegin(void) { if ( is_begin == 0 ) { is_begin = 1; u8g_Begin(&u8g); } }
//  if ( is_begin == 0 ) { 
//    is_begin = 1; 
//    u8g_Begin(&u8g); 
//  }
//  u8g_FirstPage(&u8g);
  do {
    u8g.setFont(u8g_font_6x10);    
//    u8g_SetFont(&u8g, u8g_font_6x10);
    //void setFont(const u8g_fntpgm_uint8_t *font) {u8g_SetFont(&u8g, font); }
    //u8g_SetFont(u8g, &u8g_font_6x10);
    
    u8g.drawStr( 0, 30, "setScale2x2");
    //u8g_DrawStr(&u8g, 0, 20, "setScale2x2");
//    u8g_DrawStrP(&u8g, 0, 20, (u8g_pgm_uint8_t *)"setScale2x2");
    
  } while( u8g.nextPage() );
//  } while( u8g_NextPage(&u8g) );
  
  
//  Wire.begin(address);
//  Wire.beginTransmission(address);
//  Wire.write(command);  // передача команды
//  Wire.write(u8g_dev_ssd1306_128x32_adafruit3_init_seq, sizeof(u8g_dev_ssd1306_128x32_adafruit3_init_seq));  // передача массива
//  Wire.endTransmission(true); // true - поумолчанию ( true — после запроса отправляет STOP, освобождая шину I2C, false — после запроса отправляет RESTART)
}

void loop(void) {
  
}
