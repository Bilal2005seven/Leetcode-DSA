class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        long long total = 0;
        int n = nums.size();
        for (int x : nums) total += x;
        int target = total % p;
        if (target == 0) return 0;

        unordered_map<int, int> mp; // prefix_mod -> last index where this mod occurred
        mp[0] = -1;                  // prefix before array has mod 0 at index -1
        long long prefix = 0;
        int res = n;

        for (int i = 0; i < n; ++i) {
            prefix = (prefix + nums[i]) % p;
            int curMod = (int)prefix;
            int need = (curMod - target + p) % p;
            if (mp.count(need)) {
                res = min(res, i - mp[need]); // candidate length
            }
            // update to the latest index for this mod
            mp[curMod] = i;
        }

        return res == n ? -1 : res;
    }
};
