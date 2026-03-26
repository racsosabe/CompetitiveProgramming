/**
 * File: CF105394-GYM-M.cpp
 * Author: racsosabe
 * Date: 20/03/2026
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
        a[i] -= i;
    }
    sort(a.begin(), a.end());
    int median = a[n / 2];
    long long res = 0;
    for(auto &x : a) {
        res += abs(x - median);
    }
    cout << res << endl;
    return 0;
}
