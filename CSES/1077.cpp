/**
 * File: 1077.cpp
 * Author: racsosabe
 * Date: 4/04/2026
 */

#include <bits/stdc++.h>
using namespace std;


template<typename key_type, class Compare = std::less<key_type>>
struct sum_priority_queue {
    int cnt;
    long long sum;
    multiset<key_type, Compare> pq;

    sum_priority_queue() {
        cnt = sum = 0;
        pq = multiset<key_type, Compare>();
    }

    void push(key_type key) {
        ++cnt;
        sum += key;
        pq.emplace(key);
    }

    key_type top() {
        return *pq.rbegin();
    }

    void pop() {
        if (not empty()) {
            --cnt;
            sum -= top();
            pq.erase(pq.find(*pq.rbegin()));
        }
    }

    void erase(key_type key) {
        --cnt;
        sum -= key;
        pq.erase(pq.find(key));
    }

    bool contains(key_type key) {
        return pq.find(key) != pq.end();
    }

    bool empty() {
        return cnt == 0;
    }

    long long get_sum() {
        return sum;
    }

    int size() {
        return cnt;
    }
};

sum_priority_queue<int> L;
sum_priority_queue<int, greater<int>> R;

void insert(int x) {
    L.push(x);
}

void erase(int x) {
    if (L.contains(x)) {
        L.erase(x);
    }
    else {
        R.erase(x);
    }
}

long long distance_sum() {
    if (L.empty() and R.empty()) return -1;
    while (not L.empty() and not R.empty() and L.top() > R.top()) {
        R.push(L.top());
        L.pop();
    }
    while (L.size() > R.size()) {
        R.push(L.top());
        L.pop();
    }
    while (L.size() <= R.size()) {
        L.push(R.top());
        R.pop();
    }

    int who = L.top();
    int l_cnt = L.size();
    int r_cnt = R.size();
    return 1ll * who * l_cnt - L.get_sum() + R.get_sum() - 1ll * who * r_cnt;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (i >= k) erase(a[i - k]);
        cin >> a[i];
        insert(a[i]);
        if (i >= k - 1) {
            cout << distance_sum() << " \n"[i + 1 == n];
        }
    }
    return 0;
}
