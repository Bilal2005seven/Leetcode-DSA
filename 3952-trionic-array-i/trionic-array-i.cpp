class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size();
        if (n < 4) return false;  // must have at least 3 segments

        int i = 1;

        // 1) strictly increasing
        while (i < n && nums[i] > nums[i - 1]) {
            i++;
        }
        // p must not be at start or at end
        if (i == 1 || i == n) return false;

        // 2) strictly decreasing
        while (i < n && nums[i] < nums[i - 1]) {
            i++;
        }
        // q must not be at end (need room for final increasing)
        if (i == n) return false;

        // 3) strictly increasing again
        while (i < n && nums[i] > nums[i - 1]) {
            i++;
        }

        // If we consumed the entire array, it's trionic
        return i == n;
    }
};
