#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    void backtrack(int start, int target, vector<int>& candidates, vector<int>& current, vector<vector<int>>& result) {
        // Base case: Target achieve ho gaya
        if (target == 0) {
            result.push_back(current);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {
            // Pruning 1: Array sorted hai, agar element target se bada hai toh aage ke sab bade honge
            if (candidates[i] > target) break;

            // Pruning 2: Same level par duplicate elements ko skip karo
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            // Choose
            current.push_back(candidates[i]);

            // Explore: i + 1 pass kiya kyunki har element sirf ek baar use ho sakta hai
            backtrack(i + 1, target - candidates[i], candidates, current, result);

            // Unchoose (Backtrack)
            current.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;

        // Step 1: Duplicates grouping aur branch pruning ke liye sort karna MUST hai
        sort(candidates.begin(), candidates.end());

        backtrack(0, target, candidates, current, result);
        return result;
    }
};