#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
    multiset<long long> left_set, right_set;
    long long sum_left = 0, sum_right = 0;
    int target_left_size;

    void balance() {
        while (left_set.size() > target_left_size) {
            auto it = prev(left_set.end());
            long long val = *it;
            left_set.erase(it);
            sum_left -= val;
            right_set.insert(val);
            sum_right += val;
        }
        while (left_set.size() < target_left_size && !right_set.empty()) {
            auto it = right_set.begin();
            long long val = *it;
            right_set.erase(it);
            sum_right -= val;
            left_set.insert(val);
            sum_left += val;
        }
    }

    void add(long long val) {
        if (left_set.empty() || val <= *left_set.rbegin()) {
            left_set.insert(val);
            sum_left += val;
        } else {
            right_set.insert(val);
            sum_right += val;
        }
        balance();
    }

    void remove(long long val) {
        auto it = left_set.find(val);
        if (it != left_set.end()) {
            left_set.erase(it);
            sum_left -= val;
        } else {
            it = right_set.find(val);
            if (it != right_set.end()) {
                right_set.erase(it);
                sum_right -= val;
            }
        }
        balance();
    }

    long long getCost() {
        long long median = *left_set.rbegin();
        long long cost = ((long long)left_set.size() * median - sum_left) +
                         (sum_right - (long long)right_set.size() * median);
        return cost;
    }

public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        target_left_size = (x + 1) / 2;

        left_set.clear();
        right_set.clear();
        sum_left = sum_right = 0;

        // cost[i] = cost to equalize subarray nums[i - x + 1 ... i]
        vector<long long> cost(n, 0);

        for (int i = 0; i < n; ++i) {
            add(nums[i]);
            if (i >= x) {
                remove(nums[i - x]);
            }
            if (i >= x - 1) {
                cost[i] = getCost();
            }
        }

        const long long INF = 1e18;
        // dp[i] = min cost to select j subarrays ending on or before index i
        vector<long long> prev_dp(n, 0);

        for (int j = 1; j <= k; ++j) {
            vector<long long> curr_dp(n, INF);

            for (int i = j * x - 1; i < n; ++i) {
                // Option 1: Do not place a subarray ending at index i
                curr_dp[i] = curr_dp[i - 1];

                // Option 2: Place a subarray ending at index i
                long long prev_cost = (i >= x) ? prev_dp[i - x] : 0;
                if (prev_cost != INF) {
                    curr_dp[i] = min(curr_dp[i], prev_cost + cost[i]);
                }
            }

            prev_dp = move(curr_dp);
        }

        return prev_dp[n - 1];
    }
};