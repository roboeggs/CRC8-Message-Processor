# Makefile for CRC8-Message-Processor

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = crc8_processor

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)
