class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();

        const int INF = 1e9;

        // cost[i][j] = minimum cost to reach destination from (i,j)
        vector<vector<int>> cost(n, vector<int>(m, INF));
        cost[n-1][m-1] = 0;

        int maxVal = 0;
        for (auto &row : grid)
            for (int x : row)
                maxVal = max(maxVal, x);

        vector<int> tcost(maxVal + 1, INF);

        for (int t = 0; t <= k; t++) {

            // DP from bottom-right to top-left
            for (int i = n - 1; i >= 0; i--) {
                for (int j = m - 1; j >= 0; j--) {

                    if (i < n - 1)
                        cost[i][j] = min(cost[i][j], cost[i + 1][j] + grid[i + 1][j]);

                    if (j < m - 1)
                        cost[i][j] = min(cost[i][j], cost[i][j + 1] + grid[i][j + 1]);

                    if (t > 0)
                        cost[i][j] = min(cost[i][j], tcost[grid[i][j]]);
                }
            }

            // recompute tcost for next t
            fill(tcost.begin(), tcost.end(), INF);

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    int v = grid[i][j];
                    tcost[v] = min(tcost[v], cost[i][j]);
                }
            }

            // prefix minimum
            for (int i = 1; i < (int)tcost.size(); i++) {
                tcost[i] = min(tcost[i], tcost[i - 1]);
            }
        }

        return cost[0][0];
    }
};