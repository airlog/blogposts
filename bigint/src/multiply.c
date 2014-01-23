/* ~ multiply.c
 *
 * Copyright (c) 2014 Rafal (robin92pl@gmail.com)
 * For licensing information please see LICENSE file located in main directory.
 *
 * Source code for multiplying two bigint numbers.
 */
 
#include "bigint/bigint.h"

#include <stdio.h>
#include <stdbool.h>

static void print(const char *caption, bigint_s *bi) {
    if (!bi) return;
    
    char buf[10000] = {0};
    bigint_get(buf, bi);
    
    printf("\n[%s]\nbytes\t= %d\nalloced\t= %d\nused\t= %d\ndata\t= %s\n",
            caption, bi->bytes, bi->bytes_alloced, bi->bytes_used, buf);
}

int bigint_multiply(bigint_s *dst, bigint_s *a, bigint_s *b) {
    if (!dst || !a || !b || !dst->bytes || !a->bytes || !b->bytes) return BIGINT_INVALID_ARGUMENT;
    if (a->bytes_alloced != b->bytes_alloced) return BIGINT_DIFFRENT_SIZE;  // TODO: allow different sizes (padding)

    uint32_t buffer_size = dst->bytes_alloced;
    
    /*
     * multiply two big numbers (in columns with carry)
     * assuming that:
     *       (b-number)     first row
     *     x (a-number)     second row
     *    -------------
     *           result
     */
    bool add = false;
    for (uint32_t i = 0; i < a->bytes_used; i++) {    // second row on paper
        bigint_s tmp;
        bigint_init(&tmp);
        
        uint32_t k = i;
        uint16_t rest = 0, carry = 0;
        for (uint32_t j = 0; j < b->bytes_used; j++) {
            uint16_t result = (uint16_t) a->bytes[i] * (uint16_t) b->bytes[j] + carry;
            
            carry = result/BIGINT_BASE;
            rest = result % BIGINT_BASE;
            
            if (k >= buffer_size) return BIGINT_OUT_OF_MEMORY;
            tmp.bytes[k++] = (uint8_t) rest;
        }
        if (k >= buffer_size) return BIGINT_OUT_OF_MEMORY;
        if (carry > 0) tmp.bytes[k++] = (uint8_t) carry;
        tmp.bytes_used = k;
        
        if (!add) {
            bigint_swap(dst, &tmp);
            add = true;
        } else {
            bigint_s r;
            bigint_init(&r);
            int rr = bigint_add(&r, dst, &tmp);
            if (rr != BIGINT_OK) return rr;
            bigint_swap(dst, &r);
            bigint_free(&r);
        }

        while (dst->bytes_used > 0 && dst->bytes[dst->bytes_used - 1] == 0) { dst->bytes_used--; }  // sometimes result is prefixed with zeros, cutting them off
        bigint_free(&tmp);
    }

    return BIGINT_OK;
}

