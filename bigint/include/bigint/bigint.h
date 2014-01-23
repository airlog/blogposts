/* ~ bigint/bigint.h
 *
 * Copyright (c) 2014 Rafal (robin92pl@gmail.com)
 * For licensing information please see LICENSE file located in main directory.
 *
 * This file contains declarations of public objects provided by bigint library.
 */

#ifndef BIGINT_H_
#define BIGINT_H_

#include <stdint.h>

/** Stores big integer data.
 * Each big integer is stored as an array starting from 0 index (least significant digit).
 */
typedef struct bigint {
    uint8_t     *bytes;
    uint32_t    bytes_alloced;
    uint32_t    bytes_used;
} bigint_s;

extern const uint32_t BIGINT_BASE;
extern const uint32_t BIGINT_DEFAULT_SIZE;
extern const uint32_t BIGINT_ADDITION_BUFFER_SIZE;

extern const int BIGINT_OK;
extern const int BIGINT_INVALID_ARGUMENT;
extern const int BIGINT_OUT_OF_MEMORY;
extern const int BIGINT_DIFFRENT_SIZE;

/* common functions */
extern int bigint_init(bigint_s *ptr);

extern int bigint_free(bigint_s *ptr);

extern int bigint_set(bigint_s *dst, const char *hexString);

extern int bigint_get(char *dst, bigint_s *src);

extern int bigint_swap(bigint_s *a, bigint_s *b);

/* mathematical operations */
extern int bigint_add(bigint_s *dst, bigint_s *a, bigint_s *b);

extern int bigint_multiply(bigint_s *dst, bigint_s *a, bigint_s *b);

#endif  // BIGINT_H_

