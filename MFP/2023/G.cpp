/**
 * File: G.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cout << (i & 1);
    }
    cout << '\n';
    return 0;
}