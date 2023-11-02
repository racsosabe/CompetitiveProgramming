#include<bits/stdc++.h>
using namespace::std;

long long gcd(long long a, long long b){
	while(b){
		a %= b;
		swap(a, b);
	}
	return a;
}

int main(){
	long long a, b;
	scanf("%lld %lld", &a, &b);
	long long mcd = gcd(a, b);
	a /= mcd;
	if(1.0L * a * b > 1000000000000000000LL + 1e-6) puts("Large");
	else printf("%lld\n", a * b);
	return 0;
}
