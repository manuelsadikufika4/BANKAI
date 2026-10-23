CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -O2
LDFLAGS = -lpcap -lpthread

SRC = src/main.c src/port_scanner.c src/wifi_audit.c src/exporter.c
OBJ = $(SRC:.c=.o)
TARGET = bankai

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) bankai_report.json

.PHONY: all clean