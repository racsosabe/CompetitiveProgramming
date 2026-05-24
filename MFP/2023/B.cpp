/**
 * File: B.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int res = 0;
    for (int i = 0; i < n - 1 - i; ++i) {
        res = max(res, (a[i] + a[n - 1 - i]) >> 1);
    }
    cout << res << '\n';
    return 0;
}
