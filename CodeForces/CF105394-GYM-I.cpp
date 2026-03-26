/**
 * File: CF105394-GYM-I.cpp.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int q, w;
    cin >> q >> w;
    cin.ignore();
    vector<tuple<int, int, int>> waves;
    for (int i = 0; i < q; ++i) {
        char op;
        cin >> op;
        if (op == '!') {
            int p, l, a;
            cin >> p >> l >> a;
            waves.emplace_back(p, l, a);
        }
        else {
            int x;
            cin >> x;
            long long height = 0;
            for (auto &e : waves) {
                int p, l, a;
                tie(p, l, a) = e;
                if (p <= x and x <= p + l - 1) {
                    height += (x - p) % 4 == 0 ? a : (x - p) % 4 == 2 ? -a : 0;
                }
            }
            cout << height << endl;
        }
    }
    return 0;
}