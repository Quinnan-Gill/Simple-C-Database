CC=gcc
CFLAGS=-I.
DEPS = input.h
OBJ = db.o input.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

db: $(OBJ)
	$(CC) -o db db.o input.o
	rm *.o

clean:
	rm *.o db
