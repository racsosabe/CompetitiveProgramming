#include<bits/stdc++.h>
using namespace::std;

const int MOD = 998244353;

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int pow_mod(int a, long long b){
	int r = 1;
	while(b > 0){
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

long long w, l;

int main(){
	scanf("%lld %lld", &w, &l);
	int ans = pow_mod(2, w + l);
	printf("%d\n", ans);
	return 0;
}
