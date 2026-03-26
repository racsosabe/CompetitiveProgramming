/**
 * File: CF105394-GYM-E.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 300 + 5;

set<string> plus_one;
set<string> multiply_two;
set<string> nothing_changes;

int n;
int memo[2][N][N][N];
bool vis[2][N][N][N];
int choice[2][N][N][N];

int DP(int one, int two, int nothing, int par) {
    int pos = n - one - two - nothing;
    if (one == 0 and two == 0 and nothing == 0) return (pos & 1) != par;
    if (vis[par][one][two][nothing]) return memo[par][one][two][nothing];
    int res = 0;
    if (one) {
        if (DP(one - 1, two, nothing, par ^ 1) == 0) {
            res = 1;
            choice[par][one][two][nothing] = 1;
        }
    }
    if (two) {
        if (DP(one, two - 1, nothing, 0) == 0) {
            res = 1;
            choice[par][one][two][nothing] = 2;
        }
    }
    if (nothing) {
        if (DP(one, two, nothing - 1, par) == 0) {
            res = 1;
            choice[par][one][two][nothing] = 0;
        }
    }
    vis[par][one][two][nothing] = 1;
    return memo[par][one][two][nothing] = res;
}

int get_current_choice(int current_par) {
    return choice[current_par][plus_one.size()][multiply_two.size()][nothing_changes.size()];
}

void my_move(int &current_par) {
    assert(memo[current_par][plus_one.size()][multiply_two.size()][nothing_changes.size()]);
    int ch = get_current_choice(current_par);
    if (ch == 0) {
        cout << *nothing_changes.begin() << endl;
        nothing_changes.erase(nothing_changes.begin());
    }
    else if (ch == 1) {
        cout << *plus_one.begin() << endl;
        plus_one.erase(plus_one.begin());
        current_par ^= 1;
    }
    else {
        cout << *multiply_two.begin() << endl;
        multiply_two.erase(multiply_two.begin());
        current_par = 0;
    }
}

void solve(int start) {
    int who = DP(plus_one.size(), multiply_two.size(), nothing_changes.size(), start);
    if (who) {
        cout << "me" << endl;
        my_move(start);
    }
    else {
        cout << "you" << endl;
    }
    while (not plus_one.empty() or not multiply_two.empty() or not nothing_changes.empty()) {
        string his_response;
        getline(cin, his_response);
        if (plus_one.count(his_response)) {
            plus_one.erase(his_response);
            start ^= 1;
        }
        else if (multiply_two.count(his_response)) {
            multiply_two.erase(his_response);
            start = 0;
        }
        else {
            assert(nothing_changes.count(his_response));
            nothing_changes.erase(his_response);
        }
        if (not plus_one.empty() or not multiply_two.empty() or not nothing_changes.empty()) {
            my_move(start);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n;
    cin.ignore();
    for(int i = 0; i < n; ++i) {
        char op;
        int x;
        cin >> op >> x;
        if (op == '+') {
            if (x & 1) {
                plus_one.emplace("+ " + to_string(x));
            }
            else {
                nothing_changes.emplace("+ " + to_string(x));
            }
        }
        else {
            if (x & 1) {
                nothing_changes.emplace("* " + to_string(x));
            }
            else {
                multiply_two.emplace("* " + to_string(x));
            }
        }
    }
    int x;
    cin >> x;
    x &= 1;
    cin.ignore();
    solve(x);
    return 0;
}
