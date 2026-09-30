CC = gcc
CFLAGS = -Wall -Wextra
TARGET = skill02_shell

all: $(TARGET)

$(TARGET): skill02_shell.c
	$(CC) $(CFLAGS) skill02_shell.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
