
#include "plugin.h"

#define SETTINGS_VERSION 3
#define SETTINGS_MIN_VERSION 1
#define SETTINGS_FILENAME "mpegplayer.cfg"

#if defined(TOSHIBA_GIGABEAT_F) || defined(SANSA_E200) || defined(SANSA_C200) \
    || defined (IRIVER_H10)
#define MPEG_OPTION_DITHERING_ENABLED 1
#endif

#ifndef MPEG_OPTION_DITHERING_ENABLED
#define MPEG_OPTION_DITHERING_ENABLED 0
#endif

enum mpeg_option_id
{
#if MPEG_OPTION_DITHERING_ENABLED
    MPEG_OPTION_DITHERING,
#endif
    MPEG_OPTION_DISPLAY_FPS,
    MPEG_OPTION_LIMIT_FPS,
    MPEG_OPTION_SKIP_FRAMES,
};

enum mpeg_resume_id
{
    MPEG_RESUME_MENU_ALWAYS = 0,
    MPEG_RESUME_MENU_IF_INCOMPLETE,
    MPEG_RESUME_RESTART,
    MPEG_RESUME_ALWAYS,
    MPEG_RESUME_NUM_OPTIONS,
};

enum mpeg_start_id
{
    MPEG_START_RESTART,
    MPEG_START_RESUME,
    MPEG_START_SEEK,
    MPEG_START_SETTINGS,
    MPEG_START_QUIT,
    MPEG_START_EXIT,
};

enum mpeg_menu_id
{
    MPEG_MENU_DISPLAY_SETTINGS,
    MPEG_MENU_ENABLE_START_MENU,
    MPEG_MENU_CLEAR_RESUMES,
    MPEG_MENU_QUIT,
};

struct mpeg_settings {
    int showfps;               /* flag to display fps */
    int limitfps;              /* flag to limit fps */
    int skipframes;            /* flag to skip frames */
    int resume_options;        /* type of resume action at start */
    int resume_count;          /* total # of resumes in config file */
    int resume_time;           /* resume time for current mpeg (in half minutes) */
    char resume_filename[MAX_PATH]; /* filename of current mpeg */
#if MPEG_OPTION_DITHERING_ENABLED
    int displayoptions;
#endif
};

extern struct mpeg_settings settings;

int mpeg_start_menu(uint32_t duration);

enum
{
    MPEG_MENU_HIDE_QUIT_ITEM = 0x1, /* Don't show the quit item */
};

int mpeg_menu(unsigned flags);
void mpeg_menu_sysevent_clear(void);
long mpeg_menu_sysevent(void);
int mpeg_menu_sysevent_callback(int btn, int menu);
void mpeg_menu_sysevent_handle(void);

void init_settings(const char* filename);
void save_settings(void);
