class Solution {
public:
    int ans = 0;
    vector<vector<int>> graph;
    long long dfs(int node, int parent, vector<int>& values, int k) {
        long long sum = values[node];
        for(int child : graph[node]) {
            if(child == parent) continue;
            long long childSum = dfs(child, node, values, k);
            if(childSum % k == 0) {
                ans++; 
            } else {
                sum += childSum;
            }
        }return sum % k;
    }

    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        graph.assign(n, {});
        for(auto &e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        dfs(0, -1, values, k); 
        return ans + 1;       
    }
};
