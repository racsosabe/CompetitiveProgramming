/**
* File: 3416.cpp
 * Author: racsosabe
 * Date: 19/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

struct MonotoneQueueFixedMemory {
    int* values;
    int* fulls;
    int l;
    int r;
    int n;
    MonotoneQueueFixedMemory(int n) : n(n) {
        values = new int[n];
        fulls = new int[n];
        l = -1;
        r = n;
    }

    ~MonotoneQueueFixedMemory() {
        delete[] values;
        delete[] fulls;
    }

    void push(int x) {
        if (l == -1) {
            ++l;
            values[l] = fulls[l] = x;
        }
        else {
            ++l;
            values[l] = x;
            fulls[l] = fulls[l - 1] | x;
        }
    }

    void fix() {
        if(r == n) {
            while (l >= 0) {
                int x = values[l];
                if (r == n) {
                    --r;
                    values[r] = fulls[r] = x;
                }
                else {
                    --r;
                    values[r] = x;
                    fulls[r] = fulls[r + 1] | x;
                }
                --l;
            }
        }
    }

    int front() {
        fix();
        return r == n ? 0 : values[r];
    }

    int full() {
        return (~l ? fulls[l] : 0) | (r == n ? 0 : fulls[r]);
    }

    void pop() {
        fix();
        if (r < n) r++;
    }

    bool empty() {
        return l == -1 && r == n;
    }
};

const int N = 500;
const int K = 26;

int n;
int m;
int k;
string s[N];
int masks[N];

int solve() {
    int r = 0;
    int res = 0;
    MonotoneQueueFixedMemory Q(n);
    for (int l = 0; l < n; ++l) {
        while (r < n and Q.full() < m) {
            Q.push(masks[r]);
            ++r;
        }
        if (Q.full() == m) {
            res += n - r + 1;
        }
        else break;
        Q.pop();
    }
    return res;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> k;
    m = (1 << k) - 1;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    long long res = 0;
    for (int c1 = 0; c1 < n; ++c1) {
        fill_n(masks, n, 0);
        for (int c2 = c1; c2 < n; ++c2) {
            for (int i = 0; i < n; ++i) {
                masks[i] |= 1 << (s[c2][i] - 'A');
            }
            res += solve();
        }
    }
    cout << res << endl;
    return 0;
}