#include "../graphutils.h" // header for functions to load and free adjacencyList

// A program to solve a maze that may contain cycles using BFS

// BFS requires using a queue data structure
typedef struct QueueNode {
    graphNode_t graphNode;
    struct QueueNode* next;
} QueueNode;

struct Queue {
    struct QueueNode* front; // front (head) of the queue
    struct QueueNode* back; // back (tail) of the queue
};
typedef struct Queue Queue;

// Append a new QueueNode to the back of the Queue
struct Queue enqueue ( struct Queue queue, graphNode_t graphNode ) {
    /* ... */
    QueueNode* queueNode = malloc(sizeof(QueueNode));
    queueNode->graphNode = graphNode;
    queueNode->next = NULL;

    if(queue.back==NULL) {
        queue.front = queueNode;
        queue.back = queueNode;
    } else {
        (*queue.back).next = queueNode;
        queue.back = queueNode;
    }
    return queue;
}

// Remove a QueueNode from the front of the Queue
graphNode_t dequeue ( Queue* queue ) {
    /* ... */
    if(queue->front == NULL) {
        return -1;
    } else {
        QueueNode* temp = queue->front;
        if(queue->back == temp) {
            queue->back = NULL;
        }
        queue->front = temp->next;

        graphNode_t graphNode = temp->graphNode;
        free(temp);
        return graphNode;
    }
}

int main ( int argc, char* argv[] ) {

    // First, read the query file to get the source and target nodes in the maze
    /* ... */
    FILE* queryFile = fopen(argv[2], "r"); 
    if(!queryFile) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    char buff[20000];
    fscanf(queryFile, "%s", buff);
    int src = atoi(buff); 
    fscanf(queryFile, "%s", buff);
    int dest = atoi(buff);


    fclose(queryFile);
    // READ INPUT FILE TO CREATE GRAPH ADJACENCY LIST
    AdjacencyListNode* adjacencyList = NULL;
    size_t graphNodeCount = adjMatrixToList(argv[1], &adjacencyList);
    /* ... */

    // USE A QUEUE TO PERFORM BFS
    Queue queue = { .front=NULL, .back=NULL };

    // An array that keeps track of who is the parent node of each graph node we visit
    graphNode_t* parents = calloc( graphNodeCount, sizeof(graphNode_t) );
    for (size_t i=0; i<graphNodeCount; i++) {
        if(i == src) { parents[i] = -2; }
        else { parents[i] = -1; } // -1 indicates that a nodes is not yet visited
    }
    graphNode_t current = adjacencyList[src].graphNode;
    graphNode_t target = adjacencyList[dest].graphNode;

    /* ... */
    queue = enqueue(queue, current);
    while ( current != target ) {
        current = dequeue(&queue); 
        AdjacencyListNode* neighbor = adjacencyList[current].next;
        while(neighbor) {
            if(parents[neighbor->graphNode] == -1) {
                parents[neighbor->graphNode] = current;
                queue = enqueue(queue, neighbor->graphNode);
            }
            neighbor = neighbor->next;
        }
        // so long as we haven't found the target node yet, iterate through the adjacency list
        // add each neighbor that has not been visited yet (has no parents) to the queue of nodes to visit
        /* ... */

        // Visit the next node at the front of the queue of nodes to visit
        /* ... */
    }

    // Now that we've found the target graph node, use the parent array to print maze solution
    // Print the sequence of edges that takes us from the source to the target node
    /* ... */    
    
    graphNode_t path = target;
    while(path != -2 && parents[path] != -2) { //basically just while you havent hit your source
        printf("%ld %ld\n", path, parents[path]);
        path = parents[path];
    }

    
    // free any queued graph nodes that we never visited because we already solved the maze
    while ( queue.front ) {
        dequeue(&queue);
    }
    free (parents);
    freeAdjList ( graphNodeCount, adjacencyList );

    return EXIT_SUCCESS;
}
