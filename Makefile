CC = gcc
CFLAGS = -O3 -march=native -flto -ffast-math -funroll-loops
TARGET = primes_c
SOURCE = primes_c.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) -lm

clean:
	del $(TARGET).exe

.PHONY: clean
