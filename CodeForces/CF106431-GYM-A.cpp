/**
 * File: CF106431-GYM-A.cpp
 * Author: racsosabe
 * Date: 25/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 80;

long long memo[N];

void init() {
    memo[0] = 1;
    for (int i = 1; i < N; ++i) {
        memo[i] = memo[i - 1];
        if (i >= 2) memo[i] += memo[i - 2];
        if (i >= 4) memo[i] += memo[i - 4];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    init();
    string s;
    while(getline(cin, s)) {
        long long res = 1;
        int last = -1;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == 'X') {
                int cnt = i - last - 1;
                res *= memo[cnt];
                last = i;
            }
        }
        res *= memo[s.size() - last - 1];
        cout << res << '\n';
    }
    return 0;
}
