class Solution {
public:
    int maxConsecutive(vector<int>& arr) {
        if (arr.empty()) return 1;
        sort(arr.begin(), arr.end());
        int best = 1, cur = 1;
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] == arr[i - 1] + 1) {
                cur++;
            } else {
                cur = 1;
            }
            best = max(best, cur);
        }
        // Removing k consecutive bars creates k+1 size gap
        return best + 1;
    }

    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        int maxH = maxConsecutive(hBars);
        int maxV = maxConsecutive(vBars);
        int side = min(maxH, maxV);
        return side * side;
    }
};
