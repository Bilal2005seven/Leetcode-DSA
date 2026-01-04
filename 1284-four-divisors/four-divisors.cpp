class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;

        for (int n : nums) {
            int cnt = 0;
            int sum = 0;

            for (int i = 2; i * i <= n; i++) {
                if (n % i == 0) {
                    int j = n / i;
                    if (i == j) {  // perfect square → more than 4 divisors
                        cnt = 0;
                        break;
                    }
                    cnt++;
                    sum = 1 + i + j + n;
                    if (cnt > 1) break; // more than 4 divisors
                }
            }

            if (cnt == 1) {
                ans += sum;
            }
        }

        return ans;
    }
};
