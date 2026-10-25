#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    void backtrack(int start, int target, vector<int>& candidates, vector<int>& temp, vector<vector<int>>& result) {
        // Base case: Target mil gaya
        if (target == 0) {
            result.push_back(temp);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {
            // Pruning: Kyunki array sorted hai, agar current element target se bada hai
            // toh aage ke saare elements bhi target se bade honge, seedha break karo
            if (candidates[i] > target) break;

            // Choose
            temp.push_back(candidates[i]);

            // Explore: index i hi pass hoga kyunki same element dubara use ho sakta hai
            backtrack(i, target - candidates[i], candidates, temp, result);

            // Unchoose (Backtrack)
            temp.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> temp;

        // Pruning enable karne ke liye sort karna zaroori hai
        sort(candidates.begin(), candidates.end());

        backtrack(0, target, candidates, temp, result);
        return result;
    }
};
