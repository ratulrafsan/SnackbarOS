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

    ; push multiboot info address & magic number to stack
    push eax
    push ebx

    ;jmp hang
    call k_main

hang:
    jmp hang
