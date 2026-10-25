CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
TARGET = bin/skill04-parser
SOURCES = src/main.c src/tokenizer.c src/parser.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
