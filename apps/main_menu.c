/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Bj�rn Stenberg
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#include "config.h"
#include "options.h"

#include "menu.h"
#include "tree.h"
#include "credits.h"
#include "lcd.h"
#include "font.h"
#include "button.h"
#include "kernel.h"
#include "main_menu.h"
#include "version.h"
#include "debug_menu.h"
#include "sprintf.h"
#include <string.h>
#include "playlist.h"
#include "settings.h"
#include "settings_menu.h"
#include "power.h"
#include "powermgmt.h"
#include "sound_menu.h"
#include "status.h"

#include "lang.h"

#ifdef HAVE_MAS3587F
#include "recording.h"
#endif

#ifdef HAVE_LCD_BITMAP
#include "bmp.h"
#include "icons.h"

#ifdef USE_GAMES
#include "games_menu.h"
#endif /* End USE_GAMES */

#ifdef USE_DEMOS
#include "demo_menu.h"
#endif /* End USE_DEMOS */

#endif /* End HAVE_LCD_BITMAP */

int show_logo( void )
{
#ifdef HAVE_LCD_BITMAP
    char version[32];
    unsigned char *ptr=rockbox112x37;
    int height, i, font_h, font_w;

    lcd_clear_display();

    for(i=0; i < 37; i+=8) {
        /* the bitmap function doesn't work with full-height bitmaps
           so we "stripe" the logo output */
        lcd_bitmap(ptr, 0, 10+i, 112, (37-i)>8?8:37-i, false);
        ptr += 112;
    }
    height = 37;

#if 0
    /*
     * This code is not used anymore, but I kept it here since it shows
     * one way of using the BMP reader function to display an externally
     * providing logo.
     */
    unsigned char buffer[112 * 8];
    int width;

    int i;
    int eline;

    int failure;
    failure = read_bmp_file("/rockbox112.bmp", &width, &height, buffer);

    debugf("read_bmp_file() returned %d, width %d height %d\n",
           failure, width, height);
    
    for(i=0, eline=0; i < height; i+=8, eline++) {
        /* the bitmap function doesn't work with full-height bitmaps
           so we "stripe" the logo output */
        lcd_bitmap(&buffer[eline*width], 0, 10+i, width,
                   (height-i)>8?8:height-i, false);
    }
#endif

    snprintf(version, sizeof(version), "Ver. %s", appsversion);
    lcd_setfont(FONT_SYSFIXED);
    lcd_getstringsize("A", &font_w, &font_h);
    lcd_putsxy((LCD_WIDTH/2) - ((strlen(version)*font_w)/2),
               LCD_HEIGHT-font_h, version);
    lcd_update();

#else
    char *rockbox = "  ROCKbox!";
    lcd_clear_display();
    lcd_double_height(true);
    lcd_puts(0, 0, rockbox);
    lcd_puts(0, 1, appsversion);
#endif

    return 0;
}

bool show_credits(void)
{
    int j = 0;
    int btn;

    show_logo();
#ifdef HAVE_LCD_CHARCELLS
    lcd_double_height(false);
#endif
    
    for (j = 0; j < 10; j++) {
        sleep((HZ*2)/10);

        btn = button_get(false);
        if (btn !=  BUTTON_NONE && !(btn & BUTTON_REL))
            return false;
    }
    roll_credits();
    return false;
}

#ifdef SIMULATOR
#define mp3buf 0
#define mp3end 0

extern bool simulate_usb(void);
#else
/* defined in linker script */
extern unsigned char mp3buf[];
extern unsigned char mp3end[];
#endif
bool show_info(void)
{
    char s[32];
    int buflen = ((mp3end - mp3buf) * 1000) / 0x100000;
    int integer, decimal;
    bool done = false;
    int key;
    int state=0;

    while(!done)
    {
        lcd_clear_display();
        lcd_puts(0, 0, str(LANG_ROCKBOX_INFO));
        
        integer = buflen / 1000;
        decimal = buflen % 1000;
#ifdef HAVE_LCD_CHARCELLS
        snprintf(s, sizeof(s), str(LANG_BUFFER_STAT_PLAYER), integer, decimal);
        lcd_puts(0, 0, s);
#else
        snprintf(s, sizeof(s), str(LANG_BUFFER_STAT_RECORDER), integer,
                 decimal);
        lcd_puts(0, 2, s);
#endif

#ifdef HAVE_LCD_CHARCELLS
        snprintf(s, sizeof(s), str(LANG_BATTERY_LEVEL_PLAYER), 
                 battery_level(), battery_level_safe() ? "" : "!");
        lcd_puts(0, 1, s);
#else
#ifdef HAVE_CHARGE_CTRL
        if (charger_enabled)
            snprintf(s, sizeof(s), str(LANG_BATTERY_CHARGE));
        else
            snprintf(s, sizeof(s), str(LANG_BATTERY_LEVEL_RECORDER), 
                     battery_level(), battery_level_safe() ? "" : " !!");
        lcd_puts(0, 3, s);
#else
        snprintf(s, sizeof(s), str(LANG_BATTERY_LEVEL_RECORDER), 
                 battery_level(), battery_level_safe() ? "" : " !!");
        lcd_puts(0, 3, s);
#endif
#endif
    
        lcd_update();

        /* Wait for a key to be pushed */
        key = button_get_w_tmo(HZ/2);
        if(key) {
            switch(state) {
            case 0:
                /* first, a non-release event */
                if(!(key&BUTTON_REL))
                    state++;
                break;
            case 1:
                /* then a release-event */
                if(key&BUTTON_REL)
                    done = true;
                break;
            }
        }
    }

    return false;
}

bool main_menu(void)
{
    int m;
    bool result;

    /* main menu */
    struct menu_items items[] = {
        { str(LANG_SOUND_SETTINGS),     sound_menu        },
        { str(LANG_GENERAL_SETTINGS),   settings_menu     },
#ifdef HAVE_MAS3587F
        { str(LANG_RECORDING_SETTINGS),   recording_menu     },
        { str(LANG_RECORDING),   recording_screen     },
#endif
#ifdef HAVE_LCD_BITMAP
#ifdef USE_GAMES
        { str(LANG_GAMES),              games_menu        },
#endif
#ifdef USE_DEMOS
        { str(LANG_DEMOS),              demo_menu },
#endif /* end USE_DEMOS */
#endif
        { str(LANG_INFO),               show_info         },
        { str(LANG_VERSION),            show_credits      },
#ifndef SIMULATOR
        { str(LANG_DEBUG),              debug_menu        },
#else
        { str(LANG_USB),                simulate_usb      },
#endif
    };

    m=menu_init( items, sizeof items / sizeof(struct menu_items) );
#ifdef HAVE_LCD_CHARCELLS
    status_set_param(true);
#endif
    result = menu_run(m);
#ifdef HAVE_LCD_CHARCELLS
    status_set_param(false);
#endif
    menu_exit(m);

    settings_save();

    return result;
}

/* -----------------------------------------------------------------
 * local variables:
 * eval: (load-file "../firmware/rockbox-mode.el")
 * end:
 * vim: et sw=4 ts=8 sts=4 tw=78
 */
