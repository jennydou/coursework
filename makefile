CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c my_lib.c
OBJ = $(SRC:.c=.o)
EXEC = vetclinic

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)
