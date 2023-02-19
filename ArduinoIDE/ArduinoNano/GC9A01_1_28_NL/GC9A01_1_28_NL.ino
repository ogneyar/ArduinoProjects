
// Nano

#include "spi.h"
#include "defines.h"

void GC9A01_fill_screen(uint16_t color, uint8_t hl = 0, uint8_t hr = 0, uint8_t vt = 0, uint8_t vb = 0);


void setup() 
{
  SPI_Master_Init();
  // GC9A01_init();
  GC9A01_init_minimal();
  
  GC9A01_clear_screen();
  delay(1000);
  
  GC9A01_fill_screen(_WHITE, 15, 15, 15, 15);
  delay(1000);

  GC9A01_fill_screen(_RED, 30, 30, 30, 30);  
  delay(1000);
  
  GC9A01_fill_screen(_GREEN, 45, 45, 45, 45);  
  delay(1000);

  GC9A01_fill_screen(_BLUE, 60, 60, 60, 60);  
  delay(1000);
  
  GC9A01_fill_screen(_RED_BLUE, 75, 75, 75, 75);  
  delay(1000);
  
  GC9A01_fill_screen(_BLUE_GREEN, 90, 90, 90, 90);  
  delay(1000);

  GC9A01_fill_screen(_RED_GREEN, 105, 105, 105, 105);   
}

void loop() {}



void GC9A01_display(uint16_t color)
{
  uint8_t c1=(uint8_t)((color & 0x00ff));
  uint8_t c2=color>>8;

  GC9A01_write_command(GC9A01_RAMWR); // 0x2C
  
  // for (uint32_t i=0; i < (GC9A01_WIDTH * GC9A01_HEIGHT); i++)
  for (uint32_t i=0; i < 57600; i++)
  {
     GC9A01_write_data(c1);
     GC9A01_write_data(c2);
  }
}

void GC9A01_fill_screen(uint16_t color, uint8_t hl, uint8_t hr, uint8_t vt, uint8_t vb) // hl - horisontal left,  hr - horisontal right, vt - vertical top,  vb - vertical bottom
{
  PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
  GC9A01_set_frame(GC9A01_XSTART + hl, GC9A01_XSTART + GC9A01_WIDTH - hr, GC9A01_YSTART + vt, GC9A01_YSTART + GC9A01_HEIGHT - vb);

  GC9A01_display(color);
  PORT_SPI |= (1 << DD_SS); // chip_select_disable();
}



void GC9A01_set_frame(uint8_t caset1, uint8_t caset2, uint8_t raset1, uint8_t raset2)
{
  GC9A01_write_command(GC9A01_CASET); // 0x2A
  GC9A01_write_data(0x00);   // x1 low byte - начало
  GC9A01_write_data(caset1); // x1 high byte 
  GC9A01_write_data(0x00);   // x2 low byte - конец
  GC9A01_write_data(caset2); // x1 high byte    // 240 horizontal

  GC9A01_write_command(GC9A01_RASET); // 0x2B
  GC9A01_write_data(0x00);   // y1 low byte - начало
  GC9A01_write_data(raset1); // y1 high byte 
  GC9A01_write_data( 0x00);   // y2 low byte - конец
  GC9A01_write_data(raset2); // y1 high byte    // 240 hvertical
}

void GC9A01_clear_screen()
{
  GC9A01_fill_screen(_BLACK);
}


void GC9A01_send_byte(uint8_t dc, uint8_t data)
{
  if (dc == LCD_D) PORT_SPI |= (1 << DD_DC); // gpio_set(GPIOB,DC);
  else PORT_SPI &= ~(1 << DD_DC); // gpio_reset(GPIOB,DC);
  SPI_Master_SendByte(data);
}

static void GC9A01_write_command(uint8_t cmd) {
    GC9A01_send_byte(LCD_C, cmd);
}

static void GC9A01_write_data(uint8_t data) {
    GC9A01_send_byte(LCD_D, data);
}



//
void GC9A01_init_minimal(void) 
{ 
    PORT_SPI &= ~(1 << DD_RES);
    delay(10);
    PORT_SPI |= (1 << DD_RES);
    delay(120);

    PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
        
    /* Initial Sequence */        
    GC9A01_write_command(GC9A01_INREGEN1); // 0xFE

    GC9A01_write_command(GC9A01_INREGEN2); // 0xEF
    
    GC9A01_write_command(GC9A01_MADCTL); // 0x36  - Memory Access Control
    GC9A01_write_data(GC9A01_MADCTL_OR2); // 0x48 - с верху вниз
    
    GC9A01_write_command(GC9A01_COLOR_MODE); // 0x3A
    GC9A01_write_data(GC9A01_CM_16_BIT);                
              
    GC9A01_write_command(GC9A01_66); // 0x66 - ХЗ что это, но необходимо
    GC9A01_write_data(0x3C);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0xCD);
    GC9A01_write_data(0x67);
    GC9A01_write_data(0x45);
    GC9A01_write_data(0x45);
    GC9A01_write_data(0x10);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    
    GC9A01_write_command(GC9A01_67); // 0x67 - ХЗ что это, но необходимо
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x3C);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x01);
    GC9A01_write_data(0x54);
    GC9A01_write_data(0x10);
    GC9A01_write_data(0x32);
    GC9A01_write_data(0x98);
            
    GC9A01_write_command(GC9A01_INVON); // 0x21 - Display Inversion ON 
    
    GC9A01_write_command(GC9A01_SLEEPOUT); // 0x11 - Sleep OUT 
    delay(120);

    GC9A01_write_command(GC9A01_DISPON); // 0x29 - Display ON
    delay(20);

    PORT_SPI |= (1 << DD_SS); // chip_select_disable();    
}


