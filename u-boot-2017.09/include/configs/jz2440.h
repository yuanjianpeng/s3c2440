#ifndef __CONFIG_H
#define __CONFIG_H

#ifndef CONFIG_SPL_BUILD
//#define DEBUG
#endif

#define CONFIG_MACH_TYPE		        MACH_TYPE_S3C2440
#define CONFIG_SYS_MAX_FLASH_BANKS      1
#define CONFIG_SYS_LOAD_ADDR            0x30000000

#define CONFIG_SYS_SDRAM_BASE		0x30000000
#define CONFIG_SYS_TEXT_BASE		0x30000000

#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_NAND_DRIVERS
#define CONFIG_SPL_NAND_RAW_ONLY

#define CONFIG_SYS_NAND_BASE            0
#define CONFIG_NAND_S3C2440
#define CONFIG_SYS_NAND_SELF_INIT

#define CONFIG_SYS_NAND_U_BOOT_OFFS     (128*1024)
#define CONFIG_SYS_NAND_U_BOOT_SIZE     (256*1024)
#define CONFIG_SYS_NAND_U_BOOT_DST      CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_NAND_U_BOOT_START    CONFIG_SYS_NAND_U_BOOT_DST

#define CONFIG_SYS_MAX_NAND_DEVICE      1

/*
 * SPL stack & u-boot early stack
 */
#define CONFIG_SYS_INIT_SP_ADDR 0x31000000

#define CONFIG_SYS_MALLOC_LEN		(512 * 1024)
#define CONFIG_SYS_MONITOR_BASE		0x0

#define CONFIG_ENV_OFFSET			    0x100000
#define CONFIG_ENV_SIZE			        0x20000
#define CONFIG_ENV_RANGE			    0x100000

#define CONFIG_NR_DRAM_BANKS		6

#define CONFIG_DRIVER_DM9000
#define CONFIG_DM9000_USE_16BIT     1
#define CONFIG_DM9000_BASE          0x20000000
#define DM9000_IO                   0x20000000
#define DM9000_DATA                 0x20000004

#define CONFIG_S3C2440_UART
#define CONFIG_CMDLINE_EDITING

#define CONFIG_MTD_DEVICE

#define CONFIG_SYS_BOOTPARAMS_LEN 4096
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_CMDLINE_TAG
#define CONFIG_INITRD_TAG

#define CONFIG_SYS_LONGHELP
#define CONFIG_NAND_ECC_BCH

#endif
