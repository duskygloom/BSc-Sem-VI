CC = gcc
CFLAGS = -Wall -g -lGL -lGLU -lglut -lm
BUILD = build
BINARY = a.out

FLAT_OBJECTS = $(BUILD)/vector.o $(BUILD)/flat_shading.o
GOUROUD_OBJECTS = $(BUILD)/vector.o $(BUILD)/matrix.o $(BUILD)/gouroud_shading.o

flat: start $(FLAT_OBJECTS)
	$(CC) $(FLAT_OBJECTS) -o $(BINARY) $(CFLAGS)

gouroud: start $(GOUROUD_OBJECTS)
	$(CC) $(GOUROUD_OBJECTS) -o $(BINARY) $(CFLAGS)

$(BUILD)/%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

start:
	mkdir -p $(BUILD)

clean:
	rm -f $(BUILD)/*.o $(BINARY)

run:
	./$(BINARY)
	
