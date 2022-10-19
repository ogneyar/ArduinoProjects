.section .text

.globl aesExpandKeyAsm
.globl aesEncBlockAsm
.globl aesDecBlockAsm

// peripheral block adresses
.equ SBOX0,        0x60008
.equ SBOX1,        0x6000C
.equ SBOX2,        0x60010
.equ SBOX3,        0x60014
.equ SBOX4,        0x60018
.equ SBOX5,        0x6001c
.equ SBOX6,        0x60020
.equ SBOX7,        0x60024

.equ PBYTE,        0x60028

.equ PBIT0,        0x6002C
.equ PBIT1,        0x60030
.equ PBIT2,        0x60034
.equ PBIT3,        0x60038

// store mupltiy registers to the memory at specified address with address incrementation
.macro aesSw4 datR1 datR2 datR3 datR4 addr
    sw      \datR1,0(\addr)
    sw      \datR2,4(\addr)
    sw      \datR3,8(\addr)
    sw      \datR4,12(\addr)
.endm

// load multiply registers from the memory at specified address with address incrementation
.macro aesLw4 datR1 datR2 datR3 datR4 addr
    lw      \datR1,0(\addr)
    lw      \datR2,4(\addr)
    lw      \datR3,8(\addr)
    lw      \datR4,12(\addr)
.endm

// xor multiply registers
.macro aesXor4 datR1 datR2 datR3 datR4 keyR1 keyR2 keyR3 keyR4
    xor     \datR1,\keyR1,\datR1
    xor     \datR2,\keyR2,\datR2
    xor     \datR3,\keyR3,\datR3
    xor     \datR4,\keyR4,\datR4
.endm

// copy one word from one location to another via temporary register
.macro aesCpy dstR srcR tmpR offs
    lw      \tmpR,\offs(\srcR)
    sw      \tmpR,\offs(\dstR)
.endm

// copy 4 words from one location to another via temporary register
.macro aesCpy4 dstR srcR tmpR
    aesCpy  \dstR,\srcR,\tmpR,0
    aesCpy  \dstR,\srcR,\tmpR,4
    aesCpy  \dstR,\srcR,\tmpR,8
    aesCpy  \dstR,\srcR,\tmpR,12
.endm

// key expansion
// a0 - pointer to key in normal format
// a1 - number of bits within plain key
// a2 - pointer to expanded key
aesExpandKeyAsm:
    // type >>= 5;
    srli    a1,a1,5
    // Nk = type;
    mv      t3,a1
    mv      t2,a1
    // type += 6 + 1
    addi    a1,a1,7
    // type <<= 2
    slli    a1,a1,2

    lui     a7,PBYTE

    aesCpy4 a7,a0,t0
    aesCpy4 a2,a7,t0
    li      t1,4
    bgeu    t1,t3,aesExpandKeyAsmC2start
    aesCpy  a7,a0,t0,16
    aesCpy  a2,a7,t0,16
    aesCpy  a7,a0,t0,20
    aesCpy  a2,a7,t0,20
    li      t1,6
    bgeu    t1,t3,aesExpandKeyAsmC2start
    aesCpy  a7,a0,t0,24
    aesCpy  a2,a7,t0,24
    aesCpy  a7,a0,t0,28
    aesCpy  a2,a7,t0,28

aesExpandKeyAsmC2start:
    // a0 (pointer to original key) is not needed anymore, reuse register
    lui     a0,SBOX0
    // a6 will store expKey[i], a5 will store expKey[i - Nk]
    slli    a6,t2,2
    add     a6,a6,a2
    mv      a5,a2
aesExpandKeyAsmC2:
    // tmp = expKey[i - 1];
    lw      t4,-4(a6)
    // if (i % Nk != 0) {
    remu    t6,t2,t3
    bnez    t6,aesExpandKeyAsmC22
    // tmp = (tmp << 8) | (tmp >> 24);
    slli    t6,t4,8
    srli    t5,t4,24
    or      t4,t6,t5
    // tmp -> MDR_SBLOCK0->TRM_00 (+1 cycle) -> tmp
    sw      t4,0(a0)
    nop
    lw      t4,0(a0)
    // tmp ^= (uint32_t)aesRcon[i / Nk] << 24
    divu    t5,t2,t3
    add     t5,t5,a3
    lbu     t5,0(t5)
    slli    t5,t5,24
    xor     t4,t4,t5
    j       aesExpandKeyAsmC21
aesExpandKeyAsmC22:
    // if (Nk > 6) and
    li      t5,6
    bgeu    t5,t3,aesExpandKeyAsmC21
    // if ((i % Nk) == 4) do
    remu    t5,t2,t3
    addi    t5,t5,-4
    bne     t5,zero,aesExpandKeyAsmC21
    // tmp -> MDR_SBLOCK0->TRM_00 (+1 cycle) -> tmp
    sw      t4,0(a0)
    nop
    lw      t4,0(a0)
aesExpandKeyAsmC21:
    // expKey[i] = expKey[i - Nk] ^ tmp
    lw      a4,0(a5)
    xor     t4,t4,a4
    sw      t4,0(a6)
    // i++;
    addi    t2,t2,1
    // shift key pointer
    addi    a6,a6,4
    addi    a5,a5,4
    // if (i < type) continue
    bgtu    a1,t2,aesExpandKeyAsmC2

    // pack key to matrix format
aesExpandKeyAsmC3:
    lui     a6,PBIT0
    // MDR_PBYTE->TRM_00..3 = expKey[i + 0..3]
    aesCpy4 a7,a2,t0
    // MDR_PBIT0->TRM_00..3 = MDR_PBYTE->TRM_00..3
    aesCpy4 a6,a7,t0
    // expKey[i + 0..3] = MDR_PBIT0->TRM_00..3
    aesCpy4 a2,a6,t0
    // move exp key pointer
    addi    a2,a2,16
    // if ((j-=4) != 0) continue
    addi    t2,t2,-4
    bne     t2,zero,aesExpandKeyAsmC3

    ret

// AES encryption
// a0 - pointer to data to be crypted
// a1 - pointer to expanded key
// a2 - number of bits within key
aesEncBlockAsm:
    // t0..3 = *(uint32_t*)(data + 0..12)
    aesLw4  t0,t1,t2,t3, a0

    // convert to matrix
    lui     a7,PBIT0
    aesSw4  t0,t1,t2,t3, a7
    aesLw4  t0,t1,t2,t3, a7

    // calculate number of rounds from key length
    // type = (type >> 5) + 6
    srli    a2,a2,0x5
    addi    a2,a2,6

    // store conversion block adresses to use it within cycle
    // S-box
    lui     a3,SBOX0
    // P-bit-2 - shift rows
    lui     a4,PBIT2
    // S-box-2 - mix-columns X2
    lui     a5,SBOX2
    // S-box-3 - mix-columns X3
    lui     a6,SBOX3

aesEncBlockAsmCycle:
    // t0..3 ^= expKey[0..3]
    aesLw4  t4,t5,t6,a7 a1
    aesXor4 t0,t1,t2,t3, t4,t5,t6,a7

    // expKey += 4;
    addi    a1,a1,16

    // S-box
    aesSw4  t0,t1,t2,t3, a3
    aesLw4  t0,t1,t2,t3, a3

    // shift rows
    //lui     a4,0x60034
    aesSw4  t0,t1,t2,t3, a4
    aesLw4  t0,t1,t2,t3, a4

    // if ((--rounds) == 0) break
    addi    a2,a2,-1
    beqz    a2,aesEncBlockAsmCycleEnd

    // mix rows
    // X1[0..3] = t0..3
    add     t4,t0,zero
    add     t5,t1,zero
    add     t6,t2,zero
    add     a7,t3,zero

    // MDR_SBLOCK2->TRM_00..3 = t0..3
    aesSw4  t0,t1,t2,t3, a5

    // MDR_SBLOCK3->TRM_00..3 = t0..3
    aesSw4  t0,t1,t2,t3, a6

    // wState[0] = MDR_SBLOCK2->TRM_00 ^ MDR_SBLOCK3->TRM_01 ^ X1[2] ^ X1[3];
    lw      t0,0(a5)
    lw      t3,4(a6)
    xor     t0,t0,t3
    xor     t0,t0,t6
    xor     t0,t0,a7

    // wState[1] = X1[0] ^ MDR_SBLOCK2->TRM_01 ^ MDR_SBLOCK3->TRM_02 ^ X1[3];
    lw      t1,4(a5)
    lw      t2,8(a6)
    xor     t1,t4,t1
    xor     t1,t1,t2
    xor     t1,t1,a7

    // wState[2] = X1[0] ^ X1[1] ^ MDR_SBLOCK2->TRM_02 ^ MDR_SBLOCK3->TRM_03;
    lw      t2,8(a5)
    lw      t3,12(a6)
    xor     t2,t3,t2
    xor     t2,t2,t4
    xor     t2,t2,t5

    // wState[3] = MDR_SBLOCK3->TRM_00 ^ X1[1] ^ X1[2] ^ MDR_SBLOCK2->TRM_03;
    lw      t4,12(a5)
    lw      t3,0(a6)
    xor     t3,t3,t5
    xor     t3,t3,t6
    xor     t3,t3,t4

    j       aesEncBlockAsmCycle
aesEncBlockAsmCycleEnd:

    // t0..3 ^= expKey[0..3]
    aesLw4  t4,t5,t6,a7, a1
    aesXor4 t0,t1,t2,t3, t4,t5,t6,a7

    // convert from matrix
    lui     a7,PBIT1
    aesSw4  t0,t1,t2,t3, a7
    aesLw4  t0,t1,t2,t3, a7

    // *(uint32_t*)(data + 0..12) = t0..3
    aesSw4  t0,t1,t2,t3, a0

    ret

// AES encryption
// a0 - pointer to data to be crypted
// a1 - pointer to expanded key
// a2 - number of bits within key
aesDecBlockAsm:
    // t0..3 = data[0..15]
    aesLw4  t0,t1,t2,t3, a0

    // transform to matrix
    lui     a5,PBIT0
    aesSw4  t0,t1,t2,t3, a5
    aesLw4  t0,t1,t2,t3, a5

    // rounds = (type >> 5) + 6;
    srli    a2,a2,5
    addi    a2,a2,6

    // expKey += type * 4;
    slli    a5,a2,0x4
    add     a1,a5,a1

    // t0..3 ^= expKey[0..3]
    aesLw4  a4,a5,a6,a7, a1
    aesXor4 t0,t1,t2,t3, a4,a5,a6,a7

    // store addresses
    lui     t6,PBIT3
    lui     a3,SBOX1
    lui     a4,SBOX4
    lui     a5,SBOX5
    lui     a6,SBOX6
    lui     a7,SBOX7

aesDecBlockAsmCycle:
    // MDR_PBIT3->TRM_00..3 = t0..3
    // t0..3 = MDR_PBIT3->TRM_00..3
    aesSw4  t0,t1,t2,t3, t6
    aesLw4  t0,t1,t2,t3, t6

    // MDR_SBLOCK1->TRM_00..3 = t0..3
    // t0..3 = MDR_SBLOCK1->TRM_00..3
    aesSw4  t0,t1,t2,t3, a3
    aesLw4  t0,t1,t2,t3, a3

    // expKey -= 4;
    addi    a1,a1,-16

    // t0..3 ^= expKey[0..3]
    lw      t4,0(a1)
    xor     t0,t0,t4
    lw      t4,4(a1)
    xor     t1,t1,t4
    lw      t4,8(a1)
    xor     t2,t2,t4
    lw      t4,12(a1)
    xor     t3,t3,t4

    // if ((round--) == 0) break
    addi    a2,a2,-1
    beqz    a2,aesDecBlockAsmCycleEnd

    // MDR_SBLOCK4..7->TRM_00..3 = t0..3
    aesSw4  t0,t1,t2,t3, a4
    aesSw4  t0,t1,t2,t3, a5
    aesSw4  t0,t1,t2,t3, a6
    aesSw4  t0,t1,t2,t3, a7

    // t0 = MDR_SBLOCK7->TRM_00 ^ MDR_SBLOCK5->TRM_01 ^ MDR_SBLOCK6->TRM_02 ^ MDR_SBLOCK4->TRM_03
    lw      t0,0(a7)
    lw      t4,4(a5)
    xor     t0,t0,t4
    lw      t4,8(a6)
    xor     t0,t0,t4
    lw      t4,12(a4)
    xor     t0,t0,t4

    // t1 = MDR_SBLOCK4->TRM_00 ^ MDR_SBLOCK7->TRM_01 ^ MDR_SBLOCK5->TRM_02 ^ MDR_SBLOCK6->TRM_03
    lw      t1,0(a4)
    lw      t4,4(a7)
    xor     t1,t1,t4
    lw      t4,8(a5)
    xor     t1,t1,t4
    lw      t4,12(a6)
    xor     t1,t1,t4

    // t2 = MDR_SBLOCK6->TRM_00 ^ MDR_SBLOCK4->TRM_01 ^ MDR_SBLOCK7->TRM_02 ^ MDR_SBLOCK5->TRM_03
    lw      t2,0(a6)
    lw      t4,4(a4)
    xor     t2,t2,t4
    lw      t4,8(a7)
    xor     t2,t2,t4
    lw      t4,12(a5)
    xor     t2,t2,t4

    // t3 = MDR_SBLOCK5->TRM_00 ^ MDR_SBLOCK6->TRM_01 ^ MDR_SBLOCK4->TRM_02 ^ MDR_SBLOCK7->TRM_03
    lw      t3,0(a5)
    lw      t4,4(a6)
    xor     t3,t3,t4
    lw      t4,8(a4)
    xor     t3,t3,t4
    lw      t4,12(a7)
    xor     t3,t3,t4

    j       aesDecBlockAsmCycle
aesDecBlockAsmCycleEnd:

    // MDR_PBIT1->TRM_00..3 = t0..3
    lui     t4,PBIT1
    aesSw4  t0,t1,t2,t3, t4
    aesLw4  t0,t1,t2,t3, t4

    // data[0..15] = t0..3
    aesSw4  t0,t1,t2,t3, a0

    ret

