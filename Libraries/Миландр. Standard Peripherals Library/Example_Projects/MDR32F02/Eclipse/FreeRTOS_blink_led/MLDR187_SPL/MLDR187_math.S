.section .text

.globl MATH_FFT_ASM
.globl MATH_sqrtX2pY2FastASM

// swap 2 content of memory located at 2 different positions usign 2 temp registers (store and move)
.macro swap addr1 addr2 tmp1 tmp2
	lw		\tmp1,0(\addr1)
	lw		\tmp2,0(\addr2)
	sw		\tmp2,0(\addr1)
	sw		\tmp1,0(\addr2)
.endm

// trigonometry FFT macro - multiplication with cos() and sin() factors
.macro fftTrig xt yt cos sin tmp1 tmp2 rst
	// tmp1 = (int32_t)(((int64_t)xt * cosVal) >> 32)
	mulh	\tmp1,\xt,\cos
	// tmp2 = (int32_t)(((int64_t)yt * sinVal) >> 32)
	mulh	\tmp2,\yt,\sin
	// scdPtr[0] = tmp1 + tmp2
    add     \tmp1,\tmp1,\tmp2
    sw      \tmp1,0(\rst)

	// tmp1 = (int32_t)(((int64_t)yt * cosVal) >> 32)
	mulh	\tmp1,\yt,\cos
	// tmp2 = (int32_t)(((int64_t)xt * sinVal) >> 32)
	mulh	\tmp2,\xt,\sin
	// scdPtr[1] = tmp1 - tmp2
    sub     \tmp1,\tmp1,\tmp2
    sw      \tmp1,4(\rst)
.endm

// FFT calculation
// a0 - pointer to input / output data
// a1 - fft length
// a2 - pointer to cos / sin precalculated table
// a3 - pointer to reorder index table
// used registers:
// a4 - iterator i
// a5 - iterator j
// a6 - iterator k
// a7 - yt
// t0 - tmp1
// t1 - tmp2
// t2 - fstPtr
// t3 - scdPtr
// t4 - cos
// t5 - sin
// t6 - xt
// s0 - frame pointer
// s1 - lookup table pointer
// s2 - lookup table offset
MATH_FFT_ASM:
	// due to RSIC V call convention, we must save and restore content of "saved" registers if we use them
	// stack pointer should be always be 16-bytes aligned
    addi    sp,sp,-16
    sw      s0,12(sp)
    sw      s1,8(sp)
    sw      s2,4(sp)

	// lookupOffset = (2048 << 1) / fftLen;
	// lui - load upper intermediate, fill lowest 12 bits with zero, so reg = 4096 is lui reg,1
    lui     s2,1
    divu    s2,s2,a1
    // every item has 4 bytes within
    slli	s2,s2,2

	// lookupTable = (int32_t*)cosSinTbl;
	mv		s1,a2
	// fstPtr = pSrc;
	mv		t2,a0
	// scdPtr = &pSrc[fftLen]
    slli    t3,a1,0x2
    add		t3,a0,t3

    ///////////////////////////////////////////////////////
	// first phase

	// i = 0
	mv		a4,zero

