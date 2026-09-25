class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        
        stack<int> helperStack;

        int n = temperatures.size();
        vector<int> result(n, 0);

        // Right se left traverse
        for (int idx = n - 1; idx >= 0; idx--) {

            // Current temperature se chhote ya equal
            // temperatures ko remove karo
            while (!helperStack.empty() &&
                   temperatures[idx] >= temperatures[helperStack.top()]) {
                
                helperStack.pop();
            }

            // Agar stack empty nahi hai,
            // top par next warmer temperature ka index hai
            if (!helperStack.empty()) {
                result[idx] = helperStack.top() - idx;
            }

            // Current index ko stack mein daalo
            helperStack.push(idx);
        }

        return result;
    }
};