BIN=$(shell basename $(CURDIR))
CFLAGS=-Wall -Wextra -std=c11 -g -Isrc

C_FILES=$(wildcard src/*.c)
O_FILES=$(patsubst src/%.c, obj/%.o, $(C_FILES))
H_FILES=$(wildcard src/*.h)
LICENSE_FILES=$(wildcard licenses/*.txt)
LICENSE_HEADERS=$(patsubst licenses/%.txt, src/licenses/%.h, $(LICENSE_FILES))

.PHONY: all clean run headers
all: $(BIN)

run: $(BIN)
	./$(BIN)

headers: $(LICENSE_HEADERS)

$(BIN):  $(LICENSE_HEADERS) $(O_FILES)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c $(H_FILES) obj
	$(CC) $(CFLAGS) -c -o $@ $<

obj:
	mkdir -p obj

src/licenses/%.h: licenses/%.txt
	mkdir -p src/licenses
	./license2header.sh $< $@

clean:
	rm -rf $(BIN) obj

vars:
	@echo "BIN: $(BIN)"
	@echo "C_FILES: $(C_FILES)"
	@echo "O_FILES: $(O_FILES)"
	@echo "H_FILES: $(H_FILES)"
	@echo "LICENSE_FILE: $(LICENSE_FILES)"
	@echo "LICENSE_HEADER: $(LICENSE_HEADERS)"
