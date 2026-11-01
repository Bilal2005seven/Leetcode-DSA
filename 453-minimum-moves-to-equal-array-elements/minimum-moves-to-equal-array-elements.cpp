#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int minVal = *min_element(nums.begin(), nums.end());
        long long moves = 0;

        for (int x : nums) {
            moves += (x - minVal);
        }

        return static_cast<int>(moves);
    }
};
