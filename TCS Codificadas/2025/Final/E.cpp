/**
 * File: E.cpp
 * Author: racsosabe
 * Date: 21/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

const string dir = "UDLR";

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n, m;
int queries = 0;
vector<string> s(n);

bool valid_pos(int x, int y) {
    return 0 <= x and x < n and 0 <= y and y < m;
}

int ask(int k) {
    cout << "? " << dir[k] << endl;
    int x;
    cin >> x;
    ++queries;
    if(queries > 2 * (n * m + n + m)) while(true);
    if (x == -1) while(true);
    return x;
}

void answer(int x, int y) {
    cout << "! " << x + 1 << " " << y + 1 << endl;
}

vector<int> path;
set<pair<int, int>> vis;
vector<pair<int, int>> candidates;

void print_candidates() {
    cout << "Current candidates" << endl;
    for (auto &e : candidates) {
        cout << e.first + 1 << " " << e.second + 1 << endl;
    }
    cout << "--------------" << endl;
}

void solve() {
    int x, y;
    tie(x, y) = candidates.back();
    answer(x, y);
    exit(0);
}

void filter_negate(int k, int a, int b) {
    vector<pair<int ,int>> new_candidates;
    /*cout << "Before filtering negate with " << a << " " << b << endl;
    print_candidates();*/
    for (auto &e : candidates) {
        int x, y;
        tie(x, y) = e;
        int vx = x + a + dx[k];
        int vy = y + b + dy[k];
        if (not valid_pos(vx,vy) or s[vx][vy] == '#') {
            new_candidates.emplace_back(x, y);
        }
    }
    candidates = move(new_candidates);
    /*cout << "After filtering negate" << endl;
    print_candidates();
    cout << "------------------------" << endl;*/
    if (candidates.size() == 1) solve();
}

void filter_front(int k, int a, int b) {
    vector<pair<int ,int>> new_candidates;
    /*cout << "Before filtering front with " << a << " " << b << endl;
    print_candidates();*/
    for (auto &e : candidates) {
        int x, y;
        tie(x, y) = e;
        int vx = x + a + dx[k];
        int vy = y + b + dy[k];
        if (valid_pos(vx, vy) and s[vx][vy] != '#') {
            new_candidates.emplace_back(x, y);
        }
    }
    candidates = move(new_candidates);
    /*cout << "After filtering front" << endl;
    print_candidates();
    cout << "------------------------" << endl;*/
    if (candidates.size() == 1) solve();
}

void DFS(int a = 0, int b = 0) {
    if (candidates.size() == 1) solve();
    vis.emplace(a, b);
    for (int k = 0; k < 4; k++) {
        if (k == (path.back() ^ 1)) continue;
        int cur = ask(k);
        if (cur) {
            path.emplace_back(k);
            filter_front(k, a, b);
            if (not vis.count(make_pair(a + dx[k], b + dy[k]))) {
                DFS(a + dx[k], b + dy[k]);
            }
            path.pop_back();
            ask(k ^ 1);
        }
        else {
            filter_negate(k, a, b);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> m;
    s.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] == '#') continue;
            candidates.emplace_back(i, j);
        }
    }
    path.emplace_back(4);
    DFS();
    return 0;
}
