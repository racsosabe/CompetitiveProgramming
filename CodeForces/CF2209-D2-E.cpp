/**
 * File: CF2209-D2-E.cpp
 * Author: racsosabe
 * Date: 21/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 1000000 + 5;

int z[N];
int memo[N];
int e_add, e_rem;
int add_last[N];
int add_nxt[N];
int add_val[N];
int rem_last[N];
int rem_nxt[N];
int rem_val[N];
int frec[N];

string s;

void compute_z(int x, int y) {
    const int n = y - x + 1;
    z[0] = 0;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = min(r - i + 1, z[i - l]);
        if (z[i] < 0) z[i] = 0;
        while (i + z[i] < n and s[x + z[i]] == s[i + x + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

long long solve(int a, int b) {
    const int n = b - a + 1;
    compute_z(a, b);
    int cnt = 0;
    e_add = e_rem = 0;
    fill_n(add_last, n, -1);
    fill_n(rem_last, n, -1);
    int last = 0;
    fill_n(frec, n + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int e = add_last[i]; ~e; e = add_nxt[e]) {
            int x = add_val[e];
            ++cnt;
            ++frec[x];
        }
        for (int e = rem_last[i]; ~e; e = rem_nxt[e]) {
            int x = rem_val[e];
            --cnt;
            --frec[x];
        }
        if (frec[last + 1]) ++last;
        while (last > 0 and frec[last] == 0) --last;
        memo[i] = last + 1;
        ++last;
        if (i + 1 < n) {
            int l = i + 1, r = i + z[i + 1];
            if (l <= r) {
                add_val[e_add] = memo[i];
                add_nxt[e_add] = add_last[l];
                add_last[l] = e_add++;
                if (r + 1 < n) {
                    rem_val[e_rem] = memo[i];
                    rem_nxt[e_rem] = rem_last[r + 1];
                    rem_last[r + 1] = e_rem++;
                }
            }
        }
    }
    return accumulate(memo, memo + n, 0LL);
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t, n, q;
    cin >> t;
    while(t--) {
        cin >> n >> q;
        cin >> s;
        while(q--) {
            int l, r;
            cin >> l >> r;
            --l; --r;
            cout << solve(l, r) << '\n';
        }
    }
    return 0;
}
