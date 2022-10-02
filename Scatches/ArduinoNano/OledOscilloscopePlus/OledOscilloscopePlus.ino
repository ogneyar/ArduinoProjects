#include <Wire.h>
#include <U8g2lib.h>

const uint8_t pinRotClk = 2;
const uint8_t pinRotDt = 3;
const uint8_t pinRotSw = 4;
const uint8_t pinPWM25 = 5;
const uint8_t pinPWM50 = 6;

const uint8_t bufferSize = 128; // Width of OLED screen

volatile uint8_t buffer[bufferSize];
volatile uint8_t bufferLen;
volatile uint32_t duration;

const uint8_t logicZero = 77; // 1.5V
const uint8_t logicOne = 153; // 3V

enum mode_t : uint8_t { DIV8 = 3, DIV16 = 4, DIV32 = 5, DIV64 = 6, DIV128 = 7 };

volatile mode_t mode = DIV8;

#define ROTATE U8G2_R0 // U8G2_R2 to flip screen

U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(ROTATE, U8X8_PIN_NONE);

ISR(ADC_vect) {
  buffer[bufferLen++] = ADCH;
  if (bufferLen >= bufferSize) {
    ADCSRA &= ~(bit(ADATE) | bit(ADIE)); // Turn off automatic triggering
    duration = micros() - duration;
  }
}

void rotISR() {
  static uint8_t lastState = 0B00000011;

  lastState <<= 2;
  lastState |= ((PIND >> 2) & 0B00000011); // D2 and D3
  if (lastState == 0B10000111) {
    if (mode > DIV8)
      --(*((uint8_t*)&mode));
  } else if (lastState == 0B01001011) {
    if (mode < DIV128)
      ++(*((uint8_t*)&mode));
  }
}

void getInfo(uint8_t &avg, uint8_t &minimum, uint8_t &maximum, uint16_t &freq) {
  uint8_t edge = 0, edgeCount = 0;
  uint16_t edgeSum = 0;
  uint16_t bufferSum = 0;

  minimum = 255;
  maximum = 0;

  for (uint8_t i = 0; i < bufferSize; ++i) {
    bufferSum += buffer[i];
    if (buffer[i] < minimum)
      minimum = buffer[i];
    if (buffer[i] > maximum)
      maximum = buffer[i];
    if (i && (buffer[i] > logicOne) && (buffer[i - 1] < logicZero)) { // Rising edge detected
      if (edge) {
        edgeSum += (i - edge);
        ++edgeCount;
      }
      edge = i;
    }
  }

  avg = bufferSum / bufferSize;
  if (edgeCount)
    freq = 1000000UL / (duration * (edgeSum / edgeCount) / bufferSize);
  else
    freq = 0;
}

void drawScreen(bool info) {
  u8g2.setDrawColor(1);
  for (int8_t v = 5; v >= 0; --v) {
    uint8_t tickY;

    if (v == 5)
      tickY = 0;
    else if (! v)
      tickY = u8g2.getDisplayHeight() - 1;
    else
      tickY = u8g2.getDisplayHeight() - u8g2.getDisplayHeight() * v / 5;
    for (uint8_t x = 0; x < u8g2.getDisplayWidth(); x += 8)
      u8g2.drawPixel(x, tickY);
  }

  for (uint8_t x = 1; x < bufferSize; ++x) {
    u8g2.drawLine(x - 1, map(buffer[x - 1], 0, 255, u8g2.getDisplayHeight() - 1, 0), x, map(buffer[x], 0, 255, u8g2.getDisplayHeight() - 1, 0));
  }

  u8g2.setDrawColor(0);
  u8g2.setCursor(0, 0);
  u8g2.print(F("5V"));
  u8g2.setCursor(0, u8g2.getDisplayHeight() - 8);
  if (info) {
    uint8_t avg, minimum, maximum;
    uint16_t freq;

    getInfo(avg, minimum, maximum, freq);
    u8g2.print(F("avg/min/max:"));
    u8g2.print(5.0 / 255 * avg, 1);
    u8g2.print('/');
    u8g2.print(5.0 / 255 * minimum, 1);
    u8g2.print('/');
    u8g2.print(5.0 / 255 * maximum, 1);
    u8g2.setCursor(0, u8g2.getDisplayHeight() - 16);
    u8g2.print(F("freq:"));
    if (freq)
      u8g2.print(freq);
    else
      u8g2.print('-');
  } else {
    u8g2.print(duration);
    u8g2.print(F(" us"));
  }
}

void setup() {
  pinMode(pinRotClk, INPUT);
  pinMode(pinRotDt, INPUT);
  pinMode(pinRotSw, INPUT_PULLUP);

  pinMode(pinPWM25, OUTPUT);
  pinMode(pinPWM50, OUTPUT);
  analogWrite(pinPWM25, 63); // 25% PWM
  analogWrite(pinPWM50, 127); // 50% PWM

  attachInterrupt(digitalPinToInterrupt(pinRotClk), rotISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinRotDt), rotISR, CHANGE);

  Wire.begin();
  Wire.setClock(400000);

  u8g2.begin();
  u8g2.setFont(u8g2_font_5x8_mr);
  u8g2.setFontDirection(0);
  u8g2.setFontMode(0);
  u8g2.setFontPosTop();
  u8g2.setFontRefHeightExtendedText();

  ADCSRA = bit(ADEN) | bit(ADPS1) | bit(ADPS0); // Turn ADC on with prescaler of 8
  ADMUX = bit(REFS0) | bit(ADLAR); // VCC as AREF, left align and channel 0 as input
  ADCSRB = 0; // Free running mode

  interrupts();
}

void loop() {
  static mode_t lastMode = DIV8;
  static bool stopped = false;
  static bool lastSw = HIGH;
  bool sw = digitalRead(pinRotSw);

  if (sw != lastSw) {
    static const uint32_t debounceTime = 20;
    static uint32_t lastTime = 0;

    if (millis() >= lastTime + debounceTime) {
      if (sw == LOW) { // Button pressed
        stopped = ! stopped;
      }
      lastSw = sw;
    }
    lastTime = millis();
  }

  if (! stopped) {
    if (mode != lastMode) {
      ADCSRA &= ~0x07;
      ADCSRA |= (uint8_t)mode;
      lastMode = mode;
    }

    bufferLen = 0;

    duration = micros();
    ADCSRA |= (bit(ADSC) | bit(ADATE) | bit(ADIE) | bit(ADIF)); // Start first measurement
    while (bufferLen < bufferSize); // Wait for filling buffer
  }

  u8g2.firstPage();
  do {
    drawScreen(stopped);
  } while (u8g2.nextPage());
}
