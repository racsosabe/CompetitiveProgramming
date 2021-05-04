#include<bits/stdc++.h>
using namespace::std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int key;
	int val;
	int mini;
	int priority;
	node* left;
	node* right;
	node(int key, int val) : key(key), val(val), mini(val) {
		priority = random(0, 1e9);
		left = right = nullptr;
	}
};	

const int N = 100000 + 5;
const int E = 26;

int n;
int m;
char a[N];
char b[N];
int pref[N];
int suff[N];
int nxt[E][N];
int prv[E][N];

void preprocess(){
	for(int i = 0; i < E; i++) nxt[i][n + 1] = n + 1;
	for(int i = n; i >= 1; i--){
		for(int j = 0; j < E; j++) nxt[j][i] = nxt[j][i + 1];
		nxt[a[i] - 'a'][i] = i;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < E; j++) prv[j][i] = prv[j][i - 1];
		prv[a[i] - 'a'][i] = i;
	}
	for(int i = 1; i <= m; i++){
		if(pref[i - 1] == n + 1) pref[i] = n + 1;
		else pref[i] = nxt[b[i] - 'a'][pref[i - 1] + 1];
	}
	suff[m + 1] = n + 1;
	for(int i = m; i >= 1; i--){
		if(suff[i + 1] == 0) suff[i] = 0;
		else suff[i] = prv[b[i] - 'a'][suff[i + 1] - 1];
	}
}

int getMin(node* t){
	return t ? t -> mini : INT_MAX;
}

void update(node* t){
	if(t) t -> mini = min({getMin(t -> left), t -> val, getMin(t -> right)});
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
	if(t -> key <= x){
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

node* insert(node* u, int key, int val){
	pair<node*, node*> p = split(u, key);
	pair<node*, node*> p2 = split(p.first, key - 1);
	u = merge(p2.first, new node(key, val));
	u = merge(u, p.second);
	return u;
}

node* get(node* u, int key, int &res){
	pair<node*, node*> p = split(u, key);
	res = getMin(p.second);
	u = merge(p.first, p.second);
	return u;
}

void solve(){
	node* T = nullptr;
	int l = 0;
	int r = m + 1;
	set<int> used;
	map<int, int> best;
	T = insert(T, n + 1, m + 1);
	for(int i = m; i >= 0; i--){
		int nr;
		T = get(T, pref[i], nr);
		if(nr - i - 1 < r - l - 1){
			l = i;
			r = nr;
		}
		T = insert(T, suff[i], i);
	}
	if(l == 0 and r == m + 1) puts("-");
	else{
		for(int i = 1; i <= m; i++){
			if(i <= l or r <= i) putchar(b[i]);
		}
		putchar('\n');
	}
}

int main(){
	scanf("%s", a + 1);
	scanf("%s", b + 1);
	n = strlen(a + 1);
	m = strlen(b + 1);
	preprocess();
	solve();
	return 0;
}
