#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    void backtrack(int index, const string& digits, const vector<string>& pad, string& current, vector<string>& result) {
        // Base case: jab har digit cover ho chuki ho
        if (index == digits.size()) {
            result.push_back(current);
            return;
        }

        // Current digit ke corresponding letters fetch karo
        string letters = pad[digits[index] - '0'];

        for (char ch : letters) {
            current.push_back(ch);                                // Choose
            backtrack(index + 1, digits, pad, current, result);   // Explore
            current.pop_back();                                   // Unchoose (Backtrack)
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        // 0 aur 1 unused hote hain keypad par
        vector<string> pad = {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        vector<string> result;
        string current = "";

        backtrack(0, digits, pad, current, result);
        return result;
    }
};