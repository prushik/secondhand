DEVICE     = atmega328p
PROGRAMMER = arduino
PORT       = /dev/ttyUSB0
BAUD       = 57600
FILENAME   = ass
COMPILE    = avr-gcc -Wall -Os -mmcu=$(DEVICE)
SUDO       = sudo
DEPS       = src/tokenizer.c

all: clean build upload

build:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o $(DEPS)
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload:
	$(SUDO) avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i 

clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex
