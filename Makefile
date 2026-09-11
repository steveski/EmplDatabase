TARGET = bin/kvtable
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
CFLAGS_COMMON_17 = -Wall -Wextra -std=c17 -Iinc
CFLAGS_COMMON = -Wall -Wextra -Iinc
CFLAGS_DEBUG = $(CFLAGS_COMMON) -g -O0
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2 -DNDEBUG

.PHONY: default release debug clean

default: release

release: CFLAGS = $(CFLAGS_RELEASE)
release: clean $(TARGET)

debug: CFLAGS = $(CFLAGS_DEBUG)
debug: clean $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $@ $^

obj/%.o : src/%.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o
	rm -f $(TARGET)


