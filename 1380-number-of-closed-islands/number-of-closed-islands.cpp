
class Solution {
public:
    void dfs(int i, int j, vector<vector<int>>& grid,
             int m, int n, bool &closed) {

        // If we touch the grid boundary,
        // this island is not closed.
        if (i < 0 || j < 0 || i >= m || j >= n) {
            closed = false;
            return;
        }

        // Water or already visited land
        if (grid[i][j] == 1) {
            return;
        }

        // Mark land as visited
        grid[i][j] = 1;

        // Explore all four directions
        dfs(i - 1, j, grid, m, n, closed); // Up
        dfs(i + 1, j, grid, m, n, closed); // Down
        dfs(i, j - 1, grid, m, n, closed); // Left
        dfs(i, j + 1, grid, m, n, closed); // Right
    }

    int closedIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (grid[i][j] == 0) {
                    bool closed = true;

                    dfs(i, j, grid, m, n, closed);

                    if (closed) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};
