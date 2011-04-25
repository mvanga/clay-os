CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
CP=$(CROSS_COMPILE)objcopy
OD=$(CROSS_COMPILE)objdump
  
CFLAGS=-mcpu=cortex-m3 -mthumb -Wall -Wextra -I./include -fno-builtin
LDFLAGS=-Tlink.ld -nostartfiles

SOURCES=kernel/main.o kernel/boot.o kernel/gpio.o kernel/uart.o kernel/systick.o

SOURCES += lib/atoi.o lib/ctype.o lib/printk.o lib/rand.o lib/sprintf.o lib/string.o lib/strtol.o lib/vsprintf.o

CFLAGS += -I./lib/include -nostdlib

all: main.bin checksum

clean:
	rm -rf main.lst main.elf main.lst main.bin $(SOURCES)

main.bin: main.elf
	$(CP) -Obinary main.elf main.bin

main.elf: $(SOURCES) link.ld 
	$(LD) $(LDFLAGS) -o main.elf $(SOURCES)

checksum:
	tools/lpcsum main.bin

del:
	sudo mdel c:firmware.bin

install:
	sudo mcopy main.bin c:firmware.bin
