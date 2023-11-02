#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;
const int D = 20 + 5;
const int inf = 1e9 + 10;

int n;
int d;
int a[N];
int prefix[N];
int memo[N][D];

int cost(int x){
	return x % 10 < 5 ? x - x % 10 : x + 10 - x % 10;
}

int main(){
	while(scanf("%d %d", &n, &d) == 2){
		for(int i = 1; i <= n; i++){
			scanf("%d", a + i);
			prefix[i] = a[i] + prefix[i - 1];
		}
		d = min(n, d + 1);
		for(int i = 1; i <= n; i++){
			memo[i][1] = cost(prefix[i]);
		}
		for(int k = 2; k <= d; k++){
			for(int i = 1; i <= n; i++){
				memo[i][k] = inf;
				for(int j = i; j >= 1; j--){
					int cur = cost(prefix[i] - prefix[j - 1]);
					memo[i][k] = min(memo[i][k], cur + memo[j - 1][k - 1]);
				}
			}
		}
		int ans = inf;
		for(int i = 1; i <= d; i++){
			ans = min(ans, memo[n][i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
