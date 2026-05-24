/**
 * File: D.cpp
 * Author: racsosabe
 * Date: 23/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    int g = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        g = __gcd(g, a[i]);
    }
    long long res = 0;
    for (auto &x : a) {
        res += x / g;
    }
    cout << res << '\n';
    return 0;
}
