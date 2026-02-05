class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                result[i] = 0;
            } else {
                // compute target index using modulo
                int target = (i + nums[i]) % n;
                if (target < 0) target += n; // fix negative modulo
                result[i] = nums[target];
            }
        }

        return result;
    }
};
