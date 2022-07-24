/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef OPENSANSB16PX
#define OPENSANSB16PX 1
#endif

#if OPENSANSB16PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xf,

    /* U+0022 "\"" */
    0xdb, 0x6c, 0xb2,

    /* U+0023 "#" */
    0x9, 0x6, 0x41, 0xb0, 0x6c, 0x7f, 0xdf, 0xf1,
    0x23, 0xfe, 0xff, 0x8d, 0x83, 0x60, 0x90,

    /* U+0024 "$" */
    0x10, 0x3e, 0xff, 0xd0, 0xf0, 0x78, 0x3e, 0x17,
    0x93, 0xff, 0xfc, 0x10, 0x10,

    /* U+0025 "%" */
    0x70, 0x47, 0xc6, 0x36, 0x21, 0xb3, 0xd, 0xb0,
    0x6d, 0xbb, 0xfb, 0xee, 0xdb, 0xc, 0xd8, 0x46,
    0xc6, 0x3e, 0x20, 0xe0,

    /* U+0026 "&" */
    0x3c, 0xf, 0xc1, 0x98, 0x33, 0x7, 0xe0, 0x78,
    0x1e, 0x37, 0x6e, 0xc7, 0x98, 0x73, 0xfe, 0x1e,
    0xe0,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x36, 0x6e, 0xcc, 0xcc, 0xcc, 0xc6, 0x63,

    /* U+0029 ")" */
    0xc6, 0x67, 0x33, 0x33, 0x33, 0x76, 0x6c,

    /* U+002A "*" */
    0x18, 0x8, 0x6b, 0x7f, 0x1c, 0x36, 0x76,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0x76, 0x64,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x18, 0x70, 0xc1, 0x87, 0xc, 0x18, 0x70,
    0xc1, 0x86, 0x0,

    /* U+0030 "0" */
    0x3c, 0x7e, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x67, 0x7e, 0x3c,

    /* U+0031 "1" */
    0x19, 0xff, 0xb1, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+0032 "2" */
    0x7c, 0xfe, 0x46, 0x6, 0x6, 0xc, 0x1c, 0x18,
    0x30, 0x60, 0xff, 0xff,

    /* U+0033 "3" */
    0x3e, 0x7f, 0x43, 0x3, 0x7, 0x3e, 0x3e, 0x3,
    0x3, 0x83, 0xfe, 0x7c,

    /* U+0034 "4" */
    0x6, 0x7, 0x3, 0x83, 0xc3, 0x61, 0xb1, 0x99,
    0xcc, 0xff, 0xff, 0xc1, 0x80, 0xc0,

    /* U+0035 "5" */
    0x7c, 0xfb, 0x87, 0xf, 0xdf, 0x83, 0x83, 0x7,
    0x1f, 0xf7, 0xc0,

    /* U+0036 "6" */
    0x1e, 0x3e, 0x60, 0xc0, 0xde, 0xfe, 0xe7, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0x7, 0x6, 0xe, 0xc, 0xc, 0x1c,
    0x18, 0x38, 0x30, 0x30,

    /* U+0038 "8" */
    0x3c, 0xff, 0xc3, 0xc3, 0x76, 0x3c, 0x7e, 0xe7,
    0xc3, 0xc3, 0xfe, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0x7f, 0x7b,
    0x3, 0x6, 0x7c, 0x78,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0xf0, 0xf, 0xa0,

    /* U+003C "<" */
    0x1, 0x7, 0x1c, 0x70, 0xe0, 0x7c, 0xf, 0x3,

    /* U+003D "=" */
    0xff, 0xff, 0x0, 0xff, 0xff,

    /* U+003E ">" */
    0x80, 0xe0, 0x38, 0xe, 0x7, 0x1e, 0xf0, 0xc0,

    /* U+003F "?" */
    0x7d, 0xfd, 0x18, 0x30, 0xe3, 0x8e, 0x18, 0x30,
    0x0, 0xc1, 0x80,

    /* U+0040 "@" */
    0xf, 0xc0, 0xff, 0xe, 0x1c, 0xcf, 0xee, 0xfd,
    0xee, 0x6f, 0x63, 0x7b, 0x1b, 0xd8, 0xde, 0xff,
    0x9b, 0xdc, 0xe0, 0x3, 0xfc, 0x7, 0xc0,

    /* U+0041 "A" */
    0xe, 0x1, 0xe0, 0x6c, 0xd, 0x81, 0xb8, 0x73,
    0xc, 0x61, 0xfe, 0x7f, 0xcc, 0x1b, 0x83, 0xf0,
    0x70,

    /* U+0042 "B" */
    0xfc, 0xff, 0xc3, 0xc3, 0xc3, 0xfe, 0xfe, 0xc3,
    0xc3, 0xc3, 0xfe, 0xfc,

    /* U+0043 "C" */
    0x1f, 0x1f, 0xd8, 0x5c, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc0, 0x30, 0x5f, 0xe3, 0xe0,

    /* U+0044 "D" */
    0xfc, 0x7f, 0x31, 0xd8, 0x7c, 0x1e, 0xf, 0x7,
    0x83, 0xc3, 0xe3, 0xbf, 0x9f, 0x80,

    /* U+0045 "E" */
    0xff, 0xff, 0x6, 0xc, 0x1f, 0xff, 0xe0, 0xc1,
    0x83, 0xff, 0xf0,

    /* U+0046 "F" */
    0xff, 0xff, 0x6, 0xc, 0x1f, 0xff, 0xe0, 0xc1,
    0x83, 0x6, 0x0,

    /* U+0047 "G" */
    0x1f, 0x1f, 0xdc, 0x1c, 0xc, 0x6, 0x3f, 0x1f,
    0x83, 0xe1, 0xb0, 0xdf, 0xe3, 0xe0,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0xff,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0xfb, 0xc0,

    /* U+004B "K" */
    0xc3, 0x63, 0xb3, 0x9b, 0x8d, 0x87, 0xc3, 0xe1,
    0xb8, 0xce, 0x63, 0x31, 0xd8, 0x60,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0xff, 0xf0,

    /* U+004D "M" */
    0xe0, 0x7f, 0xf, 0xf0, 0xff, 0xf, 0xd9, 0xbd,
    0x9b, 0xd9, 0xbd, 0x93, 0xcf, 0x3c, 0xf3, 0xce,
    0x3c, 0x63,

    /* U+004E "N" */
    0xe0, 0xfc, 0x3f, 0xf, 0xe3, 0xdc, 0xf7, 0x3c,
    0xef, 0x1b, 0xc7, 0xf0, 0xfc, 0x3f, 0x7,

    /* U+004F "O" */
    0x1f, 0xf, 0xf9, 0xc7, 0x70, 0x7c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xe0, 0xec, 0x19, 0xff, 0xf,
    0x80,

    /* U+0050 "P" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xfc,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1f, 0xf, 0xf9, 0xc7, 0x70, 0x7c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xe0, 0xec, 0x19, 0xff, 0xf,
    0xc0, 0x38, 0x3, 0x80, 0x38,

    /* U+0052 "R" */
    0xfc, 0x7f, 0x31, 0xd8, 0x6c, 0x36, 0x3b, 0xf9,
    0xf8, 0xce, 0x63, 0xb0, 0xd8, 0x70,

    /* U+0053 "S" */
    0x3d, 0xff, 0x6, 0xe, 0xf, 0xf, 0x7, 0x7,
    0xf, 0xf7, 0xc0,

    /* U+0054 "T" */
    0xff, 0xff, 0xc6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x0,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xf1, 0xdf, 0xc7, 0xc0,

    /* U+0056 "V" */
    0xe0, 0xf8, 0x76, 0x1d, 0xc6, 0x71, 0x8c, 0xe3,
    0x30, 0xec, 0x1f, 0x7, 0x81, 0xe0, 0x38,

    /* U+0057 "W" */
    0xe3, 0x87, 0xc7, 0xd, 0x8f, 0x1b, 0x1e, 0x76,
    0x6c, 0xce, 0xd9, 0x8d, 0xb3, 0x1b, 0x3e, 0x36,
    0x78, 0x78, 0xf0, 0x71, 0xe0, 0xe1, 0xc0,

    /* U+0058 "X" */
    0x61, 0xce, 0x38, 0xce, 0x1d, 0x81, 0xf0, 0x1c,
    0x7, 0x80, 0xf8, 0x3b, 0x6, 0x71, 0x87, 0x70,
    0x60,

    /* U+0059 "Y" */
    0xe1, 0xdc, 0xe7, 0x30, 0xcc, 0x3e, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+005A "Z" */
    0xff, 0xff, 0x6, 0xe, 0xc, 0x1c, 0x38, 0x30,
    0x70, 0x60, 0xff, 0xff,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf, 0xf0,

    /* U+005C "\\" */
    0xc0, 0xc1, 0x83, 0x83, 0x6, 0xe, 0xc, 0x18,
    0x38, 0x30, 0x60,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f, 0xf0,

    /* U+005E "^" */
    0x18, 0x18, 0x1c, 0x3c, 0x26, 0x66, 0x63, 0xc3,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xe3, 0x86,

    /* U+0061 "a" */
    0x3e, 0x7f, 0x3, 0x7f, 0xff, 0xc3, 0xc7, 0xff,
    0x7b,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe7, 0xc3, 0xc3,
    0xc3, 0xe7, 0xfe, 0xdc,

    /* U+0063 "c" */
    0x3c, 0xfb, 0x86, 0xc, 0x18, 0x38, 0xbf, 0x3c,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3b, 0x7f, 0xe7, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7f, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x7e, 0xc3, 0xff, 0xff, 0xc0, 0xe1, 0x7f,
    0x3e,

    /* U+0066 "f" */
    0x1e, 0x78, 0xc3, 0xef, 0xc6, 0xc, 0x18, 0x30,
    0x60, 0xc1, 0x80,

    /* U+0067 "g" */
    0x3f, 0xbf, 0xd8, 0xcc, 0x67, 0xf1, 0xf1, 0x80,
    0xfe, 0x7f, 0xe0, 0xf0, 0xff, 0xe7, 0xe0,

    /* U+0068 "h" */
    0xc0, 0xc0, 0xc0, 0xde, 0xff, 0xe3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006A "j" */
    0x18, 0xc0, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8f, 0xfe,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc7, 0xce, 0xdc, 0xf8, 0xf8,
    0xfc, 0xcc, 0xce, 0xc7,

    /* U+006C "l" */
    0xff, 0xff, 0xff,

    /* U+006D "m" */
    0xde, 0x7b, 0xfb, 0xfe, 0x38, 0xf0, 0xc3, 0xc3,
    0xf, 0xc, 0x3c, 0x30, 0xf0, 0xc3, 0xc3, 0xc,

    /* U+006E "n" */
    0xde, 0xff, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0070 "p" */
    0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0xfe,
    0xdc, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3b, 0x7f, 0xe7, 0xc3, 0xc3, 0xc3, 0xe3, 0x7f,
    0x3b, 0x3, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0xf9, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7b, 0xfc, 0x38, 0x78, 0x70, 0xff, 0xf8,

    /* U+0074 "t" */
    0x21, 0x8f, 0xff, 0x61, 0x86, 0x18, 0x61, 0xf3,
    0xc0,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xff,
    0x7b,

    /* U+0076 "v" */
    0xe3, 0xb1, 0xd8, 0xce, 0xe3, 0x61, 0xb0, 0xd8,
    0x38, 0x1c, 0x0,

    /* U+0077 "w" */
    0xe7, 0x19, 0x9e, 0x66, 0x79, 0x99, 0x6e, 0x7d,
    0xb0, 0xf2, 0xc3, 0xcf, 0xf, 0x38, 0x38, 0xe0,

    /* U+0078 "x" */
    0x63, 0xbb, 0x8d, 0x87, 0xc1, 0xc1, 0xf0, 0xdc,
    0xe6, 0xe3, 0x80,

    /* U+0079 "y" */
    0x61, 0x9c, 0x67, 0x38, 0xcc, 0x3b, 0x7, 0xc1,
    0xe0, 0x78, 0xc, 0x3, 0x1, 0xc1, 0xe0, 0x70,
    0x0,

    /* U+007A "z" */
    0xff, 0xfc, 0x30, 0xe3, 0x8e, 0x18, 0x7f, 0xfe,

    /* U+007B "{" */
    0x1c, 0xf3, 0xc, 0x30, 0xce, 0x38, 0x30, 0xc3,
    0xc, 0x3c, 0x70,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xe3, 0xc3, 0xc, 0x30, 0xc1, 0xc7, 0x30, 0xc3,
    0xc, 0xf3, 0x80,

    /* U+007E "~" */
    0xf1, 0xff, 0x8f,

    /* U+00B0 "°" */
    0x7b, 0xfc, 0xf3, 0xfd, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 67, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 73, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 121, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 7, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 22, .adv_w = 146, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 35, .adv_w = 231, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 192, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 68, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 73, .adv_w = 87, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 80, .adv_w = 87, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 87, .adv_w = 140, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 94, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 102, .adv_w = 74, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 104, .adv_w = 82, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 105, .adv_w = 73, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 106, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 146, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 73, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 74, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 240, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 248, .adv_w = 146, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 253, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 261, .adv_w = 122, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 230, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 295, .adv_w = 177, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 172, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 163, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 190, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 143, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 196, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 85, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 85, .box_w = 5, .box_h = 15, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 415, .adv_w = 170, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 145, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 241, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 208, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 204, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 204, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 523, .adv_w = 169, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 194, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 166, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 248, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 160, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 658, .adv_w = 85, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 666, .adv_w = 106, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 85, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 685, .adv_w = 136, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 693, .adv_w = 105, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 694, .adv_w = 155, .box_w = 5, .box_h = 3, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 696, .adv_w = 155, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 162, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 162, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 99, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 145, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 772, .adv_w = 168, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 78, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 787, .adv_w = 78, .box_w = 5, .box_h = 16, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 797, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 78, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 251, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 168, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 159, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 846, .adv_w = 162, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 859, .adv_w = 162, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 872, .adv_w = 116, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 878, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 894, .adv_w = 168, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 903, .adv_w = 146, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 219, .box_w = 14, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 930, .adv_w = 148, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 941, .adv_w = 146, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 958, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 966, .adv_w = 101, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 977, .adv_w = 141, .box_w = 2, .box_h = 16, .ofs_x = 4, .ofs_y = -4},
    {.bitmap_index = 981, .adv_w = 101, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 992, .adv_w = 146, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 995, .adv_w = 110, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 6}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 1, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t opensansb16px = {
#else
lv_font_t opensansb16px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if OPENSANSB16PX*/

