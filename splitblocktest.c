#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char** argv)
{
    void *obj1 = mymalloc(16, __FILE__, __LINE__);
    myfree(obj1, __FILE__, __LINE__);
    
    void *obj2 = mymalloc(8, __FILE__, __LINE__);
    void *obj3 = mymalloc(8, __FILE__, __LINE__);

    if (obj2 == NULL || obj3 == NULL)
    {
        printf("error with splitblocktest");
        return 1;
    }

    printf("splitblocktest successful");
    myfree(obj2, __FILE__, __LINE__);
    myfree(obj3, __FILE__, __LINE__);
    return 0;
}
