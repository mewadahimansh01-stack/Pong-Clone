.PHONY: build run clean all format

build:
	cmake -G Ninja -S . -B build/ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	cmake --build build/

run:
	./build/pong

clean:
	rm -rf build/

all: build run

format:
	find src -iname '*.h' -o -iname '*.c' -o -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i

