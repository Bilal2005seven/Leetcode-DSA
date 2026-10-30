#include <vector>
#include <string>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        if (n == 1) return 0;

        // Adjacency list: adj[u] = {v, weight}
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        const int INF = 1e9 + 7;
        // dist[u][c] = minimum weight to reach node u with run-length c of labels[u]
        vector<vector<int>> dist(n, vector<int>(k + 1, INF));

        // Priority queue stores: {cost, {node, consecutive_count}}
        using State = pair<int, pair<int, int>>;
        priority_queue<State, vector<State>, greater<State>> pq;

        // Base state: Node 0 se start kar rahe hain, count = 1
        dist[0][1] = 0;
        pq.push({0, {0, 1}});

        while (!pq.empty()) {
            auto [d, state] = pq.top();
            pq.pop();

            int u = state.first;
            int c = state.second;

            // Agar destination node n - 1 par pahuch gaye
            if (u == n - 1) {
                return d;
            }

            // Agar ye cost already optimal nahi hai toh skip karo
            if (d > dist[u][c]) continue;

            for (const auto& [v, w] : adj[u]) {
                if (labels[v] == labels[u]) {
                    // Same character: count badhega
                    if (c + 1 <= k && d + w < dist[v][c + 1]) {
                        dist[v][c + 1] = d + w;
                        pq.push({dist[v][c + 1], {v, c + 1}});
                    }
                } else {
                    // Different character: count reset to 1
                    if (d + w < dist[v][1]) {
                        dist[v][1] = d + w;
                        pq.push({dist[v][1], {v, 1}});
                    }
                }
            }
        }

        return -1;
    }
};