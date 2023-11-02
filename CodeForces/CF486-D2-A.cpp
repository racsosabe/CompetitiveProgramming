#include<bits/stdc++.h>
using namespace::std;

long long n;

int main(){
	scanf("%lld", &n);
	long long ans = n / 2;
	if(n & 1) ans -= n;
	printf("%lld\n", ans);
	return 0;
}
