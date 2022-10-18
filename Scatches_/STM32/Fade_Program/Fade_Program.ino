
// STM32F103C8T6 or STM32F401CCU6 or STM32F411CEU6
#define LED PC13
// STM32F030F4P6 
//#define LED PA4

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
