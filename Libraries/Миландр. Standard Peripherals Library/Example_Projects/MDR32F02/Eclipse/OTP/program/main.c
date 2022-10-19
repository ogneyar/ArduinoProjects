#include <MLDR187_otp.h>
#include <MLDR187_gpio.h>
#include <MLDR187_eeprom.h>

#include <stdlib.h>

#include "init.h"
#include "otp.h"
#include "otp_functions.h"

#define ARRAYLEN(a) (sizeof(a) / sizeof(a[0]))

int main()
{
    init_clock();


    struct {void * src; void * dst; size_t size;}
    write_areas[ARRAYLEN(OTP_functions)];

    uint8_t* src = (uint8_t*)&__otpfunc_load_start;
    for (int i = 0; i < (int)ARRAYLEN(OTP_functions); i++) {
        uint32_t size = OTP_functions[i].dst_end - OTP_functions[i].dst;
        write_areas[i].src = src;
        write_areas[i].dst = OTP_functions[i].dst;
        write_areas[i].size = size;

        otpStatus result = OTP_check_can_write(OTP_functions[i].dst, src, size);
        if (result != otpSuccess) {
            exit(result);
        }

        src += size;
    }

    for (int i = 0; i < (int)ARRAYLEN(write_areas); i++) {
        otpStatus result = OTP_write_memory(write_areas[i].dst, write_areas[i].src, write_areas[i].size);
        if (result != otpSuccess) {
            exit(result);
        }
    }

    return 0;
}

