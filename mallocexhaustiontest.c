#include <stdio.h>
#include "mymalloc.h"

int main() 
{
    void *blocks[500];
    int i = 0;

    while (i < 500) 
    {
        blocks[i] = mymalloc(128, __FILE__, __LINE__);
        if (blocks[i] == NULL) 
        {
            break;
        }
        i++;
    }

    printf("Allocated %d blocks before exhaustion\n", i);
    return 0;
}
