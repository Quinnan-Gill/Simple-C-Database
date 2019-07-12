CC=gcc
CFLAGS=-I.
DEPS = input.h statement.h table.h
OBJ = db.o input.o statement.o table.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

db: $(OBJ)
	$(CC) -o db $^
	rm *.o

clean:
	rm *.o *.db db
