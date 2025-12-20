class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int ans = 0;
        int rows = strs.size();
        int cols = strs[0].size();

        for (int c = 0; c < cols; c++) {
            for (int r = 1; r < rows; r++) {
                if (strs[r][c] < strs[r - 1][c]) {
                    ans++;
                    break; // stop checking this column
                }
            }
        }
        return ans;
    }
};
