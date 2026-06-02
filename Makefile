CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
LIBS = -lwiringPi -lmosquitto
TARGET = main
SRC = src/main.c src/bme280.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

debug: CFLAGS += -g -O0
debug: $(TARGET)

clean:
	rm -f $(TARGET)
