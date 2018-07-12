/*
   Yuan Jianpeng <yuanjp@hust.edu.cn>
   2017/12/22
 */

#include <common.h>
#include <config.h>
#include <serial.h>
#include "s3c2440.h"

/*
 * this file provides low level uart access of s3c2440
 * for SPL and serial driver
 */


int uart_tstc(void)
{
    return (UART_CH0->UFSTAT & 0x1f) ? 1 : 0 ;
}

void uart_putc(const char c)
{
    if (c == '\n')
        uart_putc('\r');
    while (UART_CH0->UFSTAT & (1 << 14))
        ;
    UART_CH0->UTXH = c;
}

int uart_getc(void)
{
	while (!(UART_CH0->UFSTAT & 0x1f))
        ;
    return UART_CH0->URXH;
}

void uart_puts(const char *s)
{
    while (*s) {
        uart_putc(*s);
        s++;
    }
}

#ifdef CONFIG_SPL_BUILD
void puts(const char *str)
{
    return uart_puts(str);
}
#endif

int uart_init(void)
{
    // set gpio to RXD0/TXD0
    GPH->CON = (2 << 4) | (2 << 6);
    // SET PULL-up
    GPH->UP = (1 << 2) | (1 << 3);        			
    
    // NO Parity | 1 Stop bit | 8N1
    UART_CH0->ULCON = 0x3;              		
    // Enable RX timeout, enable rx erro intr
    UART_CH0->UCON = (1<<7)|(1<<6)|(1<<2)|(1<<0);    
    UART_CH0->UFCON = (2<<6)|(2<<4)|(1<<0);
    UART_CH0->UMCON = 0;
    UART_CH0->UBRDIV = 400*1000*1000/6/16/115200;    
    return 0;
}

static struct serial_device s3c2440_serial_drv = {
	.name	= "s3c2440_serial",
	.start	= uart_init,
	.stop	= NULL,
	.setbrg	= NULL,
	.putc	= uart_putc,
	.puts	= uart_puts,
	.getc	= uart_getc,
	.tstc	= uart_tstc,
};

__weak struct serial_device *default_serial_console(void)
{
	return &s3c2440_serial_drv;
}


void print_int(uint32_t v)
{
    int i = 0;
    for (i = 0; i < 8; i++) {
        char c = '0';
        uint32_t j = (v >> (28 - 4 * i)) & 0xf;
        if (j < 10)
            c += j;
        else
            c = 'a' + j - 10;
        uart_putc(c);
    }
}

void print_newline(void)
{
    uart_putc('\n');
}
