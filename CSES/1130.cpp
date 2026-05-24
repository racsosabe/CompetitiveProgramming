/**
 * File: 1130.cpp
 * Author: racsosabe
 * Date: 6/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;
const int inf = 1e9;

int n;
bool vis[2][N];
int memo[2][N];
vector<int> G[N];

int DP(int u, int taken, int p = -1) {
    if (vis[taken][u]) return memo[taken][u];
    int best_one_fixed = -inf;
    int sum_best = 0;
    int sum_zero = 0;
    for (int &v : G[u]) {
        if (v == p) continue;
        int cur_zero = DP(v, 0, u);
        int cur_one = DP(v, 1, u);
        int cur_best = max(cur_zero, cur_one);
        sum_zero += cur_zero;
        best_one_fixed = max(best_one_fixed, cur_one - cur_zero);
        sum_best += cur_best;
    }
    int res;
    if (taken == 0) {
        res = max(sum_zero, sum_zero + best_one_fixed + 1);
    }
    else {
        res = sum_best;
    }
    vis[taken][u] = true;
    return memo[taken][u] = res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    cout << max(DP(1, 0), DP(1, 1)) << '\n';
    return 0;
}
