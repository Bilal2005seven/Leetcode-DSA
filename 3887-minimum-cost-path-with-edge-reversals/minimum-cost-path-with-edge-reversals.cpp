class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<pair<int,int>>> adj(n), radj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});   // normal
            radj[e[1]].push_back({e[0], e[2]});  // incoming (for reversal)
        }

        const long long INF = 1e18;
        vector<long long> dist(n, INF);

        priority_queue<pair<long long,int>,
            vector<pair<long long,int>>,
            greater<>> pq;

        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();

            if (cost > dist[u]) continue;

            // Normal edges
            for (auto [v, w] : adj[u]) {
                if (dist[v] > cost + w) {
                    dist[v] = cost + w;
                    pq.push({dist[v], v});
                }
            }

            // Reversed incoming edges
            for (auto [v, w] : radj[u]) {
                long long newCost = cost + 2LL * w;
                if (dist[v] > newCost) {
                    dist[v] = newCost;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist[n - 1] == INF ? -1 : (int)dist[n - 1];
    }
};
