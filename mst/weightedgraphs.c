#include "../graphutils.h" // header for functions to load and free adjacencyList
int main(int argc, char* argv[]) { 
    AdjacencyListNode* adjacencyList = NULL;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    for(int i = 0; i < graphNodeCount; i++) {
        AdjacencyListNode* nbr = adjacencyList[i].next;
        while(nbr) {
            printf("starting node: %zu; ending node: %zu\n", adjacencyList[i].graphNode, nbr->graphNode);
            printf("%f\n", nbr->weight);
            nbr = nbr->next;
        }
        
    }
    freeAdjList(graphNodeCount, adjacencyList);
    return EXIT_SUCCESS;
}