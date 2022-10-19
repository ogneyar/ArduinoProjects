//
// Created by panukov.a on 16.03.2021.
//

#ifndef OTP_OTP_H
#define OTP_OTP_H

#include <MLDR187_eeprom.h>

static void
(*const EEPROM_ProgramWord_from_OTP)(uint32_t Address, flashMemBank BankSelector, uint32_t Data) =
(void (*const)(uint32_t, flashMemBank, uint32_t)) (MDR_OTP_MEM_BASE + 0x3800);

static void
(*const EEPROM_ErasePage_from_OTP)(uint32_t Address, flashMemBank BankSelector) =
(void (*const)(uint32_t, flashMemBank)) (MDR_OTP_MEM_BASE + 0x3a00);

#endif //OTP_OTP_H

