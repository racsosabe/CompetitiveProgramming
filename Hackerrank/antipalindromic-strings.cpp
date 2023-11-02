#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;

inline int mul(int a, int b){
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

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		int n, m;
		scanf("%d %d", &n, &m);
		int ans = m;
		if(n > 1) ans = mul(ans, m - 1);
		if(n > 2) ans = mul(ans, pow_mod(m - 2, n - 2));
		printf("%d\n", ans);
	}
	return 0;
}
