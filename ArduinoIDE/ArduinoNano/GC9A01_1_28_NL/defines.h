
#ifndef _DEFINES_H_
#define _DEFINES_H_


#define GC9A01_SLEEPENTER 0x10 // Enter Sleep Mode
#define GC9A01_SLEEPOUT   0x11 // Sleep OUT

#define GC9A01_INVOFF     0x20 // Display Inversion OFF 
#define GC9A01_INVON      0x21 // Display Inversion ON 
#define GC9A01_DISPOFF    0x28 // Display OFF
#define GC9A01_DISPON     0x29 // Display ON

#define GC9A01_CASET      0x2A // Column Address Set
#define GC9A01_RASET      0x2B // Page (Row) Address Set
#define GC9A01_RAMWR      0x2C // Memory Write
// #define GC9A01_RAMRD      0x2E

#define GC9A01_TEOFF      0x34 // Tearing Effect Line OFF
#define GC9A01_TEON       0x35 // Tearing Effect Line ON

#define GC9A01_MADCTL     0x36 // Memory Access Control
#define GC9A01_MADCTL_OR0 0x18 // Memory Access Control Oriental 0
#define GC9A01_MADCTL_OR1 0x28 // Memory Access Control Oriental 1
#define GC9A01_MADCTL_OR2 0x48 // Memory Access Control Oriental 2
#define GC9A01_MADCTL_OR3 0x88 // Memory Access Control Oriental 3

#define GC9A01_COLOR_MODE 0x3A
#define GC9A01_CM_12_BIT  0x03
#define GC9A01_CM_16_BIT  0x05
#define GC9A01_CM_18_BIT  0x06

#define GC9A01_RAMWR_CONT 0x3C // Write Memory Continue

#define GC9A01_62 0x62
#define GC9A01_63 0x63
#define GC9A01_64 0x64
#define GC9A01_66 0x66
#define GC9A01_67 0x67

#define GC9A01_70 0x70
#define GC9A01_74 0x74

#define GC9A01_84 0x84
#define GC9A01_85 0x85
#define GC9A01_86 0x86
#define GC9A01_87 0x87
#define GC9A01_88 0x88
#define GC9A01_89 0x89
#define GC9A01_8A 0x8A
#define GC9A01_8B 0x8B
#define GC9A01_8C 0x8C
#define GC9A01_8D 0x8D
#define GC9A01_8E 0x8E
#define GC9A01_8F 0x8F

#define GC9A01_90 0x90
#define GC9A01_98 0x98

#define GC9A01_AE 0xAE

#define GC9A01_DFCTRL 0xB6 // Display Function Control
#define GC9A01_BC 0xBC
#define GC9A01_BD 0xBD
#define GC9A01_BE 0xBE

#define GC9A01_VR1AVCTRL 0xC3 // Vreg1a voltage Control
#define GC9A01_VR1BVCTRL 0xC4 // Vreg1b voltage Control
#define GC9A01_VR2AVCTRL 0xC9 // Vreg2a voltage Control
#define GC9A01_CD 0xCD

#define GC9A01_DF 0xDF

#define GC9A01_E1 0xE1
#define GC9A01_FRRATE 0xE8 // Frame Rate
#define GC9A01_EB 0xEB
#define GC9A01_ED 0xED
#define GC9A01_INREGEN2   0xEF // Inner register enable 2

#define GC9A01_SETGAMMA1  0xF0 // SET_GAMMA1
#define GC9A01_SETGAMMA2  0xF1 // SET_GAMMA2
#define GC9A01_SETGAMMA3  0xF2 // SET_GAMMA3
#define GC9A01_SETGAMMA4  0xF3 // SET_GAMMA4
#define GC9A01_INREGEN1   0xFE // Inner register enable 1
#define GC9A01_FF 0xFF


// Some ready-made 16-bit ('565') color settings:
// НЕ RGB А RBG
#define _BLACK      0x0000
#define _WHITE      0xFFFF
#define _RED        0x07E0
#define _GREEN      0x001F
#define _BLUE       0xF800
#define _RED_BLUE   0xFFE0    // фиолетовый
#define _RED_GREEN  0x07FF  // голубой
#define _BLUE_GREEN 0xF81F   // оранджевый

#define LCD_D        1 // data
#define LCD_C        0 // command

#define GC9A01_XSTART 0
#define GC9A01_YSTART 0
#define GC9A01_WIDTH  240
#define GC9A01_HEIGHT 240


#endif  /* _DEFINES_H_ */

