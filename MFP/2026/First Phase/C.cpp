/**
 * File: C.cpp
 * Author: racsosabe
 * Date: 23/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int a, b;
    cin >> a >> b;
    cout << max((a / 7) * b, a * (b / 7)) << '\n';
    return 0;
}
