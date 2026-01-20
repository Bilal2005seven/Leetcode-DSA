class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;
        for (int n : nums) {
            if ((n & 1) == 0) {   // even → impossible
                ans.push_back(-1);
                continue;
            }
            int r = 0;
            int t = n;
            while (t & 1) {   // count trailing ones
                r++;
                t >>= 1;
            }
            int x = n - (1 << (r - 1));
            ans.push_back(x);
        }
        return ans;
    }
};
