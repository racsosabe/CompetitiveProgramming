/**
 * File: 1640.cpp
 * Author: racsosabe
 * Date: 12/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, s;
    cin >> n >> s;
    map<int, int> position;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        if (position.find(s - x) != position.end()) {
            cout << position[s - x] << " " << i << '\n';
            return 0;
        }
        position[x] = i;
    }
    cout << "IMPOSSIBLE" << '\n';
    return 0;
}
