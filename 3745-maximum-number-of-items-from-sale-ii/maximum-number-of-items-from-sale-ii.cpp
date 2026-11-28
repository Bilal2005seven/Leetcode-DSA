#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        long long minPrice = LLONG_MAX;
        int maxFactor = 0;

        for (int i = 0; i < n; i++) {
            maxFactor = max(maxFactor, items[i][0]);
            minPrice = min(minPrice, (long long)items[i][1]);
        }

        // Step 1: Frequency of each factor
        vector<int> freq(maxFactor + 1, 0);
        for (int i = 0; i < n; i++) {
            freq[items[i][0]]++;
        }

        // Step 2: Sieve-style multiple count in O(M log M)
        // multiples[f] = total items whose factor is divisible by f
        vector<int> multiples(maxFactor + 1, 0);
        for (int f = 1; f <= maxFactor; f++) {
            if (freq[f] == 0) continue;
            for (int m = f; m <= maxFactor; m += f) {
                multiples[f] += freq[m];
            }
        }

        // Step 3: Build {price, bonus_count} buckets
        vector<pair<long long, int>> buckets;
        buckets.reserve(n);

        for (int i = 0; i < n; i++) {
            int f = items[i][0];
            long long price = items[i][1];
            int count = multiples[f] - 1; // Exclude item i itself (j != i)

            if (count > 0 && price <= budget) {
                buckets.push_back({price, count});
            }
        }

        // Step 4: Sort buckets by price ascending and greedily sweep
        sort(buckets.begin(), buckets.end());

        long long ans = budget / minPrice;
        long long spent = 0;
        long long bonusTaken = 0;

        for (auto& [price, count] : buckets) {
            long long canBuy = min((long long)count, (budget - spent) / price);
            if (canBuy <= 0) break;

            spent += canBuy * price;
            bonusTaken += canBuy;
            ans = max(ans, 2 * bonusTaken + (budget - spent) / minPrice);

            if (canBuy < count) break;
        }

        return (int)ans;
    }
};