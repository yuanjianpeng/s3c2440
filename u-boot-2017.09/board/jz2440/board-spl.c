/*
    Yuan Jianpeng <yuanjp@hust.edu.cn>
    2017/12/23
 */

#include <common.h>
#include <config.h>
#include <s3c2440.h>
#include <spl.h>

/*
 * Move these hardware related inits to lowlevel_init.S
 * We want set stack in sdram. the first 4K on s3c2440 is very valuable
 * we only use it hold SPL code.
 */
#if 0

void disable_watchdog(void)
{
    WTCTR = 0;
}

void clk_init(void)
{
    CLKCTR->CLKDIVN = (0x3 << 1) | 0x1;    // HDIVN:11b, PDIVN, 1 

    asm volatile (
        "mrc p15, 0, r1, c1, c0, 0\n\t"
        "orr r1, r1, #0xc0000000\n\t"
        "mcr p15, 0, r1, c1, c0, 0"
        :
        :
        : "r1");
   
    // according to datasheet, should set UPLLCON firstly.
    CLKCTR->UPLLCON = (56 << 12) | (2 << 4) | 2;   // 48MHz
    CLKCTR->MPLLCON = (92 << 12) | (1 << 4) | 1;   // 400MHz
}

void sdram_init(void)
{
    MEMCTR->BWSCON = 0x22011110;
    MEMCTR->BANKCON[0] = 0x0700;
    MEMCTR->BANKCON[1] = 0x0700;
    MEMCTR->BANKCON[2] = 0x0700;
    MEMCTR->BANKCON[3] = 0x0700;
    MEMCTR->BANKCON[4] = 0x0700;
    MEMCTR->BANKCON[5] = 0x0700;
    MEMCTR->BANKCON[6] = 0x018005;
    MEMCTR->BANKCON[7] = 0x018005;
    MEMCTR->REFRESH = 0x008C07A3;
    MEMCTR->BANKSIZE = 0x000000B1;
    MEMCTR->MRSRB[0] = 0x00000030;
    MEMCTR->MRSRB[1] = 0x00000030;
}

#endif

void board_init_f(unsigned long a)
{
#if 0
    disable_watchdog();
    clk_init();
    sdram_init();
#endif
    preloader_console_init();
}

u32 spl_boot_device(void)
{
	return BOOT_DEVICE_NAND;
}
