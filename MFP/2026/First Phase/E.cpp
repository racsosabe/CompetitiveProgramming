/**
 * File: E.cpp
 * Author: racsosabe
 * Date: 23/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;
const int inf = 1e9 + 10;

int n, p, s;
int t1, t2, t3;
int d1, d2, d3;
int memo[N][6];
bool vis[N][6];

int DP(int laps, int changes) {
    if (laps == 0) return 0;
    if (changes < 0) return inf;
    if (vis[laps][changes]) return memo[laps][changes];
    int res = inf;
    int take1 = min(laps, d1);
    int take2 = min(laps, d2);
    int take3 = min(laps, d3);
    res = min(res, p + DP(laps - take1, changes - 1) + t1 * take1);
    res = min(res, p + DP(laps - take2, changes - 1) + t2 * take2);
    res = min(res, p + DP(laps - take3, changes - 1) + t3 * take3);
    vis[laps][changes] = true;
    return memo[laps][changes] = res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> p >> s;
    cin >> t1 >> t2 >> t3;
    cin >> d1 >> d2 >> d3;
    cout << DP(n, s) - p << '\n';
    return 0;
}
