
// Nano, LGT8F328

extern "C" {
  extern __FlashStringHelper *D13OnOff(byte);
}

// asm volatile(
//   ".global D13OnOff \n\t"
//   ".equ DDRB, 0x04 \n\t"
//   ".equ PORTB, 0x05 \n\t"
//   "D13OnOff: \n\t"
//   "ldi R16, 1<<5 \n\t"
//   "out DDRB, R16 \n\t"
//   "out PORTB, R17 \n\t"
//   "ret \n\t"
// );
  
void setup() {
}

void loop() {
  // asm volatile(
  //   "mov R17, 0 \n\t"
  //   "call D13OnOff \n\t"
  // );
  D13OnOff(0b00000000);
  delay(900);
  
  // asm volatile(
  //   "mov R17, 1<<5 \n\t"
  //   "call D13OnOff \n\t"
  // );
  D13OnOff(1<<5);
  delay(100);
}