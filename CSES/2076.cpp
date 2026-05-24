/**
 * File: 2076.cpp
 * Author: racsosabe
 * Date: 6/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
const int M = 200000 + 5;

int n;
int m;
int T;
int A[M];
int B[M];
int tin[N];
int low[N];
bool vis[N];
bool bridge[M];
vector<int> E[N];

void DFS(int u, int p = -1) {
    vis[u] = true;
    tin[u] = low[u] = T++;
    for (auto &e : E[u]) {
        int v = A[e] ^ B[e] ^ u;
        if (v == p) continue;
        if (vis[v]) {
            low[u] = min(low[u], tin[v]);
        }
        else {
            DFS(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                bridge[e] = true;
            }
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> A[i] >> B[i];
        E[A[i]].emplace_back(i);
        E[B[i]].emplace_back(i);
    }
    DFS(1);
    cout << accumulate(bridge, bridge + m, 0) << '\n';
    for (int i = 0; i < m; ++i) {
        if (bridge[i]) {
            cout << A[i] << " " << B[i] << '\n';
        }
    }
    return 0;
}
