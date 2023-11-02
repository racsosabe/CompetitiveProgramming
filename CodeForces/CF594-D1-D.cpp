#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;
const int MAX = 1000000 + 5;
const int N = 200000 + 5;

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int pow_mod(int a, int b){
	int r = 1;
	while(b > 0){
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int n;
int q;
int a[N];
int L[N];
int f[MAX];
int ans[N];
int fi[MAX];
int pf[MAX];
int last[MAX];
int st[4 * N];
int prefix[N];
int prefixi[N];
vector<int> Q[N];
vector<int> primes;
bool composite[MAX];

void init(){
	for(int i = 2; i < MAX; i++){
		if(not composite[i]){
			pf[i] = i;
			primes.emplace_back(i);
		}
		for(int p : primes){
			if(i * p >= MAX) break;
			composite[i * p] = true;
			pf[i * p] = p;
			if(i % p == 0) break;
		}
	}
	f[0] = 1;
	for(int i = 1; i < MAX; i++) f[i] = mul(i, f[i - 1]);
	fi[MAX - 1] = pow_mod(f[MAX - 1], MOD - 2);
	for(int i = MAX - 2; i >= 0; i--) fi[i] = mul(i + 1, fi[i + 1]);
}

void preprocess(){
	prefix[0] = 1;
	for(int i = 1; i <= n; i++) prefix[i] = mul(prefix[i - 1], a[i]);
	for(int i = 0; i <= n; i++) prefixi[i] = pow_mod(prefix[i], MOD - 2);
}

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = 1;
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = mul(st[2 * pos], st[2 * pos + 1]);
}

void update(int x, int y, int pos = 1, int l = 1, int r = n){
	if(x < l or x > r) return;
	if(l == r){
		st[pos] = mul(st[pos], y);
		return;
	}
	int mi = (l + r) / 2;
	if(x <= mi) update(x, y, 2 * pos, l, mi);
	else update(x, y, 2 * pos + 1, mi + 1, r);
	st[pos] = mul(st[2 * pos], st[2 * pos + 1]);
}

int query(int x, int y, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return 1;
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return mul(query(x, y, 2 * pos, l, mi), query(x, y, 2 * pos + 1, mi + 1, r));
}

void modify(int pos){
	int x = a[pos];
	while(x != 1){
		int fact = pf[x];
		while(x % fact == 0) x /= fact;
		int val = mul(fact - 1, mul(fi[fact], f[fact - 1]));
		update(last[fact] + 1, val);
		update(pos + 1, pow_mod(val, MOD - 2));
		last[fact] = pos;
	}
}

int main(){
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	scanf("%d", &q);
	preprocess();
	for(int i = 1; i <= q; i++){
		int r;
		scanf("%d %d", L + i, &r);
		ans[i] = mul(prefix[r], prefixi[L[i] - 1]);
		Q[r].emplace_back(i);
	}
	build();
	for(int i = 1; i <= n; i++){
		modify(i);
		for(int at : Q[i]){
			ans[at] = mul(ans[at], query(1, L[at]));
		}
	}
	for(int i = 1; i <= q; i++) printf("%d\n", ans[i]);
	return 0;
}
