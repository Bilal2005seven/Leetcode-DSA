class Solution {
public:
    int minimumDeletions(string s) {
        int b_count = 0;
        int deletions = 0;

        for (char c : s) {
            if (c == 'b') {
                b_count++;
            } else { // c == 'a'
                // Option 1: delete current 'a'   → deletions + 1
                // Option 2: delete earlier 'b's → b_count
                deletions = min(deletions + 1, b_count);
            }
        }

        return deletions;
    }
};
