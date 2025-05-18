CC = gcc
FLAGS = -Wall -g
BUILD = build
BINARY = a.out

OBJECTS = $(BUILD)/vector.o $(BUILD)/matrix.o $(BUILD)/$(SOURCE:%.c=%.o)

all: $(OBJECTS)
	$(CC) -o $(BINARY) $(OBJECTS) $(FLAGS) -lGL -lGLU -lglut -lm

$(BUILD)/%.o: %.c
	$(CC) -c $< -o $@ $(FLAGS) -lGL -lGLU -lglut -lm

start:
	mkdir -p $(BUILD)

clean:
	rm -f $(BUILD)/*.o $(BINARY)

run:
	./$(BINARY)
