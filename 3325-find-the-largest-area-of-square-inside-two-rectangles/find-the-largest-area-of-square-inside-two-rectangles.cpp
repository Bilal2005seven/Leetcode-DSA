class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        int n = bottomLeft.size();
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int a1 = bottomLeft[i][0];
            int b1 = bottomLeft[i][1];
            int c1 = topRight[i][0];
            int d1 = topRight[i][1];

            for (int j = i + 1; j < n; j++) {
                int a2 = bottomLeft[j][0];
                int b2 = bottomLeft[j][1];
                int c2 = topRight[j][0];
                int d2 = topRight[j][1];

                // Intersection rectangle
                int x1 = max(a1, a2);
                int y1 = max(b1, b2);
                int x2 = min(c1, c2);
                int y2 = min(d1, d2);

                int w = x2 - x1;
                int h = y2 - y1;

                if (w > 0 && h > 0) {
                    long long side = min(w, h);
                    ans = max(ans, side * side);
                }
            }
        }
        return ans;
    }
};
