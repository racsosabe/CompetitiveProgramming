/**
 * File: project_3.cpp
 * Author: racsosabe
 * Date: 1/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

struct node {
    int size;
    long long value;
    long long minimum;
    int priority;
    node* left;
    node* right;
    long long add_lazy;
    bool reversed_lazy;
    node (long long value) : value(value), minimum(value), size(1), priority(random(0, 1e9)), reversed_lazy(false), add_lazy(0) {
        left = right = nullptr;
    }
};

int size(node* t) {
    return t ? t -> size : 0;
}

long long minimum(node* t) {
    return t ? t -> minimum + t -> add_lazy : LLONG_MAX;
}

void update(node* t) {
    if (t) {
        t -> minimum = min(t -> value, min(minimum(t -> left), minimum(t -> right)));
        t -> size = 1 + size(t -> left) + size(t -> right);
    }
}

void push(node* t) {
    if (t) {
        if (t -> add_lazy) {
            t -> value += t -> add_lazy;
            t -> minimum += t -> add_lazy;
            if (t -> left) {
                t -> left -> add_lazy += t -> add_lazy;
            }
            if (t -> right) {
                t -> right -> add_lazy += t -> add_lazy;
            }
            t -> add_lazy = 0;
        }
        if (t -> reversed_lazy) {
            swap(t -> left, t -> right);
            if (t -> left) {
                t -> left -> reversed_lazy ^= true;
            }
            if (t -> right) {
                t -> right -> reversed_lazy ^= true;
            }
            t -> reversed_lazy = false;
        }
    }
}

pair<node*, node*> split(node* t, int key, int add = 0) {
    if (t == nullptr) return {nullptr, nullptr};
    push(t);
    int cur_key = add + size(t -> left) + 1;
    if (cur_key <= key) {
        pair<node*, node*> p = split(t -> right, key, cur_key);
        t -> right = p.first;
        update(t);
        return {t, p.second};
    }
    else {
        pair<node*, node*> p = split(t -> left, key, add);
        t -> left = p.second;
        update(t);
        return {p.first, t};
    }
}

node* merge(node* l, node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    push(l);
    push(r);
    if (l -> priority > r -> priority) {
        l -> right = merge(l -> right, r);
        update(l);
        return l;
    }
    else {
        r -> left = merge(l, r -> left);
        update(r);
        return r;
    }
}

node* T = nullptr;

node* add_range(node* t, int l, int r, int x) {
    pair<node*, node*> p = split(t, r);
    pair<node*, node*> p2 = split(p.first, l - 1);
    if (p2.second) {
        p2.second -> add_lazy += x;
    }
    t = merge(p2.first, p2.second);
    t = merge(t, p.second);
    return t;
}

node* reverse(node* t, int l, int r) {
    pair<node*, node*> p = split(t, r);
    pair<node*, node*> p2 = split(p.first, l - 1);
    if (p2.second) {
        p2.second -> reversed_lazy ^= true;
    }
    t = merge(p2.first, p2.second);
    t = merge(t, p.second);
    return t;
}

node* rotate(node* t, int k) {
    pair<node*, node*> p = split(t, size(t) - k);
    t = merge(p.second, p.first);
    return t;
}

node* rotate(node* t, int l, int r, int k) {
    k %= (r - l + 1);
    pair<node*, node*> p = split(t, r);
    pair<node*, node*> p2 = split(p.first, l - 1);
    p2.second = rotate(p2.second, k);
    t = merge(p2.first, p2.second);
    t = merge(t, p.second);
    return t;
}

node* insert(node* t, int k, int x) {
    pair<node*, node*> p = split(t, k);
    t = merge(p.first, new node(x));
    t = merge(t, p.second);
    return t;
}

node* remove(node* t, int k) {
    pair<node*, node*> p = split(t, k);
    pair<node*, node*> p2 = split(p.first, k - 1);
    t = merge(p2.first, p.second);
    return t;
}

node* get_min(node* t, int l, int r, long long &res) {
    pair<node*, node*> p = split(t, r);
    pair<node*, node*> p2 = split(p.first, l - 1);
    res =  minimum(p2.second);
    t = merge(p2.first, p2.second);
    t = merge(t, p.second);
    return t;
}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        T =  merge(T, new node(x));
    }
    int q;
    cin >> q;
    while (q--) {
        string op;
        cin >> op;
        if (op == "ADD") {
            int x, y, d;
            cin >> x >> y >> d;
            T = add_range(T, x, y, d);
        }
        else if (op == "REVERSE") {
            int l, r;
            cin >> l >> r;
            T = reverse(T, l, r);
        }
        else if (op == "REVOLVE") {
            int l, r, k;
            cin >> l >> r >> k;
            T = rotate(T, l, r, k);
        }
        else if (op == "INSERT") {
            int k, x;
            cin >> k >> x;
            T = insert(T, k, x);
        }
        else if (op == "DELETE") {
            int k;
            cin >> k;
            T = remove(T, k);
        }
        else {
            int l, r;
            long long res;
            cin >> l >> r;
            T = get_min(T, l, r, res);
            cout << res << '\n';
        }
    }
    return 0;
}