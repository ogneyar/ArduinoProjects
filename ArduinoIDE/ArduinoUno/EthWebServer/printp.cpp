#include "printp.h"

const char substChar = '%';

void print_P(Stream& stream, PGM_P str, uint16_t maxlen) {
  if (! str)
    return;

  char c;

  while ((maxlen--) && (c = pgm_read_byte(str++))) {
    stream.write(c);
  }
}

void println_P(Stream& stream, PGM_P str, uint16_t maxlen) {
  print_P(stream, str, maxlen);
  stream.println();
}

void printsubst(Stream& stream, PGM_P str, const char* params[], uint16_t maxlen) {
  if (! str)
    return;

  char c;

  while ((maxlen--) && (c = pgm_read_byte(str++))) {
    if (c == substChar) {
      if ((! maxlen--) || (! (c = pgm_read_byte(str++))))
        break;
      if ((c >= '0') && (c <= '9')) {
        if (params)
          stream.print(params[c - '0']);
      } else
        stream.write(c);
    } else
      stream.write(c);
  }
}

void printsubst_P(Stream& stream, PGM_P str, PGM_P params[], uint16_t maxlen) {
  if (! str)
    return;

  char c;

  while ((maxlen--) && (c = pgm_read_byte(str++))) {
    if (c == substChar) {
      if ((! maxlen--) || (! (c = pgm_read_byte(str++))))
        break;
      if ((c >= '0') && (c <= '9')) {
        if (params)
          print_P(stream, params[c - '0']);
      } else
        stream.write(c);
    } else
      stream.write(c);
  }
}

void printlnsubst(Stream& stream, PGM_P str, const char* params[], uint16_t maxlen) {
  printsubst(stream, str, params, maxlen);
  stream.println();
}

void printlnsubst_P(Stream& stream, PGM_P str, PGM_P params[], uint16_t maxlen) {
  printsubst_P(stream, str, params, maxlen);
  stream.println();
}
