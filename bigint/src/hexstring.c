/* ~ hexstring.c
 *
 * Copyright (c) 2014 Rafal (robin92pl@gmail.com)
 * For licensing information please see LICENSE file located in main directory.
 *
 * Source code for encoding bytes to hexstrings and decoding from hexstring to bytes, implemented
 * for use with bigint library.
 */

#include "bigint/hexstring.h"

static const char g_encode_table[] = {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 
    };

static const char g_decode_table[] = {                // inclusive - exclusive
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       //   0 -  10
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       //  10 -  20
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       //  20 -  30
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       //  30 -  40
        -1, -1, -1, -1, -1, -1, -1, -1,  0,  1,       //  40 -  50
         2,  3,  4,  5,  6,  7,  8,  9, -1, -1,       //  50 -  60
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       //  60 -  70
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       //  70 -  80
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       //  80 -  90
        -1, -1, -1, -1, -1, -1, -1, 10, 11, 12,       //  90 - 100
        13, 14, 15, -1, -1, -1, -1, -1, -1, -1,       // 100 - 110
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       // 110 - 120
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,       // 120 - 130
    };

int hexstring_encode(char *dst, uint8_t *src, uint32_t size) {
    if (!dst || !src) return HEXSTRING_INVALID_ARGUMENT;
    
    uint32_t k = 0;
    for (int i = size - 1; i >= 0; i--) {
        dst[k++] = g_encode_table[(0xF0 & src[i])>>4];
        dst[k++] = g_encode_table[(0x0F & src[i])];
    }
    
    return HEXSTRING_OK;
}

int hexstring_decode(uint8_t *dst, const char *src, uint32_t size) {
    if (!dst || !src) return HEXSTRING_INVALID_ARGUMENT;
    
    uint32_t k = 0;
    for (int i = size - 1; i >= 0; i -= 2) {
        char a = g_decode_table[src[i]], b = g_decode_table[src[i - 1]];
        if (a < 0 || b < 0) return HEXSTRING_INVALID_HEXSTRING;
        
        dst[k++] = b<<4 | a;
    } 
    
    return HEXSTRING_OK;   
}

