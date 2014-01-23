/* ~ bigint/hexstring.h
 *
 * Copyright (c) 2014 Rafal (robin92pl@gmail.com)
 * For licensing information please see LICENSE file located in main directory.
 *
 */

#ifndef HEXSTRING_H_
#define HEXSTRING_H_

#include <stdint.h>

static const int HEXSTRING_OK                 = 0x00000000;
static const int HEXSTRING_INVALID_ARGUMENT   = 0x80000001;
static const int HEXSTRING_INVALID_HEXSTRING  = 0x80000002;

extern int hexstring_encode(char *dst, uint8_t *bytes, uint32_t size);

extern int hexstring_decode(uint8_t *dst, const char *src, uint32_t size);

#endif  // HEXSTRING_H_

