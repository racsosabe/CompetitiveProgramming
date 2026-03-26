/**
 * File: 1750.cpp
 * Author: racsosabe
 * Date: 22/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    int lg = 32;
    vector<vector<int>> ST(lg + 1, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        cin >> ST[0][i];
        --ST[0][i];
    }
    for (int d = 1, p = 1; d <= lg; ++d, p <<= 1) {
        for (int i = 0; i < n; ++i) {
            ST[d][i] = ST[d - 1][ST[d - 1][i]];
        }
    }
    while (q--) {
        int x, d;
        cin >> x >> d;
        --x;
        while (d > 0) {
            int k = __builtin_ctz(d);
            d &= d - 1;
            x = ST[k][x];
        }
        cout << x + 1 << endl;
    }
    return 0;
}
