/**
 * File: coprimeintegers.cpp
 * Author: racsosabe
 * Date: 11/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 10000000 + 5;


int mobius[N];
long long G[N];
vector<int> primes;
bitset<N> composite;

void init() {
    mobius[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (not composite[i]) {
            mobius[i] = -1;
            primes.emplace_back(i);
        }
        for (auto &p : primes) {
            if (i * p >= N) break;
            mobius[i * p] = -mobius[i];
            composite[i * p] = true;
            if (i % p == 0) {
                mobius[i * p] = 0;
                break;
            }
        }
    }
}

int compute_multiples(int l, int r, int x) {
    return r / x - (l - 1) / x;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    init();
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    long long res = 0;
    for (int i = 1; i < N; ++i) {
        G[i] = 1ll * compute_multiples(a, b, i) * compute_multiples(x, y, i);
        res += G[i] * mobius[i];
    }
    cout << res << '\n';
    return 0;
}