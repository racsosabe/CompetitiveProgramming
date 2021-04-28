#include<bits/stdc++.h>
using namespace::std;

long long a, b, c;

long long gcd(long long a, long long b){
	while(b){
		a %= b;
		swap(a, b);
	}
	return a;
}

int main(){
	scanf("%lld %lld %lld", &a, &b, &c);
	long long mcd = gcd(a, gcd(b, c));
	printf("%lld\n", a / mcd + b / mcd + c / mcd - 3);
	return 0;
}
