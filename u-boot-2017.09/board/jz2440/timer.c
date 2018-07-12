/*
 * 2018 (c) Herbert Yuan <yuanjp@hust.edu.cn>
 * 
 */

#include <common.h>
#include <div64.h>
#include <s3c2440.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * 1MHz
 * so we get the delay precise at 1us
 */
#define TIMER_CLK       1000000
#define PWM_INIT_CNT    0xffff


static inline uint16_t pwm_timer_read_obs (void)
{
    return (uint16_t)PWM_REG->TIMER4.TCNTO4; 
}

static inline void pwm_timer_start (void)
{
    PWM_REG->TCON = (1 << 22) | (1 << 21);
    PWM_REG->TCON = (1 << 22) | (1 << 20);
}

/*
 * Use PWM timer 4, because it has no output 
 * Serial is no ready
 * file static variable is not available
 */

int timer_init(void)
{
    int div;
    int real_timer_clk;
    int delay_timer_period;
    int prescaler, divide;
    int i, j, k = 1;
    
    // find the best prescaler & divide for TIMER_CLK
    for (i = 0; i < 256; i++) {
        for (j = 2; j <=16; j*=2) {
            int clk = PCLK/((1+i)*j);
            if (k == 1 || 
                abs(clk-TIMER_CLK) < abs(real_timer_clk-TIMER_CLK)) 
            {
                prescaler = i;
                divide = j;
                real_timer_clk = clk;
                k = 0;

            }
        }
    }


    /*
     * the us of timer period used by udelay()
     * to deal with the roll over problem, the period 
     * should less than half of real period.
     */
    delay_timer_period = 1000ULL * 1000 * PWM_INIT_CNT / real_timer_clk; 
    delay_timer_period /= 2;
    delay_timer_period -= 10;


    switch (divide)
    {
    case 16:
        div = 3;
        break;
    case 8:
        div = 2;
        break;
    case 4:
        div = 1;
        break;
    case 2:
        div = 0;
        break;
    default:
        return 1;
    }

    PWM_REG->TCFG0 = (prescaler << 8);
    PWM_REG->TCFG1 = (div << 16);
    PWM_REG->TIMER4.TCNTB4 = PWM_INIT_CNT;

    pwm_timer_start();
    
    gd->arch.timer_rate_hz = real_timer_clk;
    gd->arch.delay_timer_period = delay_timer_period;

    return 0;
}

unsigned long get_tbclk(void)
{
	return gd->arch.timer_rate_hz;
}

unsigned long get_timer_period(void)
{
    return gd->arch.delay_timer_period;
}

unsigned long timer_read_counter(void)
{
	return PWM_INIT_CNT - pwm_timer_read_obs();
}

static inline unsigned long tick_margin(unsigned long early,
    unsigned long later)
{
    return (later >= early) ? (later - early) : 
        (PWM_INIT_CNT - early + later);
}

/*---------------------- get_timer ****************************/

static inline uint64_t notrace tick_to_time(uint64_t tick)
{
	ulong div = get_tbclk();
	tick *= CONFIG_SYS_HZ;
	do_div(tick, div);
	return tick;
}

/*
 * wraps very quickly about tens ms
 * cuz our TIMER_CLK is 1MHZ, but count is only 16 bits.
 *
 * the solution is we call get_ticks() in time (less than  get_timer_period())
 * to ensure no roll over happen. then we can accumulate every get_ticks()
 * to simulate a big wrap time.
 */
uint64_t notrace get_ticks(void)
{
	unsigned long now = timer_read_counter();
    gd->arch.ts += tick_margin(gd->arch.previous_ts, now);
    gd->arch.previous_ts = now;
    return gd->arch.ts;
}

/* Returns time ticks base on CONFIG_SYS_HZ */
ulong get_timer(ulong base)
{
	return tick_to_time(get_ticks()) - base;
}

unsigned long notrace timer_get_us(void)
{
	return tick_to_time(get_ticks()) * 1000 / CONFIG_SYS_HZ * 1000;
}

/*---------------------- udelay ****************************/

static inline uint64_t usec_to_tick(unsigned long usec)
{
	uint64_t tick = usec;
	tick *= get_tbclk();
	do_div(tick, 1000000);
	return tick;
}

void __udelay(unsigned long usec)
{
    unsigned long st = timer_read_counter();
    unsigned long delay_tick = usec_to_tick(usec);

	while (tick_margin(st, timer_read_counter())
        < delay_tick + 1)	/* loop till event */
        /*NOP*/;

}

