CFLAGS         += -Wno-visibility -Wno-incompatible-pointer-types -Wall -Wextra
CFLAGS         += -DINVERT_COLORS -DVT100 -O2
LFLAGS         +=

CONFIG=Debug

PROGRAM := 2048
C_FILES := $(wildcard src/*.c)
MERGE_FILE := src/merge_std.c
FILTERED_C_FILES := $(filter-out src/gfx%.c src/merge%.c, $(C_FILES))


all: curses

curses: 
	mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=$(CONFIG) -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DNCURSES=YES ../ && make all -j$(nproc) -lcurses

terminal:
	mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=$(CONFIG) -DCMAKE_EXPORT_COMPILE_COMMANDS=YES ../ && make all -j$(nproc)

remake: clean all

clean:
	rm -rf build

.PHONY: clean remake

.PHONY: 
install-deps: 
	apt-get install -y gettext
