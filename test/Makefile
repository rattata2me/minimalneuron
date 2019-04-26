

# gcc is ok for this
CC = gcc

LIBRARY_DIRECTORY = ../build
INCLUDE_LIBRARY = ../include
INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = source
BUILD_DIRECTORY = build

CFLAGS = -I$(INCLUDE_DIRECTORY) -I$(INCLUDE_LIBRARY) -g -Wall -Werror -pedantic -std=gnu11

_OBJECT_FILES = main.o

OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))

LIBS = -lm -L$(LIBRARY_DIRECTORY) -lminneuron

all: makebuild library main

.PHONY: makebuild

makebuild:
	@mkdir -p build
	@mkdir -p build
	@mkdir -p build

library:
	cd $(LIBRARY_DIRECTORY)/.. && make all

$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $(BUILD_DIRECTORY)/$@ $^ $(CFLAGS) $(LIBS)
	@echo Executable successfully compiled!

.PHONY: clean
clean:
	rm -f $(BUILD_DIRECTORY)/*.o $(BUILD_DIRECTORY)/main
	@cd $(LIBRARY_DIRECTORY) && cd .. && make clean
