/**
 * File: 3312.cpp
 * Author: racsosabe
 * Date: 22/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int dx[] = {1, -1, 0 ,0};
const int dy[] = {0, 0, 1, -1};
const int N = 500 + 5;
const int M = 2 * 500 * 500 + 5;

int n;
int m;
int cc;
int comp[M];
string s[N];
bool vis[M];
stack<int> S;
int mask[N][N];
vector<int> G[2][M];

bool valid_pos(int i, int j) {
    return 0 <= i and i < n and 0 <= j and j < m;
}

void add_edge(int u, int v) {
    G[0][u].emplace_back(v);
    G[1][v].emplace_back(u);
}

void DFS(int u, int id) {
    vis[u] = true;
    for (auto &v : G[id][u]) {
        if (vis[v]) continue;
        DFS(v, id);
    }
    if (id == 0) {
        S.emplace(u);
    }
    else {
        comp[u] = cc;
    }
}

void compute_scc() {
    for (int i = 0; i < 2 * n * m; ++i) {
        if (vis[i]) continue;
        DFS(i, 0);
    }
    fill_n(vis, 2 * n * m, false);
    while (not S.empty()) {
        int u = S.top(); S.pop();
        if (vis[u]) continue;
        ++cc;
        DFS(u, 1);
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
        for (int j = 0; j < m; ++j) {
            mask[i][j] = 7 ^ (1 << (s[i][j] - 'A'));
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int id_u = i * m + j;
            for (int k = 0; k < 4; ++k) {
                int vx = i + dx[k];
                int vy = j + dy[k];
                if (not valid_pos(vx, vy)) continue;
                int id_v = vx * m + vy;
                int u = 2 * id_u;
                for (int m_u = mask[i][j]; m_u > 0; m_u &= m_u - 1, u ^= 1) {
                    int v = 2 * id_v;
                    for (int m_v = mask[vx][vy]; m_v > 0; m_v &= m_v - 1, v ^= 1) {
                        if (__builtin_ctz(m_u) == __builtin_ctz(m_v)) {
                            add_edge(u, v ^ 1);
                        }
                    }
                }
            }
        }
    }
    compute_scc();
    for (int id = 0; id < n * m; ++id) {
        if (comp[2 * id] == comp[2 * id + 1]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
        int i = id / m, j = id % m;
        if (comp[2 * id] < comp[2 * id + 1]) {
            s[i][j] = 31 - __builtin_clz(mask[i][j]) + 'A';
        }
        else {
            s[i][j] = __builtin_ctz(mask[i][j]) + 'A';
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << s[i] << endl;
    }
    return 0;
}