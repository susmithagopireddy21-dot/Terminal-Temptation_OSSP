CC = gcc
CFLAGS = -Wall -Wextra
TARGET = skill01_process

all: $(TARGET)

$(TARGET): skill01_process.c
	$(CC) $(CFLAGS) skill01_process.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
