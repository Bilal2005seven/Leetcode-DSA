#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> createGrid(int m, int n) {
        // Initialize an m x n grid filled with obstacles '#'
        vector<string> grid(m, string(n, '#'));

        // Step 1: Carve path across row 0
        for (int j = 0; j < n; ++j) {
            grid[0][j] = '.';
        }

        // Step 2: Carve path down the last column (n - 1)
        for (int i = 0; i < m; ++i) {
            grid[i][n - 1] = '.';
        }

        return grid;
    }
};