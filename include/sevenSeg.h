/*
 * sevenSeg.h
 *
 * Font type    : Numeric (10 characters)
 * Font size    : 32x50 pixels
 *
 *  Created on: Jul 16, 2016
 *      Author: Tim
 */

#ifndef SEVENSEG_H_
#define SEVENSEG_H_

/*
const unsigned char sevenSeg[10][200] = {
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x01, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x60,
		0x0C, 0xFF, 0xFE, 0xF0, 0x1E, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
	    0x3E, 0x00, 0x00, 0x78, 0x38, 0x00, 0x00, 0x18, 0x20, 0x00, 0x00, 0x08,
		0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x18,
		0x3E, 0x00, 0x00, 0x78, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x1E, 0x00, 0x00, 0xF0, 0x0C, 0xFF, 0xFE, 0x60, 0x01, 0xFF, 0xFF, 0x00,
		0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
		0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x08,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 1

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x01, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x60,
		0x00, 0xFF, 0xFE, 0xF0, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0x78, 0x01, 0xFF, 0xFE, 0x18, 0x03, 0xFF, 0xFF, 0x88,
		0x0F, 0xFF, 0xFF, 0xE0, 0x27, 0xFF, 0xFF, 0xC0, 0x39, 0xFF, 0xFF, 0x00,
		0x3E, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x1E, 0x00, 0x00, 0x00, 0x0C, 0xFF, 0xFE, 0x00, 0x01, 0xFF, 0xFF, 0x00,
		0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 2

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x01, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x60,
		0x00, 0xFF, 0xFE, 0xF0, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0x78, 0x01, 0xFF, 0xFE, 0x18, 0x03, 0xFF, 0xFF, 0x88,
		0x0F, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0x18,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0xF0, 0x00, 0xFF, 0xFE, 0x60, 0x01, 0xFF, 0xFF, 0x00,
		0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 3

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
		0x0C, 0x00, 0x00, 0xF0, 0x1E, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3E, 0x00, 0x00, 0x78, 0x39, 0xFF, 0xFE, 0x18, 0x23, 0xFF, 0xFF, 0x88,
		0x0F, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0x18,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 4

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x01, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00,
		0x0C, 0xFF, 0xFE, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3E, 0x00, 0x00, 0x00, 0x39, 0xFF, 0xFE, 0x00, 0x23, 0xFF, 0xFF, 0x80,
		0x0F, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0x18,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0xF0, 0x00, 0xFF, 0xFE, 0x60, 0x01, 0xFF, 0xFF, 0x00,
		0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 5

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x01, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00,
		0x0C, 0xFF, 0xFE, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
		0x3E, 0x00, 0x00, 0x00, 0x39, 0xFF, 0xFE, 0x00, 0x23, 0xFF, 0xFF, 0x80,
		0x0F, 0xFF, 0xFF, 0xE0, 0x27, 0xFF, 0xFF, 0xC0, 0x39, 0xFF, 0xFF, 0x18,
		0x3E, 0x00, 0x00, 0x78, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x1E, 0x00, 0x00, 0xF0, 0x0C, 0xFF, 0xFE, 0x60, 0x01, 0xFF, 0xFF, 0x00,
		0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 6

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x01, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x60,
		0x00, 0xFF, 0xFE, 0xF0, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x08,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 7

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x01, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x60,
		0x0C, 0xFF, 0xFE, 0xF0, 0x1E, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3E, 0x00, 0x00, 0x78, 0x39, 0xFF, 0xFE, 0x18, 0x23, 0xFF, 0xFF, 0x88,
		0x0F, 0xFF, 0xFF, 0xE0, 0x27, 0xFF, 0xFF, 0xC0, 0x39, 0xFF, 0xFF, 0x18,
		0x3E, 0x00, 0x00, 0x78, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x1E, 0x00, 0x00, 0xF0, 0x0C, 0xFF, 0xFE, 0x60, 0x01, 0xFF, 0xFF, 0x00,
		0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // 8

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x01, 0xFF, 0xFF, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x60,
		0x0C, 0xFF, 0xFE, 0xF0, 0x1E, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8, 0x3F, 0x00, 0x01, 0xF8,
		0x3E, 0x00, 0x00, 0x78, 0x39, 0xFF, 0xFE, 0x18, 0x23, 0xFF, 0xFF, 0x88,
		0x0F, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0x18,
		0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x01, 0xF8,
		0x00, 0x00, 0x00, 0xF0, 0x00, 0xFF, 0xFE, 0x60, 0x01, 0xFF, 0xFF, 0x00,
		0x03, 0xFF, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFE, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 9
};

*/