fftFirstPhaseCycle:
	// tmp1 = fstPtr[0] >> 2
    lw      t4,0(t2)
    srai    t4,t4,2
	// tmp2 = scdPtr[0] >> 2
    lw      t5,0(t3)
    srai    t5,t5,2
	// xt = tmp1 - tmp2
    sub		t6,t4,t5
	// fstPtr[0] = (tmp1 + tmp2) >> 1
    add     t4,t4,t5
    srai    t4,t4,1
    sw      t4,0(t2)

	// tmp1 = fstPtr[1] >> 2
    lw      t4,4(t2)
    srai    t4,t4,0x2
	// tmp2 = scdPtr[1] >> 2
    lw      t5,4(t3)
    srai    t5,t5,0x2
	// yt = tmp1 - tmp2
    sub     a7,t4,t5
	// fstPtr[1] = (tmp1 + tmp2) >> 1;
    add     t4,t4,t5
    srai    t4,t4,0x1
    sw      t4,4(t2)

	// load cos, sin from lookup table and shift lookup table to next item
	lw		t4,0(s1)
	lw		t5,4(s1)
    add		s1,s1,s2

   	// trigonometry fft calculation
    fftTrig t6,a7,t4,t5,t0,t1,t3

    // shift src/dst data pointers to next items (re + im)
    addi	t2,t2,8
    addi    t3,t3,8

	// i += 2
	// if (i < fftLen) continue
    addi	a4,a4,2
    bltu    a4,a1,fftFirstPhaseCycle

    ///////////////////////////////////////////////////////
    // middle phase

	// k = fftLen / 2
	srli	a6,a1,1

fftKCycle:
	// lookupTable = (int32_t*)cosSinTbl;
    mv		s1,a2
	// lookupOffset <<= 1
    slli	s2,s2,1

	// j = 0
	mv		a5,zero

fftJCycle:
	// load cos, sin from lookup table and shift lookup table to next item
	lw		t4,0(s1)
	lw		t5,4(s1)
    add		s1,s1,s2

	// fstPtr = pSrc[2 * j] - every item has 4 bytes, 8 bytes offset
    slli    t2,a5,3
    add		t2,a0,t2

	// i = j
    mv		a4,a5

fftICycle:
	// scdPtr = fstPtr + k
    slli    t3,a6,0x2
    add     t3,t2,t3
	// tmp1 = fstPtr[0]
	// tmp2 = scdPtr[0]
    lw      t0,0(t2)
    lw      t1,0(t3)
	// xt = tmp1 - tmp2
    sub     t6,t0,t1
	// fstPtr[0] = (tmp1 + tmp2) >> 1
    add     t0,t0,t1
    srai    t0,t0,0x1
    sw      t0,0(t2)

	// tmp1 = *fstPtr;
    lw      t0,4(t2)
	// tmp2 = *scdPtr;
    lw      t1,4(t3)
	// yt = tmp1 - tmp2;
    sub     a7,t0,t1
	// fstPtr[1] = (tmp1 + tmp2) >> 1
    add     t0,t0,t1
    srai    t0,t0,0x1
    sw      t0,4(t2)

	// trigonometry fft calculation
    fftTrig t6,a7,t4,t5,t0,t1,t3

	// fstPtr += (k * 2)
    slli    t0,a6,3
    add     t2,t2,t0

	// i += k
    // if (i < fftLen) continue
    add     a4,a6,a4
    bltu    a4,a1,fftICycle

	// j++
    // if (j < (k / 2)) continue
    addi	a5,a5,1
    srli    t0,a6,1
    bltu    a5,t0,fftJCycle

	// k >>= 1
	// if (k > 2) continue
    srli	a6,a6,1
    li      t0,2
    bltu    t0,a6,fftKCycle

    ///////////////////////////////////////////////////////
    // last phase

	// fstPtr = pSrc
    mv		t2,a0

    // i = 0
	mv		a4,zero
