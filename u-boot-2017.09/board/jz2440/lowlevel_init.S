/*
 * Copyright (C) 2017 Herbert Yuan
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <s3c2440.h>

    .macro setreg addr, value
    ldr r1, =\addr
    ldr r0, =\value
    str r0, [r1]
    .endm

	.globl lowlevel_init
lowlevel_init:
#if defined(CONFIG_SPL_BUILD)
    /* disable watchdog */
    setreg WTCTR_ADDR, 0

    /* init clock */
    setreg CLKDIVN_ADDR, 0x7
    mrc p15, 0, r1, c1, c0, 0
    orr r1, r1, #0xc0000000
    mcr p15, 0, r1, c1, c0, 0
    setreg UPLLCON_ADDR, (56<<12)|(2<<4)|2
    setreg MPLLCON_ADDR, (92<<12)|(1<<4)|1

    /* init sdram */
    /* 
     * here use adr instead of ldr, 
     * to get addr use pc relative addressing mode, 
     * so this code can run at any address without any relocation
     */
    adr r0, mem
    ldr r1, =MEMCTR_BASE
    /*
     * Take care!
     * some register can't be overwritten, ip for example!!!
     */
    LDMIA r0!, {r2-r8}
    STMIA r1!, {r2-r8}
    LDMIA r0!, {r2-r7}
    STMIA r1!, {r2-r7}
#endif
    mov pc, lr
#if defined(CONFIG_SPL_BUILD)
mem:
    .word 0x22011110
    .word 0x0700
    .word 0x0700
    .word 0x0700
    .word 0x0700
    .word 0x0700
    .word 0x0700
    .word 0x018005
    .word 0x018005
    .word 0x008c07a3
    .word 0xb1
    .word 0x30
    .word 0x30
#endif

