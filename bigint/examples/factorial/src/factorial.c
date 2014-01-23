/* ~ factorial.c
 *
 * Copyright (c) 2014 Rafal (robin92pl@gmail.com)
 * For licensing information please see LICENSE file located in main directory.
 *
 * Example usage of bigint library. Computs big factorials (like 1000).
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bigint/bigint.h"
#include "bigint/hexstring.h"

void print(int n, bigint_s *bi) {
    if (!bi) return;
    
    char buf[10000] = {0};
    bigint_get(buf, bi);
    
    printf("=> %d!\n%s\n\n", n, buf);
}

int factorial(bigint_s *result, int n) {
    int err = 0; 
    bigint_s tmp1, tmp2;
    
    bigint_init(&tmp1);
    bigint_init(&tmp2);
    
    bigint_set(&tmp1, "01");
    for (uint32_t i = 1; i <= n; i++) {
        char hex[1000] = {0};
        hexstring_encode(hex, (uint8_t*) &i, i/256 + 1);
        bigint_set(&tmp2, hex);
        err = bigint_multiply(result, &tmp2, &tmp1);
        if (err != BIGINT_OK) {
            fprintf(stderr, "Error during computing! (code = %d)\n", err);
            
            bigint_free(&tmp1);
            bigint_free(&tmp2);
            
            return err;
        }
        bigint_swap(result, &tmp1);
    }
    bigint_swap(result, &tmp1);
    
    bigint_free(&tmp1);
    bigint_free(&tmp2);
    
    return 0;
}

int main(int argc, char **argv) {    
    bigint_s result;
    for (int i = 1; i < argc; i++) {
        int n = atoi(argv[i]);
        
        bigint_init(&result);
        factorial(&result, n); 
        print(n, &result);
        bigint_free(&result);
    }
    
    return 0;
}

