class Solution {
public:

    vector<string> ans;

    void backtrack(string& s, int i) {

        // Base case:
        // We have processed the entire string
        if (i == s.size()) {
            ans.push_back(s);
            return;
        }

        // If it's a digit, there is only one choice
        if (isdigit(s[i])) {
            backtrack(s, i + 1);
            return;
        }

        // Choice 1: lowercase
        s[i] = tolower(s[i]);
        backtrack(s, i + 1);

        // Choice 2: uppercase
        s[i] = toupper(s[i]);
        backtrack(s, i + 1);
    }

    vector<string> letterCasePermutation(string s) {
        backtrack(s, 0);
        return ans;
    }
};