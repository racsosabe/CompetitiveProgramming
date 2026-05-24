/**
 * File: double_ended_priority_queue.cpp
 * Author: racsosabe
 * Date: 12/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    multiset<int> S;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        S.emplace(x);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int x;
            cin >> x;
            S.emplace(x);
        }
        else if (op == 1) {
            int x = *S.begin();
            S.erase(S.begin());
            cout << x << '\n';
        }
        else {
            int x = *S.rbegin();
            S.erase(S.find(x));
            cout << x << '\n';
        }
    }
    return 0;
}