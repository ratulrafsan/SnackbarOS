//
// Created by ratulrafsan on 9/30/18.
//

#ifndef SNACKBAR_STRING_H
#define SNACKBAR_STRING_H

#include <stdint.h>
#include <stddef.h>

int memcmp(const void* ptr_str1, const void* ptr_str2, size_t n);
void* memset(void* ptr_str, int value, size_t n);
void* memcpy(void* ptr_dest, void* ptr_src, size_t n);
void* memmove(void* ptr_dest, void* ptr_src, size_t n);
void itoa(char *buf, unsigned long int n, int base);


#endif //SNACKBAR_STRING_H
