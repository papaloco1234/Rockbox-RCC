#include "lcd.h"
#include "/home/ubuntu/Desktop/RockboxRCC/bu800/pluginbitmaps/fft_colors.h"
const unsigned short fft_colors[] = {
0x0002, 0x0003, 0x0003, 0x0003, 0x0004, 0x0004, 0x0004, 0x0005, 0x0005, 0x0005,
0x0006, 0x0006, 0x0006, 0x0006, 0x0007, 0x0007, 0x0007, 0x0007, 0x0008, 0x0008,
0x0008, 0x0008, 0x0009, 0x0009, 0x0009, 0x000a, 0x000a, 0x080a, 0x080a, 0x080a,
0x080b, 0x080b, 0x080b, 0x100b, 0x100c, 0x100c, 0x180c, 0x180c, 0x180c, 0x200c,
0x200d, 0x280d, 0x280d, 0x280d, 0x280d, 0x300d, 0x300e, 0x300e, 0x380e, 0x380e,
0x380e, 0x400e, 0x400e, 0x400e, 0x400f, 0x480f, 0x480f, 0x500f, 0x500f, 0x500f,
0x580f, 0x580f, 0x580f, 0x580f, 0x600f, 0x600f, 0x600f, 0x600f, 0x600f, 0x680f,
0x680f, 0x700f, 0x700f, 0x700f, 0x700f, 0x780f, 0x780f, 0x780f, 0x800f, 0x800f,
0x800f, 0x800f, 0x880f, 0x880f, 0x880f, 0x880f, 0x880f, 0x900e, 0x900e, 0x900e,
0x980e, 0x980e, 0x980e, 0x980e, 0xa00d, 0xa00d, 0xa00d, 0xa00d, 0xa80d, 0xa80d,
0xa80d, 0xa80d, 0xa80c, 0xb00c, 0xb00c, 0xb00c, 0xb00b, 0xb80b, 0xb80b, 0xb80b,
0xb80b, 0xb80a, 0xb80a, 0xc00a, 0xc00a, 0xc00a, 0xc009, 0xc009, 0xc809, 0xc808,
0xc808, 0xc808, 0xd007, 0xd007, 0xd007, 0xd007, 0xd006, 0xd006, 0xd806, 0xd806,
0xd805, 0xd805, 0xd805, 0xd805, 0xd804, 0xe004, 0xe003, 0xe003, 0xe003, 0xe002,
0xe002, 0xe002, 0xe802, 0xe802, 0xe801, 0xe801, 0xe801, 0xe800, 0xe800, 0xe800,
0xe800, 0xf020, 0xf060, 0xf080, 0xf0a0, 0xf0e0, 0xf0e0, 0xf100, 0xf140, 0xf160,
0xf180, 0xf1a0, 0xf9e0, 0xfa00, 0xfa20, 0xfa40, 0xfa60, 0xfaa0, 0xfac0, 0xfae0,
0xfb20, 0xfb40, 0xfb60, 0xfb60, 0xfba0, 0xfbc0, 0xfbe0, 0xfc00, 0xfc20, 0xfc40,
0xfc40, 0xfc40, 0xfc80, 0xfca0, 0xfcc0, 0xfce0, 0xfd20, 0xfd20, 0xfd40, 0xfd60,
0xfd80, 0xfda0, 0xfda0, 0xfdc0, 0xfde0, 0xfe00, 0xfe00, 0xfe20, 0xfe40, 0xfe61,
0xfe81, 0xfea2, 0xfec2, 0xfec3, 0xfee3, 0xfee4, 0xff05, 0xff25, 0xff25, 0xff26,
0xff47, 0xff47, 0xff67, 0xff68, 0xff89, 0xff8a, 0xffaa, 0xffab, 0xffab, 0xffab,
0xffcc, 0xffcc, 0xffcd, 0xffcd, 0xffce, 0xffce, 0xffef, 0xffef, 0xfff0, 0xfff0,
0xfff1, 0xfff2, 0xfff3, 0xfff3, 0xfff4, 0xfff4, 0xfff5, 0xfff5, 0xfff6, 0xfff6,
0xfff7, 0xfff7, 0xfff8, 0xfff8, 0xfff9, 0xfff9, 0xfffa, 0xfffb, 0xfffc, 0xfffc,
0xfffd, 0xfffd, 0xfffe, 0xfffe, 0xffff, 0xffff, 

};

const struct bitmap bm_fft_colors = { 
    .width = BMPWIDTH_fft_colors, 
    .height = BMPHEIGHT_fft_colors, 
    .format = FORMAT_NATIVE, 
    .data = (unsigned char*)fft_colors,
};