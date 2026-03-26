/**
 * File: CF105394-GYM-C.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

int names = 0;
map<string, int> ID;
vector<vector<int>> suffixes;

void print(vector<int> &s) {
    for (auto &c : s) {
        cout << c << " ";
    }
    cout << endl;
}

void initialize_suffixes(vector<string> &tokens) {
    for (int i = 0; i < tokens.size(); ++i) {
        vector<int> mapping;
        int variables = 0;
        map<string, int> last;
        for (int j = i; j < tokens.size(); j++) {
            if (tokens[j].size() == 1 and isalpha(tokens[j][0])) {
                if (last.count(tokens[j])) {
                    int d = j - last[tokens[j]];
                    mapping.emplace_back(2 * d + 1);
                }
                else {
                    mapping.emplace_back(-(2 * variables++ + 1));
                }
                last[tokens[j]] = j;
            }
            else {
                int id;
                if (ID.count(tokens[j])) id = ID[tokens[j]];
                else ID[tokens[j]] = id = names++;
                mapping.emplace_back(2 * id);
            }
        }
        suffixes.emplace_back(mapping);
    }
}

vector<int> compute_equivalent(vector<string> &tokens, bool text = false) {
    map<string, int> last;
    int number_of_variables = 0;
    vector<int> res;
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens[i].size() == 1 and isalpha(tokens[i][0])) {
            if (last.count(tokens[i])) {
                int d = i - last[tokens[i]];
                res.emplace_back(2 * d + 1);
            }
            else {
                res.emplace_back(-(2 * number_of_variables + 1));
                ++number_of_variables;
            }
            last[tokens[i]] = i;
        }
        else {
            int id;
            if (ID.count(tokens[i])) id = ID[tokens[i]];
            else return vector<int>();
            res.emplace_back(2 * id);
        }
    }
    return res;
}

bool lt(vector<int> &s, vector<int> &t) {
    int ptr = 0;
    while (ptr < s.size() and ptr < t.size() and s[ptr] == t[ptr]) {
        ++ptr;
    }
    if (ptr == s.size()) return ptr < t.size();
    if (ptr == t.size()) return false;
    return s[ptr] < t[ptr];
}

bool check(vector<int> &s, vector<int> &t) {
    int ptr = 0;
    while (ptr < s.size() and ptr < t.size() and s[ptr] == t[ptr]) {
        ++ptr;
    }
    return ptr == s.size();
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    vector<string> tokens(n);
    for(int i = 0; i < n; ++i) {
        cin >> tokens[i];
    }
    initialize_suffixes(tokens);
    sort(suffixes.begin(), suffixes.end());
    int q;
    cin >> q;
    while (q--) {
        int m;
        cin >> m;
        vector<string> cur_tokens(m);
        for (int i = 0; i < m; ++i) {
            cin >> cur_tokens[i];
        }
        vector<int> t = compute_equivalent(cur_tokens);
        if (t.empty()) {
            cout << "no" << endl;
            continue;
        }
        int lo = 0, hi = n - 1;
        while (lo < hi) {
            int mi = lo + (hi - lo) / 2;
            if (lt(suffixes[mi], t)) lo = mi + 1;
            else hi = mi;
        }
        cout << (check(t, suffixes[lo]) ? "yes" : "no") << endl;
    }
    return 0;
}