/**
 * File: CF106082-GYM-J.cpp
 * Author: racsosabe
 * Date: 1/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int LOG = 14;
const int N = 5000 + 5;
const long long inf = 1e18;

int n;
int h[N];
int ST[LOG][N];
long double STmax[LOG][N];
vector<pair<int, long double>> G[N];

void add_edge(int u, int v, long double w) {
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
}

void compute(int u, int p, long double w) {
    ST[0][u] = p;
    STmax[0][u] = w;
    for (int d = 1; 1 << d <= h[u]; ++d) {
        ST[d][u] = ST[d - 1][ST[d - 1][u]];
        STmax[d][u] = max(STmax[d - 1][u], STmax[d - 1][ST[d - 1][u]]);
    }
}

void DFS(int u, int p, long double w) {
    compute(u, p, w);
    for (auto &e : G[u]) {
        int v = e.first;
        long double w = e.second;
        if (v == p) continue;
        h[v] = h[u] + 1;
        DFS(v, u, w);
    }
}

int go_up(int u, int d) {
    while (d) {
        int k = __builtin_ctz(d);
        d &= d - 1;
        u = ST[k][u];
    }
    return u;
}

int lca(int u, int v) {
    if (h[u] < h[v]) swap(u,v);
    u = go_up(u, h[u] - h[v]);
    if (u == v) return u;
    for (int k = LOG - 1; k >= 0; --k) {
        if ((1 << k) > h[u]) continue;
        if (ST[k][u] != ST[k][v]) {
            u = ST[k][u];
            v = ST[k][v];
        }
    }
    return ST[0][u];
}

long double get_max_up(int u, int d) {
    long double res = DBL_MIN;
    while (d) {
        int k = __builtin_ctz(d);
        d &= d - 1;
        res = max(res, STmax[k][u]);
        u = ST[k][u];
    }
    return res;
}

long double get_path(int u, int v) {
    int l = lca(u, v);
    long double res = DBL_MIN;
    if (u != l) {
        res = max(res, get_max_up(u, h[u] - h[l]));
    }
    if (v != l) {
        res = max(res, get_max_up(v, h[v] - h[l]));
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n;
    vector<pair<int, int>> raw_points;
    vector<tuple<int, int, int>> points;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        raw_points.emplace_back(x, y);
        points.emplace_back(x, y, i);
    }
    vector<bool> vis(n, false);
    vector<int> parent(n, -1);
    vector<long long> best(n, inf);
    best[0] = 0;
    parent[0] = -2;
    for (int s = 1; s < n; ++s) {
        int cur = -1;
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            if (cur == -1 or best[cur] > best[i]) {
                cur = i;
            }
        }
        if (cur == -1) break;
        vis[cur] = true;
        for (int i = 0; i < n; ++i) {
            if (vis[i]) continue;
            int dx = raw_points[cur].first - raw_points[i].first;
            int dy = raw_points[cur].second - raw_points[i].second;
            long long w = 1ll * dx * dx + 1ll * dy * dy;
            if (best[i] > w) {
                best[i] = w;
                parent[i] = cur;
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        add_edge(i, parent[i], sqrtl(best[i]));
    }
    DFS(0, -1, 0);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << setprecision(16) << fixed << get_path(l, r) << endl;
    }
    return 0;
}
