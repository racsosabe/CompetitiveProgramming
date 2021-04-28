#include<bits/stdc++.h>
using namespace::std;

long long a, b, c;

int main(){
	scanf("%lld %lld %lld", &a, &b, &c);
	long long p = 1;
	for(int i = 1; i <= b; i++) p *= c;
	puts(a < p ? "Yes" : "No");
	return 0;
}
