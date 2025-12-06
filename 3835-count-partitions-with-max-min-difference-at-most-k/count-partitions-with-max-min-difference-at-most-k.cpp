#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const long long MOD = 1000000007LL;
        int n = nums.size();
        vector<long long> dp(n), pref(n);
        
        deque<int> maxQ, minQ;
        int l = 0;

        for (int i = 0; i < n; i++) {
            // maintain max queue
            while (!maxQ.empty() && nums[maxQ.back()] <= nums[i]) maxQ.pop_back();
            maxQ.push_back(i);

            // maintain min queue
            while (!minQ.empty() && nums[minQ.back()] >= nums[i]) minQ.pop_back();
            minQ.push_back(i);

            // shrink window until valid
            while (nums[maxQ.front()] - nums[minQ.front()] > k) {
                if (maxQ.front() == l) maxQ.pop_front();
                if (minQ.front() == l) minQ.pop_front();
                l++;
            }

            // DP calculation
            if (l == 0) {
                dp[i] = (i > 0 ? pref[i-1] : 0) + 1;
            } else {
                long long total = (i > 0 ? pref[i-1] : 0);
                long long subtract = (l-2 >= 0 ? pref[l-2] : 0);
                dp[i] = (total - subtract + MOD) % MOD;
            }

            pref[i] = ((i > 0 ? pref[i-1] : 0) + dp[i]) % MOD;
        }

        return (int)dp[n-1];
    }
};
