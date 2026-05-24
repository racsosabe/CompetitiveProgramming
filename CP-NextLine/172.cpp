/**
 * File: 172.cpp
 * Author: racsosabe
 * Date: 7/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int f(unsigned long long n) {
    int len = 1;
    int res = 0;
    unsigned long long cnt = 9;
    while (n > 0 and len < 20) {
        if (n <= cnt) break;
        n -= cnt;
        cnt *= 9;
        ++len;
    }
    --n;
    vector<int> value(len);
    for (int i = 0; i < len; ++i) {
        value[i] = n % 9;
        n /= 9;
    }
    for (int i = len - 1; i >= 0; --i) {
        int lhs = 0;
        int pot_lhs = i + 1 < len;
        for (int j = len - 1; j > i; --j) {
            lhs = (lhs * 9ll + value[j]) % MOD;
        }
        for (int j = len - 1; j > i; --j) {
            lhs = (lhs + pot_lhs) % MOD;
            pot_lhs = (9ll * pot_lhs) % MOD;
        }
        int rhs = 0;
        int pot = 1;
        for (int j = i - 1; j >= 0; --j) {
            rhs = (rhs * 9ll + value[j]) % MOD;
            pot = (pot * 9ll) % MOD;
        }
        for (int c = 0; c < 9; ++c) {
            int cur = (1ll * (c + 1) * lhs) % MOD * pot % MOD;
            if (c == value[i]) {
                cur = (cur + (1ll * (rhs + 1) * (c + 1)) % MOD) % MOD;
            }
            else if (c < value[i]) {
                cur = (cur + (1ll * pot * (c + 1)) % MOD) % MOD;
            }
            res = (res + cur) % MOD;
        }
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    unsigned long long n;
    cin >> n;
    cout << f(n) << '\n';
    return 0;
}
