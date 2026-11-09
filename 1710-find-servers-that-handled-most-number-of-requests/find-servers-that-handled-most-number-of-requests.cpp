#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        int n = arrival.size();
        
    
        vector<int> requestCount(k, 0);

   
        set<int> available;
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }

        using BusyServer = pair<int, int>;
        priority_queue<BusyServer, vector<BusyServer>, greater<BusyServer>> busy;

        for (int i = 0; i < n; ++i) {
            int curArrival = arrival[i];
            int curLoad = load[i];

           
            while (!busy.empty() && busy.top().first <= curArrival) {
                available.insert(busy.top().second);
                busy.pop();
            }

            if (available.empty()) {
                continue;
            }

            int target = i % k;
            auto it = available.lower_bound(target);

            if (it == available.end()) {
                it = available.begin();
            }

            int serverId = *it;
            available.erase(it);

            requestCount[serverId]++;
            busy.push({curArrival + curLoad, serverId});
        }


        int maxRequests = *max_element(requestCount.begin(), requestCount.end());

        vector<int> result;
        for (int i = 0; i < k; ++i) {
            if (requestCount[i] == maxRequests) {
                result.push_back(i);
            }
        }

        return result;
    }
};