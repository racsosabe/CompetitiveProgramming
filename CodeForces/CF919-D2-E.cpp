#include<bits/stdc++.h>
using namespace::std;

int mul(int a, int b, int m){
	return (1ll * a * b) % m;
}

int pow_mod(int a, int b, int m){
	int r = 1;
	while(b > 0){
		if(b & 1) r = mul(r, a, m);
		a = mul(a, a, m);
		b >>= 1;
	}
	return r;
}

int a;
int b;
int p;
long long x;

typedef long long ll;

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (b) { ll d = euclid(b, a % b, y, x);
		return y -= a/b * x, d; }
	return x = 1, y = 0, a;
}

ll crt(ll a, ll m, ll b, ll n) {
	if (n > m) swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	if((a - b) % g) return -1;
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m*n/g : x;
}

int main(){
	scanf("%d %d %d %lld", &a, &b, &p, &x);
	int pa = 1;
	long long ans = 0;
	long long M = 1ll * p * (p - 1);
	for(int r = 0; r < p - 1; r++){
		int r2 = mul(b, pow_mod(pa, p - 2, p), p);
		long long X = crt(r, p - 1, r2, p);
		pa = mul(pa, a, p);
		if(X == -1) continue;
		if(X > x) continue;
		ans += (x - X) / M + 1;
	}
	printf("%lld\n", ans);
	return 0;
}
