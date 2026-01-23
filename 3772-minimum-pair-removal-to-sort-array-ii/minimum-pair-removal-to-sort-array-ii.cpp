class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;
        
        // Check if already sorted
        bool isSorted = true;
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[i-1]) {
                isSorted = false;
                break;
            }
        }
        if (isSorted) return 0;
        
        // Min-heap: {sum, left_index, right_index, version_left, version_right}
        priority_queue<tuple<long long, int, int, int, int>, 
                      vector<tuple<long long, int, int, int, int>>, 
                      greater<>> pq;
        
        map<int, pair<long long, int>> active; // index -> {value, version}
        set<int> violations; // indices where active[i] > active[i+1]
        
        for (int i = 0; i < n; i++) {
            active[i] = {nums[i], 0};
        }
        
        // Find initial violations
        auto it = active.begin();
        while (it != active.end()) {
            auto next = it;
            ++next;
            if (next != active.end()) {
                if (it->second.first > next->second.first) {
                    violations.insert(it->first);
                }
                pq.push({it->second.first + next->second.first, 
                         it->first, next->first, 
                         it->second.second, next->second.second});
            }
            ++it;
        }
        
        if (violations.empty()) return 0;
        
        int ops = 0;
        
        while (!pq.empty() && !violations.empty()) {
            auto [sum, left, right, verLeft, verRight] = pq.top();
            pq.pop();
            
            // Validate pair
            auto leftIt = active.find(left);
            auto rightIt = active.find(right);
            
            if (leftIt == active.end() || rightIt == active.end() ||
                leftIt->second.second != verLeft || rightIt->second.second != verRight) {
                continue;
            }
            
            // Check adjacency
            auto checkNext = leftIt;
            ++checkNext;
            if (checkNext != rightIt) {
                continue;
            }
            
            // Remove old violations involving left and right
            auto prevIt = leftIt;
            if (prevIt != active.begin()) {
                --prevIt;
                if (prevIt->second.first > leftIt->second.first) {
                    violations.erase(prevIt->first);
                }
                ++prevIt;
            }
            if (leftIt->second.first > rightIt->second.first) {
                violations.erase(leftIt->first);
            }
            auto nextIt = rightIt;
            ++nextIt;
            if (nextIt != active.end()) {
                if (rightIt->second.first > nextIt->second.first) {
                    violations.erase(rightIt->first);
                }
            }
            
            // Merge
            leftIt->second.first = sum;
            leftIt->second.second++;
            active.erase(rightIt);
            ops++;
            
            // Add new violations
            prevIt = leftIt;
            if (prevIt != active.begin()) {
                --prevIt;
                if (prevIt->second.first > leftIt->second.first) {
                    violations.insert(prevIt->first);
                } else {
                    violations.erase(prevIt->first);
                }
                pq.push({prevIt->second.first + leftIt->second.first,
                         prevIt->first, leftIt->first,
                         prevIt->second.second, leftIt->second.second});
                ++prevIt;
            }
            
            nextIt = leftIt;
            ++nextIt;
            if (nextIt != active.end()) {
                if (leftIt->second.first > nextIt->second.first) {
                    violations.insert(leftIt->first);
                } else {
                    violations.erase(leftIt->first);
                }
                pq.push({leftIt->second.first + nextIt->second.first,
                         leftIt->first, nextIt->first,
                         leftIt->second.second, nextIt->second.second});
            }
        }
        
        return ops;
    }
};