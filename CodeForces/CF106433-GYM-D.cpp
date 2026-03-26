/**
 * File: CF106433-GYM-D.cpp
 * Author: racsosabe
 * Date: 25/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;
const int MAX = 1000000 + 5;

int e;
int a[N];
int pf[MAX];
int val[MAX];
int nxt[MAX];
int last[MAX];
bool vis[MAX];
vector<int> primes;
bitset<MAX> composite;

bool add(int f, int x) {
    bool valid = true;
    if (~last[f] and a[val[last[f]]] > a[x]) valid = false;
    val[e] = x;
    nxt[e] = last[f];
    last[f] = e;
    ++e;
    return valid;
}

void init() {
    for(int i = 2; i < MAX; ++i) {
        if (not composite[i]) {
            pf[i] = i;
            primes.emplace_back(i);
        }
        for (int &p : primes) {
            if (i * p >= MAX) break;
            pf[i * p] = p;
            composite[i * p] = true;
            if (i % p == 0) break;
        }
    }
}

bool check(int f) {
    int prv = INT_MAX;
    for (int e = last[f]; ~e; e = nxt[e]) {
        int i = val[e];
        if (a[i] > prv) {
            return false;
        }
        prv = a[i];
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    init();
    int t;
    cin >> t;
    fill_n(last, MAX, -1);
    while (t--) {
        int n;
        cin >> n;
        vector<int> cur_primes;
        e = 0;
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            for (int j = a[i]; j != 1; ) {
                int f = pf[j];
                while (j % f == 0) {
                    j /= f;
                }
                if (not vis[f]) {
                    cur_primes.emplace_back(f);
                    vis[f] = true;
                }
                if (not add(f, i)) valid = false;
            }
        }
        for (int &f : cur_primes) {
            vis[f] = false;
            last[f] = -1;
        }
        if (valid) cout << "SI" << '\n';
        else cout << "NO" << '\n';
    }
    return 0;
}
