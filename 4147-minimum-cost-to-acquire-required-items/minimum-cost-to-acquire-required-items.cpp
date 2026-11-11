#include <algorithm>

using namespace std;

class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        long long c1 = cost1;
        long long c2 = cost2;
        long long cb = costBoth;
        long long n1 = need1;
        long long n2 = need2;

        long long common = min(n1, n2);
        long long ans = 0;

        // Fulfill the common part (overlap of both needs)
        ans += common * min(cb, c1 + c2);

        // Fulfill the remaining deficit
        if (n1 > n2) {
            ans += (n1 - n2) * min(c1, cb);
        } else if (n2 > n1) {
            ans += (n2 - n1) * min(c2, cb);
        }

        return ans;
    }
};