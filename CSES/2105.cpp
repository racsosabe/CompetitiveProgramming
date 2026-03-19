/**
 * File: 2105.cpp
 * Author: racsosabe
 * Date: 19/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> compute_counts(int k, vector<int> &s) {
    vector<int> res(k, 0);
    for (auto &x : s) {
        ++res[x];
    }
    return res;
}

vector<int> compute_buckets(int k, vector<int> &s, bool end) {
    vector<int> res = compute_counts(k, s);
    int sum = 0;
    if (end) {
        for (int i = 0; i < k; ++i) {
            sum += res[i];
            res[i] = sum - 1;
        }
    }
    else {
        for (int i = 0; i < k; ++i) {
            sum += res[i];
            res[i] = sum - res[i];
        }
    }
    return res;
}

void induce(int k, vector<int> &X, vector<int> &A, vector<int> &s, vector<int> &type) {
    const int n = A.size();
    fill(A.begin(), A.end(), 0);
    vector<int> R = compute_buckets(k, s, true);
    for (int i = X.size() - 1; i >= 0; --i) {
        int c = s[X[i]];
        A[R[c]--] = X[i];
    }
    vector<int> L =  compute_buckets(k, s, false);
    for (int i = 0; i < n; ++i) {
        if (A[i] > 0 and type[A[i] - 1] == 1) {
            int c = s[A[i] - 1];
            A[L[c]++] = A[i] - 1;
        }
    }
    R = compute_buckets(k, s, true);
    for (int i = n - 1; i >= 0; --i) {
        if (A[i] > 0 and type[A[i] - 1] % 2 == 0) {
            int c = s[A[i] - 1];
            A[R[c]--] = A[i] - 1;
        }
    }
}

vector<int> SAIS(vector<int> &s, int k) {
    const int n = s.size();

    if (n <= 1) return {0};
    vector<int> type(n);
    type[n - 1] = 0;
    for (int i = n - 2; i >= 0; --i) {
        if (s[i] == s[i + 1]) type[i] = type[i + 1];
        else type[i] = s[i] > s[i + 1];
    }
    for (int i = 1; i < n; ++i) {
        if (type[i] == 0 and type[i - 1] == 1) {
            type[i] = 2;
        }
    }
    vector<int> C = compute_buckets(k, s, false);
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        int c = s[i];
        A[C[c]++] = i;
    }
    vector<int> X;
    for (auto &x : A) {
        if (type[x] == 2) X.emplace_back(x);
    }
    induce(k, X, A, s, type);
    int ptr = 0;
    for (auto &x : A) {
        if (type[x] == 2) X[ptr++] = x;
    }
    vector<int> mapping(n);
    int names = 0;
    mapping[X[0]] = names++;
    for (int k = 1; k < X.size(); ++k) {
        int i = X[k - 1];
        int j = X[k];
        int len = 0;
        while (i + len < n and j + len < n and s[i + len] == s[j + len] and type[i + len] == type[j + len]) {
            if (len > 0) {
                if (type[i + len] == 2 or type[j + len] == 2) break;
            }
            ++len;
        }
        if (len > 0 and i + len < n and type[i + len] == 2 and j + len < n and type[j + len] == 2) {
            mapping[X[k]] = mapping[X[k - 1]];
        }
        else {
            mapping[X[k]] = names++;
        }
    }
    ptr = 0;
    for (int i = 0; i < n; i++) {
        if (type[i] == 2) X[ptr++] = i;
    }
    vector<int> reduced(X.size());
    for (int i = 0; i < X.size(); i++) {
        reduced[i] = mapping[X[i]];
    }
    vector<int> SA1;
    if (names < X.size()) {
        SA1 = SAIS(reduced, names);
    }
    else {
        SA1.resize(names);
        for (int i = 0; i < names; i++) {
            SA1[reduced[i]] = i;
        }
    }
    for (auto &x : SA1) {
        x = X[x];
    }
    induce(k, SA1, A, s, type);
    return A;
}

vector<int> lcp_array(vector<int> &s, vector<int> &a) {
    const int n = s.size();
    vector<int> rnk(n);
    for (int i = 0; i < n; ++i) {
        rnk[a[i]] = i;
    }
    int k = 0;
    vector<int> lcp(n - 1, 0);
    for (int i = 0; i < n; ++i) {
        if (rnk[i] + 1 == n) {
            k = 0;
            continue;
        }
        int j = a[rnk[i] + 1];
        while (i + k < n and j + k < n and s[i + k] == s[j + k]) ++k;
        lcp[rnk[i]] = k;
        if (k) --k;
    }
    return lcp;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    string s;
    cin >> s;
    vector<int> S(s.size() + 1, 0);
    for (int i = 0; i < s.size(); ++i) {
        S[i] = s[i] - 'a' + 1;
    }
    vector<int> a = SAIS(S, 27);
    vector<int> lcp = lcp_array(S, a);
    cout << 1ll * s.size() * (s.size() + 1) / 2 - accumulate(lcp.begin(), lcp.end(), 0LL) << endl;
    return 0;
}