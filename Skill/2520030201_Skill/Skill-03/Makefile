CC = gcc
CFLAGS = -Wall -Wextra
TARGET = skill03_shell

all: $(TARGET)

$(TARGET): skill03_shell.c
	$(CC) $(CFLAGS) skill03_shell.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(TARGET)
