
// Zero(SamD)

void setup() {
  SerialUSB.begin(9600);
  while(!SerialUSB) 
    ;
}

void loop() {  
  SerialUSB.println("Test serial");
  delay(1000);
}
