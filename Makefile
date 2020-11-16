CONFIG=Debug

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
