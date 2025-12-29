class Solution {
public:
    unordered_map<string, vector<char>> mp;
    unordered_map<string, bool> memo;

    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (auto &s : allowed) {
            mp[s.substr(0, 2)].push_back(s[2]);
        }
        return dfs(bottom);
    }

    bool dfs(string bottom) {
        if (bottom.size() == 1) return true;

        if (memo.count(bottom)) return memo[bottom];

        string next;
        bool res = buildNext(bottom, 0, next);
        memo[bottom] = res;
        return res;
    }

    bool buildNext(string &bottom, int idx, string &next) {
        if (idx == bottom.size() - 1) {
            return dfs(next);
        }

        string key = bottom.substr(idx, 2);
        if (!mp.count(key)) return false;

        for (char c : mp[key]) {
            next.push_back(c);
            if (buildNext(bottom, idx + 1, next)) return true;
            next.pop_back();
        }
        return false;
    }
};
