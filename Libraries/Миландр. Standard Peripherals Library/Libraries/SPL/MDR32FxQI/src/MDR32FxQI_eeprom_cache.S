;/**
;  ******************************************************************************
;  * @file    MDR32FxQI_eeprom_cache.S
;  * @author  Milandr Application Team
;  * @version V2.0.0i
;  * @date    17/03/2022
;  * @brief   This file contains the EEPROM_UpdateDCacheAsm function.
;  ******************************************************************************
;  * <br><br>
;  *
;  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
;  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
;  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
;  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
;  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
;  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;  *
;  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
;  ******************************************************************************
;  */

#if defined ( __CC_ARM ) || (( __ARMCC_VERSION ) && ( __ARMCC_VERSION >= 6010050 )) /* Arm Compiler 4/5 || Arm Compiler 6 */
        #define CODESECT        AREA    |EXECUTABLE_MEMORY_SECTION|, CODE, READONLY, ALIGN=2
        #define CODESECT_TYPE

#elif defined ( __IASMARM__ )  /* IAR */
        #define SHT_PROGBITS    0x1
        #define SHF_WRITE       0x1
        #define SHF_EXECINSTR   0x4
        
        #define CODESECT        SECTION .textrw:CODE:NOROOT(2)
        #define CODESECT_TYPE   SECTION_TYPE SHT_PROGBITS, SHF_WRITE | SHF_EXECINSTR
        #define PROC
        #define ENDP
        #define EXPORT          PUBLIC
#endif
        
        CODESECT
        CODESECT_TYPE
        THUMB

;/**
;  * @brief   Updates data cache.
;  * @warning This function can be used only for MCU MDR32F1QI (errata 0007).
;  *          To call the function use the name EEPROM_UpdateDCache().
;  *          Registers r0-r1 are not stored on the stack, as they are non preserved registers.
;  * @param   None
;  * @retval  None
;  */
EEPROM_UpdateDCacheAsm     PROC
        EXPORT  EEPROM_UpdateDCacheAsm

        MOVS    r0,#0x50        ; r0 = 0x00000050
        NOP                     ; Align next LDR instruction
ReadFlash
        LDR     r1,[r0,#0x00]   ; Read EEPROM
        SUBS    r0,r0,#0x10     ; r0 -= 0x10
        
        CMP     r0,#0x00
        BNE     ReadFlash
        
        BX      LR
        
        ENDP
        
        END
