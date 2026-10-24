#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int totalSubsets = 1 << n; // 2^n
        vector<vector<int>> result;
        result.reserve(totalSubsets);

        for (int mask = 0; mask < totalSubsets; mask++) {
            vector<int> current;
            for (int j = 0; j < n; j++) {
                // Check agar j-th bit set (1) hai
                if (mask & (1 << j)) {
                    current.push_back(nums[j]);
                }
            }
            result.push_back(current);
        }

        return result;
    }
};