CC = gcc
CFLAGS = -Wall -g -lGL -lGLU -lglut -lm
BUILD = build
BINARY = a.out

OBJECTS = $(BUILD)/vector.o $(BUILD)/flat_shading.o

all: start $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINARY) $(CFLAGS)

$(BUILD)/%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

start:
	mkdir -p $(BUILD)

clean:
	rm -f $(BUILD)/*.o $(BINARY)

run:
	./$(BINARY)
	
