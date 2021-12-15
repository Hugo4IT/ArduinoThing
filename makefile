# Dependencies (debian install command): `sudo apt-get install gcc-avr avr-libc avrdude`

# Modify these
ARDUINO_PATH=/home/hugo4it/Downloads/ArduinoCore-avr

# Leave these be
COMPILER=avr-g++
COMPILERFLAGS=-Wall -Wextra -Os -DF_CPU=16000000UL -mmcu=atmega328p -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -I$(ARDUINO_PATH)/cores/arduino -I$(ARDUINO_PATH)/variants/standard -include Arduino.h -Wl,--gc-sections -g
LINKER=avr-gcc
LINKERFLAGS=-mmcu=atmega328p
EXETOBIN=avr-objcopy
EXETOBINFLAGS=-O ihex -R .eeprom
UPLOADER=avrdude
UPLOADERFLAGS=-F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U
UPLOADERFLAGS_ALT=-F -V -c arduino -p ATMEGA328P -P /dev/cu.usbmodem11101 -b 115200 -U
EXECUTABLE_OUT=bin/app.bin_exec
BINARY_OUT=bin/app.hex

SOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.cpp,bin/%.o,$(SOURCES))
DEPENDS := $(patsubst src/%.cpp,bin/%.d,$(SOURCES))

.PHONY: default
default: upload

clean:
	rm -f bin/*.o bin/*.d

-include $(DEPENDS)

bin/%.o: src/%.cpp makefile
	$(COMPILER) $(COMPILERFLAGS) -MMD -MP -MF bin/$*.d -c -o $@ $<

executable: $(EXECUTABLE_OUT)
$(EXECUTABLE_OUT): $(OBJECTS)
	$(LINKER) $(LINKERFLAGS) $^ -o $@

binary: $(BINARY_OUT)
$(BINARY_OUT): $(EXECUTABLE_OUT) makefile
	$(EXETOBIN) $(EXETOBINFLAGS) $< $@

run: upload
upload: $(BINARY_OUT)
	$(UPLOADER) $(UPLOADERFLAGS) flash:w:$(@<) || $(UPLOADER) $(UPLOADERFLAGS_ALT) flash:w:$(@<)
