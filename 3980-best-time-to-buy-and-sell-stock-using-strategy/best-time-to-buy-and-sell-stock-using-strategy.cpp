class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        int half = k / 2;

        // Original profit
        long long original = 0;
        for (int i = 0; i < n; i++) {
            original += 1LL * strategy[i] * prices[i];
        }

        if (n < k) return original;

        // Prefix sums
        vector<long long> prefA(n + 1, 0), prefP(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefA[i + 1] = prefA[i] + 1LL * strategy[i] * prices[i];
            prefP[i + 1] = prefP[i] + prices[i];
        }

        long long bestChange = 0;

        // Sliding window using prefix sums
        for (int i = 0; i + k <= n; i++) {
            long long removed = prefA[i + k] - prefA[i];
            long long added   = prefP[i + k] - prefP[i + half];
            long long change = -removed + added;
            bestChange = max(bestChange, change);
        }

        return original + bestChange;
    }
};
