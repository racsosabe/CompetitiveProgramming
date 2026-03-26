/**
 * File: CF106433-GYM-E.cpp
 * Author: racsosabe
 * Date: 25/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 100000 + 5;

int n;
int a[N];
int lazy[4 * N];
int st[2][4 * N];

void build(int pos = 1, int l = 0, int r = n - 1) {
    lazy[pos] = 0;
    if (l == r) {
        st[0][pos] = 1;
        st[1][pos] = 0;
        return;
    }
    int mi = (l + r) / 2;
    build(2 * pos, l, mi);
    build(2 * pos + 1, mi + 1, r);
    st[0][pos] = st[0][2 * pos] + st[0][2 * pos + 1];
    st[1][pos] = st[1][2 * pos] + st[1][2 * pos + 1];
}

void push(int pos, int l, int r) {
    if (lazy[pos]) {
        swap(st[0][2 * pos], st[1][2 * pos]);
        swap(st[0][2 * pos + 1], st[1][2 * pos + 1]);
        lazy[2 * pos] ^= 1;
        lazy[2 * pos + 1] ^= 1;
        lazy[pos] = 0;
    }
}

void update(int x, int y, int pos = 1, int l = 0, int r = n - 1) {
    if (y < l or r < x or x > y) return;
    if (x <= l and r <= y) {
        swap(st[0][pos], st[1][pos]);
        lazy[pos] ^= 1;
        return;
    }
    push(pos, l, r);
    int mi = (l + r) / 2;
    update(x, y, 2 * pos, l, mi);
    update(x, y, 2 * pos + 1, mi + 1, r);
    st[0][pos] = st[0][2 * pos] + st[0][2 * pos + 1];
    st[1][pos] = st[1][2 * pos] + st[1][2 * pos + 1];
}

int query(int x, int y, int pos = 1, int l = 0, int r = n - 1) {
    if (y < l or r < x or x > y) return 0;
    if (x <= l and r <= y) return st[1][pos];
    push(pos, l, r);
    int mi = (l + r) / 2;
    return query(x, y, 2 * pos, l, mi) + query(x, y, 2 * pos + 1, mi + 1, r);
}

long long solve() {
    build();
    map<int, int> last;
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        if (last.count(a[i])) {
            update(last[a[i]] + 1, i);
        }
        else {
            update(0, i);
        }
        res += query(0, i);
        last[a[i]] = i;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << solve() << '\n';
    }
    return 0;
}
