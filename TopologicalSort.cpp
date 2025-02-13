#include<iostream>
#include<vector>
#include<map>
#include<queue>

using namespace std;

void kahnsBFStopologicalSort(vector<vector<int>>& graph) {
    map<int, int> indegrees;  // Store the indegree of each node
    vector<int> topoprder;     // Store the topological order
    queue<int> pq;             // Queue to process nodes

    // Initialize indegree for all nodes (the number of incoming edges)
    for (auto &vec : graph) {
        for (auto &node : vec) {
            indegrees[node]++;
        }
    }

    // Add nodes with zero indegree to the queue
    for (int i = 0; i < graph.size(); ++i) {
        if (indegrees[i] == 0) {
            pq.push(i);  // Push node with zero indegree into the queue
        }
    }

    // Process nodes from the queue
    while (!pq.empty()) {
        int node = pq.front();  // Get the node with zero indegree
        topoprder.push_back(node);  // Add it to the topological order
        pq.pop();  // Remove the node from the queue
        
        // For each neighbor of the current node
        for (auto &n : graph[node]) {
            indegrees[n]--;  // Decrease the indegree of the neighbor
            
            if (indegrees[n] == 0) {
                pq.push(n);  // If the neighbor's indegree becomes 0, add it to the queue
            }
        }
    }

    // Check if a valid topological order exists
    if (topoprder.size() != graph.size()) {
        cout << "Graph has a cycle; no topological order exists." << endl;
    } else {
        cout << "Topological Order: ";
        for (int node : topoprder) {
            cout << node << " ";
        }
        cout << endl;
    }
}

bool DFShelper(vector<vector<int>>& graph, map<int, bool>& visited, vector<bool>& recStack, int node, stack<int>& topoorder) {
    // Mark the current node as visited and part of the recursion stack
    visited[node] = true;
    recStack[node] = true;

    // Recur for all the neighbors
    for (auto& neighbour : graph[node]) {
        if (!visited[neighbour]) {
            // If the neighbor hasn't been visited, recurse
            if (DFShelper(graph, visited, recStack, neighbour, topoorder)) {
                return true;  // If a cycle is detected, return true
            }
        } else if (recStack[neighbour]) {
            // If the neighbor is already in the recursion stack, a cycle is detected
            return true;
        }
    }

    // Once the node is processed and all its neighbors are processed, remove it from the recursion stack
    recStack[node] = false;

    // Add the node to the topological order
    topoorder.push(node);
    return false;  // No cycle detected for this node
}

void DFSTopoSort(vector<vector<int>>& graph) {
    int n = graph.size();
    map<int, bool> visited;        // To keep track of visited nodes
    vector<bool> recStack(n, false); // To track nodes in the current DFS path (recursion stack)
    stack<int> topoorder;          // Stack to store the topological sort

    // Perform DFS for every node to ensure all nodes are covered (useful for disconnected graphs)
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // If the node is not visited, perform DFS
            if (DFShelper(graph, visited, recStack, i, topoorder)) {
                cout << "Cycle detected" << endl;  // If a cycle is detected during DFS
                return;
            }
        }
    }

    // If no cycle is detected, output the topological order (reverse post-order)
    cout << "Topological Order: ";
    while (!topoorder.empty()) {
        cout << topoorder.top() << " ";
        topoorder.pop();
    }
    cout << endl;
}

int main() {
    vector<vector<int>> graph = {
        {1, 2},    // Node 0 → 1, 2
        {3, 4},    // Node 1 → 3, 4
        {},        // Node 2 → (no edges)
        {},        // Node 3 → (no edges)
        {3}        // Node 4 → 3
    };

    kahnsBFStopologicalSort(graph);
    DFSTopoSort(graph);
    return 0;
}
