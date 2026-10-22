#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    int solve(int i, int j, const string& s1, const string& s2, vector<vector<int>>& memo) {
        // Base case: jab koi bhi string cross ho jaye
        if (i < 0 || j < 0) return 0;

        if (memo[i][j] != -1) return memo[i][j];

        // Match case
        if (s1[i] == s2[j]) {
            return memo[i][j] = 1 + solve(i - 1, j - 1, s1, s2, memo);
        }

        // Mismatch case
        return memo[i][j] = max(solve(i - 1, j, s1, s2, memo), 
                                solve(i, j - 1, s1, s2, memo));
    }

public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> memo(n, vector<int>(m, -1));

        return solve(n - 1, m - 1, text1, text2, memo);
    }
};