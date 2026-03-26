/**
 * File: D.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

int deg[N];
vector<int> G[N];

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        G[u].emplace_back(v);
        G[v].emplace_back(u);
        deg[u]++;
        deg[v]++;
    }
    set<pair<int, int>> degrees;
    for (int i = 1; i <= n; ++i) {
        degrees.emplace(deg[i], i);
    }
    int res = n - 1;
    for (int i = 1; i <= n; i++) {
        degrees.erase(make_pair(deg[i], i));
        for (auto &v : G[i]) {
            int cur = deg[i] + deg[v] - 1;
            res = min(res, n - 1 - cur);
            degrees.erase(make_pair(deg[v], v));
        }
        if (not degrees.empty()) {
            res = min(res, n - deg[i] - (*degrees.rbegin()).first);
        }
        degrees.emplace(deg[i], i);
        for (auto &v : G[i]) {
            degrees.emplace(deg[v], v);
        }
    }
    cout << res << endl;
    return 0;
}