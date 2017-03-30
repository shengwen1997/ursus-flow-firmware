#ifndef __MT9V034_H__
#define __MT9V034_H__

#include "stdbool.h"

/* ============= camera setting ============= */
#define FLOW_IMG_WIDTH      64
#define FLOW_IMG_HEIGHT     64
#define CALIB_IMG_WIDTH     188
#define CALIB_IMG_HEIGHT    120

#if (CALIBRATION_ENABLED == 1)
#define IMG_HEIGHT FLOW_IMG_HEIGHT
#define IMG_WIDTH  FLOW_IMG_WIDTH
#else
#define IMG_HEIGHT CALIB_IMG_HEIGHT
#define IMG_WIDTH  CALIB_IMG_WIDTH
#endif

/* ========== mt9v034 register map ========== */
#define MT9V034_DEV_ADDRESS                0x90

#define MT9V034_CHIP_VERSION               0x00
#define 	MT9V034_CHIP_ID_REV3       0x1324

#define MT9V032_CHIP_CONTROL               0x07
#define MT9V034_RESET                      0x0c

#define MT9V034_COLUMN_START_A             0x01
#define MT9V034_ROW_START_A                0x02
#define MT9V034_WINDOW_HEIGHT_A            0x03
#define MT9V034_WINDOW_WIDTH_A             0x04
#define MT9V034_HORIZONTAL_BLANKING_A      0x05
#define MT9V034_VERTICAL_BLANKING_A        0x06
#define MT9V034_COARSE_SW_1_A              0x08
#define MT9V034_COARSE_SW_2_A              0x09
#define MT9V034_COARSE_SW_CTRL_A           0x0a
#define MT9V034_COARSE_SW_TOTAL_A          0x0b
#define MT9V034_FINE_SW_1_A                0xd3
#define MT9V034_FINE_SW_2_A                0xd4
#define MT9V034_FINE_SW_TOTAL_A            0xd5
#define MT9V034_READ_MODE_A                0x0d
#define MT9V034_V1_CTRL_A                  0x31
#define MT9V034_V2_CTRL_A                  0x32
#define MT9V034_V3_CTRL_A                  0x33
#define MT9V034_V4_CTRL_A                  0x34
#define MT9V034_ANALOG_GAIN_CTRL_A         0x35

#define MT9V034_COLUMN_START_B             0xc9
#define MT9V034_ROW_START_B                0xca
#define MT9V034_WINDOW_HEIGHT_B            0xcb
#define MT9V034_WINDOW_WIDTH_B             0xcc
#define MT9V034_HORIZONTAL_BLANKING_B      0xcd
#define MT9V034_VERTICAL_BLANKING_B        0xce
#define MT9V034_COARSE_SW_1_B              0xcf
#define MT9V034_COARSE_SW_2_B              0xd0
#define MT9V034_COARSE_SW_CTRL_B           0xd1
#define MT9V034_COARSE_SW_TOTAL_B          0xd2
#define MT9V034_FINE_SW_1_B                0xd6
#define MT9V034_FINE_SW_2_B                0xd7
#define MT9V034_FINE_SW_TOTAL_B            0xd8
#define MT9V034_READ_MODE_B                0x0e
#define MT9V034_V1_CTRL_B                  0x39
#define MT9V034_V2_CTRL_B                  0x3a
#define MT9V034_V3_CTRL_B                  0x3b
#define MT9V034_V4_CTRL_B                  0x3c
#define MT9V034_ANALOG_GAIN_CTRL_B         0x36

int mt9v034_init(uint32_t image_buffer_address);
bool mt9v034_calibration_is_on(void);

#endif
