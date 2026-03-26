/**
 * File: CF106433-GYM-B.cpp
 * Author: racsosabe
 * Date: 25/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            --a[i];
        }
        int cnt = 0;
        vector<int> id(n, -1);
        for (int i = 0; i < n; ++i) {
            if (~id[a[i]]) continue;
            id[a[i]] = ++cnt;
        }
        for (auto &x : a) {
            x = id[x];
        }
        for (int i = 0; i < n; i++) {
            cout << a[i] << " \n"[i + 1 == n];
        }
    }
    return 0;
}
