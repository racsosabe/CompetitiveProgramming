#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;
const int N = 200000 + 5;

int n;

int main(){
	scanf("%d", &n);
	int sum = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d", &x);
		ans += (1ll * sum * x) % MOD;
		if(ans >= MOD) ans -= MOD;
		sum += x;
		if(sum >= MOD) sum -= MOD;
	}
	printf("%d\n", ans);
	return 0;
}
