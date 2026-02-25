#include "mymalloc.h"
#include <stdlib.h>
#include <stdio.h>

# define MEMLENGTH 4096

static union {
	char bytes [MEMLENGTH];
	double not_used;
} heap;

typedef struct block_header  {
	int isAlloc;
	size_t size;
	struct block_header * next;
	struct block_header * prev;
} header;

static int isInit = 0;

static void splitBlock(header * ptr, size_t size){
	char *temp = (char *)(ptr+1) + size;
	header *next = (header *) temp;
	next->size = ptr->size - (size + sizeof(header));
	ptr->size = size;
	next->isAlloc = 0;
	next->prev = ptr;
	if(ptr->next != NULL){
		header *oldNext = ptr->next;
		oldNext->prev = next;
		next->next = oldNext;
	}
	else {
		next->next = NULL;
	}
	ptr->next = next;
}

static void leakDetectorFunction(){
	header *ptr = (header *)heap.bytes;
	int byteCount = 0;
	int objectCount = 0;
	while ( ptr != NULL ){
		if (ptr->isAlloc) {
			objectCount++;
			byteCount += ptr->size;
		}
		ptr = ptr->next;
	}
	if(objectCount){
		fprintf(stderr, "mymalloc: %d bytes leaked in %d objects\n", byteCount, objectCount);
	}
}

static void initHeap(){
	header *initial = (header *) heap.bytes;
	initial->isAlloc = 0;
	initial->size = MEMLENGTH - sizeof(header);
	initial->next = NULL;
	initial->prev = NULL;
	isInit = 1;
	atexit(leakDetectorFunction);
}

static header *coalesceChunks(header *one,  header *two){
	one->size = one->size + sizeof(header) + two->size;
	one->next = two->next;
	if(one->next!=NULL){
		header	*tempNext = one->next;
		tempNext->prev = one;
	}
	return one;
}


void *mymalloc(size_t size, char *file, int line){
	if (!isInit){
		initHeap();
	}
	if(size == 0){
		return NULL;
	}

	size  = (size + 7) & ~7;
	header *ptr = (header *) heap.bytes;
	while(ptr != NULL){
		if(!(ptr->isAlloc) && ptr->size >= size){
			if (ptr->size - size >= sizeof(header) + 8){
				splitBlock(ptr, size);
			}
			ptr->isAlloc = 1;
			return ptr+1;
		}
		ptr = ptr->next;
	}
	fprintf(stderr, "malloc: Unable to allocate %zu bytes (%s:%d)\n", size, file, line);
	return NULL;
}

void myfree(void *ptr, char *file, int line){
	if (!isInit){
		initHeap();
	}

	void *heap_start = (void *)heap.bytes;
	void *heap_end = (void *)(heap.bytes + MEMLENGTH);

	if (ptr == NULL){
		return;
	}

	header *temp = ((header *)ptr) - 1;

	if((void *)temp < heap_start || (void *)temp >= heap_end){
		fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
		return;
	}

	header *check = (header *)heap.bytes;

	while( check != temp && check != NULL){
		check = check->next;
	}

	if(check == NULL){
		fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
		return;
	}

	if(!(temp->isAlloc)){
		fprintf(stderr, "free: Inappropriate pointer (%s:%d)\n", file, line);
		return;
	}

	header *next = temp->next;
	if(next != NULL && !(next->isAlloc)){
		temp = coalesceChunks(temp, next);
	}
	
	header *prev = temp->prev;
	if(prev !=NULL && !(prev->isAlloc)){
		temp = coalesceChunks(prev, temp);
	}

	temp->isAlloc = 0;
}

