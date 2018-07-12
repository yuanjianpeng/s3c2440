/*
 * Yuan Jianpeng <yuanjp@hust.edu.cn>
 * 2017/12/23
 */

#ifndef S3C2440_H_
#define S3C2440_H_

#define FCLK    400000000
#define HCLK    (FCLK/3)
#define PCLK    (FCLK/6)



#define WATCHDOG_BASE   0x53000000
#define WTCTR_ADDR      0x53000000 

#define CLK_BASE        0x4c000000
#define MPLLCON_ADDR    0x4c000004
#define UPLLCON_ADDR    0x4c000008
#define CLKDIVN_ADDR    0x4c000014

#define MEMCTR_BASE     0x48000000
#define NANDCTR_BASE     0x4E000000


#ifndef __ASSEMBLY__

/*  watchdog */
#define WTCTR       (*(volatile unsigned long *)0x53000000)

struct S3C2440_CLK_CONTROLLER
{
    uint32_t LOCKTIME;
    uint32_t MPLLCON;
    uint32_t UPLLCON;
    uint32_t CLKCON;
    uint32_t CLKSLOW;
    uint32_t CLKDIVN;
    uint32_t CAMDIVN;
};

#define CLKCTR     ((volatile struct S3C2440_CLK_CONTROLLER *)0x4c000000)

struct S3C2440_MEM_CONTROLLER
{
	uint32_t BWSCON;
	uint32_t BANKCON[8];
	uint32_t REFRESH;
	uint32_t BANKSIZE;
	uint32_t MRSRB[2];
};

#define MEMCTR     ((volatile struct S3C2440_MEM_CONTROLLER *)0x48000000)

struct S3C2440_UART_CONTROLLER
{
    uint32_t ULCON;
    uint32_t UCON;
    uint32_t UFCON;
    uint32_t UMCON;
    uint32_t UTRSTAT;
    uint32_t UERSTAT;
    uint32_t UFSTAT;
    uint32_t UMSTAT;
    uint8_t  UTXH;
    uint8_t  unused1[3];
    uint8_t  URXH;
    uint8_t  unused2[3];
    uint32_t UBRDIV;
};

#define UART_CH0	((volatile struct S3C2440_UART_CONTROLLER *)0x50000000)
#define UART_CH1	((volatile struct S3C2440_UART_CONTROLLER *)0x50004000)
#define UART_CH2	((volatile struct S3C2440_UART_CONTROLLER *)0x50008000)

struct S3C2440_GPIO
{
	uint32_t CON;
#define GPIO_INP 0
#define GPIO_OUT 1
#define GPIO_INTR   2
#define GPIO_CON_MSK 3
#define GPIO_CON_BITS 2
	uint32_t DAT;
	uint32_t UP;
#define GPIO_PULLUP_DISABLE 1
	uint32_t reserved;
};

#define GPA			((volatile struct S3C2440_GPIO *)0x56000000)
#define GPB			((volatile struct S3C2440_GPIO *)0x56000010)
#define GPC			((volatile struct S3C2440_GPIO *)0x56000020)
#define GPD			((volatile struct S3C2440_GPIO *)0x56000030)
#define GPE			((volatile struct S3C2440_GPIO *)0x56000040)
#define GPF			((volatile struct S3C2440_GPIO *)0x56000050)
#define GPG			((volatile struct S3C2440_GPIO *)0x56000060)
#define GPH			((volatile struct S3C2440_GPIO *)0x56000070)
#define GPJ			((volatile struct S3C2440_GPIO *)0x560000d0)

struct S3C2440_NAND_REG
{
    uint32_t NFCONF;
    uint32_t NFCONT;
    uint8_t  NFCMMD;
    uint8_t  unused0[3];
    uint8_t  NFADDR;
    uint8_t  unused1[3];
    uint8_t  NFDATA;
    uint8_t  unused2[3];
    uint32_t NFMECCD0;
    uint32_t NFMECCD1;
    uint32_t NFSECCD;
    uint8_t  NFSTAT;
    uint8_t  unused3[3];
    uint32_t NFESTAT0;
    uint32_t NFESTAT1;
    uint32_t NFMECC0;
    uint32_t NFMECC1;
    uint32_t NFSECC;
    uint32_t NFSBLK;
    uint32_t NFEBLK;
};

#define NAND_REG	((volatile struct S3C2440_NAND_REG *)0x4E000000) 

struct S3C2440_PWM_TIMER
{
    uint32_t TCFG0;
    uint32_t TCFG1;
    uint32_t TCON;
    struct
    {
        uint32_t TCNTBn;
        uint32_t TCMPBn;
        uint32_t TCNTOn;
    } TIMER0_3[4];
    struct
    {
        uint32_t TCNTB4;
        uint32_t TCNTO4;
    } TIMER4;
};

#define PWM_REG ((volatile struct S3C2440_PWM_TIMER *)0x51000000)

#endif

#endif
