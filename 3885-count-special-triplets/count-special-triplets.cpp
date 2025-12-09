class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        const long long MOD = 1e9 + 7;
        unordered_map<long long, long long> left, right;
        long long result = 0;


        for (long long x : nums) {
            right[x]++;
        }

        for (int j = 0; j < nums.size(); j++) {
            long long val = nums[j];
            right[val]--;  

            long long need = val * 2;

            long long leftCount = left[need];
            long long rightCount = right[need];

            result = (result + (leftCount * rightCount) % MOD) % MOD;

            left[val]++;  
        }
        return result % MOD;
    }
};
