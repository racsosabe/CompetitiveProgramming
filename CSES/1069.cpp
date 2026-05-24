/**
 * File: 1069.cpp
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
    int cnt = 0;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if(i == 0 or s[i] == s[i - 1]) ++cnt;
        else cnt = 1;
        res = max(res, cnt);
    }
    cout << res << '\n';
    return 0;
}