#include <MLDR187_eeprom.h>

#include <stdlib.h>

#include "init.h"
#include "otp.h"


int main()
{
    init_clock();

    EEPROM_ErasePage_from_OTP(0x3000, flashMainBank);

    EEPROM_ProgramWord_from_OTP(0x3004, flashMainBank, 0xcafebabe);

    if (*(uint32_t*)(0x10003004) != 0xcafebabe) {
        exit(EXIT_FAILURE);
    }

    return 0;
}

