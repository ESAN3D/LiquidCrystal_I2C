//YWROBOT
#ifndef LiquidCrystal_I2C_h
#define LiquidCrystal_I2C_h

#include <inttypes.h>
#include "Print.h" 
#include <Wire.h>
#include <Arduino.h>

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

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit

class LiquidCrystal_I2C : public Print {
public:
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
  void createChar(uint8_t location, const char *charmap);
  // Example: 	const char bell[8] PROGMEM = {B00100,B01110,B01110,B01110,B11111,B00000,B00100,B00000};
  size_t print(const String &);
  size_t createChars(const String &);
  void mergeChars(uint8_t n, byte *first, byte *second);
  virtual size_t write(const uint8_t *buffer, size_t size);
  size_t write(const char *buffer, size_t size) {
    return write((const uint8_t *)buffer, size);
  }
  
  void setCursor(uint8_t, uint8_t); 
#if defined(ARDUINO) && ARDUINO >= 100
  virtual size_t write(uint8_t);
#else
  virtual void write(uint8_t);
#endif
  void command(uint8_t);
  void init();
  void oled_init();

////compatibility API function aliases
void blink_on();						// alias for blink()
void blink_off();       					// alias for noBlink()
void cursor_on();      	 					// alias for cursor()
void cursor_off();      					// alias for noCursor()
void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
void printstr(const char[]);

////Unsupported API functions (not implemented in this library)
uint8_t status();
void setContrast(uint8_t new_val);
uint8_t keypad();
void setDelay(int,int);
void on();
void off();
uint8_t init_bargraph(uint8_t graphtype);
void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);
  
