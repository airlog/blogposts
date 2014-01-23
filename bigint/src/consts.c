/* ~ consts.c
 *
 * Copyright (c) 2014 Rafal (robin92pl@gmail.com)
 * For licensing information please see LICENSE file located in main directory.
 *
 * Contains declarations of constants used throughout the library.
 */

#include "bigint/bigint.h"

#include <stdint.h>

/* settings */
const uint32_t BIGINT_BASE                   = 256;     // please do not change this
const uint32_t BIGINT_DEFAULT_SIZE           = 2*1024;  // 2 kB

/* errors' constants */
const int BIGINT_OK                 =  0;
const int BIGINT_INVALID_ARGUMENT   = -1;
const int BIGINT_OUT_OF_MEMORY      = -2;
const int BIGINT_DIFFRENT_SIZE      = -3;

