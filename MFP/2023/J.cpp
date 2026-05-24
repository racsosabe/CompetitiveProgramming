/**
 * File: J.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18 + 10;
const int N = 200000 + 5;
const int MASK = 1 << 16;
const int LOG = 18;
const int K = 16;

int n;
int k;
int keys[K];
int cand[N];
int depth[N];
long long h[N];
int ST_par[LOG][N];
int ST_mask[LOG][N];
long long memo[K][MASK];
vector<pair<int, int>> G[N];

void remove(int u, int p) {
    if (p == -1) return;
    for (int i = 0; i + 1 < G[u].size(); ++i) {
        if (G[u][i].first == p) {
            swap(G[u][i], G[u].back());
            break;
        }
    }
    if (not G[u].empty() and G[u].back().first == p) G[u].pop_back();
}

void compute(int u, int p) {
    ST_par[0][u] = p;
    ST_mask[0][u] = cand[u];
    for (int d = 1; (1 << d) <= depth[u]; ++d) {
        ST_par[d][u] = ST_par[d - 1][ST_par[d - 1][u]];
        ST_mask[d][u] = ST_mask[d - 1][u] | ST_mask[d - 1][ST_par[d - 1][u]];
    }
}

void DFS(int u, int p = -1) {
    remove(u, p);
    compute(u, p);
    for (auto &e : G[u]) {
        int v, w;
        tie(v, w) = e;
        h[v] = h[u] + w;
        depth[v] = depth[u] + 1;
        DFS(v, u);
    }
}

int go_up(int u, int d) {
    while (d > 0) {
        int k = __builtin_ctz(d);
        u = ST_par[k][u];
        d &= d - 1;
    }
    return u;
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    u = go_up(u, depth[u] - depth[v]);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; --i) {
        if ((1 << i) > depth[u]) continue;
        if (ST_par[i][u] != ST_par[i][v]) {
            u = ST_par[i][u];
            v = ST_par[i][v];
        }
    }
    return ST_par[0][u];
}

long long get_dis(int u, int v) {
    int l = lca(u, v);
    return h[u] + h[v] - 2 * h[l];
}

int get_cand_up(int u, int d) {
    int res = 0;
    while (d > 0) {
        int k = __builtin_ctz(d);
        res |= ST_mask[k][u];
        u = ST_par[k][u];
        d &= d - 1;
    }
    return res;
}

int get_cand_path(int u, int v) {
    int l = lca(u, v);
    return get_cand_up(u, depth[u] - depth[l]) | get_cand_up(v, depth[v] - depth[l]) | cand[l];
}

long long get_cost(int u, int v, int have) {
    int need = get_cand_path(u, v);
    if ((have & need) != need) return inf;
    return get_dis(u, v);
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> k;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        cand[x] |= 1 << i;
        fill_n(memo[i], 1 << k, inf);
    }
    for (int i = 0; i < k; ++i) cin >> keys[i];
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    DFS(1);
    long long res = get_cost(1, n, 0);
    for (int mask = 1; mask < (1 << k); ++mask) {
        if (__builtin_popcount(mask) == 1) {
            int where = __builtin_ctz(mask);
            memo[where][mask] = get_cost(1, keys[where], 0);
            res = min(res, memo[where][mask] + get_cost(keys[where], n, mask));
        }
        else {
            for (int m_last = mask; m_last > 0; m_last &= m_last - 1) {
                int last = __builtin_ctz(m_last);
                int last_mask = mask ^ (1 << last);
                memo[last][mask] = inf;
                for (int m_prev = last_mask; m_prev > 0; m_prev &= m_prev - 1) {
                    int prev = __builtin_ctz(m_prev);
                    memo[last][mask] = min(memo[last][mask], memo[prev][last_mask] + get_cost(keys[prev], keys[last], last_mask));
                }
                res = min(res, memo[last][mask] + get_cost(keys[last], n, mask));
            }
        }
    }
    if (res == inf) res = -1;
    cout << res << '\n';
    return 0;
}