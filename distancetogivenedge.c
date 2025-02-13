#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Combined direction array for moving up, down, left, right
int dRow[] = {-1, 1, 0, 0};
int dCol[] = {0, 0, -1, 1};

// Queue node structure for BFS
typedef struct {
    int row, col, dist;
} QueueNode;

// Queue structure
typedef struct {
    QueueNode nodes[MAX * MAX];
    int front, rear;
} Queue;

// Queue functions
void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int row, int col, int dist) {
    q->nodes[q->rear++] = (QueueNode){row, col, dist};
}

QueueNode dequeue(Queue *q) {
    return q->nodes[q->front++];
}

// Check if position is valid
int isValid(int row, int col, int rows, int cols, int grid[MAX][MAX], int visited[MAX][MAX]) {
    return (row >= 0 && row < rows && col >= 0 && col < cols && grid[row][col] == 1 && !visited[row][col]);
}

// Approach 1: Find shortest path from any edge to given start position (S)
int minDistanceFromEdgeToS(int grid[MAX][MAX], int rows, int cols, int startRow, int startCol) {
    if (grid[startRow][startCol] == 0) return -1;  // Invalid start

    int visited[MAX][MAX] = {0};
    Queue q;
    initQueue(&q);

    // Add all edges that have '1' to the queue
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if ((r == 0 || r == rows - 1 || c == 0 || c == cols - 1) && grid[r][c] == 1) {
                enqueue(&q, r, c, 0);
                visited[r][c] = 1;
            }
        }
    }

    // BFS
    while (!isEmpty(&q)) {
        QueueNode curr = dequeue(&q);
        int r = curr.row, c = curr.col, dist = curr.dist;

        // If we reached the start position, return distance
        if (r == startRow && c == startCol) return dist;

        for (int i = 0; i < 4; i++) {
            int newRow = r + dRow[i];
            int newCol = c + dCol[i];

            if (isValid(newRow, newCol, rows, cols, grid, visited)) {
                visited[newRow][newCol] = 1;
                enqueue(&q, newRow, newCol, dist + 1);
            }
        }
    }
    return -1;
}

// Approach 2: Find shortest path from given start to any edge
int minDistanceFromSToEdge(int grid[MAX][MAX], int rows, int cols, int startRow, int startCol) {
    if (grid[startRow][startCol] == 0) return -1;  // Invalid start

    int visited[MAX][MAX] = {0};
    Queue q;
    initQueue(&q);

    enqueue(&q, startRow, startCol, 0);
    visited[startRow][startCol] = 1;

    while (!isEmpty(&q)) {
        QueueNode curr = dequeue(&q);
        int r = curr.row, c = curr.col, dist = curr.dist;

        // If reached an edge, return distance
        if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) {
            return dist;
        }

        for (int i = 0; i < 4; i++) {
            int newRow = r + dRow[i];
            int newCol = c + dCol[i];

            if (isValid(newRow, newCol, rows, cols, grid, visited)) {
                visited[newRow][newCol] = 1;
                enqueue(&q, newRow, newCol, dist + 1);
            }
        }
    }
    return -1;
}

// Driver function
int main() {
    int grid[MAX][MAX] = {
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 1, 0},
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0}
    };
    int rows = 5, cols = 5;
    int startRow = 2, startCol = 2;

    printf("Approach 1: Distance from nearest edge to (%d, %d): %d\n", startRow, startCol,
           minDistanceFromEdgeToS(grid, rows, cols, startRow, startCol));

    printf("Approach 2: Distance from (%d, %d) to nearest edge: %d\n", startRow, startCol,
           minDistanceFromSToEdge(grid, rows, cols, startRow, startCol));

    return 0;
}
