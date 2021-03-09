#include<bits/stdc++.h>
using namespace::std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int val;
	int cnt;
	int priority;
	node* left;
	node* right;
	node(int val) : val(val) {
		cnt = 1;
		priority = random(0, 1e9);
		left = right = nullptr;
	}
};

int n;
node* T;

int cnt(node* t){
	return t ? t -> cnt : 0;
}

void update(node* t){
	if(t) t -> cnt = cnt(t -> left) + cnt(t -> right) + 1;
}

pair<node*, node*> split(node* t, int x, int add = 0){
	if(t == nullptr){
		return {nullptr, nullptr};
	}
	int key = add + cnt(t -> left) + 1;
	if(key <= x){
		pair<node*, node*> p = split(t -> right, x, key);
		t -> right = p.first;
		update(t);
		return {t, p.second};
	}
	else{
		pair<node*, node*> p = split(t -> left, x, add);
		t -> left = p.second;
		update(t);
		return {p.first, t};
	}
}

node* merge(node* l, node* r){
	if(l == nullptr) return r;
	if(r == nullptr) return l;
	if(l -> priority > r -> priority){
		l -> right = merge(l -> right, r);
		update(l);
		return l;
	}
	else{
		r -> left = merge(l, r -> left);
		update(r);
		return r;
	}
}

node* add(node* u, int val){
	u = merge(u, new node(val));
	return u;
}

void DFS(node* u){
	if(u == nullptr) return;
	DFS(u -> left);
	printf("%d ", u -> val);
	DFS(u -> right);
}

node* swap(node* u, int a, int b){
	int len = min(b - a, n - b + 1);
	pair<node*, node*> p1 = split(u, b + len - 1);
	pair<node*, node*> p2 = split(p1.first, b - 1);
	pair<node*, node*> p3 = split(p2.first, a + len - 1);
	pair<node*, node*> p4 = split(p3.first, a - 1);
	u = merge(p4.first, p2.second);
	u = merge(u, p3.second);
	u = merge(u, p4.second);
	u = merge(u, p1.second);
	return u;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		T = add(T, i);
	}
	for(int i = 1; i <= n; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		if(a > b) continue;
		T = swap(T, a, b);
	}
	DFS(T);
	puts("");
	return 0;
}
