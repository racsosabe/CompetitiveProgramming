/**
 * File: A.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int res = 0;
    int l = 0;
    while (l < n) {
        while (l < n and a[l] < k) ++l;
        if (l == n) break;
        int r = l;
        while (r < n and a[r] >= k) ++r;
        res += 1;
        l = r;
    }
    cout << res << endl;
    return 0;
}