#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAX 100

// Directions for 4 directions (up, down, left, right)
int directions4[4][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

// Directions for 8 directions (including diagonals)
int directions8[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

struct Node {
    int row, col;
};

void bfs(int grid[MAX][MAX], vector<vector<bool>>& visited, int rows, int cols, int startRow, int startCol, int directions[8][2], int directionsCount) {
    queue<Node> q;
    q.push({startRow, startCol});
    visited[startRow][startCol] = true;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        for (int i = 0; i < directionsCount; i++) {
            int newRow = current.row + directions[i][0];
            int newCol = current.col + directions[i][1];

            // Check if within bounds and if it's an unvisited land (1)
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                grid[newRow][newCol] == 1 && !visited[newRow][newCol]) {
                q.push({newRow, newCol});
                visited[newRow][newCol] = true;
            }
        }
    }
}

int countIslands(int grid[MAX][MAX], int rows, int cols, int directions[8][2], int directionsCount) {
    vector<vector<bool>> visited(rows, vector<bool>(cols, false)); // Initialize all as unvisited
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

int main() {
    int grid[MAX][MAX] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 1}
    };

    int rows = 4, cols = 5;

    // Count islands with 4 directions (up, down, left, right)
    int islands4 = countIslands(grid, rows, cols, directions4, 4);
    cout << "Number of Islands (4 Directions) = " << islands4 << endl;

    // Count islands with 8 directions (including diagonals)
    int islands8 = countIslands(grid, rows, cols, directions8, 8);
    cout << "Number of Islands (8 Directions) = " << islands8 << endl;

    return 0;
}
