class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        const int NEG_INF = -1e9;

        vector<int> prev(m + 1, NEG_INF), curr(m + 1, NEG_INF);

        for (int i = 1; i <= n; i++) {
            curr[0] = NEG_INF;
            for (int j = 1; j <= m; j++) {
                int take = nums1[i - 1] * nums2[j - 1]
                           + max(0, prev[j - 1]);

                curr[j] = max({
                    take,
                    prev[j],     // skip nums1[i-1]
                    curr[j - 1]  // skip nums2[j-1]
                });
            }
            prev = curr;
        }

        return prev[m];
    }
};
