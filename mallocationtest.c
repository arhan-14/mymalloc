#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

typedef struct TestObject{
    void *ptr;
    size_t size;
    char pattern;
} TestObject;

int main(int argc, char** argv)
{
    void *obj1 = mymalloc(100, __FILE__, __LINE__);
    void *obj2 = mymalloc(100, __FILE__, __LINE__);
    void *obj3 = mymalloc(100, __FILE__, __LINE__);

    memset(obj1, 0x01, 100);
    memset(obj2, 0x02, 100);
    memset(obj3, 0x03, 100);

    TestObject one = {obj1, 100, 0x01};
    TestObject two = {obj2, 100, 0x02};
    TestObject three = {obj3, 100, 0x03};

    TestObject objects[3] = {one, two, three};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (((char *)objects[i].ptr)[j] != objects[i].pattern)
            {
               printf("object %d failed\n", i);
               printf("expected byte value: %d, actual: %d", objects[i].pattern, ((char *)objects[i].ptr)[j]);
               return 1;
            }
        }
    }

    myfree(obj1, __FILE__, __LINE__);
    myfree(obj2, __FILE__, __LINE__);
    myfree(obj3, __FILE__, __LINE__);
    
    printf("mallocationtest completed successfully!"); 
    return 0;
}
