/**
 * File: 1673.cpp
 * Author: racsosabe
 * Date: 22/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> edges;
    for(int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        edges.emplace_back(u, v, w);
    }
    vector<long long> d(n, -inf);
    d[0] = 0;
    for (int s = 1; s < n; ++s) {
        for (auto &e : edges) {
            int u, v, w;
            tie(u, v, w) = e;
            if (d[u] == -inf) continue;
            if (d[v] < d[u] + w) {
                d[v] = d[u] + w;
            }
        }
    }
    vector<bool> relaxed(n, false);
    for (int s = 1; s <= n; ++s) {
        for (auto &e : edges) {
            int u, v, w;
            tie(u, v, w) = e;
            if (d[u] == -inf) continue;
            if (relaxed[u]) relaxed[v] = true;
            if (d[v] < d[u] + w) {
                relaxed[v] = true;
                d[v] = d[u] + w;
            }
        }
    }
    if (relaxed[n - 1] ) {
        cout << -1 << endl;
    }
    else {
        cout << d[n - 1] << endl;
    }
    return 0;
}
