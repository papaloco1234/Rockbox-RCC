/*
 * This config file is for the Apple iPod 3g
 */
#define APPLE_IPOD3G 1

/* For Rolo and boot loader */
#define MODEL_NUMBER 7

/* define this if you have recording possibility */
/*#define HAVE_RECORDING 1*/

/* define this if you have a bitmap LCD display */
#define HAVE_LCD_BITMAP 1

/* LCD dimensions */
#define LCD_WIDTH  160
#define LCD_HEIGHT 128
#define LCD_DEPTH  2   /* 4 colours - 2bpp */

#define CONFIG_KEYPAD IPOD_3G_PAD

/* Define this if you do software codec */
#define CONFIG_CODEC SWCODEC

/* define this if you have a real-time clock */
#ifndef BOOTLOADER
#define CONFIG_RTC RTC_PCF50605
#endif

/* Define this if you have a software controlled poweroff */
#define HAVE_SW_POWEROFF

/* The number of bytes reserved for loadable codecs */
#define CODEC_SIZE 0x80000

/* The number of bytes reserved for loadable plugins */
#define PLUGIN_BUFFER_SIZE 0x80000

/* Define this if you have the WM8731L audio codec */
#define HAVE_WM8731L

/* Define this for LCD backlight available */
#define CONFIG_BACKLIGHT BL_IPOD3G /* port controlled */

#ifndef SIMULATOR

/* Define this if you have a PortalPlayer PP5002 */
#define CONFIG_CPU PP5002

/* Define this if you want to use the PP5002 i2c interface */
#define CONFIG_I2C I2C_PP5002

/* Type of mobile power */
//#define CONFIG_BATTERY BATT_LIPOL1300

#define BATTERY_SCALE_FACTOR 16665 /* FIX: this value is picked at random */

/* Define this if the platform can charge batteries */
//#define HAVE_CHARGING 1

/* define this if the hardware can be powered off while charging */
//#define HAVE_POWEROFF_WHILE_CHARGING

/* The start address index for ROM builds */
#define ROM_START 0x00000000

/* Define this to the CPU frequency */
#define CPU_FREQ      11289600

#define CONFIG_LCD LCD_IPOD2BPP

/* Offset ( in the firmware file's header ) to the file length */
#define FIRMWARE_OFFSET_FILE_LENGTH 0

/* Offset ( in the firmware file's header ) to the file CRC */
#define FIRMWARE_OFFSET_FILE_CRC 0

/* Offset ( in the firmware file's header ) to the real data */
#define FIRMWARE_OFFSET_FILE_DATA 8

#define USB_IPODSTYLE

/* define this if the unit can be powered or charged via USB */
#define HAVE_USB_POWER

/* Virtual LED (icon) */
#define CONFIG_LED LED_VIRTUAL

/* Define this if you have adjustable CPU frequency */
//#define HAVE_ADJUSTABLE_CPU_FREQ

#define BOOTFILE_EXT "ipod"
#define BOOTFILE "rockbox." BOOTFILE_EXT

#endif
