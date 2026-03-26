/**
 * File: G.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int LOG = 19;
const int N = 100000 + 5;

int n;
string s;
int L[LOG];
string ones;
int prefix[2][N];
bool vis[LOG][N];
int memo[LOG][N];

int query(int id, int l, int r) {
    return l ? prefix[id][r] - prefix[id][l - 1] : prefix[id][r];
}

bool valid(int l, int r, int id) {
    int cnt = query(id, l, r);
    return cnt >= (r - l + 2) / 2;
}

int DP(int lvl, int l) {
    int len = L[lvl];
    if (len == 1) return 0;
    if (vis[lvl][l]) return memo[lvl][l];
    int r = l + len - 1;
    int nxt_len = L[lvl + 1];
    int res = 0;
    for (int i = l; i + nxt_len - 1 <= r; ++i) {
        if (not valid(i, i + nxt_len - 1, lvl & 1)) continue;
        int cand = DP(lvl + 1, i);
        if (cand == 0) {
            res = 1;
            break;
        }
    }
    vis[lvl][l] = true;
    return memo[lvl][l] = res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'F') prefix[0][i] += 1;
        else prefix[1][i] += 1;
        if (i) {
            prefix[0][i] += prefix[0][i - 1];
            prefix[1][i] += prefix[1][i - 1];
        }
    }
    for (int i = 0; i < LOG; i++) ones.push_back(i & 1 ? 'L' : 'F');
    L[0] = n;
    int lvl = 0;
    for (int i = 1; i < LOG; ++i) {
        L[i] = L[i - 1] / 2;
        if (L[i] == 1) lvl = i;
    }
    for (int id = lvl - 1; id >= 0; --id) {
        int len = L[id];
        int nxt_len = L[id + 1];
        int interval_len = len - nxt_len + 1;
        for (int i = 0; i + nxt_len - 1 < n; ++i) {
            if (not valid(i, i + nxt_len - 1, id & 1)) {
                memo[id + 1][i] = 1;
            }
        }
        int ptr = 0;
        int sum_memos = 0;
        for (int x = 0; x + 1 < interval_len; ++x, ++ptr) {
            sum_memos += memo[id + 1][ptr];
        }
        for (int l = 0; l + len - 1 < n; ++l, ++ptr) {
            sum_memos += memo[id + 1][ptr];
            if (ptr >= interval_len) sum_memos -= memo[id + 1][ptr - interval_len];
            memo[id][l] = sum_memos < interval_len;
        }
    }
    cout << (memo[0][0] ? "Fernanda" : "Leticia") << endl;
    return 0;
}