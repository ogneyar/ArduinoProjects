
// atmega8

byte pin = 5;
byte value = 255;
int pause1 = 0x000001c0;
int pause2 = 0x00000180;

void beep();
void beep7(int pause = pause1);
void beep6(int pause = pause1);
void beep5(int pause = pause1);
void beep4(int pause = pause1);
void beep3(int pause = pause2);
void beep2(int pause = pause2);
void beep1(int pause = pause2);

//
void setup() {
  pinMode(pin, OUTPUT);
}

//
void loop()
{
  beep();
  _delay_ms(1000);
}

//
void beep()
{
  beep4();
  beep7();
  beep4();
  beep6();
  beep3();
  beep2();
  beep1();
}

//
void beep7(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(700);
  }
}
//
void beep6(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(600);
  }
}
//
void beep5(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(500);
  }
}
//
void beep4(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(400);
  }
}
//
void beep3(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(300);
  }
}
//
void beep2(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(200);
  }
}
//
void beep1(int pause)
{
  for (int i = 0; i < pause; i++)
  {    
    analogWrite(pin, value);
    _delay_us(1000);
    analogWrite(pin, 0);
    _delay_us(100);
  }
}

