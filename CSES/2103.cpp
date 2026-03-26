/**
 * File: 2103.cpp
 * Author: racsosabe
 * Date: 22/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int SUML = 500000 + 5;
const int N = 100000 + 5;
const int E = 26;

int n;
string s;
int suf[SUML];
int cnt[SUML];
int nodes = 1;
int node[SUML];
int go[E][SUML];
vector<int> ordered;

int insert() {
    int pos = 0;
    for (auto &x : s) {
        int c = x - 'a';
        if (go[c][pos] == 0) go[c][pos] = nodes++;
        pos = go[c][pos];
    }
    return pos;
}

void BFS(int src) {
    queue<int> Q;
    Q.emplace(src);
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();
        ordered.emplace_back(u);
        for (int c = 0; c < E; c++) {
            if (go[c][u]) {
                int v = go[c][u];
                suf[v] = u == 0 ? 0 : go[c][suf[u]];
                Q.emplace(v);
            }
            else {
                go[c][u] = u == 0 ? 0 : go[c][suf[u]];
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string t;
    cin >> t;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        node[i] = insert();
    }
    BFS(0);
    int pos = 0;
    for (auto &x : t) {
        int c = x - 'a';
        pos = go[c][pos];
        cnt[pos] += 1;
    }
    reverse(ordered.begin(), ordered.end());
    for (int x : ordered) {
        cnt[suf[x]] += cnt[x];
    }
    for (int i = 0; i < n; ++i) {
        cout << cnt[node[i]] << '\n';
    }
    return 0;
}
