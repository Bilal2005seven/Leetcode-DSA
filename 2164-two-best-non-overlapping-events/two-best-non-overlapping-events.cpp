class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int n = events.size();
        
        // Sort by end time
        sort(events.begin(), events.end(),
             [](auto &a, auto &b) {
                 return a[1] < b[1];
             });
        
        // Prefix max of values
        vector<int> pref(n);
        pref[0] = events[0][2];
        for (int i = 1; i < n; i++) {
            pref[i] = max(pref[i - 1], events[i][2]);
        }
        
        int ans = 0;
        
        for (int i = 0; i < n; i++) {
            int start = events[i][0];
            int value = events[i][2];
            
            // Take only this event
            ans = max(ans, value);
            
            // Binary search last event with end < start
            int lo = 0, hi = i - 1, idx = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (events[mid][1] < start) {
                    idx = mid;
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            
            if (idx != -1) {
                ans = max(ans, value + pref[idx]);
            }
        }
        
        return ans;
    }
};
