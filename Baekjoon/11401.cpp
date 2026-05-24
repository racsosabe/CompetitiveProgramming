/**
 * File: 11401.cpp
 * Author: racsosabe
 * Date: 11/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int mul(long long a, long long b) {
    return a * b % MOD;
}

int pow_mod(int a, int b) {
    int r = 1;
    while (b) {
        if (b & 1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

int f(int n) {
    int res = 1;
    for (int i = 1; i <= n; ++i) {
        res = mul(res, i);
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    cout << mul(f(n), mul(pow_mod(f(k), MOD - 2), pow_mod(f(n - k), MOD - 2))) << '\n';
    return 0;
}
