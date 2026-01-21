class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;
        for (int p : nums) {
            // If LSB is 0, impossible
            if ((p & 1) == 0) {
                ans.push_back(-1);
                continue;
            }

            // Count trailing 1s
            int t = 0;
            while ((p >> t) & 1) t++;

            int k = t - 1;
            int x = p - (1 << k);
            ans.push_back(x);
        }
        return ans;
    }
};
