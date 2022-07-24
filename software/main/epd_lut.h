/*
 * epd_lut.h
 *
 * Created on: 16 gru 2021
 *     Author: Krzysztof Markiewicz <obbo.pl>
 *
 * This program is distributed under the terms of the GNU General Public License
 */

#ifndef _EPD_LUT_H_
#define _EPD_LUT_H_

#include "uc8179c_lut.h"

// full color refresh, no flicker,
// 80Hz / 875ms
const uint8_t epd_lut_vcom_data[EPD_LUTC_SIZE] = {
    EPD_VC_HLHL,       1,        1,        2,        1,        3,
    EPD_VC_0000,      20,        0,        0,        0,        1,
    EPD_VC_0000,       0,        0,        0,        0,        0, 
    EPD_VC_0000,       0,        0,        0,        0,        0, 
    EPD_VC_0000,       0,        0,        0,        0,        0, 
    EPD_VC_0000,       0,        0,        0,        0,        0, 
    EPD_VC_0000,       0,        0,        0,        0,        0, 
    EPD_VC_0000,       0,        0,        0,        0,        0, 
    EPD_VC_0000,       0,        0,        0,        0,        0, 
    EPD_VC_0000,       0,        0,        0,        0,        0, 
};

const uint8_t epd_lut_ww_data[EPD_LUTWW_SIZE] = {
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0
};

// 80Hz / 13525ms
const uint8_t epd_lut_r_data[EPD_LUTR_SIZE] = {
   EPD_GT_LRLR,        1,        1,        2,        1,        3,
   EPD_GT_R0R0,       70,        1,       70,        1,        2,
   EPD_GT_RLRL,        1,        2,        1,        2,        1,
   EPD_GT_R0R0,       70,        1,       70,        1,        2,
   EPD_GT_RLRL,        1,        2,        1,        2,        0,
   EPD_GT_R0R0,       70,        1,       70,        1,        2,
   EPD_GT_0000,       20,        0,        0,        0,        1,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0
};

// 80Hz / 1050ms
const uint8_t epd_lut_w_data[EPD_LUTW_SIZE] = {
   EPD_GT_LHLH,        1,        1,        2,        1,        3,
   EPD_GT_L0L0,        6,        2,        6,        0,        3,
   EPD_GT_0000,       20,        0,        0,        0,        1,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0
};

// 80Hz / 1575ms
const uint8_t epd_lut_k_data[EPD_LUTK_SIZE] = {
   EPD_GT_0H0H,        1,        1,        2,        1,        3,
   EPD_GT_H0H0,       10,        2,       10,        2,        4,
   EPD_GT_0000,       20,        0,        0,        0,        1,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0
};

// W/B refresh, no RED content
const uint8_t epd_lut_r_data_no_red[EPD_LUTR_SIZE] = {
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0,
   EPD_GT_0000,        0,        0,        0,        0,        0
};


#endif /* _EPD_LUT_H_ */
