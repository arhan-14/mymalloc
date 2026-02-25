#include "mymalloc.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    void *obj1 = mymalloc(8, __FILE__, __LINE__);
    void *obj2 = mymalloc(8, __FILE__, __LINE__);
    myfree(obj1, __FILE__, __LINE__);
    myfree(obj2, __FILE__, __LINE__);
    void *obj3 = mymalloc(12, __FILE__, __LINE__);
    if (obj3 == NULL)
    {
       printf("coalescing failed");
       return 1;
    }
    myfree(obj3, __FILE__, __LINE__);
    printf("coalescing test success");
    return 0; 
}
