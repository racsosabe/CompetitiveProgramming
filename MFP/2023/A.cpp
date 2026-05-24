/**
 * File: A.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            --a[i];
        }
        for (int i = 0; i < n; ++i) {
            int at = i;
            do {
                cout << at + 1 << " ";
                at = a[at];
            } while (at != i);
            cout << '\n';
        }
    }
    return 0;
}