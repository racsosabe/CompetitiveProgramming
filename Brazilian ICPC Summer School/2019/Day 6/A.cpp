#include<bits/stdc++.h>
using namespace::std;

int n;
int k;
int m;

int mul(int a, int b){
	return (1ll * a * b) % m;
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

int phi(int x){
	int ans = x;
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0){
			while(x % i == 0) x /= i;
			ans -= ans / i;
		}
	}
	if(x > 1){
		ans -= ans / x;
	}
	return ans;
}

int get(){
	int mod = phi(m);
	int res = 1;
	for(int i = 2; i <= k; i++){
		res = (res << 1) + 1;
		if(res >= mod) res %= mod;
	}
	return res;
}

int main(){
	scanf("%d %d %d", &n, &k, &m);
	int ans = 0;
	int e = get();
	for(int i = 1; i <= n; i++){
		ans += pow_mod(i, e);
		if(ans >= m) ans -= m;
	}
	printf("%d\n", ans);
	return 0;
}
