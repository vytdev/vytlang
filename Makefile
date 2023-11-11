CC = gcc
CFLAGS = -std=c99 -Wall
LDFLAGS = 
SRC = $(shell find src -type f -name '*.c')
OBJ = $(SRC:.c=.o)
TARGET = vyl

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# our sub commands
.PHONY: clean debug

clean:
	rm $(OBJ) $(TARGET)

debug: CFLAGS += -g -D__DEBUG
debug: LDFLAGS += -g
debug: all
