
// STM32F103C8T6

/*
RX2 - PA3
TX2 - PA4 
*/
 
void setup() {
  Serial.begin(9600);
  while (!Serial) ;


  Serial.print("\nUART working...");

}

void loop(void) {
}
