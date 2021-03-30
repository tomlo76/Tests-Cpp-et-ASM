CC= gcc
CXX= g++
ASA= as

CFLAGS= -g -Wall -Wextra -Iinclude
CXXFLAGS= -g -Wall -Wextra -std=c++17 -Iinclude -O3 #-fno-tree-vectorize
ASFLAGS= --warn --gstabs+
LDFLAGS = $(CXXFLAGS)


ifeq ($(OS),Windows_NT)
    #Windows stuff
    ASM_OS=win
else
    #Linux stuff
    ASM_OS=linux
endif


VEC4OBJ= obj/vec4.o obj/vec4_operations.o obj/vec4_operations_asm_wrapper.o obj/vec4_operations_$(ASM_OS).o
VEC4ASM= asm/vec4.a asm/vec4_operations.a asm/vec4_operations_asm_wrapper.a




all: init exe

init:
	mkdir -p obj
	mkdir -p bin

init_asm:
	mkdir -p asm

# Projects
exe: bin/executable bin/testvec4
asm: init_asm asm/executable


# Binaries
bin/executable: obj/main.o $(VEC4OBJ)
	$(CXX) $^ -o bin/executable $(LDFLAGS)

bin/testvec4: obj/testvec4.o obj/vec4.o
	$(CXX) $^ -o bin/vec4 $(LDFLAGS)

asm/executable: asm/main.a $(VEC4ASM)



# Source files
obj/%.o: src/%.s
	$(ASA) -o $@ -c $< $(ASFLAGS)
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
.PHONY: clean asmclean mrproper clearalldir
clean: 
	rm -f obj/*.o bin/*

asmclean:
	rm -f asm/*.a

mrproper: clean asmclean
	rm -f obj/*.o obj/*/*.o bin/*

clearalldir: mrproper
	rm -r obj bin asm
