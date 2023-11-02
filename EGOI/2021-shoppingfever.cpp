#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const long long inf = 1e18;

int n;
int q;
int a[N];
long long memo[N];

long long solve(){
	for(int i = 1; i <= n; i++){
		long long cur_sum = 0;
		memo[i] = inf;
		for(int j = 1; j <= 3 and j <= i; j++){
			cur_sum += a[i - j + 1];
			if(j < 3) memo[i] = min(memo[i], memo[i - j] + cur_sum * (100 - q) / 100);
			else memo[i] = min(memo[i], memo[i - j] + cur_sum - a[i - j + 1]);
		}
	}
	return memo[n];
}

int main(){
	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	printf("%lld\n", solve());
	return 0;
}
