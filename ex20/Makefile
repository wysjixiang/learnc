SRC = $(wildcard ./*.c)
OBJ = $(patsubst %.c,%.o,$(SRC))
TARGET = out
CFLAGS = -Wall -Werror -g -DNDEBUG


all: $(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

run:$(TARGET)
	./$(TARGET) test

clean:
	rm -rf *.o $(TARGET)

.PHNOY: all clean run
