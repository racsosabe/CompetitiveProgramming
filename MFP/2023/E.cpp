/**
 * File: E.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int msg = 0;
    for (int i = 0; i < 7; ++i) {
        int x;
        cin >> x;
        msg ^= x;
    }
    int sec;
    cin >> sec;
    cout << (msg == sec ? "N?" : "S") << '\n';
    return 0;
}