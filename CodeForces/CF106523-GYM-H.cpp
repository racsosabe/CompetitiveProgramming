/**
 * File: CF106523-GYM-H.cpp
 * Author: racsosabe
 * Date: 17/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
const int L = 20;

int pf[N];
bool done[N];
map<int, int> factors;
vector<int> primes;
bitset<N> composite;

void init() {
    for (int i = 2; i < N; ++i) {
        if (not composite[i]) {
            pf[i] = i;
            primes.emplace_back(i);
        }
        for (int &p: primes) {
            if (i * p >= N) break;
            composite[i * p] = true;
            pf[i * p] = p;
            if (i % p == 0) break;
        }
    }
}

void add(int x) {
    while (x != 1) {
        int f = pf[x];
        int e = 0;
        while (x % f == 0) {
            ++e;
            x /= f;
        }
        if (done[f]) continue;
        factors[f] += e;
        if (factors[f] >= L) {
            factors.erase(f);
            done[f] = true;
        }
    }
}

void expo(int x) {
    vector<int> to_erase;
    for (auto e: factors) {
        int new_val = e.second * x;
        if (new_val >= L) {
            done[e.first] = true;
            to_erase.emplace_back(e.first);
        }
        factors[e.first] = new_val;
    }
    for (auto &x: to_erase) {
        factors.erase(x);
    }
}

bool check(int x) {
    while (x != 1) {
        int f = pf[x];
        int e = 0;
        while (x % f == 0) {
            ++e;
            x /= f;
        }
        if (done[f]) continue;
        if (!factors.count(f)) return false;
        if (factors[f] < e) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    init();
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            add(x);
        } else if (op == 2) {
            int x;
            cin >> x;
            expo(x);
        } else {
            int x;
            cin >> x;
            cout << (check(x) ? "Yes" : "No") << '\n';
        }
    }
    return 0;
}
