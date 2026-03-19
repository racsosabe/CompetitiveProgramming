/**
 * File: 2214.cpp
 * Author: racsosabe
 * Date: 19/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    long long k;
    cin >> n >> k;
    int s = 1;
    while (1ll * s * (s + 1) / 2 <= k) {
        s++;
    }
    int extra = k - 1ll * s * (s - 1) / 2;
    if (extra > 0) {
        int ptr = s;
        for (int cnt = 0; cnt < s - extra; cnt++) {
            cout << ptr-- << " ";
        }
        cout << s + 1 << " ";
        while (ptr > 0) {
            cout << ptr-- << " ";
        }
        for (int i = s + 2; i <= n; i++) {
            cout << i << " ";
        }
        cout << endl;
    }
    else {
        int ptr = s;
        while (ptr > 0) {
            cout << ptr-- << " ";
        }
        for (int i = s + 1; i <= n; i++) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}