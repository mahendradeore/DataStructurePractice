#include <stdio.h>
#include <limits.h>

#define V 9 // Number of vertices in the graph

// A utility function to find the vertex with the minimum distance value
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

// A function to implement Dijkstra's algorithm for a graph represented using adjacency matrix
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // dist[i] holds the shortest distance from src to i
    int sptSet[V]; // sptSet[i] will be true if vertex i is included in the shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    // Distance from the source vertex to itself is always 0
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update the distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] if and only if the vertex v is not in sptSet, there is an edge from u to v,
            // and the total weight of path from source to v through u is smaller than the current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t %d\n", i, dist[i]);
    }
}
// Function to perform Dijkstra's algorithm
int dijkstraForTarget(int graph[V][V], int src, int target) {
    int dist[V];
    int sptSet[V];  // Shortest Path Tree Set
    
    // Initialize all distances as infinity, except the source node
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    // Loop through all the vertices
    for (int count = 0; count < V - 1; count++) {
        // Get the vertex with the minimum distance
        int u = minDistance(dist, sptSet);
        
        // Mark the selected vertex as processed
        sptSet[u] = 1;

        // Update the distance of adjacent vertices of the selected vertex
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }

        // If we reach the target node, we can stop early
        if (u == target) {
            return dist[u];
        }
    }

    return dist[target];  // Return the distance to the target node
}


int main() {
    // Example graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    int source = 0; // Starting node
    dijkstra(graph, source);
    int target = 4;  // Target node
    dijkstraForTarget(graph, source,target);

    return 0;
}
