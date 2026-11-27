#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> bonus(n, 0);
        int minPrice = INT_MAX;

        // Step 1: Calculate free copies (bonus) for each item and find the global minimum price
        for (int i = 0; i < n; i++) {
            minPrice = min(minPrice, items[i][1]);
            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    bonus[i]++;
                }
            }
        }

        // Step 2: 0/1 Knapsack DP
        // dp[c] = max items obtained by spending exact cost 'c' (buying at most 1 copy per item)
        vector<int> dp(budget + 1, -1);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            int value = 1 + bonus[i];

            for (int c = budget; c >= price; c--) {
                if (dp[c - price] != -1) {
                    dp[c] = max(dp[c], dp[c - price] + value);
                }
            }
        }

        // Step 3: Spend any remaining budget on the cheapest item available
        int ans = 0;
        for (int c = 0; c <= budget; c++) {
            if (dp[c] != -1) {
                int extraCopies = (budget - c) / minPrice;
                ans = max(ans, dp[c] + extraCopies);
            }
        }

        return ans;
    }
};