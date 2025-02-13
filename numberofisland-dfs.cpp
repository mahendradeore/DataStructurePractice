#include <iostream>
#include <vector>

using namespace std;

// Directions to move up, down, left, right, and diagonals
int directions[8][2] = {
    {-1, 0}, // Up
    {1, 0},  // Down
    {0, -1}, // Left
    {0, 1},  // Right
    {-1, -1}, // Up-left diagonal
    {-1, 1},  // Up-right diagonal
    {1, -1},  // Down-left diagonal
    {1, 1}    // Down-right diagonal
};

// Function to perform DFS on the grid and mark the visited land
void dfs(vector<vector<int>>& grid, int x, int y) {
    // If out of bounds or water ('0'), return
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == 0) {
        return;
    }
    
    // Mark the current cell as visited (set it to '0')
    grid[x][y] = 0;
    
    // Explore all 8 directions (up, down, left, right, and diagonals)
    for (auto dir : directions) {
        dfs(grid, x + dir[0], y + dir[1]);
    }
}

// Function to count the number of islands
int numIslands(vector<vector<int>>& grid) {
    if (grid.empty()) return 0;
    
    int count = 0;
    
    // Iterate through every cell in the grid
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            // If we find a land ('1'), it marks the start of a new island
            if (grid[i][j] == 1) {
                count++; // Increment the island count
                dfs(grid, i, j); // Perform DFS to mark all the connected lands
            }
        }
    }
    
    return count;
}

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1}
    };
    
    cout << "Number of Islands: " << numIslands(grid) << endl;
    
    return 0;
}
