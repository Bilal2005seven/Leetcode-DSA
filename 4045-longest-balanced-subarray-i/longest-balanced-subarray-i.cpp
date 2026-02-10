class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        unordered_set<int> allEven, allOdd;
        for (int x : nums) {
            if (x % 2 == 0) allEven.insert(x);
            else allOdd.insert(x);
        }
        
        int maxK = min(allEven.size(), allOdd.size());
        int n = nums.size();
        int answer = 0;
        
        for (int k = 1; k <= maxK; ++k) {
            unordered_map<int,int> cntEven, cntOdd;
            int distinctEven = 0, distinctOdd = 0;
            
            int L = 0;
            for (int R = 0; R < n; ++R) {
                int x = nums[R];
                if (x % 2 == 0) {
                    if (++cntEven[x] == 1) distinctEven++;
                } else {
                    if (++cntOdd[x] == 1) distinctOdd++;
                }
                
                while (distinctEven > k || distinctOdd > k) {
                    int y = nums[L++];
                    if (y % 2 == 0) {
                        if (--cntEven[y] == 0) distinctEven--;
                    } else {
                        if (--cntOdd[y] == 0) distinctOdd--;
                    }
                }
                
                if (distinctEven == k && distinctOdd == k) {
                    answer = max(answer, R - L + 1);
                }
            }
        }
        
        return answer;
    }
};
