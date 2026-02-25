CC = gcc
CFLAGS = -Wall -Werror -std=c11

TARGETS = coalescingtest mallocationtest deallocationtest

all: $(TARGETS)

coalescingtest: coalescingtest.c mymalloc.c
	$(CC) $(CFLAGS) -o coalescingtest coalescingtest.c mymalloc.c

mallocationtest: mallocationtest.c mymalloc.c
	$(CC) $(CFLAGS) -o mallocationtest mallocationtest.c mymalloc.c

deallocationtest: deallocationtest.c mymalloc.c
	$(CC) $(CFLAGS) -o deallocationtest deallocationtest.c mymalloc.c

clean:
	rm -f $(TARGETS)