label10:
	// scdPtr = fstPtr + 2;
    addi    t3,t2,8

	// tmp1 = fstPtr[0]
	// tmp2 = fstPtr[2]
    lw      t0,0(t2)
    lw      t1,8(t2)

	// xt = tmp1 - tmp2;
    sub     t6,t0,t1

	// fstPtr[0] = tmp1 + tmp2
    add     t0,t0,t1
    sw      t0,0(t2)

	// tmp1 = fstPtr[1]
	// tmp2 = fstPtr[3]
    lw      t0,4(t2)
    lw      t1,12(t2)
	// yt = tmp1 - tmp2;
    sub     a7,t0,t1
	// fstPtr[1] = tmp1 + tmp2;
    add     t0,t0,t1
    sw      t0,4(t2)
	// fstPtr[3] = yt
    sw		a7,12(t2)

	// scdPtr[0] = xt
    sw		t6,0(t3)

	// tmp1 = fstPtr[4]
    lw      t0,16(t2)
	// tmp2 = fstPtr[6]
    lw      t1,24(t2)

	// xt = tmp1 - tmp2;
    sub     t6,t0,t1

	// *fstPtr = tmp1 + tmp2;
    add     t0,t0,t1
    sw      t0,16(t2)

	// tmp1 = fstPtr[5]
	// tmp2 = scdPtr[7]
    lw      t0,20(t2)
    lw      t1,28(t2)

	// yt = tmp1 - tmp2
    sub     a7,t0,t1

	// *fstPtr = tmp1 + tmp2
    add     t0,t0,t1
    sw      t0,20(t2)

	// *scdPtr = yt
    sw		a7,28(t2)
	// *scdPtr = xt
    sw		t6,24(t2)

	// next pointer
    addi    t2,t2,32

	// i += 4
	// if (i < fftLen) continue
	addi	a4,a4,4
    bltu    a4,a1,label10

    ///////////////////////////////////////////////////////
    // reordering

	// lookupOffset = 2048U / fftLen;
	lui		s2,1
	srli	s2,s2,1
	divu	s2,s2,a1

	// reorderTbl = (uint16_t *)&reorderTbl[lookupOffset - 1];
	addi	a2,s2,-1
	slli	a2,a2,1
	add		a3,a2,a3

	// fstPtr, scdPtr = pSrc
    mv		t2,a0
    mv		t3,a0

	// i = 0, j = 0
    mv		a4,zero
    mv		a5,zero

label14:
	// if (i < j)
    bgeu    a4,a5,label12

	// swap fstPtr, scdPtr
	swap	t2,t3, t0,a2

    // fstPtr++, scdPtr++, swap
    addi    t2,t2,4
    addi    t3,t3,4
    swap	t2,t3, t0,a2

	// fstPtr, scdPtr += (fftLen + 1), swap
	addi	a2,a1,1
	slli	a2,a2,2
	add		t2,t2,a2
	add		t3,t3,a2
   	swap	t2,t3, t0,a2

	// fstPtr++, scdPtr++, swap
    addi    t2,t2,4
    addi    t3,t3,4
    swap	t2,t3, t0,a2

	// fstPtr = fstPtr - fftLen - 1
    addi    a2,a1,1
    sub     a2,zero,a2
    slli    a2,a2,0x2
    add     t2,t2,a2

	// scdPtr -= 3;
    addi    t3,t3,-12
    j       label13

label12:
	// fstPtr += 2;
    addi    t2,t2,8
	// scdPtr += fftLen;
    slli    a2,a1,0x2
    add     t3,t3,a2

label13:
	// swap fstPtr, scdPtr
	swap	t2,t3, t0,a2

	// fstPtr++, scdPtr++, swap
    addi    t2,t2,4
    addi    t3,t3,4
    swap	t2,t3, t0,a2

	// j = *reorderTbl
    lhu     a2,0(a3)
    mv		a5,a2

	// reorderTbl += lookupOffset
    slli    a2,s2,1
    add     a3,a2,a3
	// fstPtr++
    addi    t2,t2,4
	// scdPtr = &pSrc[2 * j]
    slli    a2,a5,0x3
    add		t3,a0,a2

	// i += 2
	// if (i < (fftLen / 2)) continue
    addi	a4,a4,2
    srli    a2,a1,0x1
    bltu    a4,a2,label14

    // restore saved registers
    lw      s0,12(sp)
    lw      s1,8(sp)
    lw      s2,4(sp)
    addi    sp,sp,16
    ret



// SQRT(x^2 + y^2) calculation
// a0 - x
// a1 - y
// return (a0) - SQRT
MATH_sqrtX2pY2FastASM:
    // if (x < 0) x = -x
    bgez    a0,1f
    neg     a0,a0
