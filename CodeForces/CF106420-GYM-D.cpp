/**
 * File: CF106420-GYM-D.cpp
 * Author: racsosabe
 * Date: 27/04/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<set<string> > S(n + 1, set<string>());
    sort(s.begin(), s.end());
    int res = 0;
    do {
        string cur = "";
        for (auto &c: s) {
            cur.push_back(c);
            if (not S[cur.size()].count(cur)) {
                S[cur.size()].emplace(cur);
                res += cur.size();
            }
        }
    } while (next_permutation(s.begin(), s.end()));
    cout << res << '\n';
    return 0;
}
