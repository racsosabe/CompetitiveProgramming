#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;

long long a, k;

long long mul(long long a, long long b){
	return (a * b) % MOD;
}

long long pow_mod(long long a, long long b){
	long long r = 1;
	while(b > 0){
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int main(){
	scanf("%lld %lld", &a, &k);
	a %= MOD;
	if(a == 1) printf("%lld\n", (k + 1) % MOD);
	else{
		long long ans = mul((pow_mod(a, k + 1) + MOD - 1) % MOD, pow_mod(a + MOD - 1, MOD - 2));
		printf("%lld\n", ans);
	}
	return 0;
}
