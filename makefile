#BIN_DIR points to the location of your cross compiler
BIN_DIR = /opt/cross/bin
#Target architecture for the cross compuler
ARCH = i686-elf

CC = $(BIN_DIR)/$(ARCH)-gcc
LINKER = $(BIN_DIR)/$(ARCH)-ld
AS = nasm

CFLAGS = -ffreestanding -Wall -Wextra -Werror -c
CFLAGS += -I $(ROOT_INCLUDE_DIR) -I $(LIBK_INCLUDE_DIR) -I $(LIBC_INCLUDE_DIR)
LDFLAGS = -T linker.ld
ASFLAGS = -f elf32

BUILD_DIR = build
SRC_DIR = src

ROOT_INCLUDE_DIR = $(SRC_DIR)/includes/
LIBK_INCLUDE_DIR = $(ROOT_INCLUDE_DIR)libk/
LIBC_INCLUDE_DIR = $(ROOT_INCLUDE_DIR)libc/

#For debug purpose. Prints out the content of a variable. USAGE: make print-VARNAME
#e.g: make print-C_FILES
print-%: ; @echo $* = $($*)

all: os.iso

run: os.iso
	bochs -f bochs/bochsrc.txt -q -rc bochs/debug.rc

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/**/*.c)
C_FILES += $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/**/*.s)
ASM_FILES += $(wildcard $(SRC_DIR)/*.s)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%_s.o)

kernel.elf: $(OBJ_FILES)
	$(LINKER) $(LDFLAGS) $(OBJ_FILES) -o $(BUILD_DIR)/kernel.elf

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
	mv os.iso $(BUILD_DIR)/os.iso

clean:
	rm -rf $(BUILD_DIR)
