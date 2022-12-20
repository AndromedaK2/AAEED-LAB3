// Autor: Creado Por Cristopher Angulo
// Archivo Contenedor de TDAS y Operaciones

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

/// @brief Estructura de Datos de un grafo
/// Representacion: (int) Aristas - (int)Vertices - (int**)Matriz de Adyacencia
typedef struct graph
{
    int edges;
    int vertices;
    int **adjMatrix;
} graph;

// Operaciones
graph *readFile(char *fileName);
graph *createEmptyGraph(int edges, int vertices);
void showGraph(graph *newGraph);
void insertNode(graph *graph, int adj1, int adj2);
void freeGraph(graph *graph);
int adjacentNodes(graph *graph, int vertexA, int vertexB);
linkedList *getAdjacentVertices(graph *graph, int vertex);
void showResults(graph *newGraph);
void calculateResults(graph *newgraph, int critic, linkedList *criticalPoints, int *centralPoint, int *isRobust);

/// @brief Crear un grafo vacío llenando de ceros, haciendo uso de la matriz de adyacencia.
/// @param edges 
/// @param vertices 
/// @return grafo
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

/// @brief Muestra los nodos del grafo en una matriz de adyacencia
/// @param newGraph 
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

/// @brief Insertar Nodo al grafo
/// @param graph 
/// @param adj1 
/// @param adj2 
void insertNode(graph *graph, int adj1, int adj2)
{
    graph->adjMatrix[adj1][adj2];
    graph->adjMatrix[adj2][adj1];
}

/// @brief Verificar si 2 vertices son adyacentes
/// @param graph 
/// @param vertexA 
/// @param vertexB 
/// @return (1,0)
int adjacentNodes(graph *graph, int vertexA, int vertexB)
{
    if (graph->adjMatrix[vertexA][vertexB] == 1)
    {
        return 1;
    }
    return 0;
}

/// @brief Lee el nombre del archivo para construir el grafo
/// @param fileName 
/// @return grafo
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
            newGraph->adjMatrix[i - 1][j - 1] = 1;
            newGraph->adjMatrix[j - 1][i - 1] = 1;
        }
        fclose(pf);

        return newGraph;
    }
}

/// @brief Crear Lista enlazada de adyacentes del vertice
/// @param graph 
/// @param vertex 
/// @return Lista enlazada de adyacentes del vertice
linkedList *getAdjacentVertices(graph *graph, int vertex)
{
    if (vertex > graph->edges)
        return NULL;

    linkedList *linkedList = createLinkedListEmpty();
    int i = 0;
    for (i = 0; i < graph->edges; ++i)
    {
        if (adjacentNodes(graph, vertex, i))
        {
            insertInit(linkedList, i + 1);
        }
    }

    return (linkedList);
}

/// @brief Obtiene la cantidad de adyacentes
/// @param adjacents 
/// @return Numero de adyancentes
int getAdjacentVerticesCantity(linkedList *adjacents)
{
    return getNumberNodes(adjacents);
}

/// @brief Obtiene los resultados principales
/// @param newgraph 
/// @param critic 
/// @param criticalPoints 
/// @param centralPoint 
/// @param isRobust 
void calculateResults(graph *newgraph, int critic, linkedList *criticalPoints, int *centralPoint, int *isRobust)
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

/// @brief Muestra los resultados
/// @param newgraph 
void showResults(graph *newgraph)
{

    linkedList *criticalPoints = createLinkedListEmpty();
    int critic = (newgraph->edges - 1) * 0.4;
    int centralPoint = 0;
    int isRobust = 0;

    calculateResults(newgraph, critic, criticalPoints, &centralPoint, &isRobust);

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

/// @brief Libera el espacio en memoria del grafo ingresado
/// @param graph 
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