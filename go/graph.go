package main

import (
	"fmt"
)

type Graph struct {
	mg map[int][]int
}
type UndirGraph struct {
	mg map[int][]int
}

func NewGraph() *Graph {
	return &Graph{mg: make(map[int][]int)}
}

func NewGraphUndir() *UndirGraph {
	return &UndirGraph{mg: make(map[int][]int)}
}
func (g *Graph) AddEdge(src, dest int) {
	g.mg[src] = append(g.mg[src], dest)
}

//for undirected add edge for src and destination
func (g *UndirGraph) AddEdge(src, dest int) {
	g.mg[src] = append(g.mg[src], dest)
	g.mg[dest] = append(g.mg[dest], src)
}

func (g *Graph) Print() {
	for ver, edge := range g.mg {
		fmt.Printf("%v->%v\n", ver, edge)
	}
}
func (g *UndirGraph) Print() {
	for ver, edge := range g.mg {
		fmt.Printf("%v->%v\n", ver, edge)
	}
}
func (g *Graph) DFS(src int) {
	visited := make(map[int]bool)
	g.DfsHelper(src, visited)
}

func (g *Graph) DfsHelper(src int, visited map[int]bool) {
	visited[src] = true
	fmt.Println(src)
	for _, edge := range g.mg[src] {
		if !visited[edge] {
			g.DfsHelper(edge, visited)
		}
	}
}

func (g *Graph) NewDFS(src int) {
	visited := make(map[int]bool)
	visited[src] = true
	fmt.Printf("New DFS Starting point %v\n", src)

	stack := []int{}
	stack = append(stack, src)
	for len(stack) > 0 {
		node := stack[len(stack)-1]
		stack = stack[:len(stack)-1]
		fmt.Println(node)
		for _, vertex := range g.mg[node] {
			if !visited[vertex] {
				visited[vertex] = true
				stack = append(stack, vertex)
			}
		}

	}
}

func (g *Graph) FindLoopDirectedHelper(node int, visited, recstack map[int]bool) bool {

	visited[node] = true
	recstack[node] = true
	for _, neighbour := range g.mg[node] {
		if !visited[neighbour] {
			if g.FindLoopDirectedHelper(neighbour, visited, recstack) {
				return true
			}
		} else if recstack[neighbour] {
			return true
		}
	}
	recstack[node] = false
	return false
}

func (g *Graph) FindLoopDirected() bool {
	visited := make(map[int]bool)
	recStack := make(map[int]bool)

	for node := range g.mg {
		if g.FindLoopDirectedHelper(node, visited, recStack) {
			return true
		}
	}
	return false
}

func (g *UndirGraph) FindLoopUnDirected() bool {
	visited := make(map[int]bool)
	for node, _ := range g.mg {
		if g.FindLoopHelperUni(node, -1, visited) {
			return true
		}
	}
	return false
}

func (g *UndirGraph) FindLoopHelperUni(node int, parent int, visited map[int]bool) bool {

	visited[node] = true
	for _, neighbour := range g.mg[node] {
		if !visited[neighbour] {
			if g.FindLoopHelperUni(neighbour, node, visited) {
				return true
			}
		} else if neighbour != node {
			return true
		}
	}
	return false
}
func (g *Graph) BFS(src int) {

	fmt.Printf("BFS starting from %v\n", src)
	queue := []int{}

	visited := make(map[int]bool)

	visited[src] = true
	queue = append(queue, src)

	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]
		fmt.Println(node)
		for _, edge := range g.mg[node] {
			if !visited[edge] {
				visited[edge] = true
				queue = append(queue, edge)
			}
		}
	}

}

func (g *Graph) dfspath(src, dest int, visited map[int]bool, path []int) ([]int, bool) {

	visited[src] = true
	path = append(path, src)
	if src == dest {
		return path, true
	}
	for _, v := range g.mg[src] {
		if !visited[v] {
			fpath, found := g.dfspath(v, dest, visited, path)
			if found {
				return fpath, true
			}
		}
	}
	return path, false
}
func (g *Graph) findpath(src, dest int) []int {
	path := []int{}
	visited := make(map[int]bool)
	foundpath, found := g.dfspath(src, dest, visited, path)
	if found {
		return foundpath
	} else {
		return []int{}
	}
}

func (g *Graph) DfsTopSort(node int, visited map[int]bool, stack *[]int) {

	visited[node] = true

	for _, v := range g.mg[node] {
		if !visited[v] {
			g.DfsTopSort(v, visited, stack)
		}
	}
	*stack = append(*stack, node)
}

func (g *Graph) toposort() {

	visited := make(map[int]bool)
	var stack []int
	for node := range g.mg {
		if !visited[node] {
			g.DfsTopSort(node, visited, &stack)
		}
	}

	//Being stack print in reverse order
	for j := len(stack) - 1; j >= 0; j-- {
		fmt.Printf("%v ", stack[j])
	}
	fmt.Println()

}

func (g *Graph) addEdge(from, to int) {
	g.mg[from] = append(g.mg[from], to)
	if _, exists := g.mg[to]; !exists {
		g.mg[to] = []int{} // Ensure the 'to' node exists in the graph
	}
}

func (g *Graph) BFStopologicalSort() {
	inDegree := make(map[int]int) // Track in-degree of each node

	// Initialize in-degrees
	for node := range g.mg {
		inDegree[node] = 0 // Initialize in-degrees to 0
	}

	// Calculate in-degrees for each node
	for _, neighbors := range g.mg {
		for _, neighbor := range g.mg[neighbors] {
			inDegree[neighbor]++ // Increment in-degree for each neighbor
		}
	}

	queue := []int{} // Queue for nodes with in-degree 0
	// Add all nodes with in-degree 0 to the queue
	for node, degree := range inDegree {
		if degree == 0 {
			queue = append(queue, node)
		}
	}

	var topoOrder []int // List to store topological order

	// Perform Kahn's Algorithm
	for len(queue) > 0 {
		// Dequeue a node with in-degree 0
		node := queue[0]
		queue = queue[1:]
		topoOrder = append(topoOrder, node)

		// Reduce in-degree of neighbors
		for _, neighbor := range g.mg[node] {
			inDegree[neighbor]--
			// If in-degree becomes 0, add it to the queue
			if inDegree[neighbor] == 0 {
				queue = append(queue, neighbor)
			}
		}
	}

	// Check if topological sort is valid (all nodes should be processed)
	if len(topoOrder) == len(g.mg) {
		fmt.Println("Topological Sort (BFS):", topoOrder)
	} else {
		fmt.Println("Graph contains a cycle, no topological sort possible.")
	}
}

func (g *Graph) printGraph() {
	for node, neighbors := range g.mg {
		fmt.Printf("%d -> %v\n", node, neighbors)
	}
}

func main() {
	// Create a new graph
	graph := NewGraph()

	// Add edges to the graph
	graph.AddEdge(1, 2)
	graph.AddEdge(1, 3)
	graph.AddEdge(2, 4)
	graph.AddEdge(3, 4)
	graph.AddEdge(4, 5)

	// Print the graph
	fmt.Println("Graph:")
	graph.Print()

	// Perform DFS
	fmt.Println("\nDFS starting from vertex 1:")
	graph.DFS(1)
	graph.NewDFS(1)
	graph.BFS(1)

	unigraph := NewGraphUndir()
	unigraph.AddEdge(0, 1)
	unigraph.AddEdge(1, 2)
	unigraph.AddEdge(2, 0) // This creates a cycle
	unigraph.AddEdge(2, 3)
	unigraph.Print()

	if unigraph.FindLoopUnDirected() {
		fmt.Println("Loop Detected")
	} else {
		fmt.Println("Loop not detected")
	}
	dirgraph := NewGraph()

	// Add edges (directed graph)
	dirgraph.AddEdge(0, 1)
	dirgraph.AddEdge(1, 2)
	dirgraph.AddEdge(2, 0) // Creates a cycle
	dirgraph.AddEdge(2, 3)

	// Print the graph structure
	dirgraph.Print()

	// Detect cycle in the graph
	if dirgraph.FindLoopDirected() {
		fmt.Println("Cycle detected in the directed graph!")
	} else {
		fmt.Println("No cycle found in the directed graph.")
	}
	graph1 := NewGraph()
	// Add edges to the graph (undirected graph example)
	graph1.AddEdge(0, 1)
	graph1.AddEdge(1, 2)
	graph1.AddEdge(1, 3)
	graph1.AddEdge(2, 4)
	graph1.AddEdge(3, 4)
	graph1.AddEdge(4, 5)
	src, dest := 1, 5
	graph1.Print()
	path := graph1.findpath(src, dest)

	if len(path) > 0 {
		fmt.Printf("Path from %d to %d: %v\n", src, dest, path)
	} else {
		fmt.Printf("No path found from %d to %d\n", src, src)
	}

	graph2 := NewGraph()
	graph2.AddEdge(5, 2)
	graph2.AddEdge(5, 0)
	graph2.AddEdge(4, 0)
	graph2.AddEdge(4, 1)
	graph2.AddEdge(2, 3)
	graph2.AddEdge(3, 1)

	graph2.Print()
	graph2.toposort()

	graph3 := NewGraph()
	graph3.addEdge(5, 2)
	graph3.addEdge(5, 0)
	graph3.addEdge(4, 0)
	graph3.addEdge(4, 1)
	graph3.addEdge(2, 3)
	graph3.addEdge(3, 1)

	graph3.printGraph()
	graph3.BFStopologicalSort()

}
