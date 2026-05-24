/**
 * File: CF106523-GYM-K.cpp
 * Author: racsosabe
 * Date: 17/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

bool check(char a, char b) {
    if (a == 'F' and b == 'G') return true;
    if (a == 'G' and b == 'W') return true;
    return a == 'W' and b == 'F';
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    char Ta, Tb;
    int p, h;
    cin >> Ta >> Tb;
    cin >> p >> h;
    if (check(Ta, Tb)) {
        h -= p * 2;
    } else {
        h -= p >> 1;
    }
    if (h < 0) h = 0;
    if (h == 0) {
        cout << "Nocaute!" << '\n';
    } else {
        cout << "Sobraram " << h << " pontos de vida!" << '\n';
    }
    return 0;
}
