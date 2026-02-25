#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main() 
{
    int x;
    myfree(&x, __FILE__, __LINE__);

    void *p = mymalloc(32, __FILE__, __LINE__);
    myfree((char *)p + 1, __FILE__, __LINE__);

    void *q = mymalloc(64, __FILE__, __LINE__);
    myfree(q, __FILE__, __LINE__);
    myfree(q, __FILE__, __LINE__);

    return 0;
}
