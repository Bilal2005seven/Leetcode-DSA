class Solution {
public:
    //optimal version
    
    long long maxSubarraySum(vector<int>& nums, int k) {
        long long prefix = 0;
        long long ans = LLONG_MIN;

        vector<long long> best(k, LLONG_MAX);
        best[0] = 0;

        for (int i = 0; i < nums.size(); i++) {
            prefix += nums[i];
            int r = (i + 1) % k;

            if (best[r] != LLONG_MAX) { 
                ans = max(ans, prefix - best[r]);
            }

            best[r] = min(best[r], prefix);
        }

        return ans;
    }
};
