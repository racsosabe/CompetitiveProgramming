/**
 * File: CF105394-GYM-K.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const string alpha = "bdpq";

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s, commands;
    cin >> s >> commands;
    bool hor = false;
    bool ver = false;
    bool half = false;
    for(auto &c : commands) {
        if (c == 'h') {
            hor ^= true;
        }
        else if (c == 'v') {
            ver ^= true;
        }
        else {
            half ^= true;
        }
    }
    if (hor) {
        reverse(s.begin(), s.end());
        for (auto &c : s) {
            if (c == 'b') c = 'd';
            else if (c == 'd') c = 'b';
            else if (c == 'p') c = 'q';
            else c = 'p';
        }
    }
    if (ver) {
        for (auto &c : s) {
            if (c == 'b') c = 'p';
            else if (c == 'd') c = 'q';
            else if (c == 'p') c = 'b';
            else c = 'd';
        }
    }
    if (half) {
        reverse(s.begin(), s.end());
        for (auto &c : s) {
            if (c == 'b') c = 'q';
            else if (c == 'd') c = 'p';
            else if (c == 'p') c = 'd';
            else c = 'b';
        }
    }
    cout << s << endl;
    return 0;
}