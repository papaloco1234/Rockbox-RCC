/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Jerome Kuptz
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file.h"
#include "lcd.h"
#include "button.h"
#include "kernel.h"
#include "tree.h"
#include "debug.h"
#include "sprintf.h"
#include "settings.h"
#include "wps.h"


#define LINE_Y      1 /* initial line */

#define PLAY_DISPLAY_DEFAULT         0 
#define PLAY_DISPLAY_FILENAME_SCROLL 1 
#define PLAY_DISPLAY_TRACK_TITLE     2 

/* demonstrates showing different formats from playtune */
void wps_show_play(char* filename)
{
    struct mp3entry mp3;
    mp3info(&mp3,filename);

    switch ( global_settings.wps_display ) {
        case PLAY_DISPLAY_TRACK_TITLE:
        {
            char ch = '/';
            char* end;
            char* szTok;
            char* szDelimit;
            char szArtist[26];
            char szBuff[257];
            szBuff[sizeof(szBuff)-1] = 0;

            strncpy(szBuff, filename, sizeof(szBuff));

            szTok = strtok_r(szBuff, "/", &end);
            szTok = strtok_r(NULL, "/", &end);

            // Assume path format of: Genre/Artist/Album/Mp3_file
            strncpy(szArtist,szTok,sizeof(szArtist));
            szArtist[sizeof(szArtist)-1] = 0;
            szDelimit = strrchr(filename, ch);
            lcd_puts(0,0, szArtist?szArtist:"<nothing>");
            lcd_puts_scroll(0,LINE_Y,(++szDelimit));
            break;
        }
        case PLAY_DISPLAY_FILENAME_SCROLL:
        {
            char ch = '/';
            char* szLast = strrchr(filename, ch);

            if (szLast)
                lcd_puts_scroll(0,0, (++szLast));
            else
                lcd_puts_scroll(0,0, mp3.path);

            break;
        }
        case PLAY_DISPLAY_DEFAULT:
        {
#ifdef HAVE_LCD_BITMAP
            char buffer[256];

            lcd_puts(0, 0, "[id3 info]");
            lcd_puts(0, LINE_Y, mp3.title?mp3.title:"");
            lcd_puts(0, LINE_Y+1, mp3.album?mp3.album:"");
            lcd_puts(0, LINE_Y+2, mp3.artist?mp3.artist:"");

            snprintf(buffer,sizeof(buffer), "%d ms", mp3.length);
            lcd_puts(0, LINE_Y+3, buffer);

            snprintf(buffer,sizeof(buffer), "%d kbits", mp3.bitrate);

            lcd_puts(0, LINE_Y+4, buffer);

            snprintf(buffer,sizeof(buffer), "%d Hz", mp3.frequency);
            lcd_puts(0, LINE_Y+5, buffer);
#else

            lcd_puts(0, 0, mp3.artist?mp3.artist:"<no artist>");
            lcd_puts(0, 1, mp3.title?mp3.title:"<no title>");
#endif
            break;
        }

    }
}

/* experimental idea still being sorted out, but want it in the the code tree still so that important playlist info is not forgotten. */
#if 0
void wps_show_playlist(char* current, playlist_info_t *list)
{
    char ch       = '/';
    char* szLast = strrchr(current, ch);
    char buf[16];
    
    buf[15] = 0;

    snprintf(buf, sizeof(buf), "[%d/%d]", list->index, list->amount);
    
    lcd_clear_display();

#ifdef HAVE_LCD_BITMAP
    lcd_puts(0, 0, "[Playlist Mode]");
    lcd_puts_scroll(0,LINE_Y, (++szLast));
    lcd_puts(0, LINE_Y+1, buf);
#else
    lcd_puts_scroll(0,0, (++szLast));
    lcd_puts(0,1,buf);
#endif


    lcd_update();
}
#endif
