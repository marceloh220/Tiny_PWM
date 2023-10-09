#### Project configuration options ####

# Name of target controller
MCU = attiny45

# Project name
PROJECTNAME = Tiny_PWM

# MCU Clock frequency
CLK_FREQ = 1000000UL

# Source files
SRC = adc.cpp button.cpp e2prom.cpp main.cpp power.cpp pwm.cpp timer.cpp

# Additional include paths
INCLUDES =

# Libraries to link in
LIBS =

# Optimization
# use s (size opt), 1, 2, 3 or 0 (off)
OPTIMIZE = s

# AVR Dude programmer
AVRDUDE_PROGRAMMER = usbasp

#### End project configuration ####

#### Flags

DEFINES = -DF_CPU=$(CLK_FREQ)

# Compiler
override FLAGS = -I. $(INCLUDES) -g -O$(OPTIMIZE) -mmcu=$(MCU) $(DEFINES) \
		-Wall -Werror -pedantic -pedantic-errors\
		-fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields \
		-ffunction-sections -fdata-sections \
		-MMD -flto
		
override CFLAGS = -std=gnu11 -fno-fat-lto-objects
		
override CPPFLAGS = -std=gnu++11 \
		-fpermissive -fno-exceptions -fno-threadsafe-statics \
		-Wno-error=narrowing
		

# Assembler
override ASMFLAGS = -I. $(INCLUDES) -mmcu=$(MCU) $(DEFINES) -c -g -x assembler-with-cpp -flto -MMD

# Linker
override LDFLAGS = -Wl,-Map,$(TRG).map $(CFLAGS)

#### Executables

CC = avr-gcc
CPP = avr-g++
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
AVRDUDE = avrdude
REMOVE = del


#### Target Names

TRG = $(PROJECTNAME).elf
DUMPTRG = $(PROJECTNAME).s

HEXROMTRG = $(PROJECTNAME).hex
HEXTRG = $(HEXROMTRG) $(PROJECTNAME).ee.hex
GDBINITFILE = gdbinit-$(PROJECTNAME)

# Filter files by type
CFILES = $(filter %.c, $(SRC))
CPPFILES = $(filter %.cpp, $(SRC))
ASMFILES = $(filter %.S, $(SRC))

# Generate list of object files
OBJS = $(CFILES:.c=.c.o) $(CPPFILES:.cpp=.cpp.o) $(ASMFILES:.S=.S.o)

# Define .lst files
LST = $(filter %.lst, $(OBJS:.o=.lst))


# Build all
all: $(TRG)
	
stats: $(TRG)
	$(OBJDUMP) -h $(TRG)
	$(SIZE) $(TRG)

hex: $(HEXTRG)

upload: hex
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -p $(MCU) -U flash:w:$(HEXROMTRG)

fuses: 
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -p $(MCU) -U lfuse:w:0x62:m -U hfuse:w:0xdc:m
	
size: 
	$(SIZE) -C --mcu=$(MCU) $(TRG)
    
# to use internal osc. for programing
# otherwise an external xtal is required
default: 
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -p $(MCU) -U lfuse:w:0x62:m -U hfuse:w:0xdc:m

program: default upload fuses

# Linking
$(TRG): $(OBJS) 
	$(CC) $(FLAGS) $(LDFLAGS) -o $(TRG) $(OBJS)

# Generate object files
%.c.o: src/%.c
	$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

%.cpp.o: src/%.cpp
	$(CPP) $(FLAGS) $(CPPFLAGS) -c $< -o $@
	
%.S.o: src/%.S
	$(CC) $(ASMFLAGS) -c $< -o $@

# Generate hex
%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.ee.hex: %.elf
	$(OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 $< $@

clean:
	$(REMOVE) *.o
	$(REMOVE) *.d
	$(REMOVE) *.map
	$(REMOVE) *.elf
	$(REMOVE) *.hex
