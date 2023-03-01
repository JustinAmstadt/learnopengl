# Compiler options
CC=g++
CFLAGS=-c -Wall
GL_FLAGS = -lGL -ldl -lglfw -lm

# Linker options
LDFLAGS=

# Source files
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
EXE=main

# Rules
all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) glad.c -o $@ $(GL_FLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(EXE)
