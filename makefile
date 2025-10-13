CC ?= gcc
CFLAGS ?= -O2 -fPIC -Wall -Wextra -I./src
LDFLAGS ?= -shared
SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)
TARGET := libgameboy_perfect_core.so

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
