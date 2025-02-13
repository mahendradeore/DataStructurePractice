#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int row, col;
} Node;

int directions[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

typedef struct {
    int row, col, dist;
} QueueNode;

typedef struct {
    QueueNode arr[MAX * MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, QueueNode n) {
    if (q->front == -1) q->front = 0;
    q->arr[++q->rear] = n;
}

QueueNode dequeue(Queue *q) {
    QueueNode n = q->arr[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return n;
}

void printPath(Node *path, int pathLen) {
    printf("Path: ");
    for (int i = 0; i < pathLen; i++) {  // Print path from start to end
        printf("(%d, %d) -> ", path[i].row, path[i].col);
    }
    printf("END\n");
}

int shortestPath(int grid[MAX][MAX], int rows, int cols, int srow, int scol, int drow, int dcol) {
    if (grid[srow][scol] == 0 || grid[drow][dcol] == 0) return -1;

    int visited[MAX][MAX] = {0};
    Node path[MAX * MAX];  // Array to store the path
    int pathIndex = 0;

    Queue q;
    initQueue(&q);

    enqueue(&q, (QueueNode){srow, scol, 0});
    visited[srow][scol] = 1;
    path[pathIndex++] = (Node){srow, scol}; // Add the start point to path

    while (!isEmpty(&q)) {
        QueueNode n = dequeue(&q);
        int row = n.row, col = n.col, dist = n.dist;

        if (row == drow && col == dcol) {
            printPath(path, pathIndex);  // Print the path in order (start -> end)
            return dist;
        }

        for (int i = 0; i < 8; i++) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                grid[newRow][newCol] == 1 && !visited[newRow][newCol]) {
                
                enqueue(&q, (QueueNode){newRow, newCol, dist + 1});
                visited[newRow][newCol] = 1;
                path[pathIndex++] = (Node){newRow, newCol}; // Add to path when moving
            }
        }
    }

    return -1;  // Return -1 if no path exists
}

int main() {
    int grid[MAX][MAX] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1}
    };

    int rows = 4, cols = 5;
    int srow = 0, scol = 0;
    int drow = 3, dcol = 4;

    int dist = shortestPath(grid, rows, cols, srow, scol, drow, dcol);
    if (dist != -1)
        printf("Shortest Path Length = %d\n", dist);
    else
        printf("No path exists.\n");

    return 0;
}
