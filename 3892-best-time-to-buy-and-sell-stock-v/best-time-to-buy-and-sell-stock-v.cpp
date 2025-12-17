class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        const long long NEG = -1e18;
        int n = prices.size();

        // dp[t][state]
        // state 0 = free
        // state 1 = holding long
        // state 2 = holding short
        vector<vector<long long>> dp(k + 1, vector<long long>(3, NEG));
        dp[0][0] = 0;

        for (int price : prices) {
            auto ndp = dp;

            for (int t = 0; t <= k; t++) {
                // Open long or short (no transaction count yet)
                ndp[t][1] = max(ndp[t][1], dp[t][0] - price); // buy
                ndp[t][2] = max(ndp[t][2], dp[t][0] + price); // short sell

                if (t + 1 <= k) {
                    // Close long
                    ndp[t + 1][0] = max(ndp[t + 1][0], dp[t][1] + price);
                    // Close short
                    ndp[t + 1][0] = max(ndp[t + 1][0], dp[t][2] - price);
                }
            }
            dp.swap(ndp);
        }

        long long ans = 0;
        for (int t = 0; t <= k; t++) {
            ans = max(ans, dp[t][0]);
        }
        return ans;
    }
};
