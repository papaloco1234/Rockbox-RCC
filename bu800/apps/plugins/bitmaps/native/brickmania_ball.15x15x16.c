#include "lcd.h"
#include "/home/ubuntu/Desktop/RockboxRCC/bu800/pluginbitmaps/brickmania_ball.h"
const unsigned short brickmania_ball[] = {
0x0000, 0x0000, 0x0000, 0x0020, 0x4228, 0x9492, 0xad75, 0xdedb, 0xc618, 0x8c71,
0x6b4d, 0x18e3, 0x0000, 0x0000, 0x0000, 
0x0000, 0x0000, 0x2104, 0x94b2, 0xdedb, 0xe71c, 0xe73c, 0xef5d, 0xe73c, 0xdefb,
0xdefb, 0xc638, 0x630c, 0x0841, 0x0000, 
0x0000, 0x18c3, 0xa534, 0xd69a, 0xdefb, 0xf79e, 0xffff, 0xffff, 0xffff, 0xffff,
0xef7d, 0xe73c, 0xd6ba, 0x7bef, 0x0841, 
0x0020, 0x8c51, 0xd69a, 0xd6ba, 0xf7bd, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xf7be, 0xd6da, 0xd6ba, 0x5289, 
0x2965, 0xd6ba, 0xce58, 0xd6da, 0xe75c, 0xef9d, 0xf7bd, 0xf7be, 0xf7de, 0xf7de,
0xfffe, 0xef7c, 0xdefb, 0xdeda, 0xbdd6, 
0x6b8d, 0xd6ba, 0xc658, 0xd6da, 0xdefa, 0xd6ba, 0xceb9, 0xd6da, 0xd6da, 0xd6da,
0xdf1b, 0xdf3b, 0xdefa, 0xce99, 0xe71b, 
0xa534, 0xce79, 0xc658, 0xd6da, 0xd6ba, 0xc658, 0xa554, 0x94f2, 0x94b2, 0xb5b6,
0xdefa, 0xdf1b, 0xd6fa, 0xce79, 0xdefb, 
0xad54, 0xd6b9, 0xce79, 0xd6b9, 0xce99, 0xc658, 0x94d2, 0x31c6, 0x39e6, 0xbdf6,
0xe73b, 0xdf1b, 0xd6da, 0xce99, 0xdefb, 
0xad54, 0xd6da, 0xce99, 0xce99, 0xc658, 0xbe17, 0x94b2, 0x0881, 0x0861, 0xb5d6,
0xdf3b, 0xdf1b, 0xd6da, 0xc658, 0xd6ba, 
0x7bef, 0xdefa, 0xce99, 0xc658, 0xbe37, 0xadb5, 0x9cf2, 0x73ae, 0x7bef, 0xc658,
0xdefb, 0xdefb, 0xd6b9, 0xc658, 0xce99, 
0x39e7, 0xd6da, 0xd6ba, 0xc658, 0xb5d6, 0x9d13, 0xce99, 0xef9d, 0xf7fe, 0xef7d,
0xce99, 0xd6ba, 0xce79, 0xc658, 0xad95, 
0x0000, 0x8c51, 0xd6da, 0xce99, 0xb5d6, 0xc658, 0xef9d, 0xefbd, 0xfffe, 0xf7de,
0xd6da, 0xc658, 0xc658, 0xce59, 0x4a69, 
0x0000, 0x2104, 0xad54, 0xce99, 0xce79, 0xd6ba, 0xe73c, 0xef7c, 0xe75c, 0xdf1b,
0xd6ba, 0xc658, 0xce59, 0x8410, 0x0861, 
0x0000, 0x0000, 0x18e3, 0x94b2, 0xc658, 0xce79, 0xce99, 0xd6ba, 0xceb9, 0xce99,
0xce99, 0xce99, 0x8410, 0x1082, 0x0000, 
0x0000, 0x0000, 0x0000, 0x0841, 0x632c, 0xad75, 0xbe17, 0xc638, 0xc658, 0xce79,
0xad75, 0x4a69, 0x0841, 0x0000, 0x0000, 

};

const struct bitmap bm_brickmania_ball = { 
    .width = BMPWIDTH_brickmania_ball, 
    .height = BMPHEIGHT_brickmania_ball, 
    .format = FORMAT_NATIVE, 
    .data = (unsigned char*)brickmania_ball,
};