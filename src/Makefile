CC=gcc
CFLAGS=-I.
DEPS = input.h statement.h
OBJ = db.o input.o statement.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

db: $(OBJ)
	$(CC) -o db $^
	rm *.o

clean:
	rm db
