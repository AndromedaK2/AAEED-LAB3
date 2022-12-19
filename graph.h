#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

typedef struct graph
{
    int edges;
    int vertices;
    int **adjMatrix;
} graph;

graph *readFile(char *fileName);
graph *createEmptyGraph(int edges, int vertices);
void showGraph(graph *newGraph);
void insertNode(graph *graph, int adj1, int adj2);
void freeGraph(graph *graph);
int adjacentNodes(graph *graph, int edgeA, int edgeB);
linkedList *getAdjacentVertices(graph *graph, int edge);
void showResults(graph *newGraph);
void getResults(graph *newgraph, int critic, linkedList *criticalPoints, int *centralPoint, int *isRobust);

graph *createEmptyGraph(int edges, int vertices)
{
    int i, j;

    graph *graphReturn = (graph *)malloc(sizeof(graph));

    int **adjMatrixReturn = (int **)malloc(sizeof(int *) * edges);
    for (i = 0; i < edges; i++)
    {
        adjMatrixReturn[i] = (int *)malloc(sizeof(int) * edges);
        for (j = 0; j < edges; j++)
        {
            adjMatrixReturn[i][j] = 0;
        }
    }
    graphReturn->adjMatrix = adjMatrixReturn;
    graphReturn->edges = edges;
    graphReturn->vertices = vertices;
    return graphReturn;
}

void showGraph(graph *newGraph)
{
    printf("\n-------Matriz de Adyacencia-----------\n\n");
    int i, j;
    for (i = 0; i < newGraph->edges; i++)
    {
        for (j = 0; j < newGraph->edges; j++)
        {
            printf("%d ", newGraph->adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n------------------\n\n");
}

void insertNode(graph *graph, int adj1, int adj2)
{
    graph->adjMatrix[adj1][adj2];
    graph->adjMatrix[adj2][adj1];
}

void freeGraph(graph *graph)
{
    int i = 0;
    for (i = 0; i < graph->edges; ++i)
    {
        free(graph->adjMatrix[i]);
    }
    free(graph->adjMatrix);
    free(graph);
}

int adjacentNodes(graph *graph, int edgeA, int edgeB)
{
    if (graph->adjMatrix[edgeA][edgeB] == 1)
    {
        return 1;
    }
    return 0;
}

graph *readFile(char *fileName)
{

    FILE *pf;
    pf = fopen(fileName, "r");
    int vertices, edges;
    int i, j, k;

    if (pf == NULL)
    {
        printf("Error de archivo\n");
        return NULL;
    }
    else
    {

        int countLines = 0;
        char c;
        do
        {
            c = fgetc(pf);
            if (c == '\n')
            {
                countLines++;
            };

        } while (c != EOF);
        rewind(pf);

        fscanf(pf, "%d %d", &vertices, &edges);
        graph *newGraph = createEmptyGraph(vertices, edges);

        for (k = 0; k < countLines; ++k)
        {
            fscanf(pf, "%d %d", &i, &j);
            // printf("%d : %d %d \n", k, i, j);
            newGraph->adjMatrix[i - 1][j - 1] = 1;
            newGraph->adjMatrix[j - 1][i - 1] = 1;
        }
        fclose(pf);

        return newGraph;
    }
}

linkedList *getAdjacentVertices(graph *graph, int edge)
{
    if (edge > graph->edges)
        return NULL;

    linkedList *linkedList = createLinkedListEmpty();
    int i = 0;
    for (i = 0; i < graph->edges; ++i)
    {
        if (adjacentNodes(graph, edge, i))
        {
            insertInit(linkedList, i + 1);
        }
    }

    return (linkedList);
}

int getAdjacentVerticesCantity(linkedList *adjacents)
{
    return getNumberNodes(adjacents);
}

void getResults(graph *newgraph, int critic, linkedList *criticalPoints, int *centralPoint, int *isRobust)
{
    linkedList *adjacentNodes = createLinkedListEmpty();
    int adjacentCantity = 0;
    int maxAdjacentCantity = 0;
    int criticalPointsCantity = 0;

    int i;
    for (i = 0; i < newgraph->edges; i++)
    {
        adjacentNodes = getAdjacentVertices(newgraph, i);
        adjacentCantity = getAdjacentVerticesCantity(adjacentNodes);
        printf("Cantidad de adjacentes del vertice (%d): %d \n", i + 1, adjacentCantity);

        if (adjacentCantity > critic)
        {
            insertInit(criticalPoints, i + 1);
            criticalPointsCantity++;

            if (adjacentCantity > maxAdjacentCantity)
            {
                maxAdjacentCantity = adjacentCantity;
                *centralPoint = i + 1;
            }
        }

        if (criticalPointsCantity == newgraph->vertices)
        {
            *isRobust = 1;
        }
    }

    freeLinkedList(adjacentNodes);
}

void showResults(graph *newgraph)
{

    linkedList *criticalPoints = createLinkedListEmpty();
    int critic = (newgraph->edges - 1) * 0.4;
    int centralPoint = 0;
    int isRobust = 0;

    getResults(newgraph, critic, criticalPoints, &centralPoint, &isRobust);

    printf("\n------------------\n");
    printf("\n-------Resultados-----------\n\n");
    printf("Promedio Conexiones Criticas: %d \n", critic);
    printf("Puntos Criticos: \n");

    showLinkedList(criticalPoints);

    printf("------------------\n");

    if (centralPoint != 0)
    {
        printf("Punto Central: %d", centralPoint);
    }
    else
    {
        printf("No hay Punto Central");
    }
    printf("\n------------------\n");
    if (isRobust)
    {
        printf("La Red es Robusta");
    }
    else
    {
        printf("La Red no es Robusta");
    }

    freeLinkedList(criticalPoints);
    freeGraph(newgraph);
}
