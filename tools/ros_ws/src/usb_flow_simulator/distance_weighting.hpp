#ifndef __DISTANCE_WEIGHTING_H__
#define __DISTANCE_WEIGHTING_H__

const uint8_t distance_weighting_table[9][9] = {
	{ 81,  63,  45,  27,  9,  27,  45,  63,  81},
	{ 63,  49,  35,  21,  7,  21,  35,  49,  63},
	{ 45,  35,  25,  15,  5,  15,  25,  35,  45},
	{ 27,  21,  15,  9,  3,  9,  15,  21,  27},
	{ 9,  7,  5,  3,  1,  3,  5,  7,  9},
	{ 27,  21,  15,  9,  3,  9,  15,  21,  27},
	{ 45,  35,  25,  15,  5,  15,  25,  35,  45},
	{ 63,  49,  35,  21,  7,  21,  35,  49,  63},
	{ 81,  63,  45,  27,  9,  27,  45,  63,  81}
};

#endif
