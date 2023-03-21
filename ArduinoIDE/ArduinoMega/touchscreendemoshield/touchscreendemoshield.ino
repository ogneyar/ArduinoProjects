
// Mega

#include <stdint.h>
#include "TouchScreen.h"

// These are the pins for the shield!
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
     Serial.print("X = "); 
    //  if (p.z>500) Serial.print(0);
    //  else 
     Serial.print(p.x);
     Serial.print("\tY = "); 
    //  if (p.z>500) Serial.print(0);
    //  else 
     Serial.print(p.y);
     Serial.print("\tPressure = "); 
    //  if (p.z>500) Serial.println(0);
    //  else Serial.println(1);
     Serial.println(p.z);
  }
}
