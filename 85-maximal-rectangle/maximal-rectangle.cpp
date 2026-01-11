class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        
        int rows = matrix.size(), cols = matrix[0].size();
        vector<int> heights(cols, 0);
        int maxArea = 0;
        
        for (int r = 0; r < rows; r++) {
            // Build histogram for this row
            for (int c = 0; c < cols; c++) {
                if (matrix[r][c] == '1')
                    heights[c] += 1;
                else
                    heights[c] = 0;
            }
            
            // Largest Rectangle in Histogram
            stack<int> st;
            for (int i = 0; i <= cols; i++) {
                int h = (i == cols ? 0 : heights[i]);
                while (!st.empty() && h < heights[st.top()]) {
                    int height = heights[st.top()];
                    st.pop();
                    int width = st.empty() ? i : i - st.top() - 1;
                    maxArea = max(maxArea, height * width);
                }
                st.push(i);
            }
        }
        
        return maxArea;
    }
};
