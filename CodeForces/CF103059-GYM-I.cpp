#include<bits/stdc++.h>
using namespace::std;

const int N = 500000 + 5;

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

int n;
int f[N];
int p[N];
int fi[N];

bool prime(int x){
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0) return false;
	}
	return true;
}

void init(){
	f[0] = 1;
	for(int i = 1; i < n; i++) f[i] = mul(i, f[i - 1], n);
	fi[n - 1] = pow_mod(f[n - 1], n - 2, n);
	for(int i = n - 2; i >= 0; i--) fi[i] = mul(i + 1, fi[i + 1], n);
}

int main(){
	scanf("%d", &n);
	if(n == 4){
		puts("1 3 2 4");
		return 0;
	}
	if(!prime(n)){
		puts("-1");
		return 0;
	}
	init();
	p[1] = 1;
	for(int i = 2; i < n; i++) p[i] = mul(i, mul(fi[i - 1], f[i - 2], n), n);
	p[n] = n;
	for(int i = 1; i <= n; i++){
		printf("%d%c", p[i], " \n"[i == n]);
	}
	return 0;
}
