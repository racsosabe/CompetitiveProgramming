#include<bits/stdc++.h>
using namespace::std;

long long inf = 2e18 + 10;
const int MASK = 1 << 15;
const int N = 15;

int n;
int k;
int x[N];
int y[N];
long long cost[MASK];
long long memo[MASK];
long long last[MASK];

void preprocess(){
	for(int mask = 1; mask < (1 << n); mask++){
		long long cur = cost[mask & (mask - 1)];
		int at = __builtin_ctz(mask);
		for(int m = mask & (mask - 1); m > 0; m &= m - 1){
			int to = __builtin_ctz(m);
			cur = max(cur, 1ll * (x[at] - x[to]) * (x[at] - x[to]) + 1ll * (y[at] - y[to]) * (y[at] - y[to]));
		}
		cost[mask] = cur;
	}
}

long long solve(){
	int len = 1 << n;
	for(int i = 1; i < len; i++){
		last[i] = inf;
	}
	for(int step = 1; step <= k; step++){
		for(int mask = 0; mask < len; mask++){
			memo[mask] = inf;
			for(int m = mask; m > 0; m = mask & (m - 1)){
				long long cur = max(cost[m], last[mask ^ m]);
				if(memo[mask] > cur) memo[mask] = cur;
			}
		}
		for(int mask = 0; mask < len; mask++){
			last[mask] = memo[mask];
		}
	}
	return last[len - 1];
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++) scanf("%d %d", x + i, y + i);
	preprocess();
	printf("%lld\n", solve());
	return 0;
}
