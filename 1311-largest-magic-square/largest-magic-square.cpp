class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        // Prefix sums for rows and columns
        vector<vector<int>> row(m, vector<int>(n+1, 0));
        vector<vector<int>> col(m+1, vector<int>(n, 0));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                row[i][j+1] = row[i][j] + grid[i][j];
                col[i+1][j] = col[i][j] + grid[i][j];
            }
        }
        
        // Try sizes from large to small
        for (int k = min(m, n); k >= 2; k--) {
            for (int i = 0; i + k <= m; i++) {
                for (int j = 0; j + k <= n; j++) {
                    int target = row[i][j+k] - row[i][j];
                    bool ok = true;
                    
                    // Check rows
                    for (int r = i; r < i + k && ok; r++) {
                        if (row[r][j+k] - row[r][j] != target)
                            ok = false;
                    }
                    
                    // Check columns
                    for (int c = j; c < j + k && ok; c++) {
                        if (col[i+k][c] - col[i][c] != target)
                            ok = false;
                    }
                    
                    // Check diagonals
                    int d1 = 0, d2 = 0;
                    for (int x = 0; x < k; x++) {
                        d1 += grid[i + x][j + x];
                        d2 += grid[i + x][j + k - 1 - x];
                    }
                    
                    if (d1 != target || d2 != target)
                        ok = false;
                    
                    if (ok) return k;
                }
            }
        }
        
        return 1; // Every 1x1 is magic
    }
};

