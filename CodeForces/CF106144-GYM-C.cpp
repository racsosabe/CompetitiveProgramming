/**
 * File: CF106144-GYM-C.cpp
 * Author: racsosabe
 * Date: 29/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 6001;
const int M = 1501;

int n;
string s;
bitset<M> memo[N];
bitset<M> last[N];

int val(int i) {
    return s[i] == '(' ? 1 : -1;
}

bool solve() {
    if (n == 1) return false;
    for (int i = 0; i < n; ++i) {
        int turn = (n - 1) & 1;
        int c = val(i);
        last[i].reset();
        if (turn == 0) {
            if (c == -1) {
                last[i][1] = true;
            }
            last[i][0] = true;
        }
        else {
            last[i].set();
            last[i][0] = false;
        }
    }
    for (int L = 2; L <= n; ++L) {
        int turn = (n - L) & 1;
        for (int l = 0; l + L - 1 < n; ++l) {
            int r = l + L - 1;
            if (turn == 0) {
                int c_l = val(l);
                int c_r = val(r);

                if (c_l > 0) {
                    memo[l] = (~last[l + 1]) >> 1;
                }
                else {
                    memo[l] = (~last[l + 1]) << 1;
                }
                if (c_r > 0) {
                    memo[l] |= (~last[l]) >> 1;
                }
                else {
                    memo[l] |= (~last[l]) << 1;
                }
                if (L < n) {
                    memo[l][0] = true;
                }
            }
            else {
                memo[l] = (~last[l]) | (~last[l + 1]);
            }
        }
        for (int l = 0; l + L - 1 < n; ++l) {
            last[l] = memo[l];
        }
    }
    return last[0][0];
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        cin >> s;
        cout << (solve() ? "Monocarp" : "Polycarp") << '\n';
    }
    return 0;
}