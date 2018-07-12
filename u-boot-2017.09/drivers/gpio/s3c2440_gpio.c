/*
 * Yuan Jianpeng <yuanjp@hust.edu.cn>
 *  2017/12/25
 */

#include <common.h>
#include <s3c2440.h>

/*
    LED / BUTTON Layout

    GPF4 GPF5 GPF6         GPG3 GPF2 GPF0
    --------------         --------------
         Led                   Button
 */

void gpio_init(void)
{
    /* gpio defaultly is input mode */
    GPF->CON |= (GPIO_OUT << 8 ) | (GPIO_OUT << 10) | (GPIO_OUT << 12);
}

/* turn on/off led */
void led(int num, int onoff)
{
    switch (num)
    {
    case 0:
        if (onoff)
            GPF->DAT &= ~(1 << 4);
        else
            GPF->DAT |= (1 << 4);
        break;
    case 1:
        if (onoff)
            GPF->DAT &= ~(1 << 5);
        else
            GPF->DAT |= (1 << 5);
        break;
    case 2:
        if (onoff)
            GPF->DAT &= ~(1 << 5);
        else
            GPF->DAT |= (1 << 5);
        break;
    }

}

/* return the button status */
int button(int num)
{
    int state = 0;
    switch (num) {
    case 0:
        state = !! (GPG->DAT & (1<<3));
        break;
    case 1:
        state = !! (GPF->DAT & (1<<2));
        break;
    case 2:
        state = !! (GPF->DAT & (1<<0));
        break;
    }
    return state;
}
