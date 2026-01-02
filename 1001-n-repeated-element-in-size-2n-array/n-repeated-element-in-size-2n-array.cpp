class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_set<int> seen;

        for (int num : nums) {
            if (seen.count(num)) {
                return num;  // Found the repeated element
            }
            seen.insert(num);
        }

        return -1; // This line will never be reached
    }
};
