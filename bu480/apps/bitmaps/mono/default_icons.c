#include "lcd.h"
#include "/home/ubuntu/Desktop/RockboxRCC/bu480/bitmaps/default_icons.h"
const unsigned char default_icons[] = {
0x60, 0x7f, 0x03, 0x33, 0x3f, 0x00, 
0x7e, 0x41, 0x41, 0x42, 0x7e, 0x00, 
0x55, 0x00, 0x55, 0x55, 0x55, 0x55, 
0x3e, 0x1c, 0x08, 0x00, 0x00, 0x00, 
0x58, 0x5f, 0x42, 0x50, 0x55, 0x55, 
0x63, 0x7f, 0x3a, 0x7f, 0x63, 0x00, 
0x60, 0x70, 0x38, 0x2c, 0x7e, 0x7e, 
0x3e, 0x2a, 0x3e, 0x2a, 0x2a, 0x3e, 
0x4e, 0x51, 0x51, 0x40, 0x55, 0x55, 
0x0a, 0x0a, 0x5f, 0x4e, 0x24, 0x18, 
0x7f, 0x41, 0x4f, 0x4a, 0x4c, 0x78, 
0x5f, 0x45, 0x5b, 0x40, 0x55, 0x55, 
0x77, 0x55, 0x55, 0x55, 0x55, 0x77, 
0x3e, 0x41, 0x3e, 0x1c, 0x1c, 0x08, 
0x7f, 0x7f, 0x1c, 0x3e, 0x77, 0x63, 
0x00, 0x00, 0x00, 0x08, 0x1c, 0x3e, 
0x06, 0x03, 0x5b, 0x5b, 0x0f, 0x06, 
0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 
0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 
0x18, 0x18, 0x7e, 0x7e, 0x18, 0x18, 
0x01, 0x55, 0x01, 0x55, 0x54, 0x54, 
0x1c, 0x3e, 0x7f, 0x7f, 0x3e, 0x1c, 
0x1c, 0x1c, 0x22, 0x41, 0x7f, 0x00, 
0x06, 0x0f, 0x78, 0x78, 0x0f, 0x06, 
0x1e, 0x22, 0x49, 0x49, 0x22, 0x1e, 
0x7f, 0x7f, 0x3e, 0x1c, 0x08, 0x00, 
0x1f, 0x51, 0x71, 0x71, 0x51, 0x1f, 
0x1e, 0x32, 0x32, 0x32, 0x1e, 0x00, 
0x03, 0x05, 0x7f, 0x05, 0x03, 0x00, 
0x1f, 0x11, 0x7d, 0x46, 0x44, 0x78, 
0x06, 0x7f, 0x06, 0x18, 0x7f, 0x18, 
0x20, 0x70, 0x70, 0x3f, 0x0a, 0x0a, 

};

const struct bitmap bm_default_icons = { 
    .width = BMPWIDTH_default_icons, 
    .height = BMPHEIGHT_default_icons, 
    .data = (unsigned char*)default_icons,
};
