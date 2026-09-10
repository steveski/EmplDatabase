TARGET = bin/kvtable
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*.o

$(TARGET): $(OBJ)
	gcc -o $@ $?

obj/%.o : src/%.c
	gcc -c $< -o $@ -Iinc -Wall
