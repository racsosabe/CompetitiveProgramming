/**
 * File: 1133.cpp
 * Author: racsosabe
 * Date: 18/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;

int n;
int sz[N];
long long in[N];
long long out[N];
vector<int> G[N];

void DFS(int id, int u, int p = -1) {
    if (id == 0) {
        sz[u] = 1;
        for (auto &v : G[u]) {
            if (v == p) continue;
            DFS(id, v, u);
            sz[u] += sz[v];
            in[u] += in[v] + sz[v];
        }
    }
    else {
        long long sum_v = 0;
        for (auto &v : G[u]) {
            if (v == p) continue;
            sum_v += in[v] + sz[v];
        }
        long long base = out[u] + sum_v;
        for (auto &v : G[u]) {
            if (v == p) continue;
            out[v] = base - in[v] + n - (sz[v] << 1);
            DFS(id, v, u);
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    DFS(0, 1);
    DFS(1, 1);
    for (int i = 1; i <= n; i++) {
        cout << in[i] + out[i] << " \n"[i == n];
    }
    return 0;
}