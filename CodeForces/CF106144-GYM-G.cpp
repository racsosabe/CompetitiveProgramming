/**
 * File: CF106144-GYM-G.cpp
 * Author: racsosabe
 * Date: 29/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

long long compute(vector<int> &rles) {
    if (rles.empty()) return 0;
    int sum = 0;
    long long cnt = 0;
    for (auto &x : rles) {
        cnt += 1ll * (sum + 1) * x;
        sum += x;
    }
    return cnt;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        vector<int> frec(26, 0);
        for (auto &c : s) {
            ++frec[c - 'a'];
        }
        long long res = 1;
        vector<vector<int>> rle(26, vector<int>());
        const int n = s.size();
        int l = 0;
        while (l < n) {
            int r = l;
            while (r < n and s[l] == s[r]) ++r;
            rle[s[l] - 'a'].emplace_back(r - l);
            l = r;
        }
        for (int i = 0; i < 26; ++i) {
            res += compute(rle[i]);
        }
        cout << res << '\n';
    }
    return 0;
}