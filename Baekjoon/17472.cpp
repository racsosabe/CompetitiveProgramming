/**
 * File: 17472.cpp
 * Author: racsosabe
 * Date: 11/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 10;

int n, m;
int a[N][N];

int solve() {
    vector<vector<pair<int, int>>> islands;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 0) continue;
            queue<pair<int, int>> Q;
            Q.emplace(i, j);
            a[i][j] = 0;
            vector<pair<int, int>> current_island;
            while (not Q.empty()) {
                int x, y;
                tie(x, y) = Q.front(); Q.pop();
                current_island.emplace_back(x, y);
                for (int k = 0; k < 4; ++k) {
                    int vx = x + dx[k];
                    int vy = y + dy[k];
                    if (vx < 0 or vx >= n or vy < 0 or vy >= m) continue;
                    if (a[vx][vy] == 0) continue;
                    Q.emplace(vx, vy);
                    a[vx][vy] = 0;
                }
            }
            islands.emplace_back(current_island);
        }
    }
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < islands.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            edges.emplace_back(best_edge(islands[i], islands[j]), i, j);
        }
    }
    sort(edges.begin(), edges.end());

}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    cout << solve() << '\n';
    return 0;
}
