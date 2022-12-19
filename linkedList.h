// Autor: Creado Por Cristopher Angulo
// Archivo Contenedor de TDAS y Operaciones

#include <stdio.h>
#include <stdlib.h>

/// @brief Estructura de Datos de un nodo
/// Representacion: (int) dato - (node*)siguiente
typedef struct node
{
    int data;
    struct node *next;
} node;

/// @brief Estructura de Datos de una lista enlazada
/// Representacion: (node*) inicio Lista
typedef struct linkedList
{
    node *init;
} linkedList;

// Operaciones
node *createNode(int data);
linkedList *createLinkedListEmpty();
int isLinkedListEmpty(linkedList *linkedList);
void showLinkedList(linkedList *linkedList);
void insertInit(linkedList *linkedList, int data);
void showLinkedList(linkedList *linkedList);
void insertInit(linkedList *linkedList, int data);
void deleteInit(linkedList *linkedList);
void freeLinkedList(linkedList *linkedList);
int getNumberNodes(linkedList *newlinkedList);

/// @brief Crear Nodo de una lista enlazada
/// @param data 
/// @return nodo
node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/// @brief Crear una lista enlazada vacia
/// @return lista enlazada
linkedList *createLinkedListEmpty()
{
    linkedList *newLinkedList = (linkedList *)malloc(sizeof(linkedList));
    newLinkedList->init = NULL;
    return newLinkedList;
}

/// @brief Revisar si la lista enlazada esta vacia
/// @param linkedList 
/// @return entero (1,0)
int isLinkedListEmpty(linkedList *linkedList)
{
    if (linkedList->init == NULL)
        return 1;
    else
        return 0;
}

/// @brief Mostrar la lista enlazada
/// @param linkedList 
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

/// @brief insertar nodo al inicio de la lista enlazada
/// @param linkedList 
/// @param data 
void insertInit(linkedList *linkedList, int data)
{
    node *newNode = createNode(data);
    newNode->next = linkedList->init;
    linkedList->init = newNode;
}

/// @brief Eliminar al inicio de la lista enlazada
/// @param linkedList 
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

/// @brief Liberar memoria de la lista enlazada
/// @param linkedList 
void freeLinkedList(linkedList *linkedList)
{
    while (!isLinkedListEmpty(linkedList))
    {
        deleteInit(linkedList);
    }
    free(linkedList);
}

/// @brief Obtener numero de nodos de la lista enlazada
/// @param newlinkedList 
/// @return 
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
