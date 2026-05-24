/**
 * File: CF106144-GYM-E.cpp
 * Author: racsosabe
 * Date: 29/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int n, m, k;

void BFS(int sx, int sy, vector<vector<bool>> &vis, vector<vector<int>> &D) {
    vis[sx][sy] = true;
    queue<pair<int, int>> Q;
    Q.emplace(sx, sy);
    while (not Q.empty()) {
        int ux, uy;
        tie(ux, uy) = Q.front(); Q.pop();
        if (uy > 0 and D[ux][uy - 1] >= k) {
            if (not vis[ux][uy - 1]) {
                vis[ux][uy - 1] = true;
                Q.emplace(ux, uy - 1);
            }
        }
        if (uy + 1 < m and D[ux][uy + 1] >= k) {
            if (not vis[ux][uy + 1]) {
                vis[ux][uy + 1] = true;
                Q.emplace(ux, uy + 1);
            }
        }
        if (D[ux][uy] >= k + 1) {
            if (not vis[ux + 1][uy]) {
                vis[ux + 1][uy] = true;
                Q.emplace(ux + 1, uy);
            }
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        vector<string> s(n);
        for (int i = 0; i < n; ++i) cin >> s[i];
        vector<vector<int>> D(n, vector<int>(m));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; j--) {
                if (s[i][j] == 'x') continue;
                D[i][j] = 1;
                if (i + 1 < n and s[i + 1][j] != 'x') D[i][j] += D[i + 1][j];
            }
        }
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        BFS(0, 0, vis, D);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (vis[i][j]) {
                    res = max(res, i + k);
                }
            }
        }
        cout << res << '\n';
    }
    return 0;
}