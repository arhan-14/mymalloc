CC = gcc
CFLAGS = -Wall -Werror -std=c11

TARGETS = coalescingtest mallocationtest deallocationtest splitblocktest \
          freeerrordetection mallocexhaustiontest malloczerotest leakdetectiontest

all: $(TARGETS)

coalescingtest: coalescingtest.c mymalloc.c
	$(CC) $(CFLAGS) -o coalescingtest coalescingtest.c mymalloc.c

mallocationtest: mallocationtest.c mymalloc.c
	$(CC) $(CFLAGS) -o mallocationtest mallocationtest.c mymalloc.c

deallocationtest: deallocationtest.c mymalloc.c
	$(CC) $(CFLAGS) -o deallocationtest deallocationtest.c mymalloc.c

splitblocktest: splitblocktest.c mymalloc.c
	$(CC) $(CFLAGS) -o splitblocktest splitblocktest.c mymalloc.c

freeerrordetection: freeerrordetection.c mymalloc.c
	$(CC) $(CFLAGS) -o freeerrordetection freeerrordetection.c mymalloc.c

mallocexhaustiontest: mallocexhaustiontest.c mymalloc.c
	$(CC) $(CFLAGS) -o mallocexhaustiontest mallocexhaustiontest.c mymalloc.c

malloczerotest: malloczerotest.c mymalloc.c
	$(CC) $(CFLAGS) -o malloczerotest malloczerotest.c mymalloc.c

leakdetectiontest: leakdetectiontest.c mymalloc.c
	$(CC) $(CFLAGS) -o leakdetectiontest leakdetectiontest.c mymalloc.c

clean:
	rm -f $(TARGETS)
