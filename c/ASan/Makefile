# Makefile

CC=gcc
CFLAGS=-fsanitize=null -fsanitize=enum -fsanitize=address -fsanitize=alignment -g -Wall
TARGET=sanitize

all: $(TARGET)

$(TARGET): sanitize.c
	$(CC) $(CFLAGS) sanitize.c -o $(TARGET)

clean:
	rm -f $(TARGET)

