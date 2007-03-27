/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Robert E. Hak
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#ifndef __MENU_H__
#define __MENU_H__

#include <stdbool.h>
#include "icon.h"
#include "icons.h"
#include "root_menu.h" /* needed for MENU_* return codes */


enum menu_item_type {
    MT_MENU = 0,
    MT_SETTING,
    MT_SETTING_W_TEXT, /* same as setting, but uses different
                          text for the setting title,
                          ID2P() or "literal" for the str param */
    MT_FUNCTION_CALL, /* call a function from the menus */
    MT_RETURN_ID, /* returns the position of the selected item (starting at 0)*/
    MT_RETURN_VALUE, /* returns a value associated with an item */
    MT_OLD_MENU, /* used so we can wrap the old menu api 
                    around the new api. Noone else should use this */
};

typedef int (*menu_function)(void);
struct menu_func {
    union {
        int (*function_w_param)(void* param); /* intptr_t instead of void*
                                                    for 64bit systems */
        int (*function)(void);
    };
    void *param; /* passed to function_w_param */
};

#define MENU_TYPE_MASK 0xF /* MT_* type */
/* these next two are mutually exclusive */
#define MENU_HAS_DESC   0x10
#define MENU_DYNAMIC_DESC 0x20

/* Flags for MT_FUNCTION_CALL */
#define MENU_FUNC_USEPARAM 0x40
#define MENU_FUNC_CHECK_RETVAL 0x80

#define MENU_COUNT_MASK 0xFFF
#define MENU_COUNT_SHIFT 8
#define MENU_ITEM_COUNT(c) ((c&MENU_COUNT_MASK)<<MENU_COUNT_SHIFT)
#define MENU_GET_COUNT(flags) ((flags>>MENU_COUNT_SHIFT)&MENU_COUNT_MASK)

struct menu_item_ex {
    unsigned int flags; /* above defines */
    union {
        const struct menu_item_ex **submenus; /* used with MT_MENU */
        void *variable; /* used with MT_SETTING,
                           must be in the settings_list.c list */
        const struct menu_func *function; /* MT_FUNCTION_* */
        const char **strings; /* used with MT_RETURN_ID */
        int value; /* MT_RETURN_VALUE */
    };
    union {
        /* For settings */
        int (*menu_callback)(int action, const struct menu_item_ex *this_item);
        /* For everything else, except if the text is dynamic */
        const struct menu_callback_with_desc {
            int (*menu_callback)(int action, 
                                 const struct menu_item_ex *this_item);
            unsigned char *desc; /* string or ID */
            int icon_id; /* from icons_6x8 in icons.h */
        } *callback_and_desc;
        /* For when the item text is dynamic */
        const struct menu_get_name_and_icon {
            int (*menu_callback)(int action, 
                                 const struct menu_item_ex *this_item);
            char *(*list_get_name)(int selected_item, void * data, char *buffer);
            void *list_get_name_data;
            int icon_id;
        } *menu_get_name_and_icon;
    };
};

typedef int (*menu_callback_type)(int action,
                                  const struct menu_item_ex *this_item);
int do_menu(const struct menu_item_ex *menu, int *start_selected);
bool do_setting_from_menu(const struct menu_item_ex *temp);

/* In all the following macros the argument names are as follows:
    - name: The name for the variable (so it can be used in a MAKE_MENU()
    - str:  the string to display for this menu item. use ID2P() for LANG_* id's
    - callback: The callback function to call for this menu item.
*/

/*  Use this to put a setting into a menu.
    The setting must appear in settings_list.c.
    If the setting is not configured properly, the menu will display "Not Done yet!"
    When the user selects this item the setting select screen will load,
    when that screen exits the user wll be back in the menu */
#define MENUITEM_SETTING(name,var,callback)                  \
    static const struct menu_item_ex name =                  \
        {MT_SETTING, {.variable = (void*)var},{callback}};

/*  Use this for settings which have a differnt title in their
    setting screen than in the menu (e.g scroll options */
