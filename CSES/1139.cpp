/**
 * File: 1139.cpp
 * Author: racsosabe
 * Date: 22/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;

int n;
int T;
int a[N];
int b[N];
int ft[N];
int in[N];
int res[N];
vector<int> Q[N];
vector<int> G[N];

void DFS(int u, int p = -1) {
    b[T] = a[u];
    in[u] = T++;
    for (auto &v : G[u]) {
        if (v == p) continue;
        DFS(v, u);
    }
    Q[T - 1].emplace_back(u);
}

void update(int pos, int val) {
    ++pos;
    while(pos <= n) {
        ft[pos] += val;
        pos += (-pos) & pos;
    }
}

int get_sum(int pos) {
    ++pos;
    int res = 0;
    while (pos > 0) {
        res += ft[pos];
        pos &= pos - 1;
    }
    return res;
}

int query(int l, int r) {
    return get_sum(r) - get_sum(l - 1);
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    DFS(0);
    map<int, int> last;
    for (int i = 0; i < n; ++i) {
        int x = b[i];
        if (last.count(x)) {
            update(last[x], -1);
            update(i, 1);
        }
        else {
            update(i, 1);
        }
        last[x] = i;
        for (auto &u : Q[i]) {
            res[u] = query(in[u], i);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << res[i] << " \n"[i + 1 == n];
    }
    return 0;
}