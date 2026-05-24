/**
 * File: ALDS1_9_C.cpp
 * Author: racsosabe
 * Date: 12/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    priority_queue<int> Q;
    string op;
    while (cin >> op) {
        if (op == "end") break;
        if (op[0] == 'i') {
            int x;
            cin >> x;
            Q.emplace(x);
        }
        else {
            cout << Q.top() << '\n';
            Q.pop();
        }
    }
    return 0;
}
