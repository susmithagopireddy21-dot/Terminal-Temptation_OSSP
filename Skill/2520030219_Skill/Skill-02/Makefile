CC = gcc
CFLAGS = -Wall -Wextra
TARGET = bin/mini-shell
SOURCES = src/main.c src/input.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
