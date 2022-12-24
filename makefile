TARGET = build/sb.exe

CC = g++

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst src/%,build/objs/%,$(SOURCES:%.c=%.o))

TEST_SOURCES = $(filter-out src/main.c,$(SOURCES)) $(wildcard test/*.test.c)
TEST_OBJECTS = $(addprefix build/objs/, $(notdir $(TEST_SOURCES:%.c=%.o)))

# Commands

build: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET) $(VAR)

.PHONY: test
test: build/test.exe
	./build/test.exe

.PHONY: clean
clean:
	rm -f build/objs/*.o

.PHONY: reset
reset: clean
	rm -f build/*.exe


# Build Rules

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

build/objs/%.test.o: test/%.test.c test/*.h src/*.h
	$(CC) -I./src -I./test -c -o $@ $<

build/objs/%.o: src/%.c src/*.h
	$(CC) -I./src -I./test -c -o $@ $<

build/test.exe: $(TEST_OBJECTS)
	$(CC) -o $@ $^
