/**
 * File: CF106420-GYM-E.cpp
 * Author: racsosabe
 * Date: 27/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

bool check(int l, int h, int n, vector<pair<int, int> > &v) {
    long long left = h;
    for (auto e: v) {
        int t, d;
        tie(t, d) = e;
        d -= l;
        if (d < 0) d = 0;
        left -= 1ll * t * d;
        if (left <= 0) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, h;
    cin >> n >> h;
    vector<pair<int, int> > v(n);
    for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;
    int lo = 0, hi = 1e9;
    while (lo < hi) {
        int mi = lo + (hi - lo) / 2;
        if (not check(mi, h, n, v)) lo = mi + 1;
        else hi = mi;
    }
    cout << lo << '\n';
    return 0;
}
