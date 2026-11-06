#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        int qLen = queries.size();
        int m = logs.size();

        // 1. Sort logs by timestamp
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        // 2. Track original query indices and sort by time
        vector<pair<int, int>> sortedQueries(qLen);
        for (int i = 0; i < qLen; ++i) {
            sortedQueries[i] = {queries[i], i};
        }
        sort(sortedQueries.begin(), sortedQueries.end());

        // 3. Sliding window over logs
        vector<int> serverCounts(n + 1, 0);
        int activeServers = 0;
        int left = 0, right = 0;

        vector<int> result(qLen);

        for (const auto& [qTime, originalIdx] : sortedQueries) {
            int windowStart = qTime - x;
            int windowEnd = qTime;

            // Expand window right: include logs up to windowEnd
            while (right < m && logs[right][1] <= windowEnd) {
                int server = logs[right][0];
                if (serverCounts[server] == 0) {
                    activeServers++;
                }
                serverCounts[server]++;
                right++;
            }

            // Shrink window left: remove logs strictly before windowStart
            while (left < m && logs[left][1] < windowStart) {
                int server = logs[left][0];
                serverCounts[server]--;
                if (serverCounts[server] == 0) {
                    activeServers--;
                }
                left++;
            }

            result[originalIdx] = n - activeServers;
        }

        return result;
    }
};