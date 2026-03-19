/**
 * File: 2220.cpp
 * Author: racsosabe
 * Date: 18/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int LOG = 20;

vector<int> v;
bool vis[LOG][10][2];
long long memo[LOG][10][2];

long long DP(int pos, int last, int menor) {
    if (pos == v.size()) {
        return 1;
    }
    if (vis[pos][last][menor]) return memo[pos][last][menor];
    long long res = 0;
    int limit = menor ? 9 : v[pos];
    for (int c = 0; c <= limit; c++) {
        if (c == last) continue;
        res += DP(pos + 1, c, menor | (c < v[pos]));
    }
    vis[pos][last][menor] = true;
    return memo[pos][last][menor] = res;
}

long long f(long long x) {
    if (x < 0) return 0;
    if (x == 0) return 1;
    v.clear();
    while (x > 0) {
        v.emplace_back(x % 10);
        x /= 10;
    }
    reverse(v.begin(), v.end());
    memset(vis, 0, sizeof vis);
    long long res = 0;
    for (int c = 1; c <= v[0]; c++) {
        res += DP(1, c, c < v[0]);
    }
    for (int s = 1; s < v.size(); s++) {
        for (int c = 1; c <= 9; c++) {
            res += DP(s + 1, c, 1);
        }
    }
    return res + 1;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    long long a, b;
    cin >> a >> b;
    cout << f(b) - f(a - 1) << endl;
    return 0;
}