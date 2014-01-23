/* ~ add.c
 *
 * Copyright (c) 2014 Rafal (robin92pl@gmail.com)
 * For licensing information please see LICENSE file located in main directory.
 *
 * Source code for adding two bigint numbers.
 */

#include "bigint/bigint.h"

#include <stdio.h>

int bigint_add(bigint_s *dst, bigint_s *a, bigint_s *b) {
    if (!dst || !a || !b || !dst->bytes || !a->bytes || !b->bytes) return BIGINT_INVALID_ARGUMENT;

    uint32_t number_size = a->bytes_used;
    if (number_size < b->bytes_used) number_size = b->bytes_used;
    uint32_t buffer_size = dst->bytes_alloced;
    
    /* add two big numbers (in columns with carry) */
    uint32_t k = 0;
    uint16_t rest = 0, carry = 0;
    for (uint32_t i = 0; i < number_size; i++) {
        uint16_t result = (uint16_t) a->bytes[i] + (uint16_t) b->bytes[i] + carry;
        
        carry = result/BIGINT_BASE;
        rest = result % BIGINT_BASE;        
        
        if (k >= buffer_size) return BIGINT_OUT_OF_MEMORY;
        dst->bytes[k++] = (uint8_t) rest;
    }
    if (k >= buffer_size) return BIGINT_OUT_OF_MEMORY;
    if (carry > 0) dst->bytes[k++] = (uint8_t) carry;
    dst->bytes_used = k;
        
    return BIGINT_OK;
}

