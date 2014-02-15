#include "lcd.h"
#include "/home/ubuntu/Desktop/RockboxRCC/bu480/pluginbitmaps/sokoban_tiles.h"
const unsigned short sokoban_tiles[] = {
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49,
0x4a49, 0x4a49, 0x4a49, 0x4a49, 
0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef,
0x7bef, 0x4a49, 0x7bef, 0x7bef, 
0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef,
0x7bef, 0x4a49, 0x7bef, 0x7bef, 
0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49,
0x4a49, 0x4a49, 0x4a49, 0x4a49, 
0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49,
0x7bef, 0x7bef, 0x7bef, 0x7bef, 
0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49,
0x4a49, 0x4a49, 0x4a49, 0x4a49, 
0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49,
0x7bef, 0x7bef, 0x7bef, 0x4a49, 
0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef,
0x7bef, 0x7bef, 0x7bef, 0x4a49, 
0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49,
0x4a49, 0x4a49, 0x4a49, 0x4a49, 
0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef,
0x7bef, 0x4a49, 0x7bef, 0x7bef, 
0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef,
0x7bef, 0x4a49, 0x7bef, 0x7bef, 
0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49, 0x4a49,
0x4a49, 0x4a49, 0x4a49, 0x4a49, 
0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef,
0x7bef, 0x7bef, 0x7bef, 0x4a49, 
0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef, 0x7bef, 0x7bef, 0x7bef, 0x4a49, 0x7bef,
0x7bef, 0x7bef, 0x7bef, 0x4a49, 
0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539,
0x9539, 0x9539, 0x9539, 0x9539, 
0x9539, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373,
0x5373, 0x5373, 0x5373, 0x9539, 
0x9539, 0x5373, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c,
0xb63c, 0xb63c, 0x5373, 0x9539, 
0x9539, 0x5373, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539,
0x9539, 0x9539, 0x5373, 0x9539, 
0x9539, 0x5373, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c,
0xb63c, 0xb63c, 0x5373, 0x9539, 
0x9539, 0x5373, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0x9539, 0x9539, 0x9539,
0x9539, 0x9539, 0x5373, 0x9539, 
0x9539, 0x5373, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0xb63c, 0xb63c, 0xb63c,
0xb63c, 0xb63c, 0x5373, 0x9539, 
0x9539, 0x5373, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c,
0xb63c, 0xb63c, 0x5373, 0x9539, 
0x9539, 0x5373, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539,
0x9539, 0x9539, 0x5373, 0x9539, 
0x9539, 0x5373, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c,
0xb63c, 0xb63c, 0x5373, 0x9539, 
0x9539, 0x5373, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539,
0x9539, 0x9539, 0x5373, 0x9539, 
0x9539, 0x5373, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c, 0xb63c,
0xb63c, 0xb63c, 0x5373, 0x9539, 
0x9539, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373, 0x5373,
0x5373, 0x5373, 0x5373, 0x9539, 
0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539,
0x9539, 0x9539, 0x9539, 0x9539, 
0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539,
0x9539, 0x9539, 0x9539, 0x9539, 
0x9539, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349,
0x8349, 0x8349, 0x8349, 0x9539, 
0x9539, 0x8349, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25,
0xcc25, 0xcc25, 0x8349, 0x9539, 
0x9539, 0x8349, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382,
0xb382, 0xb382, 0x8349, 0x9539, 
0x9539, 0x8349, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25,
0xcc25, 0xcc25, 0x8349, 0x9539, 
0x9539, 0x8349, 0xcc25, 0xcc25, 0xcc25, 0xc3e4, 0xab42, 0xb382, 0xb382, 0xb382,
0xb382, 0xb382, 0x8349, 0x9539, 
0x9539, 0x8349, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382, 0xab42, 0xb382, 0xcc25,
0xcc25, 0xcc25, 0x8349, 0x9539, 
0x9539, 0x8349, 0xcc25, 0xcc25, 0xcc25, 0xb382, 0xab42, 0xab42, 0xbba3, 0xcc25,
0xcc25, 0xcc25, 0x8349, 0x9539, 
0x9539, 0x8349, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382, 0xab42, 0xb382, 0xb382,
0xb382, 0xb382, 0x8349, 0x9539, 
0x9539, 0x8349, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25,
0xcc25, 0xcc25, 0x8349, 0x9539, 
0x9539, 0x8349, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382, 0xb382,
0xb382, 0xb382, 0x8349, 0x9539, 
0x9539, 0x8349, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25, 0xcc25,
0xcc25, 0xcc25, 0x8349, 0x9539, 
0x9539, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349, 0x8349,
0x8349, 0x8349, 0x8349, 0x9539, 
0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539, 0x9539,
0x9539, 0x9539, 0x9539, 0x9539, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xff76, 0xfeab, 0xfe44, 0xfe44, 0xfeab, 0xff76,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xff11, 0xfe00, 0xfe00, 0xfe00, 0xfe00, 0xfe00, 0xfe00,
0xff11, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xff76, 0xfe00, 0xfe00, 0xfe00, 0xe580, 0xe580, 0xfe00, 0xfe00,
0xfe00, 0xff76, 0xffff, 0xffff, 
0xffff, 0xffff, 0xfeab, 0xfe00, 0xfe00, 0xdd61, 0x4a49, 0xbca3, 0xdd41, 0xfe00,
0xfe00, 0xfeab, 0xffff, 0xffff, 
0xffff, 0xffff, 0xfe44, 0xfe00, 0xe580, 0xbca3, 0x7326, 0x4a49, 0x9c04, 0xe580,
0xfe00, 0xfe44, 0xffff, 0xffff, 
0xffff, 0xffff, 0xfe44, 0xfe00, 0xe580, 0xbca3, 0x4a49, 0x4a68, 0xbca3, 0xe580,
0xfe00, 0xfe44, 0xffff, 0xffff, 
0xffff, 0xffff, 0xfeab, 0xfe00, 0xfe00, 0xdd41, 0xbca3, 0x5aa7, 0xdd41, 0xfe00,
0xfe00, 0xfeab, 0xffff, 0xffff, 
0xffff, 0xffff, 0xff76, 0xfe00, 0xfe00, 0xfe00, 0xe580, 0xe580, 0xfe00, 0xfe00,
0xfe00, 0xff76, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xff11, 0xfe00, 0xfe00, 0xfe00, 0xfe00, 0xfe00, 0xfe00,
0xff11, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xff76, 0xfeab, 0xfe44, 0xfe44, 0xfeab, 0xff76,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffbe, 0xddb3, 0xbc06, 0x9202, 0xd593, 0xffdf,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xf79d, 0xbc06, 0x9202, 0x9202, 0x9202, 0xf79d,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xf77d, 0x9a84, 0xfe93, 0xfe93, 0x9a84, 0xf73c,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffde, 0xb40c, 0xfe93, 0xfe93, 0xb40c, 0xffbe,
0xffff, 0xffff, 0xffff, 0xffff, 
0xfe93, 0xff5b, 0xffff, 0xffbe, 0xff3c, 0xfe99, 0xfe93, 0xfe93, 0xfe99, 0xff3c,
0xffbe, 0xffff, 0xff5b, 0xfe93, 
0xfe93, 0xf920, 0xf800, 0xf820, 0xf840, 0x0000, 0xf020, 0xf020, 0x0000, 0xf840,
0xf820, 0xf800, 0xf920, 0xfe93, 
0xffff, 0xffff, 0xfe9a, 0xfcf3, 0xfaeb, 0xf020, 0x0000, 0x0000, 0xf020, 0xfaeb,
0xfcf3, 0xfe9a, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xfe38, 0xf820, 0x0000, 0x0000, 0xf820, 0xfe38,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xfdf7, 0xc861, 0x0000, 0x0000, 0xc861, 0xfdf7,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xa534, 0x0000, 0x0000, 0x0000, 0x0000, 0x9cf3,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xf79e, 0x4a69, 0x0000, 0x0000, 0x0000, 0x0000, 0x4a69,
0xf79e, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xc618, 0x0861, 0x10a2, 0x738e, 0x738e, 0x10a2, 0x0861,
0xc618, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xf79e, 0xa514, 0x0000, 0x4a69, 0xffff, 0xffff, 0x4a69, 0x0000,
0xa514, 0xf79e, 0xffff, 0xffff, 
0xffff, 0xf7be, 0x8410, 0x0000, 0x0841, 0x738e, 0xffff, 0xffff, 0x738e, 0x0841,
0x0000, 0x8410, 0xf7be, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xffbe, 0xddb3, 0xbc06, 0x9202, 0xd593, 0xffdf,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xf79d, 0xbc06, 0x9202, 0x9202, 0x9202, 0xf79d,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xffff, 0xf6f5, 0x9a61, 0xfe93, 0xfe93, 0x9a61, 0xf6f5,
0xffff, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xff11, 0xed80, 0xb341, 0xfe93, 0xfe93, 0xb341, 0xed60,
0xff11, 0xffff, 0xffff, 0xffff, 
0xfe93, 0xff5b, 0xff76, 0xfdc0, 0xfd60, 0xfce0, 0xfe93, 0xfe93, 0xfce0, 0xfd60,
0xfdc0, 0xff76, 0xff5b, 0xfe93, 
0xfe93, 0xf920, 0xf800, 0xf820, 0xf840, 0x0000, 0xf020, 0xf020, 0x0000, 0xf840,
0xf820, 0xf800, 0xf920, 0xfe93, 
0xffff, 0xffff, 0xfd23, 0xfbc0, 0xf200, 0xf020, 0x0000, 0x0000, 0xf020, 0xf200,
0xfbc0, 0xfd23, 0xffff, 0xffff, 
0xffff, 0xffff, 0xfe44, 0xfe00, 0xec40, 0xf820, 0x0000, 0x0000, 0xf820, 0xec40,
0xfe00, 0xfe44, 0xffff, 0xffff, 
0xffff, 0xffff, 0xfeab, 0xfe00, 0xfc80, 0xb841, 0x0000, 0x0000, 0xb841, 0xfc80,
0xfe00, 0xfeab, 0xffff, 0xffff, 
0xffff, 0xffff, 0xff76, 0xfe00, 0x9ba0, 0x0000, 0x0000, 0x0000, 0x0000, 0x9ba0,
0xfe00, 0xff76, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xe66f, 0x4a69, 0x0000, 0x0000, 0x0000, 0x0000, 0x4a69,
0xe66f, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xffff, 0xc618, 0x0861, 0x10a2, 0x7b01, 0x7b01, 0x10a2, 0x0861,
0xc618, 0xffff, 0xffff, 0xffff, 
0xffff, 0xffff, 0xf79e, 0xa514, 0x0000, 0x4a69, 0xffff, 0xffff, 0x4a69, 0x0000,
0xa514, 0xf79e, 0xffff, 0xffff, 
0xffff, 0xf7be, 0x8410, 0x0000, 0x0841, 0x738e, 0xffff, 0xffff, 0x738e, 0x0841,
0x0000, 0x8410, 0xf7be, 0xffff, 

};

const struct bitmap bm_sokoban_tiles = { 
    .width = BMPWIDTH_sokoban_tiles, 
    .height = BMPHEIGHT_sokoban_tiles, 
    .format = FORMAT_NATIVE, 
    .data = (unsigned char*)sokoban_tiles,
};
