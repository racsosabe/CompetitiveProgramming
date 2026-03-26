/**
 * File: B.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const string dir = "UDLR";
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n;

bool ask(char d) {
    cout << "? " << d << endl;
    char res;
    cin >> res;
    return res == '-';
}

void move(char d) {
    cout << "M " << d << endl;
}

bool valid_pos(int x, int y) {
    return 0 <= x and x < n and 0 <= y and y < n;
}

void answer() {
    cout << "!" << endl;
}

void solve() {
    int x = n / 2, y = n / 2;
    for (int id = 0; id < 4; id++) {
        while (valid_pos(x + dx[id], y + dy[id]) and ask(dir[id])) {
            move(dir[id]);
            x += dx[id];
            y += dy[id];
        }
    }
    answer();
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n;
    solve();
    return 0;
}