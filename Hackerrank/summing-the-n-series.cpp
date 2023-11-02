#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;

long long n;

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%lld", &n);
		n %= MOD;
		printf("%lld\n", (n * n) % MOD);
	}
	return 0;
}
