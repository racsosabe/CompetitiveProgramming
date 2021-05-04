#include<bits/stdc++.h>
using namespace::std;

int n;

long long solve(){
	int mitad = n / 2;
	long long ans = (2ll * (n - 1) + 1) * mitad - 2ll * mitad * (mitad - 1) - mitad;
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		printf("%lld\n", solve());
	}
	return 0;
}
