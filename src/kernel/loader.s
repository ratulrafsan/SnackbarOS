global loader                   ; the entry symbol of ELF
extern k_main

MAGIC_NUMBER equ 0x1BADB002     ; magic number const for multiboot header
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER  ; magic number + flag + checksum must yield 0

KERNEL_STACK_SIZE equ 4096      ; size of the stack in bytes

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE      ; reserve stack for the kernel

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE ; point esp to the start of the stack
    call k_main

    ;read cr0 register for debug purpese
    mov eax, cr0

hang:
    jmp hang