1:

    // if (y < 0) y = -y
    bgez    a1,1f
    neg     a1,a1
1:

	// if (y == 0) return x
	// x (a0) already in-place of returning value, do nothing but return
	bnez	a1,1f
	ret
1:
	// if (x == 0) return y
	bnez	a0,1f
	mv		a0,a1
	ret
1:

    // if (x < 0) x = -x
    bgez	a0,1f
    neg		a0,a0
1:

    // if (y < 0) y = -y
    bgez	a1,1f
    neg		a1,a1
1:

    // q = (uint64_t) x * x + (uint64_t) y * y;
    mulh	t0,a0,a0
    mul		t1,a0,a0
    mulh	t2,a1,a1
    mul		t3,a1,a1
    add		t0,t0,t2
    add		t2,t1,t3
    bgeu	t2,t1,1f
    addi	t0,t0,1
1:
	// first approximaxtion s = (x + y) / 2
	add		t1,a0,a1
	srli	t1,t1,1

	// if higher part of the result is zero, we could use reduced, 32-bit implementation
	beqz	t0,redNewton
	// otherwise 64-bit calculation should be proceeded

	// we could proceed lossy optimization: if one operand is more than 50 times greater then another
	// (typical case for FFT results), we could just return it as a result with error less than 0,02%

	// if (y > x) swap x and y
	bge		a0,a1,1f
	mv		a2,a0
	mv		a0,a1
	mv		a1,a2
1:
	// if (x / y > 50) return x
	div		a2,a0,a1
	li		a3,50
	bge		a3,a2,1f
	ret
1:

	// store registers to stack
    addi    sp,sp,-80
    sw      ra,76(sp)
    sw      s0,72(sp)
    addi    s0,sp,80

	// store previously calculated values
	sw      t2,-48(s0)
	sw      t0,-44(s0)
	sw		t1,-36(s0)

	// we should store t2,t0 - multiplication result and t1 - first approximation

fullNewtonCalc:
    // tmp = q / s;
    mv		a2,t1
    li		a3,0
    lw      a0,-48(s0)
    lw      a1,-44(s0)
    jal     ra,__udivdi3

	// result could not be greater than 32 bit, so we could forget about a1 result
    // tmp (a0) = ((q / s) + s) >> 1
    srli	a0,a0,1
    lw		a5,-36(s0)
    srli	a1,a5,1
    add		a0,a1,a0

    // if (tmp > s) { d = tmp - s } else { d = s - tmp }
    bgeu	a5,a0,1f
 	sub		a2,a0,a5
 	j		2f
1:
	sub		a2,a5,a0
2:
	// if (d < 2) return tmp (already stored within a0)
	li		a3,1
	bgeu	a3,a2,returnFullNewton
	// s = tmp
	mv		t1,a0
	sw		t1,-36(s0)
	j		fullNewtonCalc

returnFullNewton:
    // restore stack
    lw      ra,76(sp)
    lw      s0,72(sp)
    addi    sp,sp,80
    ret

	// reduced to 32 bit Newton algorithm:
	// t2 = q
	// t1 = s
	// t0 = tmp
	// t3 = 1
	// t4 = d
	// result = a0
	// no stack variables or saved registers used
redNewton:
	li		t3,1
redNewtonCycle:
	// tmp = q32 / s
	divu	t0,t2,t1
	// tmp += s
	add		t0,t0,t1
	// tmp >>= 1
	srli	t0,t0,1
	// if (tmp > s) { d = tmp - s } else { d = s - tmp }
	bgeu	t0,t1,1f
	sub     t4,t1,t0
	j		2f
1:
	sub		t4,t0,t1
2:
	// if (d < 2) return s
	bgeu	t3,t4,1f
	// s = tmp
	mv		t1,t0
	j		redNewtonCycle
1:
	mv		a0,t1
	ret


