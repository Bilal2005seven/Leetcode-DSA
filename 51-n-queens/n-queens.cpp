#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void solve(int row, int n, vector<string>& board, 
               vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2, 
               vector<vector<string>>& result) {
        // Base case: saari rows par queens successfully place ho gayi
        if (row == n) {
            result.push_back(board);
            return;
        }

        // Current row ke har column par queen rakhne ki koshish karo
        for (int col = 0; col < n; col++) {
            // O(1) safety check
            if (cols[col] || diag1[row + col] || diag2[row - col + (n - 1)]) {
                continue; // Safe nahi hai, skip karo
            }

            // Step 1: CHOOSE
            board[row][col] = 'Q';
            cols[col] = true;
            diag1[row + col] = true;
            diag2[row - col + (n - 1)] = true;

            // Step 2: EXPLORE (agli row par jao)
            solve(row + 1, n, board, cols, diag1, diag2, result);

            // Step 3: UNCHOOSE / BACKTRACK (state restore karo)
            board[row][col] = '.';
            cols[col] = false;
            diag1[row + col] = false;
            diag2[row - col + (n - 1)] = false;
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        // n x n ka empty board "." se bharo
        vector<string> board(n, string(n, '.'));

        // O(1) checks ke liye lookup arrays
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false); // row + col
        vector<bool> diag2(2 * n - 1, false); // row - col + (n - 1)

        solve(0, n, board, cols, diag1, diag2, result);
        return result;
    }
};