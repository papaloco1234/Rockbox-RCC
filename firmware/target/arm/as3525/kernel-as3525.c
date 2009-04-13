/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright � 2008 Rafa�l Carr�
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#include "config.h"
#include "system.h"
#include "kernel.h"
#include "panic.h"
#include "timer-target.h"

#ifdef HAVE_SCROLLWHEEL
/* The scrollwheel is polled every 5 ms (the tick tasks only every 10) */
extern void button_read_dbop(void);
static volatile int poll_scrollwheel = 0;

void INT_TIMER2(void)
{
    if (!poll_scrollwheel)
        call_tick_tasks();  /* Run through the list of tick tasks */
    else
        button_read_dbop();

    poll_scrollwheel ^= 1;
    TIMER2_INTCLR = 0;  /* clear interrupt */
}
#else
void INT_TIMER2(void)
{
    call_tick_tasks();  /* Run through the list of tick tasks */

    TIMER2_INTCLR = 0;  /* clear interrupt */
}
#endif

void tick_start(unsigned int interval_in_ms)
{
    int phi = 0;                            /* prescaler bits */
    int prescale = 1;
    int cycles = TIMER_FREQ / 1000 * interval_in_ms;

#ifdef HAVE_SCROLLWHEEL
    /* let the timer interrupt twice as often for the scrollwheel polling */
    cycles >>= 1;
#endif

    while(cycles > 0x10000)
    {
        phi++;
        prescale <<= 4;
        cycles >>= 4;
    }

    if(prescale > 256)
        panicf("%s : interval too big", __func__);

    CGU_PERI |= CGU_TIMER2_CLOCK_ENABLE;    /* enable peripheral */
    VIC_INT_ENABLE |= INTERRUPT_TIMER2;     /* enable interrupt */

    TIMER2_LOAD = TIMER2_BGLOAD = cycles;   /* timer period */

    /* /!\ bit 4 (reserved) must not be modified
     * periodic mode, interrupt enabled, 16 bits counter */
    TIMER2_CONTROL = (TIMER2_CONTROL & (1<<4)) | 0xe0 | (phi<<2);
}
