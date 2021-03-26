CC= gcc
CXX= g++

CFLAGS= -g -Wall -Wextra -Iinclude
CXXFLAGS= -g -Wall -Wextra -std=c++17 -Iinclude -O0 #-fno-tree-vectorize
LDFLAGS = $(CXXFLAGS)


all: init exe

init:
	mkdir -p obj
	mkdir -p bin

init_asm:
	mkdir -p asm

# Projects
exe: bin/executable
asm: init_asm asm/executable


# Binaries
bin/executable: obj/main.o obj/vec4.o
	$(CXX) $^ -o bin/executable $(LDFLAGS)

asm/executable: asm/main.a asm/vec4.a



# Source files
obj/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
obj/%.o: src/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

# Assembly files
asm/%.a: src/%.c
	$(C) -o $@ -c $< -S -fverbose-asm -Wa,-a1h $(CFLAGS)
asm/%.a: src/%.cpp
	$(CXX) -o $@ -c $< -S -fverbose-asm -Wa,-a1h $(CXXFLAGS)


# Cleaning
.PHONY: clean mrproper alldir
clean: 
	rm -f obj/*.o asm/*.a bin/executable

mrproper: clean
	rm -f obj/*.o obj/*/*.o bin/*

alldir: mrproper
	rm -r obj/* obj bin
