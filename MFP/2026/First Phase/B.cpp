/**
 * File: B.cpp
 * Author: racsosabe
 * Date: 23/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

vector<long long> read() {
    string s;
    cin >> s;
    vector<long long> frec(26, 0);
    for (auto &c : s) {
        ++frec[c - 'a'];
    }
    return frec;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    vector<long long> Ada = read();
    vector<long long> Py = read();
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int k;
            string s;
            cin >> k >> s;
            for (auto &c : s) {
                Ada[c - 'a'] += k;
            }
        }
        else if (op == 2) {
            int k;
            string s;
            cin >> k >> s;
            for (auto &c : s) {
                Py[c - 'a'] += k;
            }
        }
        else {
            int at = 0;
            while (at < 26 and Ada[at] == Py[at]) ++at;
            if (at == 26) {
                cout << "EMPATE" << '\n';
                continue;
            }
            if (Ada[at] < Py[at]) {
                if (accumulate(Ada.begin() + at + 1, Ada.end(), 0) == 0) {
                    cout << "ADA" << '\n';
                }
                else {
                    cout << "PY" << '\n';
                }
            }
            else {
                if (accumulate(Py.begin() + at + 1, Py.end(), 0) == 0) {
                    cout << "PY" << '\n';
                }
                else {
                    cout << "ADA" << '\n';
                }
            }
        }
    }
    return 0;
}
