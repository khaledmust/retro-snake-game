# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Ilibs/raylib/include -Iobjects -Ilibs/deque
LDFLAGS = -Llibs/raylib/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Source files
LIBS_DIR = libs
OBJECTS_DIR = objects

# Object files
OBJECTS = $(OBJECTS_DIR)/snake.o $(OBJECTS_DIR)/food.o
GAME_OBJECTS = $(LIBS_DIR)/deque/deque.o $(OBJECTS)

# Main source file
MAIN_SRC = main.c

# Executable
EXECUTABLE = my_game

# Build rule
$(EXECUTABLE): $(GAME_OBJECTS) main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Object files rule
$(OBJECTS_DIR)/%.o: $(OBJECTS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Main object file rule
main.o: $(MAIN_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(EXECUTABLE) $(GAME_OBJECTS) main.o

.PHONY: clean
