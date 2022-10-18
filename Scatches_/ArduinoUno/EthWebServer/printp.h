#ifndef __PRINTP_H
#define __PRINTP_H

#include <avr/pgmspace.h>
#include <Stream.h>

void print_P(Stream& stream, PGM_P str, uint16_t maxlen = (uint16_t)-1);
void println_P(Stream& stream, PGM_P str, uint16_t maxlen = (uint16_t)-1);

void printsubst(Stream& stream, PGM_P str, const char* params[], uint16_t maxlen = (uint16_t)-1);
void printsubst_P(Stream& stream, PGM_P str, PGM_P params[], uint16_t maxlen = (uint16_t)-1);
void printlnsubst(Stream& stream, PGM_P str, const char* params[], uint16_t maxlen = (uint16_t)-1);
void printlnsubst_P(Stream& stream, PGM_P str, PGM_P params[], uint16_t maxlen = (uint16_t)-1);

#endif
