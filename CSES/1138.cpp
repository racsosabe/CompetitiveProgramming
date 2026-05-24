/**
 * File: 1138.cpp
 * Author: racsosabe
 * Date: 6/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;

int n;
int q;
int T;
int a[N];
int v[N];
int in[N];
int out[N];
long long ft[N];
vector<int> G[N];

void DFS(int u, int p = -1) {
    v[T] = u;
    in[u] = T++;
    for (int &x : G[u]) {
        if (x == p) continue;
        DFS(x, u);
    }
    out[u] = T - 1;
}

void update(int pos, int val) {
    ++pos;
    while (pos <= n) {
        ft[pos] += val;
        pos += (-pos) & pos;
    }
}

long long get_sum(int pos) {
    ++pos;
    long long res = 0;
    while (pos > 0) {
        res += ft[pos];
        pos &= pos - 1;
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    DFS(1);
    for (int i = 1; i <= n; ++i) {
        update(in[i], a[i]);
        update(out[i] + 1, -a[i]);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int u, x;
            cin >> u >> x;
            update(in[u], x - a[u]);
            update(out[u] + 1, a[u] - x);
            a[u] = x;
        }
        else {
            int u;
            cin >> u;
            cout << get_sum(in[u]) << '\n';
        }
    }
    return 0;
}
