// Autor: Creado Por Cristopher Angulo
// Archivo: Main Cliente para la ejecucion principal

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    char *graphfileName = "graph2.txt";
    graph *newgraph = readFile(graphfileName);
    showGraph(newgraph);
    showResults(newgraph);
    return 1;
}
