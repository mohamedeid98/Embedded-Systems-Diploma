
#@copyright : Eng. Mohamed

CC=arm-none-eabi-
CFLAGS=-gdwarf-2 -g -mcpu=cortex-m4 -mthumb
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project_Name=ARM_CortexM4

all: $(Project_Name).bin
	@echo "============Build Done===================="

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@



$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(AsOBJ) $(OBJ) -o $@ -Map=Map_file.map
	cp $(Project_Name).elf $(Project_Name).axf
	
$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@



clean:
	rm *.elf *.bin *.map

clean_all:
	rm *.o *.bin *.elf *.map