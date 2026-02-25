Arhan Nagavelli - arn97
Keith Miquela - kvm33

TESTING PLAN
-------------
mallocationtest.c (specifications taken from writeup example)
- Requirement: mymalloc() reserves unallocated memory.
- Detection method: when successful, mymalloc() returns a pointer to an object that does not overlap with any other allocated object.
- Test: write a program that allocates three large objects. Once allocation is complete, it fills each object with a distinct byte pattern (object 1 is 0x01, object 2 is 0x02, and object 3 is 0x03). Finally, it checks whether each object still contains the written pattern.

deallocationtest.c
- Requirement: myfree() successfully deallocates chunks of memory.
- Detection method: when successful, myfree() marks a previously allocated block as available, allowing subsequent allocations of the same size to reuse that memory.
- Test: write a program that allocates an object, frees it, then allocates an identical object. The program checks whether the pointers returned by the allocated objects are equal to confirm that myfree() deallocated the initial chunk and reused the space for the new same-size chunk.

coalescingtest.c
- Requirement: myfree() coalesces adjacent blocks of memory that have been freed.
- Detection method: when successful, myfree() merges adjacent free blocks into a single larger block. This is verified by checking that a subsequent allocation larger than either individual freed block succeeds, which would only be possible if the two blocks were coalesced into one.
- Test: write a program that allocates two equally-sized blocks of memory and then frees them. After they have been freed, a new object with a size greater than that of ONE of the previously allocated blocks is allocated. The program checks whether the pointer returned by allocating the new object is NULL or not.

splitblocktest.c
- Requirement: mymalloc() splits a large free block when allocating smaller chunks.
- Detection method: when successful, mymalloc() divides a large free block into an allocated portion and a remaining free portion when servicing a smaller allocation request.
- Test: write a program that allocates a large block of memory and then frees it. Subsequently, two smaller chunks that can both fit in the previously allocated large chunk will be allocated.

freeerrordetection.c
- Requirement: myfree() detects and reports invalid usage errors.
- Detection method: when successful, myfree() prints an error message to standard error in the required format when misuse is detected.
- Test: write a program that (1) calls myfree() on an address not obtained from mymalloc(), (2) calls myfree() on an address not at the start of an allocated chunk, and (3) calls myfree() twice on the same pointer. The program verifies that an error message is printed in each case.

mallocexhaustiontest.c
- Requirement: mymalloc() returns NULL and prints the required error message when insufficient memory is available.
- Detection method: when successful, repeated allocations eventually exhaust the fixed heap size (4096 bytes), causing mymalloc() to return NULL and print the formatted error message.
- Test: write a program that continuously allocates fixed-size blocks until mymalloc() returns NULL.

malloczerotest.c
- Requirement: mymalloc() correctly handles allocation requests of size 0.
- Detection method: when successful, mymalloc(0) returns NULL (or behaves according to the implementation specification) without corrupting the heap.
- Test: write a program that calls mymalloc(0) and checks whether the returned pointer is NULL.

leakdetectiontest.c
- Requirement: the allocator correctly reflects memory that has not been freed.
- Detection method: when successful, allocated blocks that are not freed remain marked as allocated in the heap structure. If leak reporting is implemented, it should identify the unfreed block.
- Test: write a program that allocates multiple blocks, frees only some of them, and exits without freeing at least one allocated block.
