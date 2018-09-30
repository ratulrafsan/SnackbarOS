cmake_minimum_required(VERSION 3.12)
project(snackbar C)

set(CMAKE_C_STANDARD 99)
include_directories(src/includes/ src/includes/libk src/includes/libc)
add_executable(snackbar src/kernel/kmain.c src/includes/vga.h src/kernel/vga.c src/includes/magicaddr.h src/includes/common.h src/includes/libk/kstdio.h src/libk/kstdio.c src/libc/string.c src/includes/libc/string.h)