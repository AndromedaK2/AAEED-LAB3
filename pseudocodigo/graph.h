
.. Definicion TDA Grafo

graph: Registro
    edges
    vertices
    adjMatrix
Fin Registro



..Complejidad O(n^2)
createEmptyGraph(num edges, num vertices): graph *
    i <- 0
    j <- 0
    graph *graphReturn <- allocateMemory
    adjMatrixReturn    <- allocateMemory
    FOR i <- 0 TO edges STEP 1
        adjMatrixReturn[i] <- allocateMemory
        FOR j <- 0 TO edges STEP 1        
            adjMatrixReturn[i][j] <- 0        
    graphReturn->adjMatrix <- adjMatrixReturn
    graphReturn->edges     <- edges
    graphReturn->vertices  <- vertices
    RETURN (graphReturn)


..Complejidad O(n^2)
showGraph(graph *newGraph): void
    i <- 0
    j <- 0
    FOR i <- 0 TO newGraph->edges STEP 1   
        FOR j <- 0 TO newGraph->edges STEP 1       
            WRITE(newGraph->adjMatrix[i][j])
   
    
..Complejidad O(1)
insertNode(graph *graph, num adj1, num adj2):void
    graph->adjMatrix[adj1][adj2]
    graph->adjMatrix[adj2][adj1]

..Complejidad O(1)
num adjacentNodes(graph *graph, num vertexA, num vertexB)
    IF graph->adjMatrix[vertexA][vertexB] = 1)  THEN
        RETURN 1   
    RETURN 0


..Complejidad O(n)
readFile(char *fileName): graph *
    file <- fileOpen
    num vertices = 0
    num edges    = 0
    num i = 0 
    num j = 0
    num k = 0
    IF file = NULL THEN  
        PRINT("Error de archivo")
        RETURN NULL
    ELSE IF 
        countLines = countLinesFile(file)
        graph *newGraph <- createEmptyGraph(vertices, edges)
        FOR k <- 0 TO countLines STEP 1
            newGraph->adjMatrix[i - 1][j - 1] <- 1
            newGraph->adjMatrix[j - 1][i - 1] <- 1      
        closeFile(file)
        RETURN (newGraph)
    

..Complejidad O(n)
getAdjacentVertices(graph *graph, num vertex): linkedList *
    IF vertex > graph->edges THEN
        RETURN NULL
    linkedList *linkedList <- createLinkedListEmpty()
    i <- 0
    FOR i <- 0 i TO graph->edges STEP 1
        IF adjacentNodes(graph, vertex, i)
            insertInit(linkedList, i + 1)
    RETURN (linkedList)

..Complejidad O(1)
getAdjacentVerticesCantity(linkedList *adjacents): num
    RETURN getNumberNodes(adjacents)


..Complejidad O(n)
calculateResults(graph *newgraph, num critic, linkedList *criticalPoints, num *centralPoint, num *isRobust): void
    linkedList *adjacentNodes <- createLinkedListEmpty()
    adjacentCantity       <- 0
    maxAdjacentCantity    <- 0
    criticalPointsCantity <- 0
    i <- 0
    FOR i <- 0 i TO newgraph->edges STEP 1
        adjacentNodes <- getAdjacentVertices(newgraph, i)
        adjacentCantity <- getAdjacentVerticesCantity(adjacentNodes)
        IF adjacentCantity > critic THEN
            insertInit(criticalPoints, i + 1)
            criticalPointsCantity++
            IF adjacentCantity > maxAdjacentCantity THEN
                maxAdjacentCantity <- adjacentCantity
                centralPoint       <- i + 1
        IF criticalPointsCantity = newgraph->vertices THEN
            isRobust <- 1
    freeLinkedList(adjacentNodes)


..Complejidad O(n)
showResults(graph *newgraph): void
    linkedList *criticalPoints <- createLinkedListEmpty()
    critic       <- (newgraph->edges - 1) * 0.4
    centralPoint <- 0
    isRobust     <- 0

    calculateResults(newgraph, critic, criticalPoints, centralPoint, isRobust)

    PRINT("Puntos Criticos")
    showLinkedList(criticalPoints)

    IF centralPoint <> 0 THEN
        PRINT("Punto Central: %d", centralPoint)
    ELSE
        PRINT("No hay Punto Central")
    
    IF isRobust THEN    
        PRINT("La Red es Robusta")    
    ELSE
        PRINT("La Red no es Robusta")
    
    freeLinkedList(criticalPoints)
    freeGraph(newgraph)

..Complejidad O(n)
freeGraph(graph *graph): void
    i <- 0
    FOR i <- 0 i TO graph->edges STEP 1    
        free(graph->adjMatrix[i])
    free(graph->adjMatrix)
    free(graph)
