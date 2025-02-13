#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

// Graph structure
typedef struct {
    int adj[MAX_NODES][MAX_NODES]; // Adjacency matrix
    int V; // Number of vertices
} Graph;

void addEdge(Graph *graph, int u, int v) {
    graph->adj[u][v] = 1; // Add directed edge from u to v
}

// DFS for Topological Sort with Cycle Detection using recStack
int dfsTopologicalSort(Graph *graph, int node, int *visited, int *recStack, int *result, int *resultIndex) {
    visited[node] = 1;         // Mark node as visited
    recStack[node] = 1;        // Add node to recursion stack

    // Visit all neighbors of the current node
    for (int i = 0; i < graph->V; i++) {
        if (graph->adj[node][i]) {
            // If node is already in recursion stack, cycle detected
            if (recStack[i]) {
                return 1; // Cycle detected, return
            }
            // If neighbor is not visited, do DFS on it
            if (!visited[i]) {
                if (dfsTopologicalSort(graph, i, visited, recStack, result, resultIndex)) {
                    return 1; // Cycle detected in DFS
                }
            }
        }
    }

    // After visiting all neighbors, add the node to the result
    result[(*resultIndex)++] = node;
    recStack[node] = 0; // Remove node from recursion stack
    return 0; // No cycle detected
}

// Function for Topological Sort with Cycle Detection
void topologicalSort(Graph *graph) {
    int visited[MAX_NODES] = {0};  // Keeps track of visited nodes
    int recStack[MAX_NODES] = {0}; // Recursion stack to track the current DFS path
    int result[MAX_NODES];         // Array to store the topological order
    int resultIndex = 0;

    // Perform DFS from every unvisited node
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            if (dfsTopologicalSort(graph, i, visited, recStack, result, &resultIndex)) {
                printf("Cycle detected! Topological sorting not possible.\n");
                return;
            }
        }
    }

    // Print the topological order (in reverse order)
    printf("Topological Sort: ");
    for (int i = resultIndex - 1; i >= 0; i--) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    Graph graph;
    graph.V = 5;

    // Initialize adjacency matrix to 0
    for (int i = 0; i < graph.V; i++) {
        for (int j = 0; j < graph.V; j++) {
            graph.adj[i][j] = 0;
        }
    }

    // Add directed edges to the graph (example)
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 0); // This edge creates a cycle

    topologicalSort(&graph); // Will show that topological sort is not possible due to cycle

    return 0;
}
