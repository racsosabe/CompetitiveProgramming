/**
 * File: 1686.cpp
 * Author: racsosabe
 * Date: 6/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

int n;
int m;
int cc;
int cnt[N];
bool vis[N];
int comp[N];
stack<int> S;
long long a[N];
vector<int> T[N];
long long memo[N];
vector<int> G[2][N];

void add_edge(int u, int v) {
    G[0][u].emplace_back(v);
    G[1][v].emplace_back(u);
}

void DFS(int u, int id) {
    vis[u] = true;
    for (int &v : G[id][u]) {
        if (vis[v]) continue;
        DFS(v, id);
    }
    if (id == 0) S.emplace(u);
    else {
        comp[u] = cc;
        a[cc] += cnt[u];
    }
}

void get_scc() {
    for (int i = 1; i <= n; ++i) {
        if (vis[i]) continue;
        DFS(i, 0);
    }
    fill_n(vis, n + 1, false);
    while (not S.empty()) {
        int u = S.top(); S.pop();
        if (vis[u]) continue;
        DFS(u, 1);
        ++cc;
    }
    for (int i = 1; i <= n; ++i) {
        for (int &v : G[0][i]) {
            if (comp[i] == comp[v]) continue;
            T[comp[i]].emplace_back(comp[v]);
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> cnt[i];
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    get_scc();
    for (int i = cc - 1; i >= 0; --i) {
        memo[i] = a[i];
        for (auto &v : T[i]) {
            memo[i] = max(memo[i], a[i] + memo[v]);
        }
    }
    cout << *max_element(memo, memo + cc) << '\n';
    return 0;
}