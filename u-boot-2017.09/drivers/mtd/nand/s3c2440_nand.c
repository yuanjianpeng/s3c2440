#include <common.h>
#include <nand.h>
#include <s3c2440.h>

static struct nand_chip nand_chip[CONFIG_SYS_MAX_NAND_DEVICE];

static inline int nand_dev_ready(void)
{
    return (NAND_REG->NFSTAT & 1);
}

static inline void nand_select_chip(void)
{
	NAND_REG->NFCONT &= ~(1<<1);
}

static inline void nand_deselect_chip(void)
{
	NAND_REG->NFCONT |= (1<<1);
}

#ifdef CONFIG_SPL_BUILD
static inline void nand_wait_idle(void)
{
	while (!nand_dev_ready())
		asm volatile ("nop");
}

static inline void nand_write_cmd(uint8_t cmd)
{
	NAND_REG->NFCMMD = cmd;
}

static inline void nand_write_addr(uint8_t addr)
{
	NAND_REG->NFADDR = addr;
}

static inline uint8_t nand_read_data(void)
{
    return NAND_REG->NFDATA;
}

// here is the api for K9F2G08U0C
// Page 2K + 64
// 64 pages per block
// total 2048 blocks

#define NAND_PAGES_PER_BLOCK     64
#define NAND_PAGE_SIZE           2048
#define NAND_PAGE_SPARE_SIZE     64
#define NAND_TOTAL_BLOCKS        2048 

void nand_reset(void)
{
    nand_select_chip();
    nand_write_cmd(0xff);
    nand_wait_idle();
    nand_deselect_chip();
}

int nand_read_page(unsigned int block, unsigned int page, 
    unsigned char *buf, unsigned int off, unsigned int len)
{
    if (block >= NAND_TOTAL_BLOCKS || page > NAND_PAGES_PER_BLOCK)
        return -1;

    if (off >= NAND_PAGE_SIZE + NAND_PAGE_SPARE_SIZE
        || len > NAND_PAGE_SIZE + NAND_PAGE_SPARE_SIZE - off) 
        return -1;

    nand_select_chip();
    nand_write_cmd(0x0);
    nand_write_addr((uint8_t)off);
    nand_write_addr((uint8_t)(off >> 8));
    nand_write_addr((uint8_t)(page|((block&3)<<6)));
    nand_write_addr((uint8_t)(block >> 2));
    nand_write_addr((uint8_t)(block >> 10));
    nand_write_cmd(0x30);
    nand_wait_idle();

    while ( len-- > 0)
        *buf++ = nand_read_data();

    return 1;
}

int nand_spl_load_image(uint32_t offs, unsigned int size, void *dst)
{
    int block;
    int page;
    int readed = 0;
    int readlen;

    puts("Loading U-Boot...\n");
    while (readed < size) {
        block = (offs + readed) / (NAND_PAGES_PER_BLOCK * NAND_PAGE_SIZE);
        page = ((offs + readed) / NAND_PAGE_SIZE) % NAND_PAGES_PER_BLOCK;
        readlen = NAND_PAGE_SIZE;
        if (size - readed < NAND_PAGE_SIZE)
            readlen = size - readed;
        nand_read_page(block, page, dst+readed,  0, readlen);
        readed += readlen;
    }

    return 0;
}

void nand_deselect(void)
{
    nand_deselect_chip();
}

void nand_init(void)
{
#define TACLS   0
#define TWRPH0  3
#define TWRPH1  0

    NAND_REG->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	NAND_REG->NFCONT = (1<<4)|(1<<1)|(1<<0);
}
#endif

static void s3c2440_nand_cmd_ctrl(struct mtd_info *mtd, int data, unsigned int ctrl)
{
    if (ctrl & NAND_NCE)
    {
        if (ctrl & NAND_CTRL_CHANGE)
            nand_select_chip();
    }
    else {
        nand_deselect_chip();
        return;
    }

    if (data == NAND_CMD_NONE)
        return;

    if (ctrl & NAND_CLE)
        NAND_REG->NFCMMD = data & 0xff;
    else if (ctrl & NAND_ALE)
        NAND_REG->NFADDR = data & 0xff;
}

static int s3c2440_nand_dev_ready(struct mtd_info *mtd)
{
    return nand_dev_ready();
}

static void s3c2440_nand_select_chip(struct mtd_info *mtd, int chip)
{
    if (chip == -1)
        nand_deselect_chip();
    else if (chip == 0)
        nand_select_chip();
    else
        printf("select unknown chip %d\n", chip);
}

static int s3c2440_nand_init(struct nand_chip *nand_chip, int devnum)
{
	struct mtd_info *mtd;
	int err = -1;

	mtd = nand_to_mtd(nand_chip);

    nand_chip->IO_ADDR_R = nand_chip->IO_ADDR_W 
        = (void __iomem *)&NAND_REG->NFDATA;

    nand_chip->ecc.mode = NAND_ECC_SOFT_BCH;
    nand_chip->cmd_ctrl = s3c2440_nand_cmd_ctrl;
    nand_chip->dev_ready = s3c2440_nand_dev_ready;
    nand_chip->chip_delay = 75;
	nand_chip->select_chip = s3c2440_nand_select_chip;
	nand_chip->bbt_options = NAND_BBT_USE_FLASH;

	/* first scan to find the device and get the page size */
	if (nand_scan_ident(mtd, 1, NULL)) {
		printf("%s: nand_scan_ident failed\n", __func__);
		goto fail;
	}


	if (nand_scan_tail(mtd)) {
		printf("%s: nand_scan_tail failed\n", __func__);
		goto fail;
	}

	if (nand_register(devnum, mtd)) {
		printf("Nand Register Fail\n");
		goto fail;
	}

	return 0;
fail:
	return err;
}

void board_nand_init(void)
{
	struct nand_chip *nand = &nand_chip[0];

	if (s3c2440_nand_init(nand, 0))
		puts("NAND init failed\n");
}

