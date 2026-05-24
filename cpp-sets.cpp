/**
 * File: cpp-sets.cpp
 * Author: racsosabe
 * Date: 12/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int q;
    cin >> q;
    set<int> S;
    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            S.emplace(x);
        }
        else if (op == 2) {
            S.erase(x);
        }
        else {
            cout << (S.count(x) ? "Yes" : "No") << '\n';
        }
    }
    return 0;
}