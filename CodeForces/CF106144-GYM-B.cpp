/**
 * File: CF106144-GYM-B.cpp
 * Author: racsosabe
 * Date: 29/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

bool to_right(pair<int, int> a, pair<int, int> b, pair<int, int> c) {
    return 1ll * (c.first - b.first) * (b.second - a.second) > 1ll * (c.second - b.second) * (b.first - a.first);
}

bool still_convex(vector<pair<int, int>> &a, int l, int r) {
    return to_right(a[r - 2], a[r - 1], a[r]) and to_right(a[r - 1], a[r], a[l]) and to_right(a[r], a[l], a[l + 1]);
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<pair<int, int>> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i].first >> a[i].second;
        }
        vector<int> valid(n, 0);
        for (int i = 0; i + 2 < n; ++i) {
            if (to_right(a[i], a[i + 1], a[i + 2])) {
                valid[i] = 1;
            }
        }
        int res = 0;
        int r = 2;
        for (int l = 0; l + 2 < n; ++l) {
            r = max(r, l + 2);
            while (r < n and still_convex(a, l, r)) ++r;
            if (r - l >= 3) res = max(res, r - l);
        }
        cout << res << '\n';
    }
    return 0;
}