class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int n = row * col;
        int TOP = n;
        int BOTTOM = n + 1;

        vector<int> parent(n + 2), rank(n + 2, 0);
        vector<vector<int>> grid(row, vector<int>(col, 1));

        for (int i = 0; i < n + 2; i++)
            parent[i] = i;

        function<int(int)> find = [&](int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        };

        auto unite = [&](int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return;
            if (rank[a] < rank[b]) parent[a] = b;
            else if (rank[a] > rank[b]) parent[b] = a;
            else {
                parent[b] = a;
                rank[a]++;
            }
        };

        auto index = [&](int r, int c) {
            return r * col + c;
        };

        vector<int> dr = {1, -1, 0, 0};
        vector<int> dc = {0, 0, 1, -1};

        // Reverse days
        for (int day = cells.size() - 1; day >= 0; day--) {
            int r = cells[day][0] - 1;
            int c = cells[day][1] - 1;
            grid[r][c] = 0;

            int id = index(r, c);

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr >= 0 && nr < row && nc >= 0 && nc < col && grid[nr][nc] == 0) {
                    unite(id, index(nr, nc));
                }
            }

            if (r == 0) unite(id, TOP);
            if (r == row - 1) unite(id, BOTTOM);

            if (find(TOP) == find(BOTTOM))
                return day;
        }

        return 0;
    }
};
