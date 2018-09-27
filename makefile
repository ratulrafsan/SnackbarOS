#OBJECTS = loader.o kmain.o kio.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T linker.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

BUILD_DIR = build
SRC_DIR = src

print-%: ; @echo $* = $($*)

all: kernel.elf

run: os.iso
	bochs -f bochs/bochsrc.txt -q -rc bochs/debug.rc

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.s)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%_s.o)

kernel.elf: $(OBJ_FILES)
	ld $(LDFLAGS) $(OBJ_FILES) -o $(BUILD_DIR)/kernel.elf

os.iso: kernel.elf
	cp $(BUILD_DIR)/kernel.elf iso/boot/kernel.elf
	genisoimage -R 								\
				-b boot/grub/stage2_eltorito 	\
				-no-emul-boot					\
				-boot-load-size 4				\
				-A os							\
				-input-charset utf8				\
				-boot-info-table				\
				-o os.iso						\
				iso
	cp os.iso $(BUILD_DIR)/os.iso

clean:
	rm -rf $(BUILD_DIR)
