#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PairHashLL {
    size_t operator()(const pair<ll,ll>& p) const noexcept {
        return ((uint64_t)p.first << 32) ^ (uint64_t)p.second;
    }
};
struct PairHashInt {
    size_t operator()(const pair<int,int>& p) const noexcept {
        return ((uint64_t)(uint32_t)p.first << 32) ^ (uint32_t)p.second;
    }
};

static ll gcdll(ll a, ll b) {
    a = llabs(a); b = llabs(b);
    while (b) { ll t = a % b; a = b; b = t; }
    return a;
}

class Solution {
public:
    long long countTrapezoids(vector<vector<int>>& points) {
        int n = (int)points.size();
        if (n < 4) return 0;

        // Map slope -> (line constant -> count of unordered point-pairs on that line)
        unordered_map<pair<int,int>, unordered_map<ll,ll>, PairHashInt> linePairCount;
        // Map slope -> (line constant -> vector of point indices on that line) for degenerate counting
        unordered_map<pair<int,int>, unordered_map<ll, vector<int> >, PairHashInt> linePoints;
        // global midpoint counts (pair sums)
        unordered_map<pair<ll,ll>, ll, PairHashLL> midCount;
        midCount.reserve((size_t)n * (n-1) / 4 + 10);

        // build maps by iterating unordered point pairs
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                ll dx = (ll)points[j][0] - points[i][0];
                ll dy = (ll)points[j][1] - points[i][1];

                int ndx, ndy;
                if (dx == 0) { ndx = 0; ndy = 1; }
                else if (dy == 0) { ndx = 1; ndy = 0; }
                else {
                    ll g = gcdll(dx, dy);
                    dx /= g; dy /= g;
                    if (dx < 0) { dx = -dx; dy = -dy; }
                    ndx = (int)dx; ndy = (int)dy;
                }
                pair<int,int> slopeKey = {ndx, ndy};
                ll c = (ll)ndy * (ll)points[i][0] - (ll)ndx * (ll)points[i][1];

                linePairCount[slopeKey][c] += 1;
                // push endpoints for dedup later (we'll uniquify before per-line work)
                linePoints[slopeKey][c].push_back(i);
                linePoints[slopeKey][c].push_back(j);

                ll sx = (ll)points[i][0] + (ll)points[j][0];
                ll sy = (ll)points[i][1] + (ll)points[j][1];
                midCount[{sx, sy}] += 1;
            }
        }

        // 1) trapezoids from choosing two lines of same slope (choose two point-pairs from different lines)
        long long S = 0;
        for (auto &skv : linePairCount) {
            long long totalP = 0;
            long long sumSq = 0;
            for (auto &lkv : skv.second) {
                long long p = lkv.second; // number of unordered point-pairs on this geometric line
                totalP += p;
                sumSq += p * p;
            }
            if (totalP >= 2) {
                S += (totalP * totalP - sumSq) / 2;
            }
        }

        // 2) Count parallelograms: global mid pairs minus degenerate same-line mid pairs
        long long total_mid_pairs = 0;
        for (auto &kv : midCount) {
            ll m = kv.second;
            if (m >= 2) total_mid_pairs += m * (m - 1) / 2;
        }

        // degenerate_count: for each geometric line, count how many pair-of-pairs among pairs on that line share the same midpoint.
        // Use sort + run-length on sums to avoid heavy hashing in large buckets.
        long long degenerate_count = 0;
        for (auto &skv : linePoints) {
            for (auto &lkv : skv.second) {
                auto &vec = lkv.second;
                if (vec.empty()) continue;
                sort(vec.begin(), vec.end());
                vec.erase(unique(vec.begin(), vec.end()), vec.end()); // unique point indices on this line
                int m = (int)vec.size();
                if (m < 2) continue;
                // Build vector of y-sums (since x is same on a given geometric line, x-sum is constant)
                // Use 64-bit for sums
                vector<ll> sums;
                sums.reserve((size_t)m * (m - 1) / 2);
                for (int a = 0; a < m; ++a) {
                    for (int b = a+1; b < m; ++b) {
                        ll sx = (ll)points[ vec[a] ][0] + (ll)points[ vec[b] ][0];
                        ll sy = (ll)points[ vec[a] ][1] + (ll)points[ vec[b] ][1];
                        // pack sx,sy into single 64-bit value to sort-run-length efficiently
                        // sx and sy range fits in 32-bit signed given constraints; pack as (sx<<32)|((sy)&0xffffffff)
                        ll packed = (sx << 32) ^ (sy & 0xffffffffLL);
                        sums.push_back(packed);
                    }
                }
                if (sums.empty()) continue;
                sort(sums.begin(), sums.end());
                // count runs
                ll run = 1;
                for (size_t t = 1; t <= sums.size(); ++t) {
                    if (t < sums.size() && sums[t] == sums[t-1]) {
                        ++run;
                    } else {
                        if (run >= 2) degenerate_count += run * (run - 1) / 2;
                        run = 1;
                    }
                }
            }
        }

        long long parallelograms = total_mid_pairs - degenerate_count;
        if (parallelograms < 0) parallelograms = 0;

        long long ans = S - parallelograms;
        if (ans < 0) ans = 0;
        return ans;
    }
};
