#include<bits/stdc++.h>
using namespace::std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int cnt;
	int val;
	int priority;
	node* left;
	node* right;
	node(int val) : val(val) {
		cnt = 1;
		priority = random(0, 1e9);
		left = right = nullptr;
	}
};

const int N = 30000 + 5;

int n;
int q;
node* T;
int a[N];
int u[N];

int cnt(node* t){
	return t ? t -> cnt : 0;
}

void update(node* t){
	if(t) t -> cnt = cnt(t -> left) + cnt(t -> right) + 1;
}

pair<node*, node*> split(node* t, int x){
	if(t == nullptr){
		return {nullptr, nullptr};
	}
	if(t -> val <= x){
		pair<node*, node*> p = split(t -> right, x);
		t -> right = p.first;
		update(t);
		return {t, p.second};
	}
	else{
		pair<node*, node*> p = split(t -> left, x);
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

node* insert(node* u, int val){
	pair<node*, node*> p = split(u, val);
	u = merge(p.first, new node(val));
	u = merge(u, p.second);
	return u;
}

int get(node* u, int k){
	if(cnt(u -> left) + 1 == k) return u -> val;
	if(cnt(u -> left) + 1 < k) return get(u -> right, k - cnt(u -> left) - 1);
	return get(u -> left, k);
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		T = nullptr;
		scanf("%d %d", &n, &q);
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i <= q; i++) scanf("%d", &u[i]);
		int k = 0;
		int pos = 1;
		for(int i = 1; i <= n; i++){
			T = insert(T, a[i]);
			while(pos <= q and u[pos] == i){
				k += 1;
				printf("%d\n", get(T, k));
				pos += 1;
			}
		}
		if(t) puts("");
	}
	return 0;
}