//
void GC9A01_init(void) 
{ 
    PORT_SPI &= ~(1 << DD_RES);
    delay(10);
    PORT_SPI |= (1 << DD_RES);
    delay(120);

    PORT_SPI &= ~(1 << DD_SS); // chip_select_enable();
        
    /* Initial Sequence */     
    GC9A01_write_command(GC9A01_INREGEN2); // 0xEF
    
    GC9A01_write_command(GC9A01_EB); // 0xEB
    GC9A01_write_data(0x14);
    
    GC9A01_write_command(GC9A01_INREGEN1); // 0xFE

    GC9A01_write_command(GC9A01_INREGEN2); // 0xEF
    
    GC9A01_write_command(GC9A01_EB); // 0xEB
    GC9A01_write_data(0x14);
    
    GC9A01_write_command(GC9A01_84); // 0x84
    GC9A01_write_data(0x40);
    
    GC9A01_write_command(GC9A01_85); // 0x85
    GC9A01_write_data(0xFF);
    
    GC9A01_write_command(GC9A01_86); // 0x86
    GC9A01_write_data(0xFF);
    
    GC9A01_write_command(GC9A01_87); // 0x87
    GC9A01_write_data(0xFF);
    
    GC9A01_write_command(GC9A01_88); // 0x88
    GC9A01_write_data(0x0A);
    
    GC9A01_write_command(GC9A01_89); // 0x89
    GC9A01_write_data(0x21);
    
    GC9A01_write_command(GC9A01_8A); // 0x8A
    GC9A01_write_data(0x00);
    
    GC9A01_write_command(GC9A01_8B); // 0x8B
    GC9A01_write_data(0x80);
    
    GC9A01_write_command(GC9A01_8C); // 0x8C
    GC9A01_write_data(0x01);
    
    GC9A01_write_command(GC9A01_8D); // 0x8D
    GC9A01_write_data(0x01);
    
    GC9A01_write_command(GC9A01_8E); // 0x8E
    GC9A01_write_data(0xFF);
    
    GC9A01_write_command(GC9A01_8F); // 0x8F
    GC9A01_write_data(0xFF);
    
    
    GC9A01_write_command(GC9A01_DFCTRL); // 0xB6
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    
    GC9A01_write_command(GC9A01_MADCTL); // 0x36
    
#if ORIENTATION == 0
    GC9A01_write_data(GC9A01_MADCTL_OR0); // 0x18 - с низу вверх
#elif ORIENTATION == 1
    GC9A01_write_data(GC9A01_MADCTL_OR1); // 0x28 - с права на лево
#elif ORIENTATION == 2
    GC9A01_write_data(GC9A01_MADCTL_OR2); // 0x48 - с верху вниз
#else
    GC9A01_write_data(GC9A01_MADCTL_OR3); // 0x88 - тоже с низу вверх
#endif
    
    GC9A01_write_command(GC9A01_COLOR_MODE); // 0x3A
    GC9A01_write_data(GC9A01_CM_16_BIT);
    
    GC9A01_write_command(GC9A01_90); // 0x90
    GC9A01_write_data(0x08);
    GC9A01_write_data(0x08);
    GC9A01_write_data(0x08);
    GC9A01_write_data(0x08);
    
    GC9A01_write_command(GC9A01_BD); // 0xBD
    GC9A01_write_data(0x06);
    
    GC9A01_write_command(GC9A01_BC); // 0xBC
    GC9A01_write_data(0x00);
    
    GC9A01_write_command(GC9A01_FF); // 0xFF
    GC9A01_write_data(0x60);
    GC9A01_write_data(0x01);
    GC9A01_write_data(0x04);
    
    GC9A01_write_command(GC9A01_VR1AVCTRL); // 0xC3
    GC9A01_write_data(0x13);
    
    GC9A01_write_command(GC9A01_VR1BVCTRL); // 0xC4
    GC9A01_write_data(0x13);
    
    GC9A01_write_command(GC9A01_VR2AVCTRL); // 0xC9
    GC9A01_write_data(0x22);
    
    GC9A01_write_command(GC9A01_BE); // 0xBE
    GC9A01_write_data(0x11);
    
    GC9A01_write_command(GC9A01_E1); // 0xE1
    GC9A01_write_data(0x10);
    GC9A01_write_data(0x0E);
    
    GC9A01_write_command(GC9A01_DF); // 0xDF
    GC9A01_write_data(0x21);
    GC9A01_write_data(0x0c);
    GC9A01_write_data(0x02);
    
    GC9A01_write_command(GC9A01_SETGAMMA1); // 0xF0
    GC9A01_write_data(0x45);
    GC9A01_write_data(0x09);
    GC9A01_write_data(0x08);
    GC9A01_write_data(0x08);
    GC9A01_write_data(0x26);
    GC9A01_write_data(0x2A);
    
    GC9A01_write_command(GC9A01_SETGAMMA2); // 0xF1
    GC9A01_write_data(0x43);
    GC9A01_write_data(0x70);
    GC9A01_write_data(0x72);
    GC9A01_write_data(0x36);
    GC9A01_write_data(0x37);
    GC9A01_write_data(0x6F);
    
    GC9A01_write_command(GC9A01_SETGAMMA3); // 0xF2
    GC9A01_write_data(0x45);
    GC9A01_write_data(0x09);
    GC9A01_write_data(0x08);
    GC9A01_write_data(0x08);
    GC9A01_write_data(0x26);
    GC9A01_write_data(0x2A);
    
    GC9A01_write_command(GC9A01_SETGAMMA4); // 0xF3
    GC9A01_write_data(0x43);
    GC9A01_write_data(0x70);
    GC9A01_write_data(0x72);
    GC9A01_write_data(0x36);
    GC9A01_write_data(0x37);
    GC9A01_write_data(0x6F);
    
    GC9A01_write_command(GC9A01_ED); // 0xED
    GC9A01_write_data(0x1B);
    GC9A01_write_data(0x0B);
    
    GC9A01_write_command(GC9A01_AE); // 0xAE
    GC9A01_write_data(0x77);
    
    GC9A01_write_command(GC9A01_CD); // 0xCD
    GC9A01_write_data(0x63);
    
    GC9A01_write_command(GC9A01_70); // 0x70
    GC9A01_write_data(0x07);
    GC9A01_write_data(0x07);
    GC9A01_write_data(0x04);
    GC9A01_write_data(0x0E);
    GC9A01_write_data(0x0F);
    GC9A01_write_data(0x09);
    GC9A01_write_data(0x07);
    GC9A01_write_data(0x08);
    GC9A01_write_data(0x03);
    
    GC9A01_write_command(GC9A01_FRRATE); // 0xE8
    GC9A01_write_data(0x34);
    
    GC9A01_write_command(GC9A01_62); // 0x62
    GC9A01_write_data(0x18);
    GC9A01_write_data(0x0D);
    GC9A01_write_data(0x71);
    GC9A01_write_data(0xED);
    GC9A01_write_data(0x70);
    GC9A01_write_data(0x70);
    GC9A01_write_data(0x18);
    GC9A01_write_data(0x0F);
    GC9A01_write_data(0x71);
    GC9A01_write_data(0xEF);
    GC9A01_write_data(0x70);
    GC9A01_write_data(0x70);
    
    GC9A01_write_command(GC9A01_63); // 0x63
    GC9A01_write_data(0x18);
    GC9A01_write_data(0x11);
    GC9A01_write_data(0x71);
    GC9A01_write_data(0xF1);
    GC9A01_write_data(0x70);
    GC9A01_write_data(0x70);
    GC9A01_write_data(0x18);
    GC9A01_write_data(0x13);
    GC9A01_write_data(0x71);
    GC9A01_write_data(0xF3);
    GC9A01_write_data(0x70);
    GC9A01_write_data(0x70);
    
    GC9A01_write_command(GC9A01_64); // 0x64
    GC9A01_write_data(0x28);
    GC9A01_write_data(0x29);
    GC9A01_write_data(0xF1);
    GC9A01_write_data(0x01);
    GC9A01_write_data(0xF1);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x07);
    
    GC9A01_write_command(GC9A01_66); // 0x66
    GC9A01_write_data(0x3C);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0xCD);
    GC9A01_write_data(0x67);
    GC9A01_write_data(0x45);
    GC9A01_write_data(0x45);
    GC9A01_write_data(0x10);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    
    GC9A01_write_command(GC9A01_67); // 0x67
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x3C);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x01);
    GC9A01_write_data(0x54);
    GC9A01_write_data(0x10);
    GC9A01_write_data(0x32);
    GC9A01_write_data(0x98);
    
    GC9A01_write_command(GC9A01_74); // 0x74
    GC9A01_write_data(0x10);
    GC9A01_write_data(0x85);
    GC9A01_write_data(0x80);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x00);
    GC9A01_write_data(0x4E);
    GC9A01_write_data(0x00);
    
    GC9A01_write_command(GC9A01_98); // 0x98
    GC9A01_write_data(0x3e);
    GC9A01_write_data(0x07);

    GC9A01_write_command(GC9A01_TEON); // 0x35 - Tearing Effect Line ON 
    
    GC9A01_write_command(GC9A01_INVON); // 0x21 - Display Inversion ON 
    
    GC9A01_write_command(GC9A01_SLEEPOUT); // 0x11 - Sleep OUT 
    delay(120);

    GC9A01_write_command(GC9A01_DISPON); // 0x29 - Display ON
    delay(20);

    PORT_SPI |= (1 << DD_SS); // chip_select_disable();    
}




