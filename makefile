# Dependencies (debian install command): `sudo apt-get install gcc-avr avr-libc avrdude`
# Arduino IDE also installs all necessary components

# Uncomment one, or create a new one

# Hugo's Mac
ARDUINO_PATH=/Users/hugo4it/Library/Arduino15/packages/arduino/hardware/avr/1.8.4
# Hugo's PC
#ARDUINO_PATH=/home/hugo4it/Downloads/ArduinoCore-avr

# Leave these be
COMPILER=avr-g++
COMPILERFLAGS=-Wall -Wextra -Os -DF_CPU=16000000UL -mmcu=ATmega2560 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -I$(ARDUINO_PATH)/cores/arduino -I$(ARDUINO_PATH)/variants/standard -g
LINKER=avr-g++
LINKERFLAGS=-mmcu=ATmega2560 lib/*.o
EXETOBIN=avr-objcopy
EXETOBINFLAGS=-O ihex -R .eeprom
UPLOADER=avrdude
UPLOADERFLAGS=-F -V -C avrdude.conf -c arduino -p atmega2560 -P /dev/ttyACM0 -b 115200 -D
UPLOADERFLAGS_ALT=-F -V -C /Users/hugo4it/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -c wiring -p atmega2560 -P /dev/cu.usbmodem11101 -b 115200 -D
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
	$(UPLOADER) $(UPLOADERFLAGS) -U flash:w:$< || $(UPLOADER) $(UPLOADERFLAGS_ALT) -U flash:w:$<
