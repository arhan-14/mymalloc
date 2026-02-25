Arhan Nagavelli - arn97
Keith Miquela - kvm33

TESTING PLAN
-------------
mallocation.c (specifications as per writeup example)
- Requirement: malloc() reserves unallocated memory.
- Detection method: when successful, malloc() returns a pointer to an object that does not overlap with any other allocated object.
- Test: Write a program that allocates three large objects. Once allocation is complete, it fills each object with a distinct byte pattern (object 1 is 0x01, object 2 is 0x02, and object 3 is 0x03). Finally, it checks whether each object still contains the written pattern.
