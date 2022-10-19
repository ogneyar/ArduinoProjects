        MODULE  ?mutex

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)
        
        THUMB

        SECTION .text:CODE:NOROOT(2)        
locked    EQU 1
unlocked  EQU 0

; lock_mutex
; Declare for use from C as extern void lock_mutex(void * mutex);
    EXPORT lock_mutex
lock_mutex 
    LDR     r1, =locked
loop1    
    LDREX   r2, [r0]
    CMP     r2, r1        ; Test if mutex is locked or unlocked
    ITEE EQ
    BEQ     loop2         ; If locked - wait for it to be released, from 2
    STREXNE r2, r1, [r0]  ; Not locked, attempt to lock it
    CMPNE   r2, #1        ; Check if Store-Exclusive failed
    BEQ     loop1         ; Failed - retry from 1
    ; Lock acquired
    DMB                   ; Required before accessing protected resource
    BX      lr
loop2
    ; Take appropriate action while waiting for mutex to become unlocked
    WFE                   ; Indicate opportunity to enter low-power state
    B       loop1         ; Retry from 1
    


; unlock_mutex
; Declare for use from C as extern void unlock_mutex(void * mutex);
    EXPORT unlock_mutex
unlock_mutex 
    LDR     r1, =unlocked
    DMB                   ; Required before releasing protected resource
    STR     r1, [r0]      ; Unlock mutex
    DSB                   ; Ensure update has completed before signalling
    SEV                   ; Signal update
    BX      lr
    

              END