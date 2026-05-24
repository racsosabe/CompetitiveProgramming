/**
 * File: 1644.cpp
 * Author: racsosabe
 * Date: 4/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;

struct MonotoneQueueFixedMemory {
    long long* values;
    long long* fulls;
    int l;
    int r;
    int n;
    MonotoneQueueFixedMemory(int n) : n(n) {
        values = new long long[n];
        fulls = new long long[n];
        l = -1;
        r = n;
    }

    ~MonotoneQueueFixedMemory() {
        delete[] values;
        delete[] fulls;
    }

    void push(long long x) {
        if (l == -1) {
            ++l;
            values[l] = fulls[l] = x;
        }
        else {
            ++l;
            values[l] = x;
            fulls[l] = min(fulls[l - 1], x);
        }
    }

    void fix() {
        if(r == n) {
            while (l >= 0) {
                long long x = values[l];
                if (r == n) {
                    --r;
                    values[r] = fulls[r] = x;
                }
                else {
                    --r;
                    values[r] = x;
                    fulls[r] = min(fulls[r + 1], x);
                }
                --l;
            }
        }
    }

    long long front() {
        fix();
        return r == n ? inf : values[r];
    }

    long long full() {
        return min((~l ? fulls[l] : inf), (r == n ? inf : fulls[r]));
    }

    void pop() {
        fix();
        if (r < n) r++;
    }

    int size() {
        return (l + 1) + (n - r);
    }

    bool empty() {
        return l == -1 && r == n;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, a, b;
    cin >> n >> a >> b;
    long long prefix = 0;
    long long prev_prefix = 0;
    vector<int> v(n);
    long long res = -inf;
    MonotoneQueueFixedMemory Q(b - a + 1);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        if (i >= b) Q.pop();
        if (i >= a - 1) Q.push(prev_prefix);
        prefix += v[i];
        res = max(res, prefix - Q.full());
        if (i >= a - 1) prev_prefix += v[i - a + 1];
    }
    cout << res << '\n';
    return 0;
}
