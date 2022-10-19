//
// Created by panukov.a on 16.03.2021.
//

#ifndef PROGRAM_OTP_H
#define PROGRAM_OTP_H

#include <MLDR187_otp.h>
#include <stdlib.h>

otpStatus OTP_write_memory(void * dst, void* src, size_t size);

otpStatus OTP_check_can_write(void * dst, void* src, size_t size);

#endif //PROGRAM_OTP_H

