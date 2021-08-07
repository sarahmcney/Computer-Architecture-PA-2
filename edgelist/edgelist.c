#include "../graphutils.h" // header for functions to load and free adjacencyList
#include <stdlib.h>
#include <stdio.h>

// A program to print the edge list of a graph given the adjacency matrix
int main ( int argc, char* argv[] ) {

    // FIRST, READ THE ADJACENCY MATRIX FILE
    AdjacencyListNode* adjacencyList = NULL;
    //size_t numNodes = adjMatrixToList(adjMatrix_file, &adjacencyList);
    size_t numNodes = adjMatrixToList(argv[1], &adjacencyList);
    //printf("number of nodes = %zu\n", numNodes);
    // NEXT, TRAVERSE THE ADJACENCY LIST AND PRINT EACH EDGE, REPRESENTED AS A PAIR OF NODES
    // Example of traversing the adjacency list is in the freeAdjList() function in graphutils.h
    for(size_t source = 0; source < numNodes; source++) {
        AdjacencyListNode* dest = adjacencyList[source].next;
        while(dest) {
            if(source > dest->graphNode) {
                printf("%zu %zu\n", source, dest->graphNode);
            }
            dest = dest->next;
        }
    }

    // NOW, BE SURE TO FREE THE ADJACENCY LIST
    freeAdjList(numNodes, adjacencyList);
    return EXIT_SUCCESS;
}
