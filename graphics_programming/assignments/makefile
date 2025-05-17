# Usage:
# make SOURCE=foo.c

CC = gcc
BUILD = build
FLAGS = -Wall -g
BINARY = a.out

all:
	mkdir -p $(BUILD)
	$(CC) $(FLAGS) $(SOURCE) -o $(BUILD)/$(BINARY) -lGL -lGLU -lglut -lm

clean:
	rm -f $(BUILD)/*

run:
	$(BUILD)/$(BINARY)

