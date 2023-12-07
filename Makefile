CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
SRC = main.c reversing.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = RETools

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRC)

clean:
	rm -f $(OBJ) $(EXECUTABLE)
