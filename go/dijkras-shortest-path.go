package main

import (
	"container/heap"
	"fmt"
	"math"
)

type Item struct {
	node   int // The node in the graph
	weight int // The distance from the start node to this node
	index  int // The index of the item in the heap
}

// A priority queue of Items
type PriorityQueue []*Item

func (pq PriorityQueue) Len() int {
	return len(pq)
}

func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].weight < pq[j].weight // Min-heap based on weight
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
	pq[i].index = i
	pq[j].index = j
}

func (pq *PriorityQueue) Push(x interface{}) {
	n := len(*pq)
	item := x.(*Item)
	item.index = n
	*pq = append(*pq, item)
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	*pq = old[0 : n-1]
	return item
}

// Edge represents an edge in the graph with a destination node and a weight.
type Edge struct {
	to     int
	weight int
}

// Graph structure: A map where each node points to its neighbors and their respective edge weights.
type Graph struct {
	adjList map[int][]Edge
}

// NewGraph creates a new graph
func NewGraph() *Graph {
	return &Graph{adjList: make(map[int][]Edge)}
}

// Dijkstra's algorithm implementation
func (g *Graph) dijkstra(start int) []int {
	// Find the maximum node index to handle sparse graphs properly
	n := len(g.adjList)
	dist := make([]int, n)
	visited := make(map[int]bool)

	for i := 0; i < n; i++ {
		dist[i] = math.MaxInt32
		visited[i] = false
	}

	// Set distance to the start node as 0
	dist[start] = 0

	// Iterate over all nodes
	for count := 0; count < len(g.adjList); count++ {
		nextnode := -1

		// Find the unvisited node with the smallest distance
		for i := 0; i < n; i++ {
			if !visited[i] && (nextnode == -1 || (dist[i] < dist[nextnode])) {
				nextnode = i
			}
		}

		// If there's no next node, break the loop
		if nextnode == -1 {
			break
		}

		// Mark the node as visited
		visited[nextnode] = true

		// Update distances for neighbors of nextnode
		for _, edge := range g.adjList[nextnode] {
			v := edge.to
			weight := edge.weight
			// Relax the edge if a shorter path is found
			if dist[nextnode]+weight < dist[v] {
				dist[v] = dist[nextnode] + weight
			}
		}
	}

	return dist
}

// Add an edge to the graph
func (g *Graph) addEdge(from, to, weight int) {
	g.adjList[from] = append(g.adjList[from], Edge{to: to, weight: weight})
	// Ensure the 'to' node is also in the adjacency list
	if _, exists := g.adjList[to]; !exists {
		g.adjList[to] = []Edge{} // Initialize with an empty slice if it has no edges
	}
}

// Print the graph's adjacency list
func (g *Graph) printGraph() {
	fmt.Println("Graph adjacency list:")
	for node, edges := range g.adjList {
		fmt.Printf("Node %d:", node)
		for _, edge := range edges {
			fmt.Printf(" -> %d (weight: %d)", edge.to, edge.weight)
		}
		fmt.Println()
	}
}

func (g *Graph) dijkstraPriorityQueue(start int) []int {
	dist := make([]int, len(g.adjList))
	for i := range dist {
		dist[i] = math.MaxInt32
	}
	dist[start] = 0
	pq := &PriorityQueue{}
	heap.Push(pq, &Item{node: start, weight: 0})

	for pq.Len() > 0 {
		// Pop the node with the smallest distance
		current := heap.Pop(pq).(*Item)

		// Explore neighbors
		for _, edge := range g.adjList[current.node] {
			v := edge.to
			weight := edge.weight

			// Relax the edge if a shorter path is found
			if dist[current.node]+weight < dist[v] {
				dist[v] = dist[current.node] + weight
				heap.Push(pq, &Item{node: v, weight: dist[v]}) // Add updated distance to the queue
			}
		}
	}
	return dist
}

func main() {
	graph := NewGraph()

	// Add edges to the graph (from, to, weight)
	graph.addEdge(0, 1, 5)
	graph.addEdge(0, 3, 9)
	graph.addEdge(1, 2, 2)
	graph.addEdge(2, 3, 3)
	graph.addEdge(2, 4, 7)
	graph.addEdge(3, 4, 1)

	// Print the graph structure
	graph.printGraph()

	start := 0 // Ensure the starting node is valid

	// Get the shortest distances from the start node
	distances := graph.dijkstra(start)

	// Print the shortest path from the start node to all other nodes
	fmt.Printf("Shortest distances from node %d:\n", start)
	for node, dist := range distances {
		if dist == math.MaxInt32 {
			fmt.Printf("Node %d: Unreachable\n", node)
		} else {
			fmt.Printf("Node %d: %d\n", node, dist)
		}
	}
	distances1 := graph.dijkstraPriorityQueue(start)

	// Print the shortest path from the start node to all other nodes
	fmt.Printf("Priority Queue Shortest distances from node %d:\n", start)
	for node, dist := range distances1 {
		if dist == math.MaxInt32 {
			fmt.Printf("Node %d: Unreachable\n", node)
		} else {
			fmt.Printf("Node %d: %d\n", node, dist)
		}
	}
}
