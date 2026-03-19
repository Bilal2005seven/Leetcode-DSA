class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {

        // Step 1: Count frequency
        unordered_map<int, int> freq;
        for (int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++;
        }

        // Step 2: Sort the array
        sort(nums.begin(), nums.end(), [&](int a, int b) {

            // If frequency is same
            if (freq[a] == freq[b]) {
                return a > b;   // bigger number first
            }

            // Otherwise, smaller frequency first
            return freq[a] < freq[b];
        });

        return nums;
    }
};