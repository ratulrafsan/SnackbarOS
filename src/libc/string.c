//
// Created by ratulrafsan on 9/30/18.
//


#include <stddef.h> // for size_t
#include <stdint.h>

int memcmp(uint8_t* ptr_s1, uint8_t* ptr_s2, size_t n){
    if ( n == 0) return 0;

    for(size_t i = 0; i < n; i++){
        if(ptr_s1[i] < ptr_s2[i]) return 1;
        else if(ptr_s1[i] > ptr_s2[i]) return -1;
    }

    return 0;
}

