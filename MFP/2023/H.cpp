/**
 * File: H.cpp
 * Author: racsosabe
 * Date: 30/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

bool check(vector<pair<int, int>> &pos_slope, vector<pair<int, int>> &neg_slope, vector<int> &a, int p1) {
    int ptr_pos = 0, ptr_neg = 0;
    while (ptr_pos < pos_slope.size() and ptr_neg < neg_slope.size()) {
        if (pos_slope[ptr_pos].first - p1 < neg_slope[ptr_neg].first + p1) {
            int cur = pos_slope[ptr_pos].first - p1;
            if (a[ptr_pos + ptr_neg] != cur) return false;
            ++ptr_pos;
        }
        else {
            int cur = neg_slope[ptr_neg].first + p1;
            if (a[ptr_pos + ptr_neg] != cur) return false;
            ++ptr_neg;
        }
    }
    while (ptr_pos < pos_slope.size()) {
        int cur = pos_slope[ptr_pos].first - p1;
        if (a[ptr_pos + ptr_neg] != cur) return false;
        ++ptr_pos;
    }
    while (ptr_neg < neg_slope.size()) {
        int cur = neg_slope[ptr_neg].first + p1;
        if (a[ptr_pos + ptr_neg] != cur) return false;
        ++ptr_neg;
    }
    return true;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> value(n, 0);
    for (int i = 1; i < n; ++i) {
        int x;
        cin >> x;
        value[i] = x - value[i - 1];
    }
    // pos_slope are all values that have the structure p1 + pi
    // neg_slope are all values that have the structure pi - p1
    vector<pair<int, int>> pos_slope, neg_slope;
    for (int i = 0; i < n; ++i) {
        if (i & 1) pos_slope.emplace_back(value[i], i);
        else neg_slope.emplace_back(value[i], i);
    }
    sort(pos_slope.begin(), pos_slope.end());
    sort(neg_slope.begin(), neg_slope.end());
    sort(a.begin(), a.end());
    if (check(pos_slope, neg_slope, a, a[0] - neg_slope[0].first)) {
        value[0] = a[0] - neg_slope[0].first;
    }
    else {
        value[0] = pos_slope[0].first - a[0];
    }
    for (int i = 1; i < n; ++i) {
        if (i & 1) value[i] -= value[0];
        else value[i] += value[0];
    }
    for (int i = 0; i < n; ++i) {
        cout << value[i] << " \n"[i + 1 == n];
    }
    return 0;
}