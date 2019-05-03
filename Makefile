
# gcc is ok for this
CC = gcc


INCLUDE_DIRECTORY = include
SOURCE_DIRECTORY = source
BUILD_DIRECTORY = build


CFLAGS = -I$(INCLUDE_DIRECTORY) -g -Wall -Werror -pedantic -std=gnu11 -lm

_OBJECT_FILES = network.o

OBJ = $(patsubst %,$(BUILD_DIRECTORY)/%,$(_OBJECT_FILES))


all: main

.PHONY: makebuild

makebuild:
	@mkdir -p build

LIB_NAME = libminneuron.a

LIBS = -lmath


$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.c makebuild
	$(CC) -c -o $@ $< $(CFLAGS)


main: $(OBJ)
	ar rcs $(BUILD_DIRECTORY)/$(LIB_NAME) $^
	@echo Library Succesfully compiled!!!

.PHONY: clean
clean:
	rm -f $(BUILD_DIRECTORY)/*.o $(BUILD_DIRECTORY)/main
