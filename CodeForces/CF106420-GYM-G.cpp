/**
 * File: CF106420-GYM-G.cpp
 * Author: racsosabe
 * Date: 27/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

long long cross(vector<int> &a, vector<long long> &b, int l, int r, bool strict) {
    int mi = (l + r) / 2;
    long long s = 0;
    for (int i = mi; i >= l; --i) {
        s += a[i];
        b[i] = s;
    }
    s = 0;
    for (int i = mi + 1; i <= r; ++i) {
        s += a[i];
        b[i] = s;
    }
    sort(b.begin() + l, b.begin() + mi + 1);
    sort(b.begin() + mi + 1, b.begin() + r + 1);
    int at = r;
    long long res = 0;
    for (int i = l; i <= mi; ++i) {
        while (at >= mi + 1 and (strict ? b[i] + b[at] >= 0 : b[i] + b[at] > 0)) --at;
        res += at - mi;
    }
    return res;
}

long long solve(vector<int> &a, vector<long long> &b, int l, int r, bool strict) {
    if (l == r) return strict ? a[l] < 0 : a[l] <= 0;
    int mi = (l + r) / 2;
    long long res = solve(a, b, l, mi, strict) + solve(a, b, mi + 1, r, strict);
    res += cross(a, b, l, r, strict);
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> v(n);
    vector<long long> w(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    long long res = 0;
    for (auto &x : v) {
        x -= b;
    }
    res += solve(v, w, 0, n - 1, false);
    for (auto &x : v) {
        x += b;
        x -= a;
    }
    res -= solve(v, w, 0, n - 1, true);
    cout << res << '\n';
    return 0;
}
