/**
 * File: CF106420-GYM-F.cpp
 * Author: racsosabe
 * Date: 27/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

struct Fraction {
    int num;
    int den;

    Fraction(int num, int den) : num(num), den(den) {
        int g = __gcd(num, den);
        num /= g;
        den /= g;
    }

    bool operator <(const Fraction &rhs) const {
        return 1ll * num * rhs.den < 1ll * rhs.num * den;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, q, d;
    cin >> n >> q >> d;
    vector<Fraction> umas;
    vector<int> a(n), s(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> s[i];
    for (int i = 0; i < n; ++i) {
        umas.emplace_back(Fraction(a[i] + d, s[i]));
    }
    sort(umas.begin(), umas.end());
    while (q--) {
        int g;
        cin >> g;
        Fraction cur(n + 1 + d, g);
        int position = upper_bound(umas.begin(), umas.end(), cur) - umas.begin();
        cout << position + 1 << '\n';
    }
    return 0;
}
