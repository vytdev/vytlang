# C compiler to use
CC = clang
# flags to pass to the compiler and linker
CFLAGS = -std=c99 -Wall -pedantic -MMD -MP
LDFLAGS =
# some paths
DRS = $(patsubst src%,out%,$(shell find src -type d))
SRC = $(shell find src -type f -name '*.c')
OBJ = $(patsubst src/%.c,out/%.o,$(SRC))
DEP = $(OBJ:.o=.d)
# the output binary
TARGET = vyl

all: dirs $(TARGET)

out/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

dirs:
	mkdir -p $(DRS)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# include dependency files
-include $(DEP)

# our sub commands
.PHONY: clean debug

clean:
	rm -rf out $(TARGET)

debug: CFLAGS += -g -D__DEBUG
debug: LDFLAGS += -g
debug: all
