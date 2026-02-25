#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void task1(void)
{
    for (int i = 0; i < 50; i++)
    {
        void *obj = mymalloc(1, __FILE__, __LINE__);
        myfree(obj, __FILE__, __LINE__);
    }
}

void task2(void)
{
    void *objects[50];
    for (int i = 0; i < 50; i++)
    {
        void *obj = mymalloc(1, __FILE__, __LINE__);
        if (obj != NULL)
        {
            objects[i] = obj;
        }
    }
    for (int i = 0; i < 50; i++)
    {
        myfree(objects[i], __FILE__, __LINE__);   
    } 
}

void task3(void)
{
    void *objects[50];
    int totalallocs = 0;
    int activeallocs = 0;
    while (totalallocs < 50)
    {
        int random_number = rand() % 2;
        if (random_number == 0)
        {
            if (activeallocs < 50)
            {
                void *obj = mymalloc(1, __FILE__, __LINE__);
                if (obj != NULL)
                {
                    objects[activeallocs++] = obj;
                    totalallocs++;
                }
            }
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

void task4()
{
    
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
