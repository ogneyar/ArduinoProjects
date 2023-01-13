
// Nano, LGT8F328

#define LIGHT_ON LOW
#define LIGHT_OFF HIGH

unsigned int intervalRising = 1024; // количество микро секунд (при значении 2000 срабатывает WTD походу)
unsigned int intervalFalling = 0;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {

  while(intervalRising) {    
    digitalWrite(LED_BUILTIN, LIGHT_ON);  
    delayMicroseconds(intervalRising);
    digitalWrite(LED_BUILTIN, LIGHT_OFF);
    delayMicroseconds(intervalFalling);

    intervalRising--;
    intervalFalling++;    
  }
    

  while(intervalFalling) {    
    digitalWrite(LED_BUILTIN, LIGHT_ON);  
    delayMicroseconds(intervalRising);
    digitalWrite(LED_BUILTIN, LIGHT_OFF);
    delayMicroseconds(intervalFalling);
      
    intervalRising++;
    intervalFalling--;
  }

}
