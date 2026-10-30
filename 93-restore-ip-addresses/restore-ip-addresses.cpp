#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    bool isValid(const string& segment) {
        if (segment.empty() || segment.size() > 3) return false;
        if (segment.size() > 1 && segment[0] == '0') return false;
        int val = stoi(segment);
        return val >= 0 && val <= 255;
    }

    void backtrack(int start, int dots, const string& s, string& current, vector<string>& result) {
        if (dots == 3) {
            string lastSegment = s.substr(start);
            if (isValid(lastSegment)) {
                result.push_back(current + lastSegment);
            }
            return;
        }

        for (int len = 1; len <= 3 && start + len <= s.size(); len++) {
            string segment = s.substr(start, len);
            if (isValid(segment)) {
                int prevLen = current.size();

                // Choose
                current += segment + ".";

                // Explore
                backtrack(start + len, dots + 1, s, current, result);

                // Unchoose (Backtrack to previous size)
                current.resize(prevLen);
            }
        }
    }

public:
    vector<string> restoreIpAddresses(string s) {
        if (s.size() < 4 || s.size() > 12) return {};

        vector<string> result;
        string current = "";
        backtrack(0, 0, s, current, result);
        return result;
    }
};