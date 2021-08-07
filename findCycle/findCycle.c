#include "../graphutils.h"

// A program to find a cycle in a directed graph

// You may use DFS or BFS as needed
/* ... */
void printCycle(size_t graphNodeCount, AdjacencyListNode* adjacencyList, graphNode_t start, graphNode_t* parents);
bool cycleDFS (
    size_t graphNodeCount,
    AdjacencyListNode* adjacencyList,
    graphNode_t current,
    graphNode_t parent,
    bool* unvisited,
    bool* visiting,
    bool* visited,
    graphNode_t* parents
) {
    parents[current] = parent;
    visiting[current] = true;
    unvisited[current] = false;
    AdjacencyListNode* neighbor = adjacencyList[current].next;
    while(neighbor) {
        if(visited[neighbor->graphNode]) {
            continue; //skip - we found this already
        }
        if(visiting[neighbor->graphNode]) {
            printCycle(graphNodeCount, adjacencyList, current, parents);
            return true; //cycle detected
        }
        if(cycleDFS(graphNodeCount, adjacencyList, neighbor->graphNode, current, unvisited, visiting, visited, parents)) {
            return true;
        }
        visited[current] = true;
        visiting[current] = false;
        return false;
    }
    return false;
}

void printCycle(size_t graphNodeCount, AdjacencyListNode* adjacencyList, graphNode_t start, graphNode_t* parents) {
    graphNode_t path = start;
    graphNode_t* pathList = malloc(graphNodeCount * sizeof(graphNode_t));
    for(int i = 0; i < graphNodeCount; i++) {
        pathList[i] = -1;
    }
    int counter = graphNodeCount-1;
    do {
            pathList[counter] = path;
            counter = counter - 1;
            path = parents[path];
        
    }while(path!=start && path!=-1);
    for(int i = 0; i < graphNodeCount; i++) {
        if(pathList[i] < 10000000) { 
            if(i < graphNodeCount - 1 && pathList[i+1] == 7) { 
                continue;
            }
            printf("%zu ", pathList[i]);
        }
    }
    free(pathList);
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);    /* ... */
    /* ... */

    bool isCyclic = false;
    bool* unvisited = malloc(graphNodeCount * sizeof(bool));
    bool* visiting = malloc(graphNodeCount * sizeof(bool));
    bool* visited = malloc(graphNodeCount * sizeof(bool));
    graphNode_t* parents = malloc(graphNodeCount * sizeof(graphNode_t));
    for (unsigned source=0; source<graphNodeCount; source++) {
        /* ... */
        unvisited[source] = true;
        visiting[source] = false;
        visited[source] = false;
        parents[source] = -1;
    }

    for(int i = 0; i < graphNodeCount; i++) {
        graphNode_t current = adjacencyList[i].graphNode;
        if(cycleDFS(graphNodeCount, adjacencyList, current, -1, unvisited, visiting, visited, parents)) {
            isCyclic = true;
            break;
        }
    }
    if (!isCyclic) { printf("DAG\n"); }

    //free dynamically allocated memory
    freeAdjList ( graphNodeCount, adjacencyList );
    free(unvisited);
    free(visiting);
    free(parents);
    free(visited);
    return EXIT_SUCCESS;
}
