cmake_minimum_required(VERSION 3.12)
project(snackbar C)

set(CMAKE_C_STANDARD 99)

add_executable(snackbar src/kmain.c src/includes/clib/ministdint.h src/includes/kio.h src/kio.c src/includes/magicaddr.h)