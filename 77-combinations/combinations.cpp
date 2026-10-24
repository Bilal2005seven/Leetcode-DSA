#include <vector>

using namespace std;

class Solution {
private:
    void magic(vector<vector<int>>& v, vector<int>& temp, int n, int k, int index) {
        if (temp.size() == k) {
            v.push_back(temp);
            return;
        }
        int need = k-temp.size() ;
        for (int i = index; i <= n-need+1; i++) {
            temp.push_back(i);
            magic(v, temp, n, k, i + 1);
            temp.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> v;
        vector<int> temp;
        magic(v, temp, n, k, 1);
        return v;
    }
};