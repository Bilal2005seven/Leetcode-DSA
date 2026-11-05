#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int count = 0;

        for (int x : arr1) {
            // Find the first element in arr2 >= x - d
            auto it = lower_bound(arr2.begin(), arr2.end(), x - d);

            // If found and it is <= x + d, then |x - *it| <= d
            if (it == arr2.end() || *it > x + d) {
                count++;
            }
        }

        return count;
    }
};