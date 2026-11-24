#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 1;
        // Max LCM for numbers in [1..10] is 2520, max GCD is 10 -> max product <= 25200
        const long long MAX_PROD = 25200;

        for (int i = 0; i < n; ++i) {
            long long prod = 1;
            long long g = 0;
            long long l = 1;

            for (int j = i; j < n; ++j) {
                prod *= nums[j];
                if (prod > MAX_PROD) {
                    break;
                }

                g = gcd(g, (long long)nums[j]);
                l = lcm(l, (long long)nums[j]);

                if (prod == l * g) {
                    maxLen = max(maxLen, j - i + 1);
                }
            }
        }

        return maxLen;
    }
};