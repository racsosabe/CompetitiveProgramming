/**
* File: 3416.cpp
 * Author: racsosabe
 * Date: 19/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

struct MonotoneStack {
    int len;
    int* values;
    int* fulls;
    MonotoneStack(int n) : len(0) {
        values = new int[n];
        fulls = new int[n];
    }

    ~MonotoneStack() {
        delete[] values;
        delete[] fulls;
    }

    void push(int x) {
        if (len == 0) {
            values[len] = fulls[len] = x;
        }
        else {
            values[len] = x;
            fulls[len] = fulls[len - 1] | x;
        }
        ++len;
    }

    int top() {
        return len ? values[len - 1] : 0;
    }

    int full() {
        return len ? fulls[len - 1] : 0;
    }

    void pop() {
        if (len > 0) --len;
    }

    bool empty() {
        return len == 0;
    }
};

struct MonotoneQueue {
    MonotoneStack in, out;
    MonotoneQueue(int n) : in(n), out(n) {
    }

    ~MonotoneQueue() = default;

    void push(int x) {
        in.push(x);
    }

    int front() {
        if (out.empty()) {
            while (not in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        return out.empty() ? 0 : out.top();
    }

    int full() {
        return out.full() | in.full();
    }

    void pop() {
        if (out.empty()) {
            while (not in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        if (not out.empty()) {
            out.pop();
        }
    }

    bool empty() {
        return in.empty() && out.empty();
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
    MonotoneQueue Q(n);
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