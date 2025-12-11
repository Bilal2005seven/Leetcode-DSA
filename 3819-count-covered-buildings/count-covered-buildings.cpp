class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        unordered_map<int, vector<int>> rows, cols;

        // Fill row and column lists
        for (auto &b : buildings) {
            int x = b[0], y = b[1];
            rows[x].push_back(y);
            cols[y].push_back(x);
        }

        // Sort them to know min/max easily
        for (auto &p : rows) sort(p.second.begin(), p.second.end());
        for (auto &p : cols) sort(p.second.begin(), p.second.end());

        int covered = 0;

        // Check all buildings
        for (auto &b : buildings) {
            int x = b[0], y = b[1];

            auto &row = rows[x];
            auto &col = cols[y];

            bool left  = (row.front() <  y);
            bool right = (row.back()  >  y);
            bool above = (col.front() <  x);
            bool below = (col.back()  >  x);

            if (left && right && above && below)
                covered++;
        }

        return covered;
    }
};
