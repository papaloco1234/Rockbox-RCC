/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2007 by Will Robertson
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#include "cpu.h"
#include "mmu-imx31.h"
#include "mmu-arm.h"

void memory_init(void) {
    ttb_init();
    set_page_tables();
    enable_mmu();
}

void set_page_tables() {
    map_section(0, 0, 0x1000, CACHE_NONE); /* map every memory region to itself */
    /*This pa *might* change*/
    map_section(0x80000000, 0, 64, CACHE_ALL); /* map RAM to 0 and enable caching for it */
    map_section((int)FRAME1, (int)FRAME1, 1, BUFFERED); /* enable buffered writing for the framebuffer */
    map_section((int)FRAME2, (int)FRAME2, 1, BUFFERED);
}

