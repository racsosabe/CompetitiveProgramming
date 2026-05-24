/**
 * File: C.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int d, m;
    cin >> d >> m;
    int times = int(m / (d * sqrtl(2)));
    long double x = times * d;
    long double y = times & 1 ? d : 0;
    long double z = m - times * d * sqrtl(2);
    if (times & 1) {
        y -= z / sqrtl(2);
    }
    else {
        y += z / sqrtl(2);
    }
    x += z / sqrtl(2);
    cout << setprecision(12) << fixed << x << " " << y << '\n';
    return 0;
}
