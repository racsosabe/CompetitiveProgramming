/**
 * File: 11478.cpp
 * Author: racsosabe
 * Date: 10/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> suffix_array(string &s) {
    s += char(0);
    const int n = s.size();
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    sort(a.begin(), a.end(), [&] (int i, int j) {
        return s[i] < s[j];
    });
    vector<int> mapeo(n);
    mapeo[a[0]] = 0;
    for (int i = 1; i < n; ++i) {
        mapeo[a[i]] = mapeo[a[i - 1]] + (s[a[i - 1]] != s[a[i]]);
    }
    int len = 1;
    vector<int> sbs(n);
    vector<int> head(n);
    vector<int> new_mapeo(n);
    while (len < n) {
        for (int i = 0; i < n; ++i) {
            sbs[i] = (a[i] + n - len) % n;
        }
        for (int i = n - 1; i >= 0; --i) {
            head[mapeo[a[i]]] = i;
        }
        for (int i = 0; i < n; ++i) {
            int x = sbs[i];
            a[head[mapeo[x]]++] = x;
        }
        new_mapeo[a[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (mapeo[a[i - 1]] != mapeo[a[i]]) {
                new_mapeo[a[i]] = new_mapeo[a[i - 1]] + 1;
            }
            else {
                int pre = mapeo[(a[i - 1] + len) % n];
                int cur = mapeo[(a[i] + len) % n];
                new_mapeo[a[i]] = new_mapeo[a[i - 1]] + (pre != cur);
            }
        }
        len <<= 1;
        swap(mapeo, new_mapeo);
    }
    return a;
}

vector<int> lcp_array(string &s, vector<int> &a) {
    const int n = s.size();
    vector<int> rnk(n);
    for (int i = 0; i < n; ++i) {
        rnk[a[i]] = i;
    }
    int k = 0;
    vector<int> lcp(n, 0);
    for (int i = 0; i < n; ++i) {
        if (rnk[i] + 1 == n) {
            k = 0;
            continue;
        }
        int j = a[rnk[i] + 1];
        while (i + k < n and j + k < n and s[i + k] == s[j + k]) ++k;
        lcp[rnk[i]] = k;
        if (k) --k;
    }
    return lcp;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s;
    cin >> s;
    long long res = 1ll * s.size() * (s.size() + 1) / 2;
    vector<int> a = suffix_array(s);
    vector<int> lcp = lcp_array(s, a);
    cout << res - accumulate(lcp.begin(), lcp.end(), 0LL) << '\n';
    return 0;
}