private:
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
  bool _oled = false;
  uint8_t _cols;
  uint8_t _rows;
  uint8_t _backlightval;
  uint8_t _currow;
  byte _thchar[88][8] = {
      {
	  B00000,B00000,B00000,B01111,B00101,B00101,B00101,B00101  
      },
      {
	  B00000,B00000,B00000,B01101,B00101,B00101,B00101,B00111  
      },
      {
	  B00000,B00000,B00000,B10101,B11101,B00101,B00101,B00111 
      },
      {
	  B00000,B00000,B00000,B01111,B01001,B01101,B01001,B01001
      },
      {
	  B00000,B00000,B00000,B01101,B01011,B01001,B01101,B01001
      },
      {
	  B00000,B00000,B00000,B10101,B11101,B00101,B01111,B01101	//KHO RAKHANG
      },
      {
	  B00000,B00000,B00000,B00011,B00001,B01001,B00101,B00011
      },
      {
	  B00000,B00000,B00000,B01111,B00001,B00111,B00001,B00001
      },
      {
	  B00000,B00000,B00000,B11110,B00010,B11010,B01111,B01011
      },
      {
	  B00000,B00000,B00001,B11010,B01100,B01010,B01010,B01110	//CHO CHANG
      },
      {
	  B00000,B00000,B00001,B10110,B01100,B01010,B01010,B01110
      },
      {
	  B00000,B00000,B00000,B11101,B10101,B10101,B11111,B11101
      },
      {
	  B00000,B00000,B00000,B11101,B10101,B10101,B11101,B11111
      },
      {
	  B00000,B00000,B00000,B01111,B00101,B00101,B01101,B01101	//DO CHADA
      },
      {
	  B00000,B00000,B00000,B01111,B00101,B00101,B01101,B01101
      },
      {
	  B00000,B00000,B00111,B01111,B00001,B00111,B00001,B01101
      },
      {
	  B00000,B00000,B00000,B10101,B01011,B01101,B01001,B01001
      },
      {
	  B00000,B00000,B00000,B11101,B10101,B11101,B11111,B10101
      },
      {
	  B00000,B00000,B00000,B11101,B10101,B10101,B11111,B11101	//NO NEN
      },
      {
	  B00000,B00000,B00000,B01111,B01001,B01001,B01101,B01101
      },
      {
	  B00000,B00000,B00000,B01101,B01011,B01001,B01101,B01101
      },
      {
	  B00000,B00000,B00000,B11111,B01001,B01001,B01101,B01101
      },
      {
	  B00000,B00000,B00000,B11001,B01011,B01101,B01001,B01001	//TO THAHAN
      },
      {
	  B00000,B00000,B00000,B00111,B01111,B00001,B01001,B01111
      },
      {
	  B00000,B00000,B00000,B11010,B01010,B01010,B01111,B01011
      },
      {
	  B00000,B00000,B00000,B11001,B01001,B01001,B01001,B01111
      },
      {
	  B00000,B00001,B00001,B11001,B01001,B01001,B01001,B01111	//PO PLA
      },
      {
	  B00000,B00000,B00000,B01101,B01101,B01001,B01011,B01101
      },
      {
	  B00000,B00001,B00001,B01101,B01101,B01001,B01011,B01101
      },
      {
	  B00000,B00000,B00000,B11001,B11001,B01001,B01101,B01011	//PO PHAN
      },
      {
	  B00000,B00001,B00001,B11001,B11001,B01001,B01101,B01011
      },
      {
	  B00000,B00000,B00000,B01111,B00101,B00101,B01101,B01101
      },
      {
	  B00000,B00000,B00000,B01101,B00101,B00101,B01111,B01101
      },
      {
	  B00000,B00000,B00000,B01101,B01001,B01101,B01001,B01111	//YO YAK
      },
      {
	  B00000,B00000,B00000,B01111,B00010,B00001,B00011,B00011
      },
      {
	  B00000,B00000,B00000,B01111,B00101,B01001,B01101,B01101
      },
      {
	  B00000,B00000,B00000,B01111,B00001,B01111,B01001,B01101
      },
      {
	  B00000,B00000,B00000,B01111,B00101,B00101,B01101,B01101	//LU
      },
      {
	  B00000,B00000,B00000,B01111,B00001,B00001,B00011,B00011
      },
      {
	  B00000,B00000,B00001,B01111,B01001,B01101,B01001,B01001
      },
      {
	  B00000,B00000,B00000,B11010,B01011,B01110,B01010,B01110
      },
      {
	  B00000,B00000,B00001,B01111,B00001,B01111,B01001,B01101	//SO SUA
      },
      {
	  B00000,B00000,B00000,B11011,B01011,B01101,B01001,B01001
      },
      {
	  B00000,B00001,B00010,B11011,B01001,B01001,B01101,B01011
      },
      {
	  B00000,B00000,B00000,B01111,B00001,B01101,B01001,B01111
      },
      {
	  B00000,B00000,B00001,B01111,B00001,B01101,B01001,B01111	//HO NOKHUK
      },
      {
	  B00000,B00000,B00000,B01011,B01101,B00001,B00001,B00001	//PAIYANNOI
      },
      {
	  B00000,B00000,B00000,B01010,B01100,B00000,B01010,B01100	//SARA A
      },
      {
	  B00100,B00111,B00000,B00000,B00000,B00000,B00000,B00000	//MAI HAN-AKAT
      },
      {
	  B00000,B00000,B00000,B01110,B00010,B00010,B00010,B00010	//SARA AA
      },
      {
	  B11000,B11000,B00000,B00111,B00001,B00001,B00001,B00001	//SARA AM
      },
      {
	  B00000,B00111,B00000,B00000,B00000,B00000,B00000,B00000	//SARA I
      },
      {
	  B00001,B00111,B00000,B00000,B00000,B00000,B00000,B00000	//SARA II
      },
      {
	  B00011,B00111,B00000,B00000,B00000,B00000,B00000,B00000	//SARA UE
      },
      {
	  B00101,B01111,B00000,B00000,B00000,B00000,B00000,B00000	//SARA UEE
      },
      {
	  B00011,B00001,B00000,B00000,B00000,B00000,B00000,B00000	//SARA U
      },
      {
	  B00111,B00011,B00000,B00000,B00000,B00000,B00000,B00000	//SARA UU
      },
      {
	  B00011,B00011,B00000,B00000,B00000,B00000,B00000,B00000	//PHINTHU
      },
      {
	  B00100,B11110,B10101,B10101,B11110,B10101,B10101,B11110	//BAHT
      },
      {
	  B00000,B00000,B00000,B00010,B00010,B00010,B00011,B00011	//SARA E
      },
      {
	  B00000,B00000,B00000,B01010,B01010,B01010,B01111,B01111	//SARA AE
      },
      {
	  B00111,B01100,B00010,B00010,B00010,B00010,B00011,B00011	//SARA O
      },
      {
	  B01110,B01110,B00010,B00010,B00010,B00010,B00011,B00011	//SARA AI MUAN
      },
      {
	  B10110,B11010,B00010,B00010,B00010,B00010,B00011,B00011	//SARA AI MALAI
      },
      {
	  B00000,B00000,B00000,B01110,B00010,B00010,B00010,B00010	//LAKKHANGYAO
      },
      {
	  B00000,B00000,B00000,B00000,B10100,B11100,B00100,B00100	//MAIYAMOK
      },
      {
	  B00111,B00110,B00000,B00000,B00000,B00000,B00000,B00000	//MAITAIKHU
      },
      {
	  B00001,B00001,B00000,B00000,B00000,B00000,B00000,B00000	//MAI EK
      },
      {
	  B00110,B00011,B00000,B00000,B00000,B00000,B00000,B00000	//MAI THO
      },
      {
	  B01101,B01111,B00000,B00000,B00000,B00000,B00000,B00000	//MAI TRI
      },
      {
	  B00010,B00111,B00010,B00000,B00000,B00000,B00000,B00000	//MAI CHATTAWA
      },
      {
	  B00111,B00100,B00000,B00000,B00000,B00000,B00000,B00000	//THANTHAKHAT
      },
      {
	  B00011,B00011,B00000,B00000,B00000,B00000,B00000,B00000	//NIKHAHIT
      },
      {
	  B00000,B00000,B00000,B00011,B00100,B00111,B00100,B00011	//YAMAKKAN
      },
      {
	  B00000,B00000,B00000,B01110,B10001,B10101,B10001,B01110	//FONGMAN
      },
      {
	  B00000,B00000,B00000,B01110,B10001,B10001,B10001,B01110	//ZERO
      },
      {
	  B00000,B00000,B00000,B00110,B01001,B01101,B00001,B01110	//ONE
      },
      {
	  B00000,B00000,B10000,B10101,B10111,B10111,B10001,B11110	//TWO
      },
      {
	  B00000,B00000,B00000,B10101,B11111,B10101,B10001,B11001	//THREE
      },
      {
	  B00000,B00000,B00001,B00110,B01000,B10110,B10100,B01111	//FOUR
      },
      {
	  B00000,B00001,B01001,B01110,B01000,B10110,B10100,B01111	//FIVE
      },
      {
	  B00000,B10000,B01000,B00110,B00001,B01101,B01001,B01111	//SIX
      },
      {
	  B00000,B00001,B00001,B10101,B11101,B10101,B10011,B11011	//SEVEN
      },
      {
	  B00000,B00001,B00001,B00111,B01000,B10011,B10101,B11011	//EIGHT
      },
      {
	  B00000,B00001,B00001,B00001,B01010,B10100,B10100,B11010	//NINE
      },
      {
	  B00000,B00000,B00000,B01011,B01111,B00011,B00011,B00011	//ANGKHANKHU
      },
      {
	  B00000,B00000,B00000,B00000,B00000,B11000,B10010,B11101	//KHOMUT
      }
  };
  byte _tmpchar[8][8];
  byte _blankchar[8] = {
	B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000
  };
};

#endif
