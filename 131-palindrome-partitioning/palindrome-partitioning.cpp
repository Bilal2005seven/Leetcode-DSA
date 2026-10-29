#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }

    void backtrack(int start, const string& s, vector<string>& current, vector<vector<string>>& result) {
        // Base case: String end tak successfully partition ho gayi
        if (start == s.size()) {
            result.push_back(current);
            return;
        }

        for (int i = start; i < s.size(); i++) {
            // Agar start se i tak ka part palindrome hai
            if (isPalindrome(s, start, i)) {
                // Choose
                current.push_back(s.substr(start, i - start + 1));

                // Explore
                backtrack(i + 1, s, current, result);

                // Unchoose (Backtrack)
                current.pop_back();
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> current;
        backtrack(0, s, current, result);
        return result;
    }
};