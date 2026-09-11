CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

LIBOPENCM3 = /home/ankitgote/Documents/Bare_Metal/libopencm3

CFLAGS = -mcpu=cortex-m3 -mthumb -Wall -O0 -g3 \
         -DSTM32L1 \
         -Iinc \
         -I$(LIBOPENCM3)/include

LDFLAGS = -Tlinkerscript.ld \
          -nostartfiles \
          -Wl,-Map=main.map

#object files from libopencm3
LIBOBJ = $(wildcard $(LIBOPENCM3)/lib/stm32/l1/*.o)

all: main.elf main.bin

#object files from the project
main.elf: src/main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBOBJ)

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o main.elf main.bin main.map

flash: main.elf
	openocd -f interface/stlink.cfg -f target/stm32l1.cfg \
		-c "program main.elf verify" \
		-c "reset run" \
		-c "shutdown"