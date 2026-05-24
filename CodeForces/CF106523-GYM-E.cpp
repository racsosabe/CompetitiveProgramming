/**
 * File: CF106523-GYM-E.cpp
 * Author: racsosabe
 * Date: 17/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

long long f(int n) {
    n /= 2;
    return 1ll * n * (n + 1);
}

long long s(int n) {
    return 1ll * n * (n + 1) / 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    cout << max(f(n), s(n) - f(n)) << '\n';
    return 0;
}
