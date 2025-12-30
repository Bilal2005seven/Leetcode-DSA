class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int count = 0;

        for (int r = 0; r + 2 < rows; r++) {
            for (int c = 0; c + 2 < cols; c++) {
                if (isMagic(grid, r, c)) {
                    count++;
                }
            }
        }
        return count;
    }

    bool isMagic(vector<vector<int>>& grid, int r, int c) {
        // Center must be 5
        if (grid[r + 1][c + 1] != 5) return false;

        bool seen[10] = {false};

        // Check numbers are 1–9 and unique
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int val = grid[r + i][c + j];
                if (val < 1 || val > 9 || seen[val]) return false;
                seen[val] = true;
            }
        }

        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if (grid[r + i][c] + grid[r + i][c + 1] + grid[r + i][c + 2] != 15)
                return false;
            if (grid[r][c + i] + grid[r + 1][c + i] + grid[r + 2][c + i] != 15)
                return false;
        }

        // Check diagonals
        if (grid[r][c] + grid[r + 1][c + 1] + grid[r + 2][c + 2] != 15)
            return false;
        if (grid[r][c + 2] + grid[r + 1][c + 1] + grid[r + 2][c] != 15)
            return false;

        return true;
    }
};
