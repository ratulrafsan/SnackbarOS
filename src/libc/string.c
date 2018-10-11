//
// Created by ratulrafsan on 9/30/18.
//


#include <stddef.h> // for size_t
#include <stdint.h>
#include <kstdio.h>

/**
 * Compare ptr_str1 & ptr_str2
 * @param ptr_str1 : First string
 * @param ptr_str2 : Second string
 * @param count    : How many bytes to check for
 * @return If count is 0, return 0
 * if ptr_str1 & ptr_str2 are equal, return 0
 * if ptr_str1 is greater than ptr_str2, return 1
 * if ptr_str1 is less than ptr_str2, return -1
 */

int memcmp(const void* ptr_str1, const void* ptr_str2, size_t count){
    const unsigned char* s1 = ptr_str1;
    const unsigned char* s2 = ptr_str2;

    while (count--){
        if(*s1++ != *s2++)
            return s1[-1] < s2[-1] ? -1 : 1;
    }
    return 0;
}


/**
 * Sets memory area of ptr_dest + len to val
 * @param ptr_dest : Where to copy to
 * @param val      : Which value to set
 * @param len      : How many bytes to cover
 * @return ptr_dest
 */
void* memset(void* ptr_dest, int val, size_t len){
    unsigned char* ptr = ptr_dest;
    while(len--){
        *ptr++ = val;
    }
    return ptr_dest;
}

/**
 *  Copies len bytes from ptr_src to ptr_dest. Doesn't care about overlapping.
 * @param ptr_dest : Where to copy to
 * @param ptr_src  : Where to copy from
 * @param len      : How many bytes to copy
 * @return ptr_dest
 */

void* memcpy(void* ptr_dest, const void* ptr_src, size_t len){
    char* dest = ptr_dest;
    const char* src = ptr_src;

    while(len--){
        *dest++ = *src++;
    }

    return ptr_dest;
}

/**
 * Copies n bytes from ptr_src to ptr_dest. Overlapping aware.
 * @param ptr_dest  : Where to copy to
 * @param ptr_src   : Where to copy from
 * @param len       : How many bytes to copy
 * @return ptr_dest
 */
void* memmove(void* ptr_dest, const void* ptr_src, size_t len){
    /* If the source & destination overlaps, we need to be careful not to
     * overwrite the data pointed by ptr_dest.
     * I.E.
     *        ptr_src = ..ssssssssssssssssss.......
     *                         ^                ^
     *                         |                |
     *       src_dest = .......dddddddddddddddddd...
     *
     * In such cases, we simply have to copy the source data to destination data backwards
     */

    // If ptr_dest points to an address lower than ptr_src then they don't overlap
    if(ptr_dest < ptr_src){
        return memcpy(ptr_dest, ptr_src, len);
    } else{
        // They overlap, so get the last address of both ptr_dest & ptr_src
        char* dest_end = ptr_dest + len;
        char* src_end = (char*)ptr_src + len;

        while(len--){
            *--dest_end = *--src_end;
        }
    }

    return ptr_dest;
}

/**
 * Converts numeric value to string
 *
 * @param buff  : Where to write the output to
 * @param n     : The number that will be converted
 * @param base  : Base of the target numeric value
 */
void itoa(char *buff, unsigned long int n, int base) {
    unsigned long int tmp;
    int i = 0;

    do {
        tmp = n % base;
        buff[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
    } while (n /= base);
    buff[i--] = '\0';

    for (int j = 0; j < i; j++, i--) {
        tmp = buff[j];
        buff[j] = buff[i];
        buff[i] = tmp;
    }
}
