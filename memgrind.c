#include "mymalloc.h"
#include <sys/time.h>
#include <stdlib.h>

void task1(void)
{
    for (int i = 0; i < 120; i++)
    {
        void *obj = mymalloc(1, __FILE__, __LINE__);
        myfree(obj);
    }
}

void task2(void)
{
    void *objects[120];
    for (int i = 0; i < 120; i++)
    {
        void *obj = mymalloc(1, __FILE__, __LINE__);
        objects[i] = obj;
    }
    for (int i = 0; i < 120; i++)
    {
        myfree(objects[i], __FILE__, __LINE__);   
    } 
}

void task3(void)
{
    void *objects[120];
    int totalallocs = 0;
    int activeallocs = 0;
    while (totalallocs < 120)
    {
        int random_number = rand() % 2;
        if (random_number == 0)
        {
            void *obj = mymalloc(1, __FILE__, __LINE__);
            objects[activeallocs] = obj;
            totalallocs++;
            activeallocs++;
        }
        else
        {
            if (activeallocs > 0)
            {
                int randindex = rand() % activeallocs;
                myfree(objects[randindex], __FILE__, __LINE__);
                objects[randindex] = objects[activeallocs - 1];
                activeallocs--;
            }
        }    
    }

    for (int i = 0; i < (activeallocs); i++)
    {
        myfree(objects[i], __FILE__, __LINE__);
    }
}

int main(int argc, char** argv)
{
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 50; i++)
    {
        task1();
        task2();
        task3();
    }
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;
    long total_micros = seconds * 1000000 + useconds;
    long avg = total_micros/50;
    printf("average time for workload: %ld\n", avg);
}
