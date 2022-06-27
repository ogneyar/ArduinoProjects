
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

//
#define SDA        PC4
#define SDA_DDR   DDRC
#define SDA_PIN   PINC

#define SCL       PC5
#define SCL_DDR   DDRC
#define SCL_PIN   PINC

//
#define I2C_DELAY _delay_us(10)

//
#define SDA_1   SDA_DDR&=~(1<<SDA)
#define SDA_0   SDA_DDR|=(1<<SDA)
#define SCL_1   SCL_DDR&=~(1<<SCL)
#define SCL_0   SCL_DDR|=(1<<SCL)

// i2c functions
void i2c_start();
void i2c_stop();
uint8_t i2c_send(uint8_t data);
uint8_t i2c_read(uint8_t ask);



// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100  // Enable bit
#define Rw 0b00000010  // Read/Write bit
#define Rs 0b00000001  // Register select bit


void printIIC(uint8_t value);

LiquidCrystal_I2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
void clear();
void home();
void noDisplay();
void display();
void noBlink();
void blink();
void noCursor();
void cursor();
void scrollDisplayLeft();
void scrollDisplayRight();
void printLeft();
void printRight();
void leftToRight();
void rightToLeft();
void shiftIncrement();
void shiftDecrement();
void noBacklight();
void backlight();
void autoscroll();
void noAutoscroll();
void createChar(uint8_t, uint8_t[]);
void setCursor(uint8_t, uint8_t);

virtual size_t write(uint8_t);

void command(uint8_t);
void init();

////compatibility API function aliases
void blink_on();						// alias for blink()
void blink_off();       					// alias for noBlink()
void cursor_on();      	 					// alias for cursor()
void cursor_off();      					// alias for noCursor()
void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
void printstr(const char[]);

void init_priv();
void send(uint8_t, uint8_t);
void write4bits(uint8_t);
void expanderWrite(uint8_t);
void pulseEnable(uint8_t);



uint8_t _Addr;
uint8_t _displayfunction;
uint8_t _displaycontrol;
uint8_t _displaymode;
uint8_t _numlines;
uint8_t _cols;
uint8_t _rows;
uint8_t _backlightval;




int main(void)
{
    while(1) {}
}


// i2c functions

//
void i2c_start(void){
	SDA_0;
	I2C_DELAY;
	SCL_0;
}
//
void i2c_stop(void){
	SDA_0;
	I2C_DELAY;
	SCL_1;
	I2C_DELAY;
	SDA_1;
}
// 
uint8_t i2c_send(uint8_t data){
	uint8_t i=8, ask;
	while (i--)
	{
		if(data&(1<<i)) SDA_1;//
		else SDA_0;//
		I2C_DELAY;
		SCL_1;//
		I2C_DELAY;
		SCL_0;//
	}
	SDA_1;//
	I2C_DELAY;
	SCL_1;//
	I2C_DELAY;
	ask=(SDA_PIN&(1<<SDA));//
	SCL_0;//
	return ask;//  1 - ask, or 0 - no_ask
}
// 
uint8_t i2c_read(uint8_t ask){
	uint8_t bytes=0, i=8;
	while(i--)
	{
		SCL_1;//
		I2C_DELAY;
		if(SDA_PIN & (1 << SDA)) bytes|=(1<<i);//
		SCL_0;//
		I2C_DELAY;
	}
	if(ask) SDA_0;// ask or no_ask
	else SDA_1;	
	SCL_1;//
	I2C_DELAY;//
	SCL_0;//
	I2C_DELAY;
	SDA_1;//
	return bytes;
}


// LiquidCrystal_I2C functions

inline size_t write(uint8_t value) {
	send(value, Rs);
	return 1;
}


void printIIC(uint8_t value) {
	i2c_start();
	i2c_send(value);
	i2c_stop();
}


LiquidCrystal_I2C(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows)
{
	_Addr = lcd_Addr;
	_cols = lcd_cols;
	_rows = lcd_rows;
	_backlightval = LCD_NOBACKLIGHT;
}

void init(){
	init_priv();
}

void init_priv()
{
	//Wire.begin();
	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	begin(_cols, _rows);
}

void begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
	if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;

	// for some 1 line displays you can select a 10 pixel high font
	if ((dotsize != 0) && (lines == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	_delay_ms(50);
	
	// Now we pull both RS and R/W low to begin commands
	expanderWrite(_backlightval);	// reset expanderand turn backlight off (Bit 8 =1)
	_delay_ms(1000);

	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46
	
	// we start in 8bit mode, try to set 4 bit mode
	write4bits(0x03 << 4);
	_delay_us(4500); // wait min 4.1ms
	
	// second try
	write4bits(0x03 << 4);
	_delay_us(4500); // wait min 4.1ms
	
	// third go!
	write4bits(0x03 << 4);
	_delay_us(150);
	
	// finally, set to 4-bit interface
	write4bits(0x02 << 4);


	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);
	
	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();
	
	// clear it off
	clear();
	
	// Initialize to default text direction (for roman languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	
	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);
	
	home();
	
}

/********** high level commands, for the user! */
void clear(){
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	_delay_us(2000);  // this command takes a long time!
}

void home(){
	command(LCD_RETURNHOME);  // set cursor position to zero
	_delay_us(2000);  // this command takes a long time!
}

void setCursor(uint8_t col, uint8_t row){
int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
if ( row > _numlines ) {
	row = _numlines-1;    // we count rows starting w/0
}
command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void display() {
	_displaycontrol |= LCD_DISPLAYON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void noCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void cursor() {
	_displaycontrol |= LCD_CURSORON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void noBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void blink() {
	_displaycontrol |= LCD_BLINKON;
	command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void scrollDisplayLeft(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void scrollDisplayRight(void) {
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void leftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void rightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void autoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void createChar(uint8_t location, uint8_t charmap[]) {
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		write(charmap[i]);
	}
}

// Turn the (optional) backlight off/on
void noBacklight(void) {
	_backlightval=LCD_NOBACKLIGHT;
	expanderWrite(0);
}

void backlight(void) {
	_backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}



/*********** mid level commands, for sending data/cmds */

inline void command(uint8_t value) {
	send(value, 0);
}


/************ low level data pushing commands **********/

// write either command or data
void send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
       write4bits((highnib)|mode);
	write4bits((lownib)|mode); 
}

void write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void expanderWrite(uint8_t _data){                                        
	//Wire.beginTransmission(_Addr);
	printIIC(_data | _backlightval);
	//Wire.endTransmission();   
}

void pulseEnable(uint8_t _data){
	expanderWrite(_data | En);	// En high
	_delay_us(1);		// enable pulse must be >450ns
	
	expanderWrite(_data & ~En);	// En low
	_delay_us(50);		// commands need > 37us to settle
} 


// Alias functions

void cursor_on(){
	cursor();
}

void cursor_off(){
	noCursor();
}

void blink_on(){
	blink();
}

void blink_off(){
	noBlink();
}

void load_custom_character(uint8_t char_num, uint8_t *rows){
		createChar(char_num, rows);
}

void setBacklight(uint8_t new_val){
	if(new_val){
		backlight();		// turn backlight on
	}else{
		noBacklight();		// turn backlight off
	}
}

void printstr(const char c[]){
	//This function is not identical to the function used for "real" I2C displays
	//it's here so the user sketch doesn't have to be changed 
	print(c);
}

