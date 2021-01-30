/*
 * font_8x12.h
 *
 *  Created on: Apr 10, 2012
 *      Author: RobG @ 43oh
 */

#ifndef FONT_8X12_H_
#define FONT_8X12_H_

const unsigned char font_8x12[95][12] = {	// offset 0x20
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		//
0x00, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 		// !
0x36, 0x36, 0x36, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// "
0x00, 0x6C, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C, 0x00, 0x00, 		// #
0x18, 0x18, 0x7C, 0xC6, 0xC0, 0x78, 0x3C, 0x06, 0xC6, 0x7C, 0x18, 0x18, 		// $
0x00, 0x00, 0x00, 0x62, 0x66, 0x0C, 0x18, 0x30, 0x66, 0xC6, 0x00, 0x00, 		// %
0x00, 0x38, 0x6C, 0x38, 0x38, 0x76, 0xF6, 0xCE, 0xCC, 0x76, 0x00, 0x00, 		// &
0x0C, 0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// '
0x00, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0C, 0x00, 0x00, 		// (
0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x18, 0x30, 0x00, 0x00, 		// )
0x00, 0x00, 0x00, 0x6C, 0x38, 0xFE, 0x38, 0x6C, 0x00, 0x00, 0x00, 0x00, 		// *
0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 		// +
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x18, 0x00, 		// ,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// -
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 		// .
0x00, 0x00, 0x02, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 		// /
0x00, 0x7C, 0xC6, 0xCE, 0xDE, 0xF6, 0xE6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 		// 0
0x00, 0x18, 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x00, 0x00, 		// 1
0x00, 0x7C, 0xC6, 0xC6, 0x0C, 0x18, 0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 		// 2
0x00, 0x7C, 0xC6, 0x06, 0x06, 0x3C, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 		// 3
0x00, 0x0C, 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x0C, 0x0C, 0x00, 0x00, 		// 4
0x00, 0xFE, 0xC0, 0xC0, 0xC0, 0xFC, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 		// 5
0x00, 0x7C, 0xC6, 0xC0, 0xC0, 0xFC, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 		// 6
0x00, 0xFE, 0xC6, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 		// 7
0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 		// 8
0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 		// 9
0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 		// :
0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x0C, 0x18, 0x00, 		// ;
0x00, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x00, 0x00, 		// <
0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 		// =
0x00, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00, 0x00, 		// >
0x00, 0x7C, 0xC6, 0xC6, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 		// ?
0x00, 0x7C, 0xC6, 0xC6, 0xDE, 0xDE, 0xDE, 0xDC, 0xC0, 0x7E, 0x00, 0x00, 		// @
0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 		// A
0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x66, 0xFC, 0x00, 0x00, 		// B
0x00, 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00, 0x00, 		// C
0x00, 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00, 0x00, 		// D
0x00, 0xFE, 0x66, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x66, 0xFE, 0x00, 0x00, 		// E
0x00, 0xFE, 0x66, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 		// F
0x00, 0x7C, 0xC6, 0xC6, 0xC0, 0xC0, 0xCE, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 		// G
0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 		// H
0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 		// I
0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0xD8, 0xD8, 0x70, 0x00, 0x00, 		// J
0x00, 0xC6, 0xCC, 0xD8, 0xF0, 0xF0, 0xD8, 0xCC, 0xC6, 0xC6, 0x00, 0x00, 		// K
0x00, 0xF0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 		// L
0x00, 0xC6, 0xC6, 0xEE, 0xFE, 0xD6, 0xD6, 0xD6, 0xC6, 0xC6, 0x00, 0x00, 		// M
0x00, 0xC6, 0xC6, 0xE6, 0xE6, 0xF6, 0xDE, 0xCE, 0xCE, 0xC6, 0x00, 0x00, 		// N
0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 		// O
0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 		// P
0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0x7C, 0x06, 0x00, 		// Q
0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66, 0xE6, 0x00, 0x00, 		// R
0x00, 0x7C, 0xC6, 0xC0, 0x60, 0x38, 0x0C, 0x06, 0xC6, 0x7C, 0x00, 0x00, 		// S
0x00, 0x7E, 0x5A, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 		// T
0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 		// U
0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x10, 0x00, 0x00, 		// V
0x00, 0xC6, 0xC6, 0xD6, 0xD6, 0xD6, 0xFE, 0xEE, 0xC6, 0xC6, 0x00, 0x00, 		// W
0x00, 0xC6, 0xC6, 0x6C, 0x38, 0x38, 0x38, 0x6C, 0xC6, 0xC6, 0x00, 0x00, 		// X
0x00, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 		// Y
0x00, 0xFE, 0xC6, 0x8C, 0x18, 0x30, 0x60, 0xC2, 0xC6, 0xFE, 0x00, 0x00, 		// Z
0x00, 0x7C, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7C, 0x00, 0x00, 		// [
0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00, 0x00, 		// '\'
0x00, 0x7C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x7C, 0x00, 0x00, 		// ]
0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// ^
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 		// _
0x18, 0x18, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 		// `
0x00, 0x00, 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0xDC, 0x76, 0x00, 0x00, 		// a
0x00, 0xE0, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x66, 0xFC, 0x00, 0x00, 		// b
0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 		// c
0x00, 0x1C, 0x0C, 0x0C, 0x7C, 0xCC, 0xCC, 0xCC, 0xCC, 0x7E, 0x00, 0x00, 		// d
0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xFE, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 		// e
0x00, 0x1C, 0x36, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x30, 0x78, 0x00, 0x00, 		// f
0x00, 0x00, 0x00, 0x00, 0x76, 0xCE, 0xC6, 0xC6, 0x7E, 0x06, 0xC6, 0x7C, 		// g
0x00, 0xE0, 0x60, 0x60, 0x6C, 0x76, 0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 		// h
0x00, 0x18, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 		// i
0x00, 0x0C, 0x0C, 0x00, 0x1C, 0x0C, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 		// j
0x00, 0xE0, 0x60, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00, 0x00, 		// k
0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 		// l
0x00, 0x00, 0x00, 0x00, 0x6C, 0xFE, 0xD6, 0xD6, 0xC6, 0xC6, 0x00, 0x00, 		// m
0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 		// n
0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 		// o
0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 		// p
0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0x0C, 0x1E, 		// q
0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 		// r
0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0x70, 0x1C, 0xC6, 0x7C, 0x00, 0x00, 		// s
0x00, 0x30, 0x30, 0x30, 0xFC, 0x30, 0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 		// t
0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 		// u
0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x10, 0x00, 0x00, 		// v
0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xD6, 0xFE, 0x6C, 0x00, 0x00, 		// w
0x00, 0x00, 0x00, 0x00, 0xC6, 0x6C, 0x38, 0x38, 0x6C, 0xC6, 0x00, 0x00, 		// x
0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xCE, 0x76, 0x06, 0xC6, 0x7C, 		// y
0x00, 0x00, 0x00, 0x00, 0xFE, 0x8C, 0x18, 0x30, 0x62, 0xFE, 0x00, 0x00, 		// z
0x00, 0x0E, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0x0E, 0x00, 0x00, 		// {
0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 		// |
0x00, 0x70, 0x18, 0x18, 0x18, 0x0E, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00, 		// }
0x00, 0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00	 		// ~
};

#endif /* FONT_8X12_H_ */
