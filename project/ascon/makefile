CC = g++
FLAGS = -Wall -g
BUILD = build
BINARY = a.out

OBJECTS = $(BUILD)/byte_arr.o $(BUILD)/ascon.o $(BUILD)/$(SOURCE:%.cpp=%.o)

all: $(OBJECTS)
	$(CC) -o $(BUILD)/$(BINARY) $(OBJECTS) $(FLAGS)

$(BUILD)/%.o: %.cpp
	$(CC) -c $< -o $@ $(FLAGS)

start:
	mkdir -p $(BUILD)

clean:
	rm -f $(BUILD)/*.o $(BUILD)/$(BINARY)

run:
	$(BUILD)/$(BINARY)
