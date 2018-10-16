global load_GDT

load_GDT:
    mov eax, [esp+4] ; move the address of gdt_ptr to EAX
    lgdt [eax] ;
    ret