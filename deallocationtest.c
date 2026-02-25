#include "mymalloc.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    void *obj1 = mymalloc(8, __FILE__, __LINE__);
    myfree(obj1, __FILE__, __LINE__);

    void *obj2 = mymalloc(8, __FILE__, __LINE__);

    if (obj1 != obj2)
    {
        printf("Error with myfree()\n");
        return 1;
    }
    
    myfree(obj2, __FILE__, __LINE__);

    printf("deallocation test was successful");
    return 0;
}
