#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    int expandAroundCenter(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        }
        // Valid palindrome length = (right - 1) - (left + 1) + 1
        return right - left - 1;
    }

public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n <= 1) return s;

        int start = 0;
        int maxLen = 1;

        for (int i = 0; i < n; i++) {
            // Odd length palindrome (center is s[i])
            int len1 = expandAroundCenter(s, i, i);

            // Even length palindrome (center is between s[i] and s[i+1])
            int len2 = expandAroundCenter(s, i, i + 1);

            int len = max(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                // Center se start index calculate karo
                start = i - (len - 1) / 2;
            }
        }

        return s.substr(start, maxLen);
    }
};