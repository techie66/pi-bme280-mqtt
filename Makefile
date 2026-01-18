CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
LIBS = -lwiringPi -lpaho-mqtt3c
TARGET = main
SRC = src/main.c src/bme280.c src/mqtt_client_helper.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

debug: CFLAGS += -g -O0
debug: $(TARGET)

clean:
	rm -f $(TARGET)
