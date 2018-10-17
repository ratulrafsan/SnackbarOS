; Flushes old gdt and installs a newly defined one pointed by gdt_ptr
global gdt_flush
gdt_flush:
    mov eax, [esp + 4] ; Get the pointer to gdt
    lgdt [eax]         ; Load the newly defined gdt
    mov ax, 0x10       ; 0x10 is the offset in the new gdt to the data segment
    mov ds, ax         ; Load all data sectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush    ; 0x08 is the offset to code segment. This line performs a far jump
flush:
    ret