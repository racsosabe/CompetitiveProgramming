/**
 * File: F.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int MASK = 1 << 8;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> cnt(MASK, 0);
    cnt[0] = 1;
    int mask = 0;
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        mask ^= 1 << (s[i] - 'a');
        res += cnt[mask];
        for (int c = 0; c < 8; ++c) {
            res += cnt[mask ^ (1 << c)];
        }
        ++cnt[mask];
    }
    cout << res << '\n';
    return 0;
}