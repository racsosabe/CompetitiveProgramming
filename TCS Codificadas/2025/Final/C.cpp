/**
 * File: C.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    for(int i = 0; i + 2 < n; ++i) {
        for(int j = i + 1; j + 1 < n; ++j) {
            string A = a.substr(0, i + 1);
            string B = a.substr(i + 1, j - i);
            string C = a.substr(j + 1);
            vector<string> s = {A, B, C};
            sort(s.begin(), s.end());
            do {
                string cur = "";
                for (auto &x : s) {
                    cur += x;
                }
                if (cur == b) {
                    cout << "YES" << endl;
                    cout << A << " " << B << " " << C << endl;
                    cout << s[0] << " " << s[1] << " " << s[2] << endl;
                    return 0;
                }

            } while (next_permutation(s.begin(), s.end()));
        }
    }
    cout << "NO" << endl;
    return 0;
}