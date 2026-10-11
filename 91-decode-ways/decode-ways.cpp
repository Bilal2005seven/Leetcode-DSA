
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();

        if (s[0] == '0') return 0;

        int prev2 = 1;
        int prev1 = 1;

        for (int i = 1; i < n; i++) {
            int current = 0;

            // Take one digit
            if (s[i] != '0') {
                current += prev1;
            }

            // Take two digits
            int twoDigit = (s[i - 1] - '0') * 10
                         + (s[i] - '0');

            if (twoDigit >= 10 && twoDigit <= 26) {
                current += prev2;
            }

            prev2 = prev1;
            prev1 = current;
        }

        return prev1;
    }
};