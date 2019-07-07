CC=gcc
CFLAGS=-I.
DEPS = input.h statement.h row.h
OBJ = db.o input.o statement.o row.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

db: $(OBJ)
	$(CC) -o db $^
	rm *.o

clean:
	rm -rf *.o
	rm db
