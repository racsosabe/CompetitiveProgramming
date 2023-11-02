#include<bits/stdc++.h>
using namespace::std;

int n;

long long f(int x){
	return 1ll * x * (x + 1) / 2;
}

int main(){
	scanf("%d", &n);
	long long ans = 0;
	for(int i = 0; i < n; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		ans += f(r) - f(l - 1);
	}
	printf("%lld\n", ans);
	return 0;
}
