# Makefile

CC=gcc
# CFLAGS=-fsanitize=null -fsanitize=enum -fsanitize=address -fsanitize=alignment -g -Wall
CFLAGS+=-Iinc -Ia
TARGET=main

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET)

