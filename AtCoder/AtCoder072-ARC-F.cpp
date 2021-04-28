#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int cnt;
	int val;
	int frec;
	int priority;
	long long suma;
	node* left;
	node* right;
	node(int val, int frec = 1) : val(val), frec(frec) {
		priority = random(0, 1e9);
		suma = 1ll * val * frec;
		cnt = frec;
		left = right = nullptr;
	}
};

int n;
int L;
node* T;
int v[N];
int t[N];
long double ans[N];

int cnt(node* t){
	return t ? t -> cnt : 0;
}

long long suma(node* t){
	return t ? t -> suma : 0;
}

void update(node* t){
	if(t){
		t -> cnt = cnt(t -> left) + t -> frec + cnt(t -> right);
		t -> suma = suma(t -> left)  + t -> suma + suma(t -> right);
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

pair<node*, node*> split(node* t, int x){
	if(t == nullptr) return {nullptr, nullptr};
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

node* insert(node* u, int val, int frec){
	pair<node*, node*> p = split(u, val);
	pair<node*, node*> p2 = split(p.first, val - 1);
	int new_frec = frec + cnt(p2.second);
	u = merge(p2.first, new node(val, new_frec));
	u = merge(u, p.second);
	return u;
}

long long get(node* u, int k){
	int left_subtree = cnt(u -> left);
	if(left_subtree >= k) return get(u -> left, k);
	int cur_pos = left_subtree + u -> frec;
	if(cur_pos >= k) return suma(u -> left) + 1ll * (k - left_subtree) * u -> val;
	return suma(u -> left) + u -> suma + get(u -> right, k - cur_pos);
}

void DFS(node* u){
	if(u == nullptr) return;
	DFS(u -> left);
	cout << u -> val << " " << u -> frec << " " << u -> suma << " " << u -> cnt << endl;
	DFS(u -> right);
}

void solve(){
	ans[1] = t[1];
	T = insert(T, -t[1], v[1]);
	for(int i = 2; i <= n; i++){
		long long max_suma;
		DFS(T);
		max_suma = get(T, L - v[i]);
		cout << i << " " << max_suma << endl;
		ans[i] = (1.0 * t[i] * v[i] - max_suma) / L;
		T = insert(T, -t[i], v[i]);
	}
}

int main(){
	scanf("%d %d", &n, &L);
	for(int i = 1; i <= n; i++){
		scanf("%d %d", t + i, v + i);
	}
	solve();
	for(int i = 1; i <= n; i++){
		printf("%.10Lf\n", ans[i]);
	}
	return 0;
}
