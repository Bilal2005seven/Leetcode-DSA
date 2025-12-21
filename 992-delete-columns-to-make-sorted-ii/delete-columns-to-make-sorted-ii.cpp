class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        
        vector<bool> resolved(n - 1, false);
        int deletions = 0;

        for (int col = 0; col < m; col++) {
            bool needDelete = false;

            // Check if this column breaks ordering
            for (int i = 0; i < n - 1; i++) {
                if (!resolved[i] && strs[i][col] > strs[i + 1][col]) {
                    needDelete = true;
                    break;
                }
            }

            if (needDelete) {
                deletions++;
                continue; // Skip updating resolved, column is deleted
            }

            // Update resolved pairs
            for (int i = 0; i < n - 1; i++) {
                if (!resolved[i] && strs[i][col] < strs[i + 1][col]) {
                    resolved[i] = true;
                }
            }
        }

        return deletions;
    }
};
