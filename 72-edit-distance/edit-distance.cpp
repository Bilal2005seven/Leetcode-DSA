#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);

        // Base case for row 0 (empty word1)
        for (int j = 0; j <= n; j++) {
            prev[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            curr[0] = i; // Base case: converting prefix length i to empty word2
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    curr[j] = prev[j - 1];
                } else {
                    int insertOp = curr[j - 1];
                    int deleteOp = prev[j];
                    int replaceOp = prev[j - 1];

                    curr[j] = 1 + min({insertOp, deleteOp, replaceOp});
                }
            }
            prev = curr;
        }

        return prev[n];
    }
};