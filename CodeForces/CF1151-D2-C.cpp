#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;

int add(int a, int b){
	return (a + b) % MOD;
}

int mul(long long a, long long b){
	return ((a % MOD) * (b % MOD)) % MOD;
}

long long l, r;

int f(long long x){
	int turn = 1;
	long long len = 1;
	long long total = 0;
	long long lenodd = 0;
	long long leneven = 0;
	while(total + len <= x){
		if(turn) lenodd += len;
		else leneven += len;
		total += len;
		len <<= 1;
		turn ^= 1;
	}
	if(turn) lenodd += x - total;
	else leneven += x - total;
	return add(mul(leneven, leneven + 1), mul(lenodd, lenodd));
}

int main(){
	scanf("%lld %lld", &l, &r);
	printf("%d\n", add(f(r), MOD - f(l - 1)));
	return 0;
}
