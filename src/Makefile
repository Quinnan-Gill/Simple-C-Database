CC=gcc
INCFLAGS=-I.
DEPS = *.h
OBJ = db.o input.o statement.o queue.o table.o
CFLAGS = -c -g

all: db

debug: CFLAGS += -DDEBUG
debug: db
	
db: $(OBJ)
	$(CC) -o db $^
	rm *.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $< $(INCFLAGS)

clean:
	rm *.o *.db db
