#include <avr/io.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include "uart.h"

UART uart;

int main() {
  uint8_t osccal = 0;

  power_all_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  uart.begin();

  do {
    OSCCAL = osccal;
    asm volatile ("nop\n"
      "nop\n"
      "nop\n"
      "nop\n");
    uart.print_P(PSTR("OSCCAL: 0x"));
    uart.hex(osccal);
    uart.print_P(PSTR("\r\n*** 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ***\r\n"));
  } while (++osccal);

  sleep_enable();
  sleep_cpu();
}
