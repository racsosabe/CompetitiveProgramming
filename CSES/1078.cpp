/**
 * File: 1078.cpp
 * Author: racsosabe
 * Date: 19/03/2026
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
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> v(m);
    for(int i = 0; i < m; ++i) {
        cin >> v[i].first >> v[i].second;
    }
    sort(v.begin(), v.end());
    v.emplace_back(n, n);
    vector<int> f(2 * n + 1), fi(2 * n + 1);
    f[0] = 1;
    for (int i = 1; i <= 2 * n; ++i) f[i] = mul(i, f[i - 1]);
    fi[2 * n] = pow_mod(f[2 * n], MOD - 2);
    for (int i = 2 * n - 1; i >= 0; --i) {
        fi[i] = mul(fi[i + 1], i + 1);
    }
    function<int(int, int)> C = [&] (int n, int k) -> int {
        if (n < k) return 0;
        return mul(f[n], mul(fi[k], fi[n - k]));
    };

    vector<int> memo(v.size());
    for (int i = 0; i < v.size(); ++i) {
        memo[i] = C(v[i].first + v[i].second - 2, v[i].first - 1);
        for (int j = 0; j < i; ++j) {
            if (v[j].first <= v[i].first and v[j].second <= v[i].second) {
                int dx = v[i].first - v[j].first;
                int dy = v[i].second - v[j].second;
                memo[i] += MOD - mul(memo[j], C(dx + dy, dx));
                if(memo[i] >= MOD) memo[i] -= MOD;
            }
        }
    }
    cout << memo.back() << endl;
    return 0;
}