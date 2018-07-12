/*
 * Board initialization for EP93xx
 *
 * Copyright (C) 2013
 * Sergey Kostanbaev <sergey.kostanbaev <at> fairwaves.ru>
 *
 * Copyright (C) 2009
 * Matthias Kaehlcke <matthias <at> kaehlcke.net>
 *
 * (C) Copyright 2002 2003
 * Network Audio Technologies, Inc. <www.netaudiotech.com>
 * Adam Bezanson <bezanson <at> netaudiotech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>
#include <netdev.h>
#include <asm/io.h>
#include <asm/mach-types.h>


DECLARE_GLOBAL_DATA_PTR;

/* delay execution before timers are initialized */
static inline void early_udelay(uint32_t usecs)
{
	/* loop takes 4 cycles at 5.0ns (fastest case, running at 200MHz) */
	register uint32_t loops = (usecs * 1000) / 20;

	__asm__ volatile ("1:\n"
			"subs %0, %1, #1\n"
			"bne 1b" : "=r" (loops) : "0" (loops));
}

void reset_cpu(ulong addr)
{
	return;
}

int board_init(void)
{
	/* Go to Async mode */
	__asm__ volatile ("mrc p15, 0, r0, c1, c0, 0");
	__asm__ volatile ("orr r0, r0, #0xc0000000");
	__asm__ volatile ("mcr p15, 0, r0, c1, c0, 0");

	icache_enable();

#ifdef USE_920T_MMU
	dcache_enable();
#endif

	/* Machine number, as defined in linux/arch/arm/tools/mach-types */
	gd->bd->bi_arch_number = CONFIG_MACH_TYPE;

	/* adress of boot parameters */
//	gd->bd->bi_boot_params = LINUX_BOOT_PARAM_ADDR;

	/* We have a console */
	gd->have_console = 1;

	enable_interrupts();

//	flash_cfg();

//	green_led_on();
//	red_led_off();

	return 0;
}

int board_early_init_f(void)
{
	return 0;
}

/* called in board_init_f (before relocation) */
int dram_init(void)
{
    gd->ram_size = 64 * 1024 * 1024;
    return 0;
}

int print_cpuinfo(void)
{
	return 0;
}

#ifdef CONFIG_CMD_NET
int dm9000_initialize(bd_t *bis);
int board_eth_init(bd_t *bis)
{
    int rc = 0;
    rc = dm9000_initialize(bis);
    return rc;
}
#endif
