class Solution {
public:
    struct Event {
        double y, x1, x2;
        int type;
    };

    struct Node {
        int cnt = 0;
        double len = 0;
    };

    vector<Node> seg;
    vector<double> xs;

    void pushUp(int idx, int l, int r) {
        if (seg[idx].cnt > 0) {
            seg[idx].len = xs[r+1] - xs[l];
        } else if (l == r) {
            seg[idx].len = 0;
        } else {
            seg[idx].len = seg[idx*2].len + seg[idx*2+1].len;
        }
    }

    void update(int idx, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            seg[idx].cnt += val;
            pushUp(idx, l, r);
            return;
        }
        int mid = (l + r) / 2;
        update(idx*2, l, mid, ql, qr, val);
        update(idx*2+1, mid+1, r, ql, qr, val);
        pushUp(idx, l, r);
    }

    double separateSquares(vector<vector<int>>& squares) {
        vector<Event> events;
        for (auto &s : squares) {
            double x = s[0], y = s[1], l = s[2];
            events.push_back({y, x, x+l, 1});
            events.push_back({y+l, x, x+l, -1});
            xs.push_back(x);
            xs.push_back(x+l);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        int m = xs.size() - 1;
        seg.assign(4*m, {0,0});

        sort(events.begin(), events.end(), [](auto &a, auto &b){
            return a.y < b.y;
        });

        auto getIndex = [&](double v) {
            return lower_bound(xs.begin(), xs.end(), v) - xs.begin();
        };

        double total = 0, prevY = events[0].y;

        for (auto &e : events) {
            double coverX = seg[1].len;
            total += coverX * (e.y - prevY);
            int L = getIndex(e.x1);
            int R = getIndex(e.x2) - 1;
            if (L <= R) update(1, 0, m-1, L, R, e.type);
            prevY = e.y;
        }

        double target = total / 2;

        // Reset
        seg.assign(4*m, {0,0});
        double acc = 0;
        prevY = events[0].y;

        for (auto &e : events) {
            double coverX = seg[1].len;
            double slab = coverX * (e.y - prevY);
            if (acc + slab >= target) {
                return prevY + (target - acc) / coverX;
            }
            acc += slab;
            int L = getIndex(e.x1);
            int R = getIndex(e.x2) - 1;
            if (L <= R) update(1, 0, m-1, L, R, e.type);
            prevY = e.y;
        }

        return prevY;
    }
};
