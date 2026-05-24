/**
 * File: H.cpp
 * Author: racsosabe
 * Date: 23/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;
const int MOD = 1e9 + 7;

int n;
int q;
int u[N];
int v[N];
int w[N];
int f[N];
int sz[N];
vector<int> G[N];

void DFS(int u, int p = -1) {
    sz[u] = 1;
    for (int &v : G[u]) {
        if (v == p) continue;
        DFS(v, u);
        sz[u] += sz[v];
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i < n; ++i) {
        cin >> u[i] >> v[i] >> w[i];
        G[u[i]].emplace_back(v[i]);
        G[v[i]].emplace_back(u[i]);
    }
    DFS(1);
    int factor = 0;
    for (int i = 1; i < n; ++i) {
        if (sz[u[i]] > sz[v[i]]) {
            swap(u[i], v[i]);
        }
        f[i] = (1ll * sz[u[i]] * (n - sz[u[i]])) % MOD;
        factor += 1ll * f[i] * w[i] % MOD;
        if (factor >= MOD) factor -= MOD;
    }
    while (q--) {
        int i, x;
        cin >> i >> x;
        factor += MOD - 1ll * f[i] * w[i] % MOD;
        if (factor >= MOD) factor -= MOD;
        w[i] = x;
        factor += 1ll * f[i] * w[i] % MOD;
        if (factor >= MOD) factor -= MOD;
        cout << factor << '\n';
    }
    return 0;
}