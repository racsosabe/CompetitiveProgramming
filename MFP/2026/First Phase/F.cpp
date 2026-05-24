/**
 * File: F.cpp
 * Author: racsosabe
 * Date: 23/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    long double q = 1.0;
    for (int i = 0; i < n; ++i) {
        int d;
        cin >> d;
        int l = max(0, min(d, k - 1));
        q *= 1.0 * l / d;
    }
    cout << setprecision(10) << fixed << 1 - q << '\n';
    return 0;
}