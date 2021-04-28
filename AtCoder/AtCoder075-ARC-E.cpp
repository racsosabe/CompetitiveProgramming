#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- If you want to count the number of subarrays with mean >= x, just notice that

	  sum(a[l], a[l + 1], ..., a[r]) / (r - l + 1) >= x implies

	  sum(a[l], a[l + 1], ..., a[r]) >= (r - l + 1) * x
	  sum(a[l] - x, a[l + 1] - x, ..., a[r] - x) >= 0

	  so we can work with a new array a'[i] = a[i] - x;
	  
	- After this, just count the number of subarrays with sum greater than or equal to 0.

	- Complexity: O(nlogn)
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r){
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node{
	int cnt;
	int frec;
	int priority;
	long long val;
	node* left;
	node* right;
	node(long long val, int cnt) : val(val), cnt(cnt) {
		frec = cnt;
		left = right = nullptr;
		priority = random(0, 2e9);
	}
};

const int N = 200000 + 5;

int n;
int k;
int a[N];
node* T;

int cnt(node* t){
	return t ? t -> cnt : 0;
}

void update(node* t){
	if(t) t -> cnt = cnt(t -> left) + t -> frec + cnt(t -> right);
}

pair<node*, node*> split(node* u, long long x){
	if(u == nullptr) return {nullptr, nullptr};
	if(u -> val <= x){
		pair<node*, node*> p = split(u -> right, x);
		u -> right = p.first;
		update(u);
		return {u, p.second};
	}
	else{
		pair<node*, node*> p = split(u -> left, x);
		u -> left = p.second;
		update(u);
		return {p.first, u};
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

node* insert(node* u, long long val){
	pair<node*, node*> p = split(u, val);
	pair<node*, node*> p2 = split(p.first, val - 1);
	int new_frec = cnt(p2.second) + 1;
	u = merge(p2.first, new node(val, new_frec));
	u = merge(u, p.second);
	return u;
}

node* getLeq(node* u, long long val, int &res){
	pair<node*, node*> p = split(u, val);
	res = cnt(p.first);
	u = merge(p.first, p.second);
	return u;
}

long long solve(){
	T = insert(T, 0);
	long long ans = 0;
	long long prefix = 0;
	for(int i = 1; i <= n; i++){
		prefix += a[i];
		int act;
		T = getLeq(T, prefix, act);
		ans += act;
		T = insert(T, prefix);
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
		a[i] -= k;
	}
	printf("%lld\n", solve());
	return 0;
}
