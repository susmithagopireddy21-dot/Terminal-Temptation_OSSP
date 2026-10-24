CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = bin/mini-shell
SOURCES = src/main.c src/input.c src/history.c
HEADERS = src/input.h src/history.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
