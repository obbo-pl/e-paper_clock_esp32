/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef OPENSANSB20PX
#define OPENSANSB20PX 1
#endif

#if OPENSANSB20PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xff, 0xe0, 0x7f, 0xc0,

    /* U+0022 "\"" */
    0xef, 0xcf, 0x9b, 0x36, 0x60,

    /* U+0023 "#" */
    0xc, 0xc0, 0xcc, 0xc, 0xc0, 0xcc, 0x7f, 0xf7,
    0xff, 0x19, 0x81, 0x98, 0xff, 0xef, 0xfe, 0x33,
    0x3, 0x30, 0x33, 0x3, 0x30,

    /* U+0024 "$" */
    0x8, 0x2, 0x7, 0xff, 0xfe, 0xe8, 0xba, 0xf,
    0x81, 0xf8, 0x1f, 0x83, 0xf0, 0x9e, 0x27, 0xff,
    0x9f, 0xc0, 0x80, 0x20,

    /* U+0025 "%" */
    0x38, 0x18, 0x3e, 0xc, 0x3b, 0x8c, 0x1d, 0xce,
    0xe, 0xe6, 0x7, 0x76, 0x73, 0xbb, 0x7c, 0xfb,
    0x77, 0x39, 0xbb, 0x81, 0x9d, 0xc1, 0xce, 0xe0,
    0xc7, 0x70, 0xc1, 0xf0, 0x60, 0x70,

    /* U+0026 "&" */
    0x1f, 0x0, 0x7f, 0x1, 0xc7, 0x3, 0x8e, 0x7,
    0x3c, 0x7, 0xf0, 0xf, 0xc0, 0x3f, 0xe, 0xff,
    0x1d, 0xc7, 0xf3, 0x87, 0xe7, 0x87, 0x87, 0xff,
    0x87, 0xf3, 0x80,

    /* U+0027 "'" */
    0xff, 0xb6,

    /* U+0028 "(" */
    0x18, 0xe7, 0x1c, 0x73, 0x8e, 0x38, 0xe3, 0x8e,
    0x38, 0x71, 0xc7, 0xe, 0x18,

    /* U+0029 ")" */
    0x61, 0xc3, 0xe, 0x38, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x38, 0xe3, 0x9c, 0x60,

    /* U+002A "*" */
    0x1c, 0xe, 0x6, 0x1f, 0xff, 0xf8, 0xe0, 0xd8,
    0xee, 0x22, 0x0,

    /* U+002B "+" */
    0xc, 0x3, 0x0, 0xc3, 0xff, 0xff, 0xc3, 0x0,
    0xc0, 0x30, 0xc, 0x0,

    /* U+002C "," */
    0x7f, 0xec,

    /* U+002D "-" */
    0xff, 0xc0,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x7, 0x7, 0xe, 0xe, 0xc, 0x1c, 0x1c, 0x18,
    0x38, 0x38, 0x70, 0x70, 0x60, 0xe0,

    /* U+0030 "0" */
    0x1e, 0x1f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1d, 0xce, 0x7f,
    0x87, 0x80,

    /* U+0031 "1" */
    0xe, 0x3d, 0xff, 0xf4, 0xe1, 0xc3, 0x87, 0xe,
    0x1c, 0x38, 0x70, 0xe1, 0xc0,

    /* U+0032 "2" */
    0x3f, 0x3f, 0xe6, 0x1c, 0x7, 0x1, 0xc0, 0xf0,
    0x38, 0x1e, 0xf, 0x7, 0x83, 0xc1, 0xe0, 0xff,
    0xff, 0xf0,

    /* U+0033 "3" */
    0x3f, 0x1f, 0xe6, 0x3c, 0x7, 0x1, 0xc0, 0xe1,
    0xf0, 0x7e, 0x3, 0xc0, 0x70, 0x1f, 0xf, 0xff,
    0x9f, 0x80,

    /* U+0034 "4" */
    0x3, 0x80, 0xf0, 0x3e, 0x7, 0xc1, 0xb8, 0x77,
    0xc, 0xe3, 0x9c, 0xe3, 0x9f, 0xff, 0xff, 0x81,
    0xc0, 0x38, 0x7, 0x0,

    /* U+0035 "5" */
    0x7f, 0x9f, 0xe7, 0x1, 0xc0, 0x70, 0x1f, 0xc7,
    0xf8, 0xf, 0x1, 0xc0, 0x70, 0x1f, 0xf, 0xff,
    0x9f, 0x80,

    /* U+0036 "6" */
    0xf, 0x8f, 0xe7, 0x81, 0xc0, 0xe0, 0x3b, 0xcf,
    0xfb, 0xcf, 0xe1, 0xf8, 0x7e, 0x1d, 0xcf, 0x7f,
    0x87, 0xc0,

    /* U+0037 "7" */
    0xff, 0xff, 0xf0, 0x1c, 0xe, 0x3, 0x81, 0xc0,
    0x70, 0x38, 0xe, 0x3, 0x81, 0xc0, 0x70, 0x38,
    0xe, 0x0,

    /* U+0038 "8" */
    0x3f, 0x1f, 0xee, 0x1f, 0x87, 0xf1, 0xdf, 0xe1,
    0xe1, 0xfc, 0x73, 0xb8, 0x7e, 0x1f, 0xc7, 0x7f,
    0x8f, 0xc0,

    /* U+0039 "9" */
    0x3e, 0x1f, 0xef, 0x3b, 0x87, 0xe1, 0xf8, 0x7f,
    0x3d, 0xff, 0x3d, 0xc0, 0x70, 0x38, 0x1e, 0x7f,
    0x1f, 0x0,

    /* U+003A ":" */
    0xff, 0x80, 0x0, 0xff, 0x80,

    /* U+003B ";" */
    0x77, 0x70, 0x0, 0x0, 0x77, 0x66, 0x60,

    /* U+003C "<" */
    0x0, 0xc0, 0xf0, 0xf0, 0xf0, 0xf0, 0x3c, 0x3,
    0xe0, 0x3e, 0x3, 0xc0, 0x30,

    /* U+003D "=" */
    0xff, 0xff, 0xf0, 0x0, 0x0, 0xff, 0xff, 0xf0,

    /* U+003E ">" */
    0xc0, 0x3c, 0x7, 0xc0, 0x7c, 0x7, 0xc1, 0xf1,
    0xf1, 0xf0, 0xe0, 0x20, 0x0,

    /* U+003F "?" */
    0x7e, 0x7f, 0xb0, 0xe0, 0x70, 0x78, 0x78, 0x78,
    0x78, 0x38, 0x0, 0x0, 0x7, 0x3, 0x81, 0xc0,

    /* U+0040 "@" */
    0x7, 0xf0, 0x1f, 0xf8, 0x3c, 0x1e, 0x73, 0xf6,
    0x6f, 0xf7, 0xce, 0x73, 0xdc, 0x73, 0xdc, 0x73,
    0xdc, 0x73, 0xdc, 0xf7, 0xef, 0xfe, 0x67, 0x9c,
    0x78, 0x0, 0x3f, 0xf8, 0xf, 0xf0,

    /* U+0041 "A" */
    0x7, 0x80, 0x3e, 0x0, 0xfc, 0x3, 0x70, 0x1c,
    0xc0, 0x73, 0x81, 0xce, 0xe, 0x18, 0x3f, 0xf0,
    0xff, 0xc7, 0x3, 0x9c, 0xe, 0x70, 0x3b, 0x80,
    0xf0,

    /* U+0042 "B" */
    0xff, 0x1f, 0xf3, 0x8f, 0x70, 0xee, 0x1d, 0xc7,
    0xbf, 0xe7, 0xfe, 0xe1, 0xfc, 0x1f, 0x83, 0xf0,
    0xff, 0xfd, 0xff, 0x0,

    /* U+0043 "C" */
    0xf, 0xc7, 0xfd, 0xe1, 0x38, 0xe, 0x1, 0xc0,
    0x38, 0x7, 0x0, 0xe0, 0x1c, 0x1, 0xc0, 0x3c,
    0x13, 0xfe, 0x1f, 0x80,

    /* U+0044 "D" */
    0xff, 0xf, 0xfc, 0xe1, 0xee, 0xe, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0,
    0xee, 0x1e, 0xff, 0xcf, 0xf0,

    /* U+0045 "E" */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff,
    0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff,
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,

    /* U+0047 "G" */
    0xf, 0xe3, 0xff, 0x78, 0x27, 0x0, 0xe0, 0xe,
    0x0, 0xe3, 0xfe, 0x3f, 0xe0, 0x7e, 0x7, 0x70,
    0x77, 0x87, 0x3f, 0xf0, 0xfe,

    /* U+0048 "H" */
    0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e,
    0x7, 0xff, 0xff, 0xff, 0xe0, 0x7e, 0x7, 0xe0,
    0x7e, 0x7, 0xe0, 0x7e, 0x7,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+004A "J" */
    0xe, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x87, 0xe,
    0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x8f, 0xfd, 0xf0,

    /* U+004B "K" */
    0xe0, 0xfc, 0x3b, 0x8e, 0x73, 0xce, 0xf1, 0xdc,
    0x3f, 0x87, 0xf0, 0xf7, 0x1c, 0xf3, 0x8e, 0x71,
    0xee, 0x1f, 0xc1, 0xc0,

    /* U+004C "L" */
    0xe0, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x3, 0x81,
    0xc0, 0xe0, 0x70, 0x38, 0x1c, 0xf, 0xff, 0xfc,

    /* U+004D "M" */
    0xf8, 0x1f, 0xf0, 0x7f, 0xe0, 0xff, 0xc1, 0xff,
    0xc6, 0xfd, 0x8d, 0xfb, 0x1b, 0xf7, 0x77, 0xe6,
    0xcf, 0xcd, 0x9f, 0x9b, 0x3f, 0x3c, 0x7e, 0x38,
    0xfc, 0x71, 0xc0,

    /* U+004E "N" */
    0xf0, 0x3f, 0xc1, 0xff, 0xf, 0xf8, 0x7e, 0xe3,
    0xf7, 0x1f, 0x9c, 0xfc, 0xe7, 0xe3, 0xbf, 0x1d,
    0xf8, 0x7f, 0xc3, 0xfe, 0xf, 0xf0, 0x3c,

    /* U+004F "O" */
    0xf, 0xc0, 0xff, 0xc7, 0x87, 0x9c, 0xe, 0xe0,
    0x1f, 0x80, 0x7e, 0x1, 0xf8, 0x7, 0xe0, 0x1f,
    0x80, 0x77, 0x3, 0x9e, 0x1e, 0x3f, 0xf0, 0x3f,
    0x0,

    /* U+0050 "P" */
    0xff, 0x3f, 0xee, 0x3f, 0x87, 0xe1, 0xf8, 0x7e,
    0x3f, 0xfe, 0xfe, 0x38, 0xe, 0x3, 0x80, 0xe0,
    0x38, 0x0,

    /* U+0051 "Q" */
    0xf, 0xc0, 0xff, 0xc7, 0x87, 0x9c, 0xe, 0xe0,
    0x1f, 0x80, 0x7e, 0x1, 0xf8, 0x7, 0xe0, 0x1f,
    0x80, 0x77, 0x3, 0x9e, 0x1e, 0x3f, 0xf0, 0x3f,
    0x80, 0xf, 0x0, 0x1e, 0x0, 0x38,

    /* U+0052 "R" */
    0xff, 0xf, 0xf8, 0xe3, 0xce, 0x1c, 0xe1, 0xce,
    0x3c, 0xff, 0x8f, 0xe0, 0xe7, 0xe, 0x38, 0xe3,
    0x8e, 0x1c, 0xe1, 0xee, 0xe,

    /* U+0053 "S" */
    0x3f, 0x3f, 0xf8, 0x5c, 0xf, 0x7, 0xc1, 0xf8,
    0x7e, 0xf, 0x81, 0xc0, 0xf8, 0x7f, 0xf3, 0xf0,

    /* U+0054 "T" */
    0xff, 0xff, 0xfc, 0x38, 0x7, 0x0, 0xe0, 0x1c,
    0x3, 0x80, 0x70, 0xe, 0x1, 0xc0, 0x38, 0x7,
    0x0, 0xe0, 0x1c, 0x0,

    /* U+0055 "U" */
    0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7e, 0x7, 0xe0,
    0x77, 0xe, 0x7f, 0xe1, 0xf8,

    /* U+0056 "V" */
    0xe0, 0x3b, 0x83, 0x9c, 0x1c, 0xe0, 0xe3, 0x8e,
    0x1c, 0x70, 0xe3, 0x83, 0x38, 0x1d, 0xc0, 0xee,
    0x3, 0x60, 0x1f, 0x0, 0xf8, 0x3, 0x80,

    /* U+0057 "W" */
    0xe0, 0xe0, 0xfc, 0x1c, 0x1d, 0xc3, 0xc3, 0xb8,
    0xf8, 0x67, 0x1b, 0x1c, 0xe3, 0x73, 0x8e, 0x6e,
    0x71, 0xdc, 0xcc, 0x3b, 0x9b, 0x87, 0x63, 0xf0,
    0x6c, 0x7e, 0xf, 0x87, 0x81, 0xe0, 0xf0, 0x1c,
    0x1e, 0x0,

    /* U+0058 "X" */
    0x70, 0x7b, 0xc3, 0x8e, 0x38, 0x39, 0xc1, 0xdc,
    0x7, 0xc0, 0x1e, 0x1, 0xf0, 0xf, 0xc0, 0xee,
    0xe, 0x38, 0x71, 0xe7, 0x7, 0x78, 0x1c,

    /* U+0059 "Y" */
    0x70, 0x73, 0x83, 0x8e, 0x38, 0x71, 0xc1, 0xdc,
    0xe, 0xe0, 0x3e, 0x1, 0xf0, 0x7, 0x0, 0x38,
    0x1, 0xc0, 0xe, 0x0, 0x70, 0x3, 0x80,

    /* U+005A "Z" */
    0xff, 0xff, 0xf0, 0x38, 0xe, 0x7, 0x3, 0xc0,
    0xe0, 0x70, 0x3c, 0xe, 0x7, 0x1, 0xc0, 0xff,
    0xff, 0xf0,

    /* U+005B "[" */
    0xff, 0xf9, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce,
    0x73, 0x9f, 0xf8,

    /* U+005C "\\" */
    0xe0, 0x60, 0x70, 0x70, 0x38, 0x38, 0x18, 0x1c,
    0x1c, 0xc, 0xe, 0xe, 0x7, 0x7,

    /* U+005D "]" */
    0xff, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73,
    0x9c, 0xff, 0xf8,

    /* U+005E "^" */
    0xc, 0x1, 0xc0, 0x78, 0xf, 0x83, 0x30, 0x67,
    0x1c, 0x63, 0x6, 0xe0, 0xc0,

    /* U+005F "_" */
    0xff, 0xff,

    /* U+0060 "`" */
    0x70, 0xe1, 0xc0,

    /* U+0061 "a" */
    0x3f, 0x1f, 0xe2, 0x1c, 0x7, 0x3f, 0xdf, 0xff,
    0x1f, 0x87, 0xe3, 0xff, 0xf7, 0xcc,

    /* U+0062 "b" */
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xef, 0x3f, 0xef,
    0x3b, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xf3,
    0xbf, 0xee, 0xf0,

    /* U+0063 "c" */
    0x1f, 0xbf, 0x9c, 0x5c, 0xe, 0x7, 0x3, 0x81,
    0xc0, 0x70, 0xbf, 0xc7, 0xc0,

    /* U+0064 "d" */
    0x1, 0xc0, 0x70, 0x1c, 0x7, 0x3d, 0xdf, 0xff,
    0x3f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xf3,
    0xdf, 0xf3, 0xdc,

    /* U+0065 "e" */
    0x1f, 0x1f, 0xe7, 0x3f, 0x87, 0xff, 0xff, 0xfe,
    0x3, 0x80, 0x70, 0x9f, 0xe1, 0xf8,

    /* U+0066 "f" */
    0x1f, 0x3f, 0x38, 0x38, 0x7e, 0xfe, 0x38, 0x38,
    0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,

    /* U+0067 "g" */
    0x1f, 0xe7, 0xfd, 0xc6, 0x38, 0xe7, 0x1c, 0xe3,
    0x8f, 0xe1, 0xf8, 0x70, 0xf, 0xf8, 0xff, 0xf0,
    0x7e, 0xf, 0xc3, 0xff, 0xf1, 0xf8,

    /* U+0068 "h" */
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xef, 0x3f, 0xef,
    0x3f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1,
    0xf8, 0x7e, 0x1c,

    /* U+0069 "i" */
    0xff, 0x8f, 0xff, 0xff, 0xff, 0xf8,

    /* U+006A "j" */
    0x1c, 0x71, 0xc0, 0x1c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x7f, 0xbc,

    /* U+006B "k" */
    0xe0, 0x1c, 0x3, 0x80, 0x70, 0xe, 0x1d, 0xc7,
    0x39, 0xc7, 0x70, 0xfe, 0x1f, 0xc3, 0xfc, 0x73,
    0x8e, 0x39, 0xc7, 0xb8, 0x70,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,

    /* U+006D "m" */
    0xcf, 0x1e, 0x7f, 0xdf, 0xbc, 0xf9, 0xfc, 0x38,
    0x7e, 0x1c, 0x3f, 0xe, 0x1f, 0x87, 0xf, 0xc3,
    0x87, 0xe1, 0xc3, 0xf0, 0xe1, 0xf8, 0x70, 0xe0,

    /* U+006E "n" */
    0xcf, 0x3f, 0xef, 0x3f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1c,

    /* U+006F "o" */
    0x1f, 0xf, 0xf9, 0xc7, 0x70, 0x7e, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0x71, 0xcf, 0xf8, 0x7c, 0x0,

    /* U+0070 "p" */
    0xef, 0x3f, 0xef, 0x3f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xf3, 0xbf, 0xee, 0xf3, 0x80, 0xe0,
    0x38, 0xe, 0x3, 0x80,

    /* U+0071 "q" */
    0x3d, 0xdf, 0xff, 0x3f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xf3, 0xdf, 0xf3, 0xdc, 0x7, 0x1,
    0xc0, 0x70, 0x1c, 0x7,

    /* U+0072 "r" */
    0xcf, 0xff, 0xff, 0x8e, 0x1c, 0x38, 0x70, 0xe1,
    0xc3, 0x80,

    /* U+0073 "s" */
    0x3e, 0xff, 0xe2, 0xf0, 0xfc, 0x7e, 0x1f, 0x7,
    0x87, 0xfe, 0xfc,

    /* U+0074 "t" */
    0x30, 0x30, 0x70, 0xff, 0xff, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x70, 0x70, 0x7f, 0x3f,

    /* U+0075 "u" */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xf3, 0xdf, 0xf3, 0xcc,

    /* U+0076 "v" */
    0xe0, 0xee, 0x1d, 0xc7, 0x38, 0xe3, 0x9c, 0x77,
    0xe, 0xe0, 0xfc, 0x1f, 0x1, 0xe0, 0x38, 0x0,

    /* U+0077 "w" */
    0xe1, 0xc3, 0xb8, 0xf1, 0xdc, 0xd9, 0xce, 0x6c,
    0xe7, 0x36, 0x71, 0xdb, 0xb0, 0xfc, 0xf8, 0x7c,
    0x7c, 0x1e, 0x3e, 0xf, 0x1e, 0x7, 0x8f, 0x0,

    /* U+0078 "x" */
    0x70, 0xef, 0x38, 0xef, 0xf, 0xc1, 0xf0, 0x1e,
    0x7, 0xc1, 0xfc, 0x39, 0xce, 0x3b, 0xc3, 0x80,

    /* U+0079 "y" */
    0xf0, 0xf7, 0xe, 0x70, 0xe3, 0x9c, 0x39, 0xc3,
    0x9c, 0x1f, 0x81, 0xf8, 0xf, 0x80, 0xf0, 0xf,
    0x0, 0x60, 0xe, 0x0, 0xe0, 0x7c, 0x7, 0x80,

    /* U+007A "z" */
    0xff, 0xff, 0xe, 0xe, 0x1c, 0x38, 0x38, 0x70,
    0x70, 0xff, 0xff,

    /* U+007B "{" */
    0xf, 0x1f, 0x1c, 0x1c, 0x1c, 0x1c, 0x3c, 0xf8,
    0xf8, 0x3c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1f,
    0xf,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xf1, 0xf0, 0xe1, 0xc3, 0x87, 0xe, 0xf, 0x1e,
    0x70, 0xe1, 0xc3, 0x87, 0xe, 0x7c, 0xf0,

    /* U+007E "~" */
    0x78, 0x7f, 0xf8, 0x78,

    /* U+00B0 "°" */
    0x38, 0xfb, 0x1e, 0x3c, 0x6f, 0x8e, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 83, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 92, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 151, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 12, .adv_w = 207, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 183, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 288, .box_w = 17, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 240, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 85, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 112, .adv_w = 108, .box_w = 6, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 125, .adv_w = 108, .box_w = 6, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 138, .adv_w = 174, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 149, .adv_w = 183, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 161, .adv_w = 93, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 163, .adv_w = 103, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 165, .adv_w = 91, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 132, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 183, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 183, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 91, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 93, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 370, .adv_w = 183, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 383, .adv_w = 183, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 391, .adv_w = 183, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 404, .adv_w = 153, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 287, .box_w = 16, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 450, .adv_w = 221, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 215, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 204, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 237, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 179, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 176, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 232, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 245, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 106, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 106, .box_w = 7, .box_h = 18, .ofs_x = -2, .ofs_y = -4},
    {.bitmap_index = 628, .adv_w = 213, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 181, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 302, .box_w = 15, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 260, .box_w = 13, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 714, .adv_w = 255, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 201, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 255, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 787, .adv_w = 211, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 176, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 185, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 844, .adv_w = 242, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 865, .adv_w = 208, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 888, .adv_w = 309, .box_w = 19, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 922, .adv_w = 213, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 945, .adv_w = 200, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 968, .adv_w = 185, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 986, .adv_w = 106, .box_w = 5, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 997, .adv_w = 132, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1011, .adv_w = 106, .box_w = 5, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1022, .adv_w = 170, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1035, .adv_w = 132, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1037, .adv_w = 194, .box_w = 6, .box_h = 3, .ofs_x = 3, .ofs_y = 12},
    {.bitmap_index = 1040, .adv_w = 193, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1054, .adv_w = 203, .box_w = 10, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1073, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1086, .adv_w = 203, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1105, .adv_w = 189, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1119, .adv_w = 124, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1134, .adv_w = 181, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1156, .adv_w = 210, .box_w = 10, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1175, .adv_w = 98, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1181, .adv_w = 98, .box_w = 6, .box_h = 20, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1196, .adv_w = 198, .box_w = 11, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1217, .adv_w = 98, .box_w = 3, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1223, .adv_w = 314, .box_w = 17, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1247, .adv_w = 210, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1261, .adv_w = 198, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1277, .adv_w = 203, .box_w = 10, .box_h = 16, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 1297, .adv_w = 203, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1317, .adv_w = 145, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1327, .adv_w = 159, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1338, .adv_w = 139, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1352, .adv_w = 210, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1366, .adv_w = 182, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1382, .adv_w = 274, .box_w = 17, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1406, .adv_w = 185, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1422, .adv_w = 182, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1446, .adv_w = 156, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1457, .adv_w = 126, .box_w = 8, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1474, .adv_w = 176, .box_w = 2, .box_h = 20, .ofs_x = 4, .ofs_y = -5},
    {.bitmap_index = 1479, .adv_w = 126, .box_w = 7, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1494, .adv_w = 183, .box_w = 10, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1498, .adv_w = 137, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 8}
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
const lv_font_t opensansb20px = {
#else
lv_font_t opensansb20px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if OPENSANSB20PX*/

