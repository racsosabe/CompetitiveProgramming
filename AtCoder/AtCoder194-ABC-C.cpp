#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;

int n;
int a[N];

int main(){
	scanf("%d", &n);
	long long ans = 0;
	int sum = 0;
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		ans += 1ll * (n - 1) * x * x;
		ans -= 2ll * sum * x;
		sum += x;
	}
	printf("%lld\n", ans);
	return 0;
}
