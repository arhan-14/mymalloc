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
