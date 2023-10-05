BIN=$(shell basename $(CURDIR))
CFLAGS=-Wall -Wextra -g -Isrc -std=gnu17

C_FILES=$(wildcard src/*.c)
O_FILES=$(patsubst src/%.c, obj/%.o, $(C_FILES))
H_FILES=$(wildcard src/*.h)

.PHONY: all clean run headers vars licenses
all: $(BIN)

run: $(BIN)
	./$(BIN)

$(BIN):  src/licenses.h $(O_FILES)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c $(H_FILES) obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir -p obj

clean:
	rm -rf $(BIN) obj src/licenses.h

vars:
	@echo "BIN: $(BIN)"
	@echo "C_FILES: $(C_FILES)"
	@echo "O_FILES: $(O_FILES)"
	@echo "H_FILES: $(H_FILES)"
	@echo "LICENSE_FILE: $(LICENSE_FILES)"
	@echo "LICENSE_HEADER: $(LICENSE_HEADERS)"

src/licenses.h: scripts/update-licenses.sh
	./scripts/update-licenses.sh > $@
