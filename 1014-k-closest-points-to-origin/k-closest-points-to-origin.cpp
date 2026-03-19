class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {

        // Max heap: {distance, index}
        priority_queue<pair<int,int>> pq;

        for (int i = 0; i < points.size(); i++) {
            int x = points[i][0];
            int y = points[i][1];

            int dist = x*x + y*y;

            pq.push({dist, i});

            // Keep only k elements
            if (pq.size() > k) {
                pq.pop();
            }
        }

        // Extract result
        vector<vector<int>> result;
        while (!pq.empty()) {
            result.push_back(points[pq.top().second]);
            pq.pop();
        }

        return result;
    }
};