#include<bits/stdc++.h>
using namespace::std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int lazy;
	int add;
	int pos;
	int rev;
	int cnt;
	int priority;
	node* left;
	node* right;
	node(int pos) : pos(pos) {
		priority = random(0, 1e9);
		add = lazy = 0;
		rev = 0;
		cnt = 1;
		left = right = nullptr;
	};
};

int cnt(node* t){
	return t ? t -> cnt : 0;
}

void update(node* t){
	if(t) t -> cnt = cnt(t -> left) + cnt(t -> right) + 1;
}

void push(node* t){
	if(t){
		if(t -> lazy){
			t -> add = (t -> add + t -> lazy) % 26;
			if(t -> left) t -> left -> lazy = (t -> left -> lazy + t -> lazy) % 26;
			if(t -> right) t -> right -> lazy = (t -> right -> lazy + t -> lazy) % 26;
			t -> lazy = 0;
		}
		if(t -> rev){
			t -> rev = 0;
			swap(t -> left, t -> right);
			if(t -> left) t -> left -> rev ^= 1;
			if(t -> right) t -> right -> rev ^= 1;
		}
	}
}

node* merge(node* l, node* r){
	if(l == nullptr) return r;
	if(r == nullptr) return l;
	push(l);
	push(r);
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

pair<node*, node*> split(node* t, int key, int add = 0){
	if(t == nullptr) return {nullptr, nullptr};
	push(t);
	int cur_key = add + cnt(t -> left) + 1;
	if(cur_key <= key){
		pair<node*, node*> p = split(t -> right, key, cur_key);
		t -> right = p.first;
		update(t);
		return {t, p.second};
	}
	else{
		pair<node*, node*> p = split(t -> left, key, add);
		t -> left = p.second;
		update(t);
		return {p.first, t};
	}
}

const int N = 100000 + 5;

int n;
int q;
node* T;
char s[N];

void init(){
	T = nullptr;
	for(int i = 0; i < n; i++){
		T = merge(T, new node(i));
	}
}

void DFS(node* t){
	if(t){
		push(t);
		DFS(t -> left);
		int val = (s[t -> pos] - 'a' + t -> add) % 26;
		putchar('a' + val);
		DFS(t -> right);
	}
}

void change(int l1, int r1, int l2, int r2){
	pair<node*, node*> p1 = split(T, r2);
	pair<node*, node*> p2 = split(p1.first, l2 - 1);
	pair<node*, node*> p3 = split(p2.first, r1);
	pair<node*, node*> p4 = split(p3.first, l1 - 1);
	p2.second -> rev ^= 1;
	p2.second -> lazy += 1;
	p4.second -> rev ^= 1;
	p4.second -> lazy += 1;
	T = merge(p4.first, p2.second);
	T = merge(T, p3.second);
	T = merge(T, p4.second);
	T = merge(T, p1.second);
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%s %d", s, &q);
		n = strlen(s);
		init();
		while(q--){
			int l1, r1, l2, r2;
			scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
			change(l1, r1, l2, r2);
		}
		DFS(T);
		puts("");
	}
	return 0;
}
