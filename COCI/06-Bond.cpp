#include<bits/stdc++.h>
using namespace::std;

const int N = 25;
const int MASK = 1 << 20;

int n;
long double a[N][N];
long double memo[MASK];

long double solve(){
	for(int mask = 1; mask < 1 << n; mask++){
		int pos = n - __builtin_popcount(mask);
		memo[mask] = -1e18;
		for(int m = mask; m > 0; m &= m - 1){
			int at = 31 - __builtin_clz(m & (-m));
			memo[mask] = max(memo[mask], memo[mask ^ (1 << at)] + a[pos][at]);
		}
	}
	return memo[(1 << n) - 1];
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int x;
			scanf("%d", &x);
			a[i][j] = x == 0 ? -1e9 : log(x / 100.0);
		}
	}
	printf("%.10Lf\n", expl(solve()) * 100.0);
	return 0;
}
