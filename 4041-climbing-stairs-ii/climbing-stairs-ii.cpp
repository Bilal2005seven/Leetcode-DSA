#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        // p1 = dp[i - 1], p2 = dp[i - 2], p3 = dp[i - 3]
        long long p1 = 0; // dp[0] = 0
        long long p2 = 1e18;
        long long p3 = 1e18;

        for (int i = 1; i <= n; ++i) {
            long long best_prev = p1 + 1; // jump of 1: 1^2 = 1
            
            if (i >= 2) {
                best_prev = min(best_prev, p2 + 4); // jump of 2: 2^2 = 4
            }
            if (i >= 3) {
                best_prev = min(best_prev, p3 + 9); // jump of 3: 3^2 = 9
            }

            long long curr = costs[i - 1] + best_prev;

            // Slide window forward
            p3 = p2;
            p2 = p1;
            p1 = curr;
        }

        return p1;
    }
};