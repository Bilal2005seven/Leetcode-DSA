#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Fenwick tree supporting range XOR updates and point queries
struct FenwickTree {
    int n;
    vector<int> tree;

    FenwickTree(int n) : n(n), tree(n + 2, 0) {}

    void add(int i, int delta) {
        for (; i <= n; i += i & -i) {
            tree[i] ^= delta;
        }
    }

    // Range XOR update on [l, r]
    void rangeUpdate(int l, int r, int delta) {
        add(l, delta);
        add(r + 1, delta);
    }

    // Point query at index i
    int query(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) {
            res ^= tree[i];
        }
        return res;
    }
};

class Solution {
    int timer;
    int LOG;
    vector<int> tin, tout, depth;
    vector<vector<int>> up;

    void dfs(int u, int p, int d, const vector<vector<int>>& adj) {
        tin[u] = ++timer;
        depth[u] = d;
        up[u][0] = p;

        for (int j = 1; j < LOG; ++j) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u, d + 1, adj);
            }
        }
        tout[u] = timer;
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        // Bring u to the same depth as v
        for (int j = LOG - 1; j >= 0; --j) {
            if (depth[u] - (1 << j) >= depth[v]) {
                u = up[u][j];
            }
        }

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        tin.assign(n, 0);
        tout.assign(n, 0);
        depth.assign(n, 0);
        up.assign(n, vector<int>(LOG, 0));
        timer = 0;

        dfs(0, 0, 0, adj);

        FenwickTree bit(n);

        // Initialize Fenwick tree with base characters
        for (int i = 0; i < n; ++i) {
            int mask = 1 << (s[i] - 'a');
            bit.rangeUpdate(tin[i], tout[i], mask);
        }

        vector<bool> result;

        for (const string& q : queries) {
            stringstream ss(q);
            string type;
            ss >> type;

            if (type == "update") {
                int u;
                char c;
                ss >> u >> c;

                if (s[u] != c) {
                    int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                    s[u] = c;
                    bit.rangeUpdate(tin[u], tout[u], delta);
                }
            } else {
                int u, v;
                ss >> u >> v;

                int lca = getLCA(u, v);

                int maskU = bit.query(tin[u]);
                int maskV = bit.query(tin[v]);
                int lcaCharMask = 1 << (s[lca] - 'a');

                // Path mask: mask(u) ^ mask(v) ^ node_val(lca)
                int pathMask = maskU ^ maskV ^ lcaCharMask;

                // At most one bit set check
                bool canBePalindrome = (pathMask == 0) || ((pathMask & (pathMask - 1)) == 0);
                result.push_back(canBePalindrome);
            }
        }

        return result;
    }
};