/**
* File: INVPHI.cpp
 * Author: racsosabe
 * Date: 6/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 203000000;
const int M = 100000001;

int ans[M];
int phi[N];
vector<int> primes;
bitset<N> composite;

void init() {
    phi[1] = 1;
    fill_n(ans, M, -1);
    ans[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (not composite[i]) {
            phi[i] = i - 1;
            primes.emplace_back(i);
        }
        for (auto &p : primes) {
            if (1ll * i * p >= N) break;
            phi[i * p] = phi[i] * (p - 1);
            composite[i * p] = true;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
        }
        if (phi[i] < M and ans[phi[i]] == -1) {
            ans[phi[i]] = i;
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    init();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << ans[n] << '\n';
    }
    return 0;
}