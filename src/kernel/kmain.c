#include <stdint.h>
#include <vga.h>
#include <kstdio.h>

struct gdt{
    uint32_t address;
    uint16_t size;
}__attribute__((packed));

int32_t k_main(){
    vga_clear_screen();
    vga_write_cell('t', VGA_COLOR_CYAN, VGA_COLOR_WHITE);
    k_puts("Bidai pitibi :(");
    return 0x5555;
}