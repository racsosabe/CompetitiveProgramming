/**
 * File: CF106523-GYM-N.cpp
 * Author: racsosabe
 * Date: 17/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<long long> sum(m + 1, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        sum[x] += x;
    }
    for (int i = m - 1; i >= 1; --i) {
        sum[i] += sum[i + 1];
    }
    for (int i = 1; i <= m; ++i) {
        cout << sum[i] << " \n"[i == m];
    }
    return 0;
}
