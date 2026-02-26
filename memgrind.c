#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

//for task 4
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

//for task 5
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

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

//linked list
void task4()
{
    Node *head = NULL;
    Node *prev = NULL;

    for (int i = 0; i < 50; i++)
    {
        Node *node = mymalloc(sizeof(Node) , __FILE__, __LINE__);
        if (i == 0)
        {
            head = node;
        }
        node->data = i;
        if (prev != NULL)
        {
            node->prev = prev;
            prev->next = node;
        }
        prev = node;
        node->next = NULL; 
    }

    Node *curr = head;
    while (curr != NULL)
    {
        Node *temp = curr->next;
        myfree(curr, __FILE__, __LINE__);
        curr = temp;
    }
}

//helper functions for task 5 (binary search tree)
TreeNode * insertNode(TreeNode *root, int value)
{
    if (root == NULL)
    {
        TreeNode *node = mymalloc(sizeof(TreeNode), __FILE__, __LINE__);
        node->data = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    TreeNode *curr = root;
    TreeNode *parent = NULL;
    while (curr != NULL)
    {
        if (value < curr->data)
        {
            parent = curr;
            curr = curr->left;
        }
        else
        {
            parent = curr;
            curr = curr->right;
        }
    }
    curr = mymalloc(sizeof(TreeNode), __FILE__, __LINE__);
    curr->data = value;
    curr->left = NULL;
    curr->right = NULL;
    if (value < parent->data)
    {
        parent->left = curr;
    }
    else
    {
        parent->right = curr;
    }
    return root;
}

void freeTree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    myfree(root, __FILE__, __LINE__);
}

void task5()
{
    TreeNode *root = NULL;
    for (int i = rand() % 1000; i < 50; i++)
    {
        root = insertNode(root, i);
    }
    freeTree(root);

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
        task4();
        task5();
    }
    gettimeofday(&end, NULL);
    long seconds = end.tv_sec - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;
    long total_micros = seconds * 1000000 + useconds;
    long avg = total_micros/50;
    printf("average time for workload: %ld\n", avg);
}
