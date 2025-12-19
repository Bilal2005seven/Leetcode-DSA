class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        sort(meetings.begin(), meetings.end(),
             [](auto &a, auto &b) { return a[2] < b[2]; });

        vector<bool> knows(n, false);
        knows[0] = knows[firstPerson] = true;

        int i = 0;
        int m = meetings.size();

        while (i < m) {
            int time = meetings[i][2];

            unordered_map<int, vector<int>> graph;
            unordered_set<int> people;

            // Collect all meetings at this time
            while (i < m && meetings[i][2] == time) {
                int x = meetings[i][0];
                int y = meetings[i][1];
                graph[x].push_back(y);
                graph[y].push_back(x);
                people.insert(x);
                people.insert(y);
                i++;
            }

            queue<int> q;
            unordered_set<int> visited;

            // Start BFS from people who already know the secret
            for (int p : people) {
                if (knows[p]) {
                    q.push(p);
                    visited.insert(p);
                }
            }

            // BFS within this time frame
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : graph[u]) {
                    if (!visited.count(v)) {
                        visited.insert(v);
                        q.push(v);
                    }
                }
            }

            // Mark all reachable people as knowing the secret
            for (int p : visited) {
                knows[p] = true;
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (knows[i]) ans.push_back(i);
        }
        return ans;
    }
};
