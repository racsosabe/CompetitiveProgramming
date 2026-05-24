/**
 * File: 2107.cpp
 * Author: racsosabe
 * Date: 4/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s;
    cin >> s;
    const int n = s.size();

    int l = 0, r = 0;
    vector<int> z(n, 0);
    for (int i = 1; i < n; ++i) {
        z[i] = min(r - i + 1, z[i - l]);
        if (z[i] < 0) z[i] = 0;
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << z[i] << " \n"[i + 1 == n];
    }

    vector<int> pi(n, 0);
    int k = 0;
    for (int i = 1; i < n; ++i) {
        while(k > 0 and s[k] != s[i]) k = pi[k - 1];
        if(s[i] == s[k]) ++k;
        pi[i] = k;
    }
    for (int i = 0; i < n; ++i) {
        cout << pi[i] << " \n"[i + 1 == n];
    }
    return 0;
}