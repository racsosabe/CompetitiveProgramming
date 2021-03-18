#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;

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

const int N = 100000 + 5;

int n;
int k;
int par[N];
int sizes[N];

int get(int x){
	return par[x] == x ? x : par[x] = get(par[x]);
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
}

int solve(int shift){
	for(int i = 0; i < n; i++){
		par[i] = i;
		sizes[i] = 1;
	}
	for(int i = 0; i < n - 1 - i; i++) join(i, n - i - 1);
	for(int i = 0; i < n; i++){
		int j = (i + shift) % n;
		join(i, j);
	}
	int ans = 1;
	for(int i = 0; i < n; i++){
		if(par[i] == i) ans = mul(ans, k);
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &k);
	int ans = 0;
	for(int i = 0; i < n; i++){
		cout << i << " " << solve(i) << endl;
		ans += solve(i);
		if(ans >= MOD) ans -= MOD;
	}
	cout << ans << endl;
	ans = mul(ans, pow_mod(n, MOD - 2));
	printf("%d\n", ans);
	return 0;
}
