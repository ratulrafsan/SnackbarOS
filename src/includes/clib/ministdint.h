//
// Created by ratulrafsan on 9/23/18.
//

#ifndef SNACKBAR_MINISTDINT_H
#define SNACKBAR_MINISTDINT_H

#endif //SNACKBAR_MINISTDINT_H


#ifndef  __int_t_defined
#define  __int_t_defined
typedef signed char int8_t;
typedef short int   int16_t;
typedef int         int32_t;
typedef long int    int64_t;
#endif

#ifndef __uint_t_defined
#define __uint_t_defined
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long int   uint64_t;
#endif

//Limits of integral types

//Minimum of signed integral types:
#define INT8_MIN            (-128)
#define INT16_MIN           (-32768)
#define INT32_MIN           (-2147483648)
#define INT64_MIN           (-9223372036854775808)

//Maximum of signed integral types
# define INT8_MAX                (127)
# define INT16_MAX                (32767)
# define INT32_MAX                (2147483647)
# define INT64_MAX                (9223372036854775807)

//Maximum of unsigned integral types
# define UINT8_MAX                (255)
# define UINT16_MAX                (65535)
# define UINT32_MAX                (4294967295)
# define UINT64_MAX                (18446744073709551615)