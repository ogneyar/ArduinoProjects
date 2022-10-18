
// Wemos D1 mini

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
    os_delay_us(intervalRising);
    digitalWrite(LED_BUILTIN, LIGHT_OFF);
    os_delay_us(intervalFalling);

    intervalRising--;
    intervalFalling++;    
  }
    

  while(intervalFalling) {    
    digitalWrite(LED_BUILTIN, LIGHT_ON);  
    os_delay_us(intervalRising);
    digitalWrite(LED_BUILTIN, LIGHT_OFF);
    os_delay_us(intervalFalling);
      
    intervalRising++;
    intervalFalling--;
  }

}
