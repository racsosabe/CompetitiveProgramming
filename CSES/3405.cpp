/**
 * File: 3405.cpp
 * Author: racsosabe
 * Date: 6/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

struct MonotoneQueueFixedMemory {
    int *values;
    int *fulls;
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
        } else {
            ++l;
            values[l] = x;
            fulls[l] = fulls[l - 1] | x;
        }
    }

    void fix() {
        if (r == n) {
            while (l >= 0) {
                int x = values[l];
                if (r == n) {
                    --r;
                    values[r] = fulls[r] = x;
                } else {
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

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    MonotoneQueueFixedMemory Q(k);
    int x, a, b, c;
    cin >> x >> a >> b >> c;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (i >= k) Q.pop();
        Q.push(x);
        if (i >= k - 1) {
            res ^= Q.full();
        }
        x = (1ll * a * x + b) % c;
    }
    cout << res << '\n';
    return 0;
}
