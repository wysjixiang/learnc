
OUTPUT = out
SRC = $(wildcard src/**/*.c src/*.c)
OBJ = $(patsubst %.c,%.o,$(SRC))

CFLAGS = -g -O2 -Wall -Werror -Isrc -rdynamic $(OPTFLAGS)
# -Isrc: include /src folder when compiling. -I: include
# -rdynamic: used when linking dynamic lib. it writes string tables
# to executable files so it can parse the string table
# -fPIC: using position independent code to compile. PIC: position independent code
# so that code could be used in various platforms.
LIBS = -ldl $(OPTLIBS)
PREFIX ?= 

TEST_SRC = $(wildcard test/**/*.c test/*.c)
TESTS = $(patsubst %.c,%,$(TEST_SRC))


TARGET = build/lib.a
SO_TARGET = $(patsubst %.a,%.so,$(TARGET))


# test!
lib: $(TARGET) $(SO_TARGET) 
lib_test: lib
	gcc -o $(OUTPUT) src/test.c $(TARGET) $(LIBS)
	./$(OUTPUT)


# The target build
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS= -g -Wall -Isrc -Wextra $(OPTFLAGS)
dev: all


# to generate static lib 
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJ) # build command is to make sure build/ exists
	ar rcs $@ $(OBJ)
	ranlib $@

# to generate dynamic lib
$(SO_TARGET): $(TARGET) $(OBJ)
	$(CC) -shared -o $@ $(OBJ)

build:
	@mkdir -p build
	@mkdir -p bin
# -p to create the folder if the folder doesn't exist
# so -p command makes sure the folder exists

# The Unit test
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND = "valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)


# The Cleaner
clean:
	rm -rf build $(OBJ) $(TESTS)
	rm -f $(OUTPUT)
	rm -f test/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf 'find . -name "*.dSYM" -print'

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true