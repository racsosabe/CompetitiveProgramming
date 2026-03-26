/**
 * File: CF105394-GYM-D.cpp
 * Author: racsosabe
 * Date: 20/03/2026
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

int read_fraction() {
    string s;
    cin >> s;
    int den = pow_mod(pow_mod(10, (int)s.size() - 2), MOD - 2);
    int num = stoi(s.substr(2));
    return (1 + MOD - mul(num, den)) % MOD;
}

const int N = 200000 + 5;

int n;
int q;
int P[N];
int Pi[N];
int a[N];
int st_dec[4 * N];
int st_inc[4 * N];

int inter(int a, int b, int c, int d) {
    int r = min(b, d);
    int l = max(a, c);
    return l <= r ? r - l + 1 : 0;
}

void update_inc(int x, int y, int z, int pos = 1, int l = 0, int r = n - 1) {
    // Pi
    if (y < l or r < x or x > y) return;
    if (x <= l and r <= y) {
        st_inc[pos] += z;
        if (st_inc[pos] >= MOD) st_inc[pos] -= MOD;
        return;
    }
    int mi = (l + r) / 2;
    update_inc(x, y, z, 2 * pos, l, mi);
    update_inc(x, y, mul(z, Pi[inter(l, mi, x, y)]), 2 * pos + 1, mi + 1, r);
}

void update_dec(int x, int y, int z, int pos = 1, int l = 0, int r = n - 1) {
    // P
    if (y < l or r < x or x > y) return;
    if (x <= l and r <= y) {
        st_dec[pos] += z;
        if (st_dec[pos] >= MOD) st_dec[pos] -= MOD;
        return;
    }
    int mi = (l + r) / 2;
    update_dec(x, y, z, 2 * pos, l, mi);
    update_dec(x, y, mul(z, P[inter(l, mi, x, y)]), 2 * pos + 1, mi + 1, r);
}

int query(int x, int pos = 1, int l = 0, int r = n - 1) {
    if (l == r) {
        return (st_inc[pos] + st_dec[pos]) % MOD;
    }
    int mi = (l + r) / 2;
    int res = (mul(st_inc[pos], Pi[x - l]) + mul(st_dec[pos], P[x - l])) % MOD;
    if (x <= mi) {
        res += query(x, 2 * pos, l, mi);
        if (res >= MOD) res -= MOD;
    }
    else {
        res += query(x, 2 * pos + 1, mi + 1, r);
        if (res >= MOD) res -= MOD;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> q;
    P[1] = read_fraction();
    P[0] = 1;
    for (int i = 2; i <= n; ++i) P[i] = mul(P[1], P[i - 1]);
    Pi[n] = pow_mod(P[n], MOD - 2);
    for (int i = n - 1; i >= 0; --i) Pi[i] = mul(P[1], Pi[i + 1]);
    cin.ignore();
    while (q--) {
        char op;
        cin >> op;
        if (op == '+') {
            int b, x;
            cin >> b >> x;
            --x;
            update_dec(x, n - 1, b);
            update_inc(0, x - 1, mul(b, P[x]));
        }
        else if (op == '-') {
            int b, x;
            cin >> b >> x;
            --x;
            b = MOD - b;
            update_dec(x, n - 1, b);
            update_inc(0, x - 1, mul(b, P[x]));
        }
        else {
            int x;
            cin >> x;
            --x;
            cout << query(x) << '\n';
        }
    }
    return 0;
}
