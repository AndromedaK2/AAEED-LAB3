#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct linkedList
{
    node *init;
} linkedList;

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

linkedList *createLinkedListEmpty()
{
    linkedList *newLinkedList = (linkedList *)malloc(sizeof(linkedList));
    newLinkedList->init = NULL;
    return newLinkedList;
}

int isLinkedListEmpty(linkedList *linkedList)
{
    if (linkedList->init == NULL)
        return 1;
    else
        return 0;
}

void showLinkedList(linkedList *linkedList)
{

    if (!isLinkedListEmpty(linkedList))
    {
        node *node = linkedList->init;
        while (node != NULL)
        {
            printf("%d ", node->data);
            node = node->next;
        }
        printf("\n");
    }
    else
        printf("No hay puntos criticos\n");
}

void insertInit(linkedList *linkedList, int data)
{
    node *newNode = createNode(data);
    newNode->next = linkedList->init;
    linkedList->init = newNode;
}

void deleteInit(linkedList *linkedList)
{
    node *node;
    if (!isLinkedListEmpty(linkedList))
    {
        node = linkedList->init;
        linkedList->init = linkedList->init->next;
        free(node);
    }
}

void freeLinkedList(linkedList *linkedList)
{
    while (!isLinkedListEmpty(linkedList))
    {
        deleteInit(linkedList);
    }
    free(linkedList);
}

int getNumberNodes(linkedList *newlinkedList)
{
    node *newNode = newlinkedList->init;
    int total = 0;
    while (newNode != NULL)
    {
        total = total + 1;
        newNode = newNode->next;
    }
    return (total);
}


