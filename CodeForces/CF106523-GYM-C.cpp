/**
 * File: CF106523-GYM-C.cpp
 * Author: racsosabe
 * Date: 17/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

long double area(int l) {
    return l * l * sqrtl(3) / 4 * 6.0;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int b, h, l;
    cin >> b >> h >> l;
    cout << setprecision(10) << fixed << area(l) / b / h << '\n';
    return 0;
}