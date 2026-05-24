/**
 * File: 1753.cpp
 * Author: racsosabe
 * Date: 6/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> get_pi(string &s) {
    const int n = s.size();
    vector<int> pi(n, 0);
    int k = 0;
    for (int i = 1; i < n; ++i) {
        while (k > 0 and s[i] != s[k]) k = pi[k - 1];
        if (s[i] == s[k]) ++k;
        pi[i] = k;
    }
    return pi;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string t, p;
    cin >> t >> p;
    vector<int> pi = get_pi(p);
    int k = 0;
    int res = 0;
    for (auto &c : t) {
        while (k > 0 and c != p[k]) k = pi[k - 1];
        if (c == p[k]) ++k;
        if (k == p.size()) {
            ++res;
            k = pi[k - 1];
        }
    }
    cout << res << '\n';
    return 0;
}