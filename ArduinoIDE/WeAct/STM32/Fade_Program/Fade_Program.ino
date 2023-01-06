
// STM32F103C8T6

#define LED PB2

byte ledPin = LED; 

#define LIGHT_ON LOW
#define LIGHT_OFF HIGH

unsigned int intervalRising = 1024; // количество микро секунд (при значении 2000 срабатывает WTD походу)
unsigned int intervalFalling = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
}


void loop() {

  while(intervalRising) {    
    digitalWrite(ledPin, LIGHT_ON);  
    delayMicroseconds(intervalRising);
    digitalWrite(ledPin, LIGHT_OFF);
    delayMicroseconds(intervalFalling);

    intervalRising--;
    intervalFalling++;    
  }
    

  while(intervalFalling) {    
    digitalWrite(ledPin, LIGHT_ON);  
    delayMicroseconds(intervalRising);
    digitalWrite(ledPin, LIGHT_OFF);
    delayMicroseconds(intervalFalling);
      
    intervalRising++;
    intervalFalling--;
  }

}
