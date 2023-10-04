BIN=$(shell basename $(CURDIR))
CFLAGS=-Wall -Wextra -std=c11 -g

C_FILES=$(wildcard src/*.c)
O_FILES=$(patsubst src/%.c, obj/%.o, $(C_FILES))
H_FILES=$(wildcard src/*.h)

.PHONY: all clean run
all: $(BIN)

run: $(BIN)
	./$(BIN)

$(BIN): $(O_FILES)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c $(H_FILES) obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir -p obj

clean:
	rm -rf $(BIN) obj
