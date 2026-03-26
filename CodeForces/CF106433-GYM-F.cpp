/**
 * File: CF106433-GYM-F.cpp
 * Author: racsosabe
 * Date: 25/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 2000 + 5;
const int inf = 1e9;

int n;
int k;
int sz[N];
int memo[2][N][N];
vector<int> G[N];

void remove(int u, int p) {
    if (p == -1) return;
    for (int i = 0; i + 1 < G[u].size(); ++i) {
        if (G[u][i] == p) {
            swap(G[u][i], G[u].back());
            break;
        }
    }
    if (not G[u].empty() and G[u].back() == p) G[u].pop_back();
}

void DFS(int u, int p = -1) {
    sz[u] = 1;
    remove(u, p);
    fill_n(memo[0][u], k + 1, -inf);
    fill_n(memo[1][u], k + 1, -inf);
    memo[0][u][0] = 0;
    memo[1][u][1] = G[u].size();
    vector<vector<int>> tmp(2, vector<int>(k + 1));
    copy(memo[0][u], memo[0][u] + k + 1, tmp[0].begin());
    copy(memo[1][u], memo[1][u] + k + 1, tmp[1].begin());
    for (auto &v : G[u]) {
        DFS(v, u);
        for (int i = 1; i <= min(sz[v], k); ++i) {
            for (int j = 0; j <= sz[u] and i + j <= k; ++j) {
                tmp[0][i + j] = max(tmp[0][i + j], memo[0][u][j] + max(memo[0][v][i], memo[1][v][i] + 1));
                tmp[1][i + j] = max(tmp[1][i + j], memo[1][u][j] + max(memo[0][v][i], memo[1][v][i] - 1));
            }
        }
        sz[u] += sz[v];
        for (int i = 0; i <= min(k, sz[u]); ++i) {
            memo[0][u][i] = tmp[0][i];
            memo[1][u][i] = tmp[1][i];
        }
    }
}

void clear() {
    for (int i = 1; i <= n; ++i) {
        G[i].clear();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        DFS(1);
        cout << max(memo[0][1][k], memo[1][1][k]) << '\n';
        if (t) clear();
    }
    return 0;
}