const unsigned char sevenSeg[10][200] = {

   {0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0x0F,0xF8,0xFF,0xFF,0x1F,0x0C,0x00,0x00,0x30,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x06,0x00,0x00,0x60,0x02,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x40,0x06,0x00,0x00,0x60,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0C,0x00,0x00,0x30,0xF8,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x0F,0xE0,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00}, //0
   {0x00,0x00,0x00,0x00,0x00,0xC0,0x03,0x00,0x00,0xE0,0x03,0x00,0x00,0xF0,0x03,0x00,0x00,0xF8,0x03,0x00,0x00,0xFC,0x03,0x00,0x00,0x9E,0x03,0x00,0x00,0x8E,0x03,0x00,0x00,0x86,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0x00,0x80,0x03,0x00,0xF8,0x3F,0xF9,0x1F,0xFC,0x7F,0xFC,0x3F,0xFE,0xFF,0xFF,0x7F,0x00,0x00,0x00,0x00}, //1
   {0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x07,0xFC,0xFF,0xFF,0x0F,0xFE,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x60,0xF0,0xFF,0xFF,0x4F,0xF8,0xFF,0xFF,0x1F,0xF8,0xFF,0xFF,0x1F,0xF2,0xFF,0xFF,0x0F,0x06,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x7F,0xF0,0xFF,0xFF,0x3F,0xE0,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x00}, //2
   {0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x07,0xFC,0xFF,0xFF,0x0F,0xFE,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x60,0xF0,0xFF,0xFF,0x4F,0xF8,0xFF,0xFF,0x1F,0xF8,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x4F,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x30,0xFE,0xFF,0xFF,0x1F,0xFC,0xFF,0xFF,0x0F,0xF8,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00}, //3
   {0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x10,0x0C,0x00,0x00,0x30,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x06,0x00,0x00,0x60,0xF2,0xFF,0xFF,0x4F,0xF8,0xFF,0xFF,0x1F,0xF8,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x4F,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00}, //4
   {0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x3F,0xF8,0xFF,0xFF,0x7F,0x0C,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0xF2,0xFF,0xFF,0x0F,0xF8,0xFF,0xFF,0x1F,0xF8,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x4F,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x30,0xFE,0xFF,0xFF,0x1F,0xFC,0xFF,0xFF,0x0F,0xF8,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00}, //5
   {0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x3F,0xF8,0xFF,0xFF,0x7F,0x0C,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0xF2,0xFF,0xFF,0x0F,0xF8,0xFF,0xFF,0x1F,0xF8,0xFF,0xFF,0x1F,0xF2,0xFF,0xFF,0x4F,0x06,0x00,0x00,0x60,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0C,0x00,0x00,0x30,0xF8,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x0F,0xE0,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00}, //6
   {0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0x07,0xFC,0xFF,0xFF,0x0F,0xFE,0xFF,0xFF,0x1F,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00}, //7
   {0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0x0F,0xF8,0xFF,0xFF,0x1F,0x0C,0x00,0x00,0x30,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x06,0x00,0x00,0x60,0xF2,0xFF,0xFF,0x4F,0xF8,0xFF,0xFF,0x1F,0xF8,0xFF,0xFF,0x1F,0xF2,0xFF,0xFF,0x4F,0x06,0x00,0x00,0x60,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0C,0x00,0x00,0x30,0xF8,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x0F,0xE0,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00}, //8
   {0x00,0x00,0x00,0x00,0xE0,0xFF,0xFF,0x07,0xF0,0xFF,0xFF,0x0F,0xF8,0xFF,0xFF,0x1F,0x0C,0x00,0x00,0x30,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x06,0x00,0x00,0x60,0xF2,0xFF,0xFF,0x4F,0xF8,0xFF,0xFF,0x1F,0xF8,0xFF,0xFF,0x1F,0xF0,0xFF,0xFF,0x4F,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x30,0xFE,0xFF,0xFF,0x1F,0xFC,0xFF,0xFF,0x0F,0xF8,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00}  //9

};



#endif /* SEVENSEG_H_ */