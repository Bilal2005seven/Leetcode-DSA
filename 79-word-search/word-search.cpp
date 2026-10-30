#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    bool dfs(int r, int c, int index, vector<vector<char>>& board, const string& word) {
        // Base case: saare characters match ho gaye
        if (index == word.size()) return true;

        // Boundary check aur character match check
        if (r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] != word[index]) {
            return false;
        }

        // STEP 1: CHOOSE (Cell ko temporary mark karo taaki current path me repeat na ho)
        char originalChar = board[r][c];
        board[r][c] = '#';

        // STEP 2: EXPLORE (Charo directions: Up, Down, Left, Right)
        bool found = dfs(r + 1, c, index + 1, board, word) ||
                     dfs(r - 1, c, index + 1, board, word) ||
                     dfs(r, c + 1, index + 1, board, word) ||
                     dfs(r, c - 1, index + 1, board, word);

        // STEP 3: UNCHOOSE / BACKTRACK (Original character restore karo)
        board[r][c] = originalChar;

        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        // Har cell ko starting point bana kar check karo
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word[0]) {
                    if (dfs(i, j, 0, board, word)) {
                        return true; // Early exit milte hi
                    }
                }
            }
        }

        return false;
    }
};