/**
 * File: 1080.cpp
 * Author: racsosabe
 * Date: 22/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int mul(long long a, long long b) {
    return a * b % MOD;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s;
    cin >> s;
    const int n = s.size();
    vector<vector<int>> C(n + 1, vector<int>(n + 1));
    for(int i = 0; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if (C[i][j] >= MOD) C[i][j] -= MOD;
        }
    }
    vector<vector<int>> memo(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) memo[i][i] = 0;
    for (int i = 0; i + 1 < n; ++i) memo[i][i + 1] = s[i] == s[i + 1];
    for (int L = 3; L <= n; ++L) {
        for (int i = 0; i + L - 1 < n; ++i) {
            int j = i + L - 1;
            for (int k = i + 1; k <= j; ++k) {
                if (s[i] != s[k]) continue;
                int pairs_l = (k - i + 1) / 2;
                int pairs_r = (j - k) / 2;
                int l = i + 1 <= k - 1 ? memo[i + 1][k - 1] : 1;
                int r = k + 1 <= j ? memo[k + 1][j] : 1;
                int ways = C[pairs_l + pairs_r][pairs_l];
                memo[i][j] += mul(l, mul(r, ways));
                if (memo[i][j] >= MOD) memo[i][j] -= MOD;
            }
        }
    }
    cout << memo[0][n - 1] << endl;
    return 0;
}