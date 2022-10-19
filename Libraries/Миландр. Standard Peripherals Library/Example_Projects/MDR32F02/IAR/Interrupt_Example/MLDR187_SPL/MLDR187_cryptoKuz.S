.section .text

.globl kuzBlockEncAsm
.globl kuzBlockDecAsm
.globl kuzExpandKeyAsm

// extreme optimization (linearized algorithm) to show how fast implementation could be (>10 Mbit/s)
// too huge for common usage
// .globl asmKuzBlockEncExtremeOptimization

// peripheral block adresses
.equ SBOX0,        0x60008
.equ SBOX1,        0x6000C
.equ LBLOCK_SETUP, 0x60004
.equ LBLOCK_DATA,  0x60004
.equ PBYTE,        0x60028

// XOR 4 words with another 4 words, save result within first 4 words
.macro kuzXor4 datR1 datR2 datR3 datR4 keyR1 keyR2 keyR3 keyR4
    xor     \datR1,\datR1,\keyR1
    xor     \datR2,\datR2,\keyR2
    xor     \datR3,\datR3,\keyR3
    xor     \datR4,\datR4,\keyR4
.endm

// store mupltiy registers to the memory at specified address with address incrementation
.macro kuzSw4 datR1 datR2 datR3 datR4 addr
    sw      \datR1,0(\addr)
    sw      \datR2,4(\addr)
    sw      \datR3,8(\addr)
    sw      \datR4,12(\addr)
.endm

// load multiply registers from the memory at specified address with address incrementation
.macro kuzLw4 datR1 datR2 datR3 datR4 addr
    lw      \datR1,0(\addr)
    lw      \datR2,4(\addr)
    lw      \datR3,8(\addr)
    lw      \datR4,12(\addr)
.endm

// just 4 nop's
.macro kuzNop4
    nop
    nop
    nop
    nop
.endm

// copy from one memory location to another with same offsets and swapping byte-order
.macro kuzSwp tempR convAddr srcAddr dstAddr offs
    lw      \tempR,\offs(\srcAddr)
    sw      \tempR,0(\convAddr)
    lw      \tempR,0(\convAddr)
    sw      \tempR,\offs(\dstAddr)
.endm

// move from one memory location (with offset) to another (with offset) using specified temp register
.macro kuzMv4 tempR srcAddr srcOffs dstAddr dstOffs
    lw      \tempR,\srcOffs(\srcAddr)
    sw      \tempR,\dstOffs(\dstAddr)
.endm

// key expansion
// sp-4  - return addr
// sp-8  - expanded key pointer
// sp-12 - normal key form
kuzExpandKeyAsm:
    // load first 32-bytes of the key and transform them to little endian
    lui     a7,PBYTE // PBYTE addr for endians swapping
    kuzSwp  t4,a7, a0,a1, 0
    kuzSwp  t4,a7, a0,a1, 4
    kuzSwp  t4,a7, a0,a1, 8
    kuzSwp  t4,a7, a0,a1, 12
    kuzSwp  t4,a7, a0,a1, 16
    kuzSwp  t4,a7, a0,a1, 20
    kuzSwp  t4,a7, a0,a1, 24
    kuzSwp  t4,a7, a0,a1, 28
    // normal key (a0) and endians-swapping mechanism (a7) not needed any more

    // MDR_LBLOCK->SETUP = 0x10
    lui     a5,LBLOCK_SETUP
    li      a7,16
    sw      a7,32(a5)
    // store LBLOCK address to a7 and do not touch it anymore
    lui     a7,LBLOCK_DATA
    // store SBOX address to a2 and do not touch it anymore
    lui     a2,SBOX0

    // store to a0 - expKey[j + 8], note that a1 is poited to expKey itself
    addi    a0,a1,32

    // j = 0
    li      t6,0
kuzExpandKeyjCycle:
    kuzMv4  t4, a0,-32, a0,0
    kuzMv4  t4, a0,-28, a0,4
    kuzMv4  t4, a0,-24, a0,8
    kuzMv4  t4, a0,-20, a0,12
    kuzMv4  t4, a0,-16, a0,16
    kuzMv4  t4, a0,-12, a0,20
    kuzMv4  t4, a0,-8,  a0,24
    kuzMv4  t4, a0,-4,  a0,28

// i = 1
    li      t5,1
kuzExpandKeyiCycle:
    // t0..3 = 0,0,0,(j+i)
    li      t0,0
    li      t1,0
    li      t2,0
    add     t3,t6,t5

    // L-operation - load data to the transformation block, wait 16 cycles and get data back
    kuzSw4  t3,t2,t1,t0, a7
    // use L-block delay to load next portion of XOR material from memory
    lw      a3,0(a0)
    lw      a4,4(a0)
    lw      a5,8(a0)
    lw      a6,12(a0)
    kuzNop4
    kuzNop4
    nop
    nop
    kuzLw4  t3,t2,t1,t0, a7

    // t0..3 ^= expKey[j + 8 + 0..3]
    xor     t0,t0,a3
    xor     t1,t1,a4
    xor     t2,t2,a5
    xor     t3,t3,a6

    // S-box operation - store data to S-box data register and load transformed data back
    kuzSw4  t3,t2,t1,t0, a2
    kuzLw4  t3,t2,t1,t0, a2

    // L-operation - load data to the transformation block, wait 16 cycles and get data back
    kuzSw4  t3,t2,t1,t0, a7
    lw      a3,16(a0)
    lw      a4,20(a0)
    lw      a5,24(a0)
    lw      a6,28(a0)
    kuzNop4
    kuzNop4
    nop
    nop
    kuzLw4  t3,t2,t1,t0, a7

    // t0..3 ^= expKey[j + 12 + 0..3]
    xor     t0,t0,a3
    xor     t1,t1,a4
    xor     t2,t2,a5
    xor     t3,t3,a6

    // expKey[j + 12 + 0..3] = expKey[j + 8 + 0..3]
    kuzMv4    t4, a0,0,  a0,16
    kuzMv4    t4, a0,4,  a0,20
    kuzMv4    t4, a0,8,  a0,24
    kuzMv4    t4, a0,12, a0,28

    // expKey[j + 8 + 0..3] = t0..3
    sw      t0,0(a0)
    sw      t1,4(a0)
    sw      t2,8(a0)
    sw      t3,12(a0)

    // i++
    addi    t5,t5,1
    // if (i < 9) continue
    li      a3,9
    bltu    t5,a3,kuzExpandKeyiCycle

    // shift key pointer to next portion
    addi    a0,a0,32

    // j += 8
    addi    t6,t6,8
    // if (j < 32) continue
    li      a3,32
    bltu    t6,a3,kuzExpandKeyjCycle

    ret

// common functionality fro Kuznechik enryption/decryption
//
// KUZNECHIK decryption
// a0 - pointer to expanded key
// a1 - pointer to input / output data
// a6 - expanded key shift
kuzBlockCommonAsm:
    // store L-block address
    lui     a3,LBLOCK_DATA

    // store P-byte address
    lui     a7,PBYTE

    // iterator
    li      a5,9
    // t0..3 = inpout[0..3]
    kuzLw4  t0,t1,t2,t3, a1
    // swap byte order of the input data
    kuzSw4  t0,t1,t2,t3, a7
    kuzLw4  t0,t1,t2,t3, a7

    // load next portion of the key
    kuzLw4  t4,t5,t6,a4, a0

    // 9 times of XSL/XLS sequences
kuzBlockCommonCycle:
    // XOR with key
    kuzXor4   t0,t1,t2,t3, t4,t5,t6,a4

    // S-box for encryption
    bge     zero,a6,kuzBlockX1skip
    kuzSw4  t0,t1,t2,t3, a2
    kuzLw4  t0,t1,t2,t3, a2
kuzBlockX1skip:

    // L-block transformation
    // store data for L-transformation
    kuzSw4  t3,t2,t1,t0, a3
    // use Lblock delay to decrement iteration, shift key exponent to next element
    // and load new portion of the key material
    // shift pointer to next key portion and load new portion of the key material
    add     a0,a0,a6
    kuzLw4  t4,t5,t6,a4, a0
    // decrement iterator
    addi    a5,a5,-1
    // wait more
    kuzNop4
    kuzNop4
    // read result of the L-transformation
    kuzLw4  t3,t2,t1,t0, a3

    // S-box for decryption
    bge     a6,zero,kuzBlockX2skip
    kuzSw4  t0,t1,t2,t3, a2
    kuzLw4  t0,t1,t2,t3, a2
kuzBlockX2skip:

    //addi    a5,a5,-1
    bne     a5,zero,kuzBlockCommonCycle
    // end of XSL/XLS sequences

    // xor with key t0..3 = expKey[0..3]
    kuzXor4   t0,t1,t2,t3, t4,t5,t6,a4

    // swap byte order of the output data
    kuzSw4  t0,t1,t2,t3, a7
    kuzLw4  t0,t1,t2,t3, a7
    // inpout[0..3] = t0..3
    kuzSw4  t0,t1,t2,t3, a1

    ret

// KUZNECHIK encryption
// a0 - pointer to expanded key
// a1 - pointer to input / output data
kuzBlockEncAsm:
    // MDR_LBLOCK->SETUP = 16 + LBLOCK_SETUP_DIRECT
    // do that first to release registers for the further use
    lui     a3,LBLOCK_SETUP
    li      t0,16
    sw      t0,32(a3)

    // a0 - expanded key pointer
    sw      a0,-12(sp)
    // expanded key shift
    li      a6,16
    // a1 - input / output data pointer
    sw      a1,-8(sp)

    // store S-box address
    lui     a2,SBOX0

    // proceed common path
    j       kuzBlockCommonAsm

// KUZNECHIK decryption
// a0 - pointer to expanded key
// a1 - pointer to input / output data
kuzBlockDecAsm:
    // MDR_LBLOCK->SETUP = 16 + LBLOCK_SETUP_DIRECT
    // do that first to release registers for the further use
    lui     a3,LBLOCK_SETUP
    li      t0,65552
    sw      t0,32(a3)

    // a0 - expanded key pointer
    sw      a0,-12(sp)
    // shift key to last portion
    addi    a0,a0,144
    // expanded key shift
    li      a6,-16
    // a1 - input / output data pointer
    sw      a1,-8(sp)

    // store S-box address
    lui     a2,SBOX1

    // proceed common path
    j       kuzBlockCommonAsm


//////////////////////////////////////////////////////////////////////////////////////////
// Extreme optimized Kuznechik implementation, performance up to 10,189 Mbit/sec while: //
// - been executed from RAM                                                             //
// - core speed 64 MHz (suitable for core, but not all peripherals)                     //
// - operands already in CPU little-endian format                                       //
//                                                                                      //
// for reference only, recommended to use code-optimized implementation instead         //
//////////////////////////////////////////////////////////////////////////////////////////

/*
// XSL operations combination for linearized algorithm
.macro kuzXSL datR1 datR2 datR3 datR4 keyR1 keyR2 keyR3 keyR4 sBox lBlock keyPtr
    // xor with key t0..3 = expKey[0..3]
    kuzXor4 \datR1,\datR2,\datR3,\datR4,\keyR1,\keyR2,\keyR3,\keyR4

    // S-box
    kuzSw4  \datR1,\datR2,\datR3,\datR4,\sBox
    kuzLw4  \datR1,\datR2,\datR3,\datR4,\sBox

    // load data for L-transformation
    kuzSw4  \datR4,\datR3,\datR2,\datR1,\lBlock

    // use Lblock delay to shift exponent pointer to next element and load new portion of the key material
    // expKey += 16
    addi    \keyPtr,\keyPtr,16
    // load new portion of key material
    kuzLw4  \keyR1,\keyR2,\keyR3,\keyR4,\keyPtr
    // wait more
    nop
    nop
    nop
    nop
    nop
    nop
    // read temporary enc data from L-transformation
    kuzLw4  \datR4,\datR3,\datR2,\datR1,\lBlock
.endm

// KUZNECHIK encryption
// a0 - expanded key pointer
// a1 - pointer to input / output data (must be in CPU format already)
asmKuzBlockEncExtremeOptimization:
    // unused registers: a5..a7 (could be not restored), s0..s11 (should be restored)
    sw      a0,-12(sp)
    sw      a1,-8(sp)

    // MDR_LBLOCK->SETUP = 16 + LBLOCK_SETUP_DIRECT;
    // do that first to release registers for the further use
    lui     a3,LBLOCK_SETUP
    li      t0,16
    sw      t0,32(a3)

    // store S-box address
    lui     a2,SBOX0
    // store L-block address
    lui     a3,LBLOCK_DATA

    // t0..3 = inpout[0..3]
    kuzLw4  t0,t1,t2,t3, a1

    // load next portion of the key
    kuzLw4  t4,t5,t6,a4, a0

    // 9 times of XSL sequences
    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0
    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0
    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0

    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0
    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0
    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0

    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0
    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0
    kuzXSL  t0,t1,t2,t3, t4,t5,t6,a4, a2,a3,a0

    // xor with key t0..3 = expKey[0..3]
    kuzXor4 t0,t1,t2,t3, t4,t5,t6,a4

    // inpout[0..3] = t0..3
    kuzSw4  t0,t1,t2,t3, a1

    ret
*/
