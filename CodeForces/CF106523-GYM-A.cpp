/**
 * File: CF106523-GYM-A.cpp
 * Author: racsosabe
 * Date: 17/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

int n;
int q;
int a[N];
int ans[N];
vector<int> G[N];
map<int, int> frec;

void DFS(int u, int p = -1) {
    ++frec[a[u]];
    ans[u] = frec.size();
    for (int &v: G[u]) {
        if (v == p) continue;
        DFS(v, u);
    }
    --frec[a[u]];
    if (frec[a[u]] == 0) frec.erase(a[u]);
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    DFS(1);
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
    }
    return 0;
}
