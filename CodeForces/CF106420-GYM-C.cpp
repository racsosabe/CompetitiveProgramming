/**
 * File: CF106420-GYM-C.cpp
 * Author: racsosabe
 * Date: 27/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    int at = 0;
    for (int i = 0; i < n; ++i) {
        while (at < m and b[at] < a[i]) {
            cout << 'B';
            ++at;
        }
        cout << 'A';
    }
    while (at < m) {
        cout << 'B';
        ++at;
    }
    cout << '\n';
    return 0;
}
