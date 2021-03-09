#include<bits/stdc++.h>
using namespace::std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

const int B = 311;
const int N = 6000000 + 5;
const int MOD = 1000000000 + 99999;

int add(int a, int b){
	return a + b < MOD ? a + b : a + b - MOD;
}

int mul(int a, int b){
	return (1LL * a * b) % MOD;
}

struct node{
	int Hlr;
	int Hrl;
	int cnt;
	int priority;
	node* left;
	node* right;
	node(char c) {
		int val = c - 'a' + 1;
		Hlr = Hrl = val;
		cnt = 1;
		priority = random(0, 1e9);
		left = right = nullptr;
	}
};

int n;
int q;
node* T;
char s[N];
int pot[N];
int poti[N];

void init(){
	pot[0] = 1;
	for(int i = 1; i < N; i++) pot[i] = mul(B, pot[i - 1]);
	poti[N - 1] = pow_mod(pot[N - 1], MOD - 2);
	for(int i = N - 2; i >= 0; i--){
		poti[i] = mul(B, poti[i + 1]);
	}
}

int cnt(node* t){
	return t ? t -> cnt : 0;
}

int Hlr(node* t){
	return t ? t -> Hlr : 0;
}

int Hrl(node* t){
	return t ? t -> Hrl : 0;
}

void update(node* t){
	if(t){
		t -> cnt = cnt(t -> left) + cnt(t -> right) + 1;
		t -> Hlr = add(add(Hlr(t -> left), mul(pot[cnt(t -> left)], t -> val)), mul(pot[cnt(t -> left) + 1], Hlr(t -> right)));
		t -> Hrl = add(add(Hrl(t -> left), mul(poti[cnt(t -> left)], t -> val)), mul(pot[cnt(t -> left) + 1], Hrl(t -> right)));
	}
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
		udpate(t);
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

int main(){
	init();
	scanf("%d %d", &n, &q);
	scanf("%s", s);
	build();
	int op;
	while(q--){
		scanf("%d", &op);
		if(op == 1){
			int l, r;
			scanf("%d %d", &l, &r);
			T = del(T, l, r);
		}
		else if(op == 2){
			int p;
			char c = getchar();
			while(!isalpha(c)) c = getchar();
			scanf("%d", &p);
			T = insert(T, p, c);
		}
		else{
			int l, r;
			scanf("%d %d", &l, &r);
			puts(check(T, l, r) ? "yes" : "no");
		}
	}
	return 0;
}
