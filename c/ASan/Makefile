# Makefile

CC=gcc
CFLAGS=-fsanitize=address -g -Wall
TARGET=sanitize

all: $(TARGET)

$(TARGET): sanitize.c
	$(CC) $(CFLAGS) sanitize.c -o $(TARGET)

clean:
	rm -f $(TARGET)

