/**
 * File: CF106523-GYM-J.cpp
 * Author: racsosabe
 * Date: 17/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> primes;
    vector<bool> composite(n + 1, false);
    for (int i = 2; i <= n; ++i) {
        if (not composite[i]) {
            primes.emplace_back(i);
        }
        for (int &p: primes) {
            if (i * p > n) break;
            composite[i * p] = true;
            if (i % p == 0) break;
        }
    }
    cout << primes.size() << '\n';
    return 0;
}
