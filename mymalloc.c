# define MEMLENGTH 4096
static union {
	char bytes [MEMLENGTH];
	double not_used;
}

static int isInit = 0;

void *mymalloc(size_t size, char *file, int line){
	if (!isInit){
		initHeap();
	}
	// size is number of bytes needed
	// allocate memory from global array
		// must be a multiple of 8
	// header and payload 
		// header contains metadata (size and ptr to payload)
		// hear and payload must have len that is multiple of 8
	// find chunk that fits the needed size
		// split if possible, leaving second chunk free
	// smallest possible chunk is 16 bytes (header + payload)
}
void myfree(void *ptr, char *file, int line){
	if (!isInit){
		InitHeap();
	}
	// ptr is pointer to chunk
	// note memory as deallocated
	// auto coalesce if possible
}

static void initHeap(){
	// initialize the heap
	
	
	atexit(leakDetectorFunction);
}
