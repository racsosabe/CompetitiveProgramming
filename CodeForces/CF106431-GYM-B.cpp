/**
 * File: CF106431-GYM-B.cpp
 * Author: racsosabe
 * Date: 25/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

template<int BASE = 1000000000, int BLOCK_LENGTH = 9>
struct BigInt {
    vector<int> v;

    BigInt() {
        v.clear();
    }

    BigInt(BigInt&) = default;
    BigInt(BigInt&&) = default;

    BigInt(string s) {
        v.clear();
        reverse(s.begin(), s.end());
        for (int i = 0; i * BLOCK_LENGTH < s.size(); ++i) {
            int l = i * BLOCK_LENGTH;
            int r = min(l + BLOCK_LENGTH, (int)s.size()) - 1;
            int cur_val = 0;
            for (int j = r; j >= l; --j) {
                cur_val = (cur_val << 1) + (cur_val << 3) + s[j] - '0';
            }
            v.emplace_back(cur_val);
        }
    }

    BigInt operator + (const BigInt &rhs) const {
        BigInt res;
        int len = max(v.size(), rhs.v.size());
        res.v.resize(len);
        fill_n(res.v.begin(), len, 0);
        for (int i = 0 ; i < len; ++i) {
            if (i < v.size()) res.v[i] += v[i];
            if (i < rhs.v.size()) res.v[i] += rhs.v[i];
        }
        for (int i = 0; i < res.v.size(); i++) {
            if (res.v[i] >= BASE) {
                if (i + 1 < res.v.size()) {
                    res.v[i + 1] += res.v[i] / BASE;
                }
                else {
                    res.v.emplace_back(res.v[i] / BASE);
                }
                res.v[i] %= BASE;
            }
        }
        return res;
    }

    void operator = (const BigInt &rhs) {
        v = rhs.v;
    }

    void print() {
        cout << v.back();
        for (int i = (int)v.size() - 2; i >= 0; --i) {
            cout << setw(BLOCK_LENGTH) << setfill('0') << v[i];
        }
        cout << '\n';
    }
};

typedef BigInt<1000000000, 9> my_int;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<my_int> a(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        a[i] = my_int(s);
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int q;
        cin >> q;
        my_int res("0");
        for (int j = 0; j < q; ++j) {
            int x;
            cin >> x;
            --x;
            res = res + a[x];
        }
        res.print();
    }
    return 0;
}
