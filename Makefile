CC=gcc
INCLUDES=-I./include
CFLAGS:=-O0 -Wall -Wextra $(INCLUDES)
DEBUG_CFLAGS:=-DDEBUG -g3

TARGET=main

SRC_DIR=src
HEADER_DIR=include

SOURCES  = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
HEADERS  = $(wildcard $(HEADER_DIR)/*.h) $(wildcard $(HEADER_DIR)/*/*.h)

build: $(SOURCES) $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm -rf main

.PHONY: build clean