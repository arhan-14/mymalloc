#include <stdio.h>
#include "mymalloc.h"

int main() 
{
    void *p = mymalloc(0, __FILE__, __LINE__);

    if (p == NULL) 
    {
        printf("malloc(0) returned NULL\n");
    } 
    else 
    {
        printf("malloc(0) returned non-NULL\n");
    }

    return 0;
}
