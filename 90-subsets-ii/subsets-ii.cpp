class Solution {
public:
    vector<vector<int>> ans;

    void f(int ind, vector<int>& nums, vector<int>& curr) {
        ans.push_back(curr);

        for (int i = ind; i < nums.size(); i++) {

            if (i > ind && nums[i] == nums[i - 1])
                continue;

            curr.push_back(nums[i]);
            f(i + 1, nums, curr);
            curr.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<int> curr;
        f(0, nums, curr);

        return ans;
    }
};