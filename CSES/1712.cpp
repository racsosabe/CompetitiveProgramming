/**
 * File: 1712.cpp
 * Author: racsosabe
 * Date: 4/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int mul(long long a, long long b, int m) {
    return a * b % m;
}

int pow_mod(int a, int b, int m) {
    int r = 1 % m;
    while (b) {
        if (b & 1) r = mul(r, a, m);
        a = mul(a, a, m);
        b >>= 1;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << pow_mod(a, pow_mod(b, c, MOD - 1), MOD) << '\n';
    }
    return 0;
}
