#include <vector>

using namespace std;

class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int validIslands = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    long long totalSum = dfs(grid, i, j, m, n);
                    if (totalSum % k == 0) {
                        validIslands++;
                    }
                }
            }
        }

        return validIslands;
    }

private:
    long long dfs(vector<vector<int>>& grid, int r, int c, int m, int n) {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) {
            return 0;
        }

        long long currentSum = grid[r][c];
        grid[r][c] = 0;

        static const int dr[] = {-1, 1, 0, 0};
        static const int dc[] = {0, 0, -1, 1};

        for (int d = 0; d < 4; ++d) {
            currentSum += dfs(grid, r + dr[d], c + dc[d], m, n);
        }

        return currentSum;
    }
};