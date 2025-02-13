#include <stdio.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int row, col;
} Node;

typedef struct {
    Node arr[MAX * MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, Node n) {
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = n;
}

Node dequeue(Queue *q) {
    Node n = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return n;
}

// Directions for 4 directions (up, down, left, right)
int directions4[4][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

// Directions for 8 directions (including diagonals)
int directions8[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

// BFS function to mark all connected '1's as visited
void bfs(int grid[MAX][MAX], bool visited[MAX][MAX], int rows, int cols, int startRow, int startCol, int directions[8][2], int directionsCount) {
    Queue q;
    initQueue(&q);

    enqueue(&q, (Node){startRow, startCol});
    visited[startRow][startCol] = true;

    while (!isEmpty(&q)) {
        Node current = dequeue(&q);

        for (int i = 0; i < directionsCount; i++) {
            int newRow = current.row + directions[i][0];
            int newCol = current.col + directions[i][1];

            // Check if within bounds and if it's an unvisited land (1)
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                grid[newRow][newCol] == 1 && !visited[newRow][newCol]) {
                enqueue(&q, (Node){newRow, newCol});
                visited[newRow][newCol] = true;
            }
        }
    }
}

// Function to count the number of islands
int countIslands(int grid[MAX][MAX], int rows, int cols, int directions[8][2], int directionsCount) {
    bool visited[MAX][MAX] = {false}; // Initialize all as unvisited
    int islandCount = 0;

    // Traverse through each cell in the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // If we find an unvisited land cell (1), perform BFS
            if (grid[i][j] == 1 && !visited[i][j]) {
                islandCount++;  // Found a new island
                bfs(grid, visited, rows, cols, i, j, directions, directionsCount);
            }
        }
    }

    return islandCount;
}

// Main function
int main() {
    int grid[MAX][MAX] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 1, 0, 0},
        {1,0 , 0, 1, 1}
    };

    int rows = 4, cols = 5;

    // Count islands with 4 directions (up, down, left, right)
    int islands4 = countIslands(grid, rows, cols, directions4, 4);
    printf("Number of Islands (4 Directions) = %d\n", islands4);

    // Count islands with 8 directions (including diagonals)
    int islands8 = countIslands(grid, rows, cols, directions8, 8);
    printf("Number of Islands (8 Directions) = %d\n", islands8);

    return 0;
}
