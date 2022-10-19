#include "otp.h"

otpStatus OTP_write_memory(void * dst, void* src, size_t size) {
    // Bytewise copy in loop
    for (size_t offset = 0; offset < size; offset++)
    {
        // Read byte from load region
        uint8_t byte = *(uint8_t*)(src + offset);

        // Calculate bit-address of its new location in OTP
        uint32_t addr = (uint32_t) (dst - MDR_OTP_MEM_BASE + offset);
        addr <<= 3;

        // Write byte to OTP with SPL
        otpStatus result = OTP_WriteByte(addr, byte);
        if (result != otpSuccess) {
            return result;
        }
    }

    return otpSuccess;
}

otpStatus OTP_check_can_write(void *dst, void *src, size_t size) {
    // Check that write will be valid
    for (size_t offset = 0; offset < size; offset++)
    {
        // Read byte from load region
        uint8_t byte = *(uint8_t*)(src + offset);

        // Calculate bit-address of its new location in OTP
        uint32_t addr = (uint32_t) (dst - MDR_OTP_MEM_BASE + offset);
        addr <<= 3;

        // Read corresponding byte from OTP with SPL
        uint8_t otp_byte = OTP_Read(addr);

        // We can only write 1s. If there is a case when OTP bit is 1 and we need to write 0,
        // further write will fail
        if ((otp_byte | byte) != byte) {
            return otpInvalid;
        }
    }

    return otpSuccess;
}

