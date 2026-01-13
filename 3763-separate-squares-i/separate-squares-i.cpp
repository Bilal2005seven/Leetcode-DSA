class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double total = 0;
        double low = 1e18, high = -1e18;

        for (auto &s : squares) {
            double x = s[0], y = s[1], l = s[2];
            total += l * l;
            low = min(low, y);
            high = max(high, y + l);
        }

        double target = total / 2.0;

        for (int it = 0; it < 80; it++) { // enough for 1e-6 precision
            double mid = (low + high) / 2.0;
            double below = 0;

            for (auto &s : squares) {
                double y = s[1], l = s[2];
                if (mid <= y) continue;
                else if (mid >= y + l) below += l * l;
                else below += (mid - y) * l;
            }

            if (below < target) low = mid;
            else high = mid;
        }

        return low;
    }
};
