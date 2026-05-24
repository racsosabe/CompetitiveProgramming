/**
 * File: cpp-map.cpp
 * Author: racsosabe
 * Date: 12/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int q;
    cin >> q;
    map<string, int> marks;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int y;
            string x;
            cin >> x >> y;
            marks[x] += y;
        }
        else if (op == 2) {
            string x;
            cin >> x;
            marks.erase(x);
        }
        else {
            string x;
            cin >> x;
            cout << (marks.count(x) ? marks[x] : 0) << '\n';
        }

    }
    return 0;
}
