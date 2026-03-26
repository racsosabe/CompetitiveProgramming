/**
 * File: 1162.cpp
 * Author: racsosabe
 * Date: 22/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;
const int inf = 1e9;

int n;
int ft[N];

void update(int pos, int val) {
    ++pos;
    while (pos <= n) {
        ft[pos] += val;
        pos += (-pos) & pos;
    }
}

int get_sum(int pos) {
    ++pos;
    int res = 0;
    while (pos > 0) {
        res += ft[pos];
        pos &= pos - 1;
    }
    return res;
}

long long inversions(vector<int> &a) {
    long long res = 0;
    for (int i = n - 1; i >= 0; i--) {
        int x = a[i];
        res += get_sum(x);
        update(x, 1);
    }
    return res;
}

int cycles(vector<int> &a) {
    vector<bool> vis(n, false);
    int res = n;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        --res;
        int x = i;
        do {
            vis[x] = true;
            x = a[x];
        } while (not vis[x]);
    }
    return res;
}

int lis(vector<int> &a) {
    vector<int> LIS(n + 1, inf);
    LIS[0] = -inf;
    for (auto &x : a) {
        int to = lower_bound(LIS.begin(), LIS.end(), x) - LIS.begin();
        LIS[to] = x;
    }
    int res = n;
    while (LIS[res] == inf) --res;
    return n - res;
}

int suffix(vector<int> &a) {
    int last = n - 1;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] == last) {
            --last;
        }
    }
    return last + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    cout << inversions(a) << " " << cycles(a) << " " << lis(a) << " " << suffix(a) << endl;
    return 0;
}
