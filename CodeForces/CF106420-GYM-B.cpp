/**
 * File: CF106420-GYM-B.cpp
 * Author: racsosabe
 * Date: 27/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        G[u].emplace_back(v);
    }
    queue<int> Q;
    Q.emplace(0);
    vector<bool> vis(n, false);
    vis[0] = true;
    int res = 0;
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();
        ++res;
        for (int &v : G[u]) {
            if (vis[v]) continue;
            Q.emplace(v);
            vis[v] = true;
        }
    }
    cout << res << '\n';
    return 0;
}