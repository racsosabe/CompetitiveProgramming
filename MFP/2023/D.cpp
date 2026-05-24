/**
 * File: D.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    long double m1, m2, x1, x2, F;
    cin >> m1 >> m2 >> x1 >> x2 >> F;
    long double d = x1 - x2;
    cout << setprecision(12) << fixed << (F * d * d) / m1 / m2 << '\n';
    return 0;
}
