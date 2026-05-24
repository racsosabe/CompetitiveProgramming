/**
 * File: CF106144-GYM-J.cpp
 * Author: racsosabe
 * Date: 29/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        string s;
        cin >> s;
        int s_value = stoi(s);
        int n = s.size();
        vector<int> res;
        for (int x = 0; x + 1 < s.length(); ++x) {
            string cur = s.substr(s.length() - 1 - x, x + 1) + s.substr(0, s.length() - x - 1);
            int value = stoi(cur);
            // value = s_value + (x + 1) + nk
            int rem = (x + 1);
            if (value < s_value) continue;
            int lhs = value - s_value;
            if (lhs < rem) continue;
            if ((lhs - rem) % n == 0) {
                res.emplace_back(lhs);
            }
        }
        sort(res.begin(), res.end());
        cout << res.size() << '\n';
        for (auto &x : res) {
            cout << x << " ";
        }
        cout << '\n';
    }
    return 0;
}
