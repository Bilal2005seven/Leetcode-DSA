class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        long long totalApples = 0;
        for (int a : apple) {
            totalApples += a;
        }
        
        // Sort capacities in descending order
        sort(capacity.begin(), capacity.end(), greater<int>());
        
        long long currentCapacity = 0;
        int boxesUsed = 0;
        
        for (int cap : capacity) {
            currentCapacity += cap;
            boxesUsed++;
            if (currentCapacity >= totalApples) {
                return boxesUsed;
            }
        }
        
        return boxesUsed; // all boxes needed
    }
};
