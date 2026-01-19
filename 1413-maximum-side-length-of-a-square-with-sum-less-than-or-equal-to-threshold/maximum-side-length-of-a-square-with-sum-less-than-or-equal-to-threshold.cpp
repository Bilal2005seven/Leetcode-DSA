class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> pre(m+1, vector<int>(n+1, 0));

        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                pre[i][j] = mat[i-1][j-1] 
                          + pre[i-1][j] 
                          + pre[i][j-1] 
                          - pre[i-1][j-1];
            }
        }

        auto getSum = [&](int x1, int y1, int x2, int y2){
            return pre[x2][y2] - pre[x1-1][y2] - pre[x2][y1-1] + pre[x1-1][y1-1];
        };

        int ans = 0;
        for(int len = 1; len <= min(m, n); len++){
            bool found = false;
            for(int i = 1; i + len - 1 <= m && !found; i++){
                for(int j = 1; j + len - 1 <= n; j++){
                    if(getSum(i, j, i+len-1, j+len-1) <= threshold){
                        found = true;
                        break;
                    }
                }
            }
            if(found) ans = len;
            else break;   // no need to try larger
        }
        return ans;
    }
};
