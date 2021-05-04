#include<bits/stdc++.h>
using namespace::std;

const int N = 13;

long long f[N];

void init(){
	f[0] = 1;
	for(int i = 1; i < N; i++) f[i] = i * f[i - 1];
}

long long suma(int x){
	if(x < 10) return f[x];
	return f[x % 10] + suma(x / 10);
}

int main(){
	init();
	long long ans = 0;
	for(int i = 3; i < 10000000; i++){
		if(suma(i) == i) ans += i;
	}
	printf("%lld\n", ans);
	return 0;
}
