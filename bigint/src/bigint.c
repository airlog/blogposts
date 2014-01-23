/* ~ bigint.c
 *
 * Copyright (c) 2014 Rafal (robin92pl@gmail.com)
 * For licensing information please see LICENSE file located in main directory.
 *
 */
 
#include "bigint/bigint.h"

#include <stdlib.h>
#include <string.h>

#include "bigint/hexstring.h"

int bigint_init(bigint_s *ptr) {
    if (!ptr) return BIGINT_INVALID_ARGUMENT;
    
    ptr->bytes = malloc(BIGINT_DEFAULT_SIZE * sizeof(uint8_t));
    if (!ptr->bytes) return BIGINT_OUT_OF_MEMORY;
    
    ptr->bytes_alloced = BIGINT_DEFAULT_SIZE * sizeof(uint8_t);
    ptr->bytes_used = 0;
    for (uint32_t i = 0; i < ptr->bytes_alloced; i++) ptr->bytes[i] = 0;
    
    return BIGINT_OK;
}

int bigint_free(bigint_s *ptr) {
    if (!ptr) return BIGINT_INVALID_ARGUMENT;
        
    if (ptr->bytes) free(ptr->bytes);
    ptr->bytes_alloced = 0;
    ptr->bytes_used = 0;
    
    return BIGINT_OK;
}

int bigint_set(bigint_s *dst, const char *hexString) {
    if (!dst || !hexString) return BIGINT_INVALID_ARGUMENT;
    
    /* each byte is encoded with 2 characters thus expecting |hexString|/2 bytes */
    uint32_t length = strlen(hexString);
    uint32_t size = length>>1;
    if (length % 2 != 0) return BIGINT_INVALID_ARGUMENT;
    if (size > dst->bytes_alloced) return BIGINT_OUT_OF_MEMORY;
    
    if (hexstring_decode(dst->bytes, hexString, length) != HEXSTRING_OK) return BIGINT_INVALID_ARGUMENT;  // decode hex string
    dst->bytes_used = size;
    
    return BIGINT_OK;
}

int bigint_get(char *dst, bigint_s *src) {
    if (!dst || !src) return BIGINT_INVALID_ARGUMENT;
    
    if (hexstring_encode(dst, src->bytes, src->bytes_used) != HEXSTRING_OK) return BIGINT_INVALID_ARGUMENT;
    
    return BIGINT_OK;
}

int bigint_swap(bigint_s *a, bigint_s *b) {
    if (!a || !b) return BIGINT_INVALID_ARGUMENT;
    
    void *bp = a->bytes;
    int ba = a->bytes_alloced;
    int bu = a->bytes_used;
    a->bytes = b->bytes;
    a->bytes_alloced = b->bytes_alloced;
    a->bytes_used = b->bytes_used;
    b->bytes = bp;
    b->bytes_alloced = ba;
    b->bytes_used = bu;
    
    return BIGINT_OK;
}

