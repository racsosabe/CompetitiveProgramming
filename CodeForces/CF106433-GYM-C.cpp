/**
 * File: CF106433-GYM-C.cpp
 * Author: racsosabe
 * Date: 25/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        int d, c, n;
        cin >> d >> c >> n;
        vector<int> cnt(c);
        set<pair<int, int>> S;
        for (int i = 0; i < c; ++i) {
            cin >> cnt[i];
            S.emplace(cnt[i], i);
        }
        int last_t = 0;
        vector<int> res(c, 0);
        for (int i = 0; i < n; ++i) {
            int x, q;
            cin >> x >> q;
            res[(*S.rbegin()).second] += x - last_t;
            for (int j = 0; j < q; ++j) {
                int new_c, channel;
                cin >> channel >> new_c;
                --channel;
                S.erase(make_pair(cnt[channel], channel));
                cnt[channel] = new_c;
                S.emplace(cnt[channel], channel);
            }
            last_t = x;
        }
        res[(*S.rbegin()).second] += d - last_t;
        vector<int> perm(c);
        iota(perm.begin(), perm.end(), 0);
        sort(perm.begin(), perm.end(), [&] (int i, int j) {
            if (res[i] == res[j]) return i < j;
            return res[i] > res[j];
        });
        for (auto &x : perm) {
            if(res[x] == 0) break;
            cout << x + 1 << " " << res[x] << '\n';
        }
    }
    return 0;
}
