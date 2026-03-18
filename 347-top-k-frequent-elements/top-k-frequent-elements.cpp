class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;

        // Step 1: Count frequency
        for (int num : nums) {
            freq[num]++;
        }

        // Step 2: Min Heap (frequency, element)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        for (auto &it : freq) {
            pq.push({it.second, it.first});

            // Keep only top k elements
            if (pq.size() > k) {
                pq.pop();
            }
        }

        // Step 3: Extract result
        vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top().second);
            pq.pop();
        }

        return result;
    }
};