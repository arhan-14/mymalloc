#include "mymalloc.h"
#include <stdlib.h>

# define MEMLENGTH 4096

static union {
	char bytes [MEMLENGTH];
	double not_used;
} heap;

static typedef struct block_header  {
	int isAlloc,
	size_t size,
	void * next,
	void * prev
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

static void initHeap(){
	header *initial = (header *) heap.bytes
	initial->isAlloc = 0;
	initial->size = MEMLENGTH - sizeof(header);
	initial->next = NULL;
	initial->prev = NULL;
	isInit = 1;
	atexit(leakDetectorFunction)
}

static void *coalesceChunks(header *one,  header *two){
	one->size = one->size + sizeof(header) + two->size;
	one->next = two->next;
	if(one->next!=NULL){
		header	*tempNext = (header *)one->next;
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
		ptr = (header *)ptr->next;
	}
	fprintf(stderr, “malloc: Unable to allocate %d bytes (%s:%d), size, __FILE__, __LINE__”);
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

	if(temp < heap_start || temp >= heap_end){
		fprintf(stderr, “free: Inappropriate pointer (%s:%d)”, file, line);
		return;
	}

	header *check = (header *)heap.bytes;

	while( check != temp && check != NULL){
		check = (header *)check->next;
	}

	if(check == NULL){
		fprintf(stderr, “free: Inappropriate pointer (%s:%d)”, file, line);
		return;
	}

	if(!(temp->isAlloc)){
		fprintf(stderr, “free: Inappropriate pointer (%s:%d)”, file, line);
		return;
	}

	header *prev = temp->prev;
	if(prev !=NULL && !(prev->isAlloc)){
		temp = (header *)coalesceChunks(prev, temp);
	}

	header *next = temp->next;
	if(next != NULL && !(next->isAlloc)){
		temp = (header *)coalesceChunks(temp, next);
	}
	
	temp->isAlloc = 0;
}

