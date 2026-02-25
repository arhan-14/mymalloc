#include <stdio.h>
#include "mymalloc.h"

int main() 
{
    void *p1 = mymalloc(100, __FILE__, __LINE__);
    void *p2 = mymalloc(200, __FILE__, __LINE__);
    void *p3 = mymalloc(300, __FILE__, __LINE__);
    (void)p3;

    myfree(p1, __FILE__, __LINE__);
    myfree(p2, __FILE__, __LINE__);

    return 0;
}
