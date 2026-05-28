class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {

        int n = nums.size();

        int left = 0;
        int max_len = 0;
        int count_zeros = 0;

        for(int right = 0; right < n; right++) {

            // include current element
            if(nums[right] == 0) {
                count_zeros++;
            }

            // shrink window if invalid
            while(count_zeros > k) {

                if(nums[left] == 0) {
                    count_zeros--;
                }

                left++;
            }

            // valid window
            max_len = max(max_len, right - left + 1);
        }

        return max_len;
    }
};