#include "includes/clib/ministdint.h"
#include "includes/kio.h"

struct gdt{
    uint32_t address;
    uint16_t size;
}__attribute__((packed));

int32_t k_main(){
    k_clear_screen();
    k_putchar('c');
    k_putserr("Wow! an error message :D \n");
    k_write_cell('t', VGA_COLOR_CYAN, VGA_COLOR_GREEN);
    k_puts("hello world\n");
    k_puts("New\nLine\nTest\n");
    k_puts("Tab\tmore\ttab\teven\tmore\tabtab\teverything\n");
    k_puts_color("What a colorful \t world we live in~",  VGA_COLOR_LIGHT_BLUE, VGA_COLOR_LIGHT_BROWN);
    k_puts_color("Dull color", VGA_COLOR_BLACK, VGA_COLOR_WHITE);
    k_puts_color("Normal text with k_puts_color",  VGA_COLOR_WHITE ,VGA_COLOR_BLACK);
    return 0x5555;
}