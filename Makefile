SRC = $(wildcard ./*.c)
OBJ = $(patsubst %.c,%.o,$(SRC))
TARGET = output
CFLAGS = -Wall -Werror -g


all: $(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

run:$(TARGET)
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)

.PHNOY: all clean run
