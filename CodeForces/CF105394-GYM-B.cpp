/**
 * File: CF105394-GYM-B.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, h;
    cin >> n >> h;
    long long res = 0;
    for(int i = 0; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if(min(a, min(b, c)) > h) {
            cout << "impossible" << endl;
            return 0;
        }
        if (a > b) swap(a, b);
        if (a > c) swap(a, c);
        if (b > c) swap(b, c);
        if (b > h) res += b;
        else res += a;
    }
    cout << res << endl;
    return 0;
}