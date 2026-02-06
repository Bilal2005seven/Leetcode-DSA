class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        int i = 0;
        int maxBalanced = 1;
        
        for (int j = 0; j < n; j++) {
            while (nums[j] > 1LL * nums[i] * k) {  // use long long to prevent overflow
                i++;
            }
            maxBalanced = max(maxBalanced, j - i + 1);
        }
        
        return n - maxBalanced;
    }
};
