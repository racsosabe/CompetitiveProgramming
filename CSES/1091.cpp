/**
 * File: 1091.cpp
 * Author: racsosabe
 * Date: 12/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    multiset<int> S;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        S.emplace(x);
    }
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        multiset<int>::iterator it = S.upper_bound(x);
        if (it == S.begin()) {
            cout << -1 << '\n';
        }
        else {
            --it;
            cout << *it << '\n';
            S.erase(it);
        }
    }
    return 0;
}
