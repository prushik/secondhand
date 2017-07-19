DEVICE     = atmega328p
PROGRAMMER = arduino
PORT       = /dev/arduino
BAUD       = 57600
FILENAME   = src/ass
COMPILE    = avr-gcc -Wall -O3 -mmcu=$(DEVICE)
SUDO       = sudo
DEPS       = src/tokenizer.c
CFLAGS     = -I./include
LDFLAGS    = 

all: clean build upload

build:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o $(CFLAGS)
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o $(DEPS) $(CFLAGS) $(LDFLAGS)
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	$(SUDO) avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i 

clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex
