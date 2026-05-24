/**
 * File: persistent_queue.cpp
 * Author: racsosabe
 * Date: 1/05/2026
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v, Node* n) : val(v), next(n) {}
};

using List = Node*;

// hash por puntero (clave)
unordered_map<List, List> rev_cache;

List reverse_list(List s) {
    if (!s) return nullptr;
    if (rev_cache.count(s)) return rev_cache[s];

    List cur = s;
    List res = nullptr;

    while (cur) {
        res = new Node(cur->val, res);
        cur = cur->next;
    }

    return rev_cache[s] = res;
}

struct Queue {
    List front, back;

    Queue(List f = nullptr, List b = nullptr) : front(f), back(b) {}

    bool empty() const {
        return !front && !back;
    }

    Queue push(int x) const {
        return Queue(front, new Node(x, back));
    }

    pair<int, Queue> pop() const {
        if (front) {
            return {front->val, Queue(front->next, back)};
        }
        if (!back) {
            throw runtime_error("pop from empty");
        }

        List new_front = reverse_list(back);

        return {
            new_front->val,
            Queue(new_front->next, nullptr)
        };
    }
};
/*
struct PersistentStack {
    int nodes;
    vector<int> nxt;
    vector<int> val;
    vector<int> root;
    PersistentStack() {
        root.emplace_back(add_node(-1, 0));
    }

    int add_node(int next, int value) {
        val.emplace_back(value);
        nxt.emplace_back(next);
        return (int)nxt.size() - 1;
    }

    int push(int k, int x) {
        root.emplace_back(add_node(root[k], x));
        return root.back();
    }

    int pop(int k) {
        return nxt[root[k]];
    }

    int top(int k) {
        return val[root[k]];
    }
};

struct PersistentQueue {
    PersistentStack in, out;
    vector<pair<int, int>> popped;
    vector<pair<int, int>> root;
    PersistentQueue() {
        popped.emplace_back(0, 0);
        root.emplace_back(0, 0);
    }

    void push(int k, int x) {
        int in_version, out_version;
        tie(in_version, out_version) = root[k];
        popped.emplace_back(-1, -1);
        root.emplace_back(in.push(in_version, x), out_version);
    }

    int pop(int k) {
        int in_version, out_version;
        popped.emplace_back(-1, -1);
        if (~popped[k].first) {
            tie(in_version, out_version) = popped[k];
            root.emplace_back(in_version, out_version);
        }
        else {
            tie(in_version, out_version) = root[k];
            while (in_version > 0) {
                out_version = out.push(in.top(in_version));
                in_version = in.pop(in_version);
            }
            int value = ;
            root.emplace_back(in_version, out_version);
        }
    }
};*/

int main() {
    cin.tie(0)->sync_with_stdio(false);
    vector<Queue> versions;
    versions.emplace_back();
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int k, x;
            cin >> k >> x;
            ++k;
            versions.emplace_back(versions[k].push(x));
        }
        else {
            int k;
            cin >> k;
            ++k;
            int res;
            Queue cur_queue;
            tie(res, cur_queue) = versions[k].pop();
            versions.emplace_back(cur_queue);
            cout << res << '\n';
        }
    }
    return 0;
}
