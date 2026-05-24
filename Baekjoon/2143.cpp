/**
 * File: 2143.cpp
 * Author: racsosabe
 * Date: 11/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> compute(int n, vector<int> &a) {
    vector<int> L;
    for (int i = 0; i < n; ++i) {
        int cur_sum = 0;
        for (int j = i; j < n; ++j) {
            cur_sum += a[j];
            L.emplace_back(cur_sum);
        }
    }
    return L;
}

long long solve(int target, int n, int m, vector<int> &a, vector<int> &b) {
    vector<int> L = compute(n, a), R = compute(m, b);
    unordered_map<int, int> frec_a;
    for (auto &x : L) ++frec_a[x];
    long long res = 0;
    for (auto &x : R) {
        if (frec_a.find(target - x) == frec_a.end()) continue;
        res += frec_a[target - x];
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int target;
    cin >> target;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    cout << solve(target, n, m, a, b) << '\n';
    return 0;
}