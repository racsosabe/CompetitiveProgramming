/**
 * File: 1715.cpp
 * Author: racsosabe
 * Date: 18/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int mul(long long a, long long b) {
    return a * b % MOD;
}

int pow_mod(int a, int b) {
    int r = 1;
    while (b > 0) {
        if (b & 1) r = mul(r, a);
        a = mul(a, a);
        b >>= 1;
    }
    return r;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s;
    cin >> s;
    const int n = s.size();
    vector<int> frec(26, 0);
    for(int i = 0; i < s.length(); i++) {
        frec[s[i] - 'a']++;
    }
    vector<int> f(n + 1);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = mul(i, f[i - 1]);
    }
    vector<int> fi(n + 1);
    fi[n] = pow_mod(f[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) {
        fi[i] = mul(fi[i + 1], i + 1);
    }
    int res = f[n];
    for (auto &c : frec) {
        res = mul(res, fi[c]);
    }
    cout << res << endl;
    return 0;
}