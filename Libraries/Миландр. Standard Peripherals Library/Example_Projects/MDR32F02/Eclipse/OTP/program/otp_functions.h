//
// Created by panukov.a on 16.03.2021.
//

#ifndef PROGRAM_OTP_FUNCTIONS_H
#define PROGRAM_OTP_FUNCTIONS_H

#include <stdlib.h>
#include <MLDR187_eeprom.h>

__attribute__((section (".EEPROM_ProgramWord_from_OTP")))
void EEPROM_ProgramWord_from_OTP(uint32_t Address, flashMemBank BankSelector, uint32_t Data);
extern char __EEPROM_ProgramWord_from_OTP_end;

__attribute__((section (".EEPROM_ErasePage_from_OTP")))
void EEPROM_ErasePage_from_OTP(uint32_t Address, flashMemBank BankSelector);
extern char __EEPROM_ErasePage_from_OTP_end;

extern char __otpfunc_load_start;

static const struct { void * dst; void * dst_end;}
OTP_functions[] =
{
    {
        .dst = EEPROM_ProgramWord_from_OTP,
        .dst_end = &__EEPROM_ProgramWord_from_OTP_end
    },
    {
        .dst = EEPROM_ErasePage_from_OTP,
        .dst_end = &__EEPROM_ErasePage_from_OTP_end
    }
};

#endif //PROGRAM_OTP_FUNCTIONS_H

