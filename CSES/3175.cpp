/**
 * File: 3175.cpp
 * Author: racsosabe
 * Date: 19/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

void print(vector<int> &perm) {
    for (auto &x : perm) {
        cout << x << " ";
    }
    cout << endl;
}

bool check(vector<int> &perm) {
    for (int i = 1; i < perm.size(); i++) {
        if (abs(perm[i] - perm[i - 1]) == 1) return false;
    }
    return true;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    if (n == 1) {
        cout << n << endl;
        return 0;
    }
    if (n == 2 or n == 3) {
        cout << "NO SOLUTION" << endl;
        return 0;
    }
    if (n == 4) {
        cout << "2 4 1 3" << endl;
        return 0;
    }
    const vector<int> base = {1, 3, 5, 2, 4};
    if (n % 5 == 0) {
        for (int s = 0; s < n / 5; s++) {
            for (auto &x : base) {
                cout << x + s * 5 << " ";
            }
        }
        cout << endl;
        return 0;
    }
    vector<int> v;
    for (int s = 0; s < n / 5; s++) {
        for (auto &x : base) {
            v.emplace_back(x + s * 5);
        }
    }
    for (int i = n - n % 5 + 1; i <= n; i++) {
        v.emplace_back(i);
    }
    sort(v.begin() + n - 5, v.end());
    do {
        if(check(v)) {
            print(v);
            return 0;
        }
    } while (next_permutation(v.begin(), v.end()));
    return 0;
}