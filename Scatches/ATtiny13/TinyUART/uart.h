#pragma once

#include <avr/io.h>
#include <avr/pgmspace.h>

#if (F_CPU != 16000000) && (F_CPU != 9600000) && (F_CPU != 8000000) && (F_CPU != 4800000) && (F_CPU != 4000000) && (F_CPU != 2000000) && (F_CPU != 1200000)
#error "Unsupported CPU frequency!"
#endif

#define UART_DDR    DDRB
#define UART_PORT   PORTB
#define UART_TX     3

static const char CRLF[] PROGMEM = "\r\n";

void uart_init() {
/*
  asm volatile ("sbi %[ddr], %[pin]\n"
    "sbi %[port], %[pin]\n"
    : : [ddr] "I" (_SFR_IO_ADDR(UART_DDR)), [port] "I" (_SFR_IO_ADDR(UART_PORT)), [pin] "I" (UART_TX));
*/
  UART_DDR |= (1 << UART_TX);
  UART_PORT |= (1 << UART_TX);
}

void __attribute__((noinline)) uart_write(char c) {
  asm volatile ("in __tmp_reg__, __SREG__\n"
    "cli\n"
    "ldi r18, 8\n"
    "cbi %[port], %[pin]\n"
#if F_CPU == 16000000
    "ldi r19, 44;1\n"
    "nop\n"
    "nop\n"
#elif F_CPU == 9600000
    "ldi r19, 26;1\n"
#elif F_CPU == 8000000
    "ldi r19, 21;1\n"
    "nop\n"
#elif F_CPU == 4800000
    "ldi r19, 12;1\n"
    "nop\n"
#elif F_CPU == 4000000
    "ldi r19, 10;1\n"
#elif F_CPU == 2000000
    "ldi r19, 4;1\n"
#elif F_CPU == 1200000
    "ldi r19, 1;1\n"
    "nop\n"
    "nop\n"
#endif
    "l_uart_write_delay_1:\n"
    "dec r19;1\n"
    "brne l_uart_write_delay_1;1/2\n"
    "nop;1\n"
    "l_uart_write_loop:\n"
    "ldi r19, 1;1\n"
    "and r19, %[c];1\n"
    "brne l_uart_write_out1;1/2\n"
    "nop;1\n"
    "cbi %[port], %[pin];1\n"
    "rjmp l_uart_write_cont;2\n"
    "l_uart_write_out1:\n"
    "sbi %[port], %[pin];1\n"
    "nop;1\n"
    "nop;1\n"
    "l_uart_write_cont:\n"
#if F_CPU == 16000000
    "ldi r19, 42;1\n"
    "nop;1\n"
    "nop;1\n"
#elif F_CPU == 9600000
    "ldi r19, 24;1\n"
#elif F_CPU == 8000000
    "ldi r19, 19;1\n"
    "nop;1\n"
#elif F_CPU == 4800000
    "ldi r19, 10;1\n"
    "nop;1\n"
#elif F_CPU == 4000000
    "ldi r19, 8;1\n"
#elif F_CPU == 2000000
    "ldi r19, 2;1\n"
#elif F_CPU == 1200000
    // No delay
#endif
#if F_CPU != 1200000
    "l_uart_write_delay_2:\n"
    "dec r19;1\n"
    "brne l_uart_write_delay_2;1/2\n"
    "nop;1\n"
#endif
    "lsr %[c];1\n"
    "dec r18;1\n"
    "brne l_uart_write_loop;1/2\n"
    "nop;1\n"
    "nop;1\n"
    "nop;1\n"
    "nop;1\n"
    "nop;1\n"
    "sbi %[port], %[pin];1\n"
#if F_CPU == 16000000
    "ldi r19, 44;1\n"
    "nop\n"
    "nop\n"
#elif F_CPU == 9600000
    "ldi r19, 26;1\n"
#elif F_CPU == 8000000
    "ldi r19, 21;1\n"
    "nop\n"
#elif F_CPU == 4800000
    "ldi r19, 12;1\n"
    "nop\n"
#elif F_CPU == 4000000
    "ldi r19, 10;1\n"
#elif F_CPU == 2000000
    "ldi r19, 4;1\n"
#elif F_CPU == 1200000
    "ldi r19, 1;1\n"
    "nop\n"
    "nop\n"
#endif
    "l_uart_write_delay_3:\n"
    "dec r19;1\n"
    "brne l_uart_write_delay_3;1/2\n"
    "out __SREG__, __tmp_reg__;1\n"
//    "ret;4\n"
    : : [c] "r" (c), [port] "I" (_SFR_IO_ADDR(UART_PORT)), [pin] "I" (UART_TX) : "r18", "r19");
}

void uart_print(const char *str) {
  while (*str) {
    uart_write(*str++);
  }
}

void uart_print_P(PGM_P str) {
  while (pgm_read_byte(str)) {
    uart_write(pgm_read_byte(str++));
  }
}

inline void uart_println() {
  uart_print_P(CRLF);
}

void uart_hex(uint8_t hex) {
  uint8_t d;

  d = hex >> 4;
  uart_write(d > 9 ? 'A' + d - 10 : '0' + d);
  d = hex & 0x0F;
  uart_write(d > 9 ? 'A' + d - 10 : '0' + d);
}

void uart_hex(uint16_t hex) {
  uart_hex((uint8_t)(hex >> 8));
  uart_hex((uint8_t)hex);
}

void uart_print(uint8_t num) {
  for (uint8_t divider = 100; divider > 1; divider /= 10) {
    if (divider <= num) {
      uart_write('0' + (num / divider) % 10);
    }
  }
  uart_write('0' + num % 10);
}

void uart_print(int8_t num) {
  if (num < 0) {
    uart_write('-');
    num = -num;
  }
  uart_print((uint8_t)num);
}

void uart_print(uint16_t num) {
  for (uint16_t divider = 10000; divider > 1; divider /= 10) {
    if (divider <= num) {
      uart_write('0' + (num / divider) % 10);
    }
  }
  uart_write('0' + num % 10);
}

void uart_print(int16_t num) {
  if (num < 0) {
    uart_write('-');
    num = -num;
  }
  uart_print((uint16_t)num);
}

void uart_print(uint32_t num) {
  for (uint32_t divider = 1000000000; divider > 1; divider /= 10) {
    if (divider <= num) {
      uart_write('0' + (num / divider) % 10);
    }
  }
  uart_write('0' + num % 10);
}

void uart_print(int32_t num) {
  if (num < 0) {
    uart_write('-');
    num = -num;
  }
  uart_print((uint32_t)num);
}

class UART {
public:
  static void begin() {
    uart_init();
  }
  static void write(char c) {
    uart_write(c);
  }
  static void print(const char *str) {
    uart_print(str);
  }
  static void print_P(PGM_P str) {
    uart_print_P(str);
  }
  static void println() {
    uart_println();
  }
  static void print(char c) {
    uart_write(c);
  }
  static void print(uint8_t n) {
    uart_print(n);
  }
  static void print(int8_t n) {
    uart_print(n);
  }
  static void print(uint16_t n) {
    uart_print(n);
  }
  static void print(int16_t n) {
    uart_print(n);
  }
  static void print(uint32_t n) {
    uart_print(n);
  }
  static void print(int32_t n) {
    uart_print(n);
  }
  static void hex(uint8_t n) {
    uart_hex(n);
  }
  static void hex(uint16_t n) {
    uart_hex(n);
  }
};
