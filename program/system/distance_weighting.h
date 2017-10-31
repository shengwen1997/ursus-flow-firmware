#ifndef __DISTANCE_WEIGHTING_H__
#define __DISTANCE_WEIGHTING_H__

//gaussian distance weighting (sigma = 3.4, peak = 12):
const uint8_t distance_weighting_table[9][9] =
{{ 14,  13,  11,  9,  8,  9,  11,  13,  14},
 { 13,  11,  9,  7,  7,  7,  9,  11,  13},
 { 11,  9,  7,  5,  4,  5,  7,  9,  11},
 { 9,  7,  5,  3,  2,  3,  5,  7,  9},
 { 8,  7,  4,  2,  1,  2,  4,  7,  8},
 { 9,  7,  5,  3,  2,  3,  5,  7,  9},
 { 11,  9,  7,  5,  4,  5,  7,  9,  11},
 { 13,  11,  9,  7,  7,  7,  9,  11,  13},
 { 14,  13,  11,  9,  8,  9,  11,  13,  14}};

#if 0
const uint8_t distance_weighting_table[9][9] = {
	{25,  20,  15,  10,  5,  10,  15,  20,  25},
	{20,  16,  12,   8,  4,   8,  12,  16,  20},
	{15,  12,   9,   6,  3,   6,   9,  12,  15},
	{10,   8,   6,   4,  2,   4,   6,   8,  10},
	{ 5,   4,   3,   2,  1,   2,   3,   4,   5},
	{10,   8,   6,   4,  2,   4,   6,   8,  10},
	{15,  12,   9,   6,  3,   6,   9,  12,  15},
	{20,  16,  12,   8,  4,   8,  12,  16,  20},
	{25,  20,  15,  10,  5,  10,  15,  20,  25}
};
#endif

#endif
