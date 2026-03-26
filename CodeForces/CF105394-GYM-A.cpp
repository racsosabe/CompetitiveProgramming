/**
 * File: CF105394-GYM-A.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;

bool vis[N];
vector<int> G[N];

int DFS(int u) {
    vis[u] = 1;
    int res = 1;
    for (int &v : G[u]) {
        if (vis[v]) continue;
        res += DFS(v);
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> deg(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        res = max(res, DFS(i));
    }
    cout << res << endl;
    return 0;
}
