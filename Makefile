# Makefile for Raylib Program

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -I./libs/raylib/include\
-I./libs/gamelib\
-L./libs/raylib/lib\
-L./libs/gamelib\
-lraylib -lGL -lm -lpthread -ldl -lrt -lX11


# Source file and output executable
SRC = main.c \
./libs/gamelib/gameobject.c \
./libs/gamelib/deque.c
OUT = raylib_program

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC)  $(CFLAGS) -o $(OUT)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