#define MENUITEM_SETTING_W_TEXT(name, var, str, callback )              \
    static const struct menu_callback_with_desc name##__ = {callback,str, Icon_NOICON};\
    static const struct menu_item_ex name =                             \
        {MT_SETTING_W_TEXT|MENU_HAS_DESC, {.variable = (void*)var },     \
            {.callback_and_desc = & name##__}};

/*  Use this To create a list of NON-XLATABLE (for the time being) Strings
    When the user enters this list and selects one, the menu will exits
    and its return value will be the index of the chosen item */
#define MENUITEM_STRINGLIST(name, str, callback, ... )                  \
    static const char *name##_[] = {__VA_ARGS__};                       \
    static const struct menu_callback_with_desc name##__ = {callback,str, Icon_NOICON};\
    static const struct menu_item_ex name =                             \
        {MT_RETURN_ID|MENU_HAS_DESC|                                    \
         MENU_ITEM_COUNT(sizeof( name##_)/sizeof(*name##_)),            \
            { .strings = name##_},{.callback_and_desc = & name##__}};

            
/* returns a value associated with the item */
#define MENUITEM_RETURNVALUE(name, str, val, cb, icon)                      \
     static const struct menu_callback_with_desc name##_ = {cb,str,icon};     \
     static const struct menu_item_ex name   =                                  \
         { MT_RETURN_VALUE|MENU_HAS_DESC, { .value = val},             \
         {.callback_and_desc = & name##_}};
         
/* same as above, except the item name is dynamic */
#define MENUITEM_RETURNVALUE_DYNTEXT(name, val, cb, text_callback, text_cb_data, icon)                      \
     static const struct menu_get_name_and_icon name##_                       \
                                = {cb,text_callback,text_cb_data,icon}; \
     static const struct menu_item_ex name   =                              \
        { MT_RETURN_VALUE|MENU_DYNAMIC_DESC, { .value = val},               \
        {.menu_get_name_and_icon = & name##_}};
        
/*  Use this to put a function call into the menu.
    When the user selects this item the function will be run,
    unless MENU_FUNC_IGNORE_RETVAL is set, the return value
    will be checked, returning 1 will exit do_menu();                  */
#define MENUITEM_FUNCTION(name, flags, str, func, param,                   \
                              callback, icon)                         \
    static const struct menu_callback_with_desc name##_ = {callback,str,icon}; \
    static const struct menu_func name##__ = {{(void*)func}, param}; \
    /* should be const, but recording_settings wont let us do that */           \
    const struct menu_item_ex name   =                                  \
        { MT_FUNCTION_CALL|MENU_HAS_DESC|flags,                                \
         { .function = & name##__}, {.callback_and_desc = & name##_}};
            
/* As above, except the text is dynamic */
#define MENUITEM_FUNCTION_DYNTEXT(name, flags, func, param,   \
                                  text_callback, text_cb_data, callback, icon)    \
    static const struct menu_get_name_and_icon name##_                         \
                                = {callback,text_callback,text_cb_data,icon};  \
    static const struct menu_func name##__ = {{(void*)func}, param}; \
    static const struct menu_item_ex name   =                                  \
        { MT_FUNCTION_CALL|MENU_DYNAMIC_DESC|flags,                            \
         { .function = & name##__}, {.menu_get_name_and_icon = & name##_}};

/*  Use this to actually create a menu. the ... argument is a list of pointers 
    to any of the above macro'd variables. (It can also have other menus in the list. */
#define MAKE_MENU( name, str, callback, icon, ... )                           \
    static const struct menu_item_ex *name##_[]  = {__VA_ARGS__};       \
    static const struct menu_callback_with_desc name##__ = {callback,str,icon};\
    const struct menu_item_ex name =                                    \
        {MT_MENU|MENU_HAS_DESC|                                         \
         MENU_ITEM_COUNT(sizeof( name##_)/sizeof(*name##_)),            \
            { (void*)name##_},{.callback_and_desc = & name##__}};
            

/* OLD API - only use if you really have to.. Ideally this will be dropped */
struct menu_item {
    unsigned char *desc; /* string or ID */
    bool (*function) (void); /* return true if USB was connected */
};

int menu_init(const struct menu_item* mitems, int count,
                int (*callback)(int, int),
                const char *button1, const char *button2, const char *button3);
void menu_exit(int menu);

 /* Returns MENU_* define from root_menu.h, or number of selected menu item*/
int menu_show(int m);

bool menu_run(int menu);
int menu_count(int menu);

#endif /* End __MENU_H__ */
