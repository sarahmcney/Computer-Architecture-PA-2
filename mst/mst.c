#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to find the minimum spanning tree of a weighted undirected graph using Prim's algorithm
bool mstFinished(bool** inMST, int graphNodeCount) {
    for(int i = 0; i < graphNodeCount; i++) {
        if(!*inMST[i]) {
            return false;
        }
    }
    return true;
}

int main ( int argc, char* argv[] ) {

    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);    /* ... */

    // An array that keeps track of who is the parent node of each graph node we visit
    // In Prim's algorithm, this parents array keeps track of what is the edge that connects a node to the MST.
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) {
        parents[i] = -1; // -1 indicates that a nodes is not yet visited; i.e., node not yet connected to MST.
    }

    graphNode_t root = 0; 
    parents[root] = root;

    bool* inMST = calloc(graphNodeCount, sizeof(graphNode_t));


    for(int i = 0; i < graphNodeCount; i++) {
        if(i == 0) { inMST[i] = true; }
        else { inMST[i] = false; }
    }


    // Prim's algorithm:
    // A greedy algorithm that builds the minimum spanning tree.
    // For a graph with N nodes, the minimum spanning tree will have N-1 edges spanning all nodes.
    // Prim's algorithm starts with all nodes unconnected.
    // At each iteration of Prim's algorithm, the minimum weight node that connects an unconnected node to the connected set of nodes is added to the MST.
    for (unsigned iter=0; iter<graphNodeCount-1; iter++) {
        double minWeight = DBL_MAX; // If we find an edge with weight less than this minWeight, and edge connects a new node to MST, then mark this as the minimum weight to beat.
        graphNode_t minSource = -1;
        graphNode_t minDest = -1;

        for (graphNode_t source=0; source<graphNodeCount; source++) {
            if (parents[source]!=-1) { // if already visited
                    AdjacencyListNode* neighbor = adjacencyList[source].next;
                    while(neighbor) {
                        if(!inMST[neighbor->graphNode]) {
                            if(neighbor->weight < minWeight) {
                                minWeight = neighbor->weight;
                                minSource = source;
                                minDest = neighbor->graphNode;
                            }
                        }
                        neighbor = neighbor->next;
                    }
                /* ... */
            }
        }
        inMST[minDest] = true;
        parents[minDest]=minSource; // we found the minimum weight
    }

    // Using the fully populated parents array, print the edges in the MST.
    for(int i = 0; i < graphNodeCount; i++) {
        if(i == root) { continue; }
        else {
            printf("%d %zu\n", i, parents[i]);
        }
    }
    /* ... */

    free (parents);
    free(inMST);
    freeAdjList ( graphNodeCount, adjacencyList );

    return EXIT_SUCCESS;
}

