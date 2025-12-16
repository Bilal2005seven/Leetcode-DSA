class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        // Build adjacency list for the tree
        vector<vector<int>> children(n + 1);
        for (auto& edge : hierarchy) {
            children[edge[0]].push_back(edge[1]);
        }
        
        // Memoization: node -> (discounted -> states)
        vector<map<int, int>> memo_normal(n + 1);
        vector<map<int, int>> memo_discounted(n + 1);
        vector<bool> computed_normal(n + 1, false);
        vector<bool> computed_discounted(n + 1, false);
        
        // DFS returns map of {cost -> max_profit} for this subtree
        function<map<int, int>(int, bool)> dfs = [&](int node, bool discounted) -> map<int, int> {
            // Check memoization
            if (discounted) {
                if (computed_discounted[node]) {
                    return memo_discounted[node];
                }
            } else {
                if (computed_normal[node]) {
                    return memo_normal[node];
                }
            }
            
            map<int, int> states; // cost -> max profit
            states[0] = 0; // Option: don't buy anything
            
            int cost = discounted ? present[node - 1] / 2 : present[node - 1];
            int profit = future[node - 1] - cost;
            
            // If leaf node
            if (children[node].empty()) {
                states[cost] = profit;
                
                // Store in memo
                if (discounted) {
                    memo_discounted[node] = states;
                    computed_discounted[node] = true;
                } else {
                    memo_normal[node] = states;
                    computed_normal[node] = true;
                }
                return states;
            }
            
            // Get states from all children (at full price)
            vector<map<int, int>> childStates;
            for (int child : children[node]) {
                childStates.push_back(dfs(child, false));
            }
            
            // Merge all children states (full price)
            map<int, int> mergedFull = mergeAllStates(childStates);
            
            // Option 1: Don't buy this node's stock
            states = mergedFull;
            
            // Option 2: Buy this node's stock (children get discount)
            vector<map<int, int>> discountedStates;
            for (int child : children[node]) {
                discountedStates.push_back(dfs(child, true));
            }
            
            // Merge discounted children states
            map<int, int> mergedDiscounted = mergeAllStates(discountedStates);
            
            // Add current node's contribution
            for (auto& [childCost, childProfit] : mergedDiscounted) {
                int totalCost = childCost + cost;
                int totalProfit = childProfit + profit;
                
                if (states.find(totalCost) == states.end()) {
                    states[totalCost] = totalProfit;
                } else {
                    states[totalCost] = max(states[totalCost], totalProfit);
                }
            }
            
            // Keep only Pareto-optimal states
            states = paretoOptimal(states);
            
            // Store in memo
            if (discounted) {
                memo_discounted[node] = states;
                computed_discounted[node] = true;
            } else {
                memo_normal[node] = states;
                computed_normal[node] = true;
            }
            
            return states;
        };
        
        // Get all possible states from CEO (node 1)
        map<int, int> allStates = dfs(1, false);
        
        // Find maximum profit within budget
        int maxProfit = 0;
        for (auto& [cost, profit] : allStates) {
            if (cost <= budget) {
                maxProfit = max(maxProfit, profit);
            }
        }
        
        return maxProfit;
    }
    
private:
    map<int, int> mergeStates(map<int, int>& s1, map<int, int>& s2) {
        map<int, int> result;
        
        for (auto& [c1, p1] : s1) {
            for (auto& [c2, p2] : s2) {
                int totalCost = c1 + c2;
                int totalProfit = p1 + p2;
                
                if (result.find(totalCost) == result.end()) {
                    result[totalCost] = totalProfit;
                } else {
                    result[totalCost] = max(result[totalCost], totalProfit);
                }
            }
        }
        
        return paretoOptimal(result);
    }
    
    map<int, int> mergeAllStates(vector<map<int, int>>& allStates) {
        if (allStates.empty()) {
            map<int, int> empty;
            empty[0] = 0;
            return empty;
        }
        
        map<int, int> result = allStates[0];
        for (int i = 1; i < allStates.size(); i++) {
            result = mergeStates(result, allStates[i]);
        }
        
        return result;
    }
    
    map<int, int> paretoOptimal(map<int, int>& states) {
        map<int, int> result;
        int maxProfit = INT_MIN;
        
        // Map is already sorted by cost
        for (auto& [cost, profit] : states) {
            if (profit > maxProfit) {
                result[cost] = profit;
                maxProfit = profit;
            }
        }
        
        return result;
    }
};