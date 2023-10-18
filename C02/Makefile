CC=gcc
PROGS=run_simulation
CFLAGS=-std=c99 -Wall -Wpedantic
LFLAGS=-lm

all: $(PROGS)

utilities.o: utilities.h utilities.c
	$(CC) $(CFLAGS) -c utilities.c
	
shallow-water-advanced.o: shallow-water-advanced.c utilities.h utilities.c
	$(CC) $(CFLAGS) -c shallow-water-advanced.c
	
run_simulation: shallow-water-advanced.o utilities.o
	$(CC) $(LFLAGS) -o run_simulation ./shallow-water-advanced.o utilities.o
	
	
clean:
	rm -f *.o $(PROGS)


# gcc -std=c99 -Wall -Wpedantic -c utilities.c
# gcc -std=c99 -Wall -Wpedantic -c shallow-water-advanced.c
# gcc -lm -o run_simulation ./shallow-water-advanced.o utilities.o

