#include<bits/stdc++.h>
using namespace::std;

const int N = 15;
const int inf = 1e9;
const int MASK = 1 << 15;

int n;
int m;
int total;
int c[N][N];
int sum[N][MASK];
bool vis[N][MASK];
int memo[N][MASK];

void preprocess(){
	for(int i = 0; i < n; i++){
		for(int mask = 1; mask < 1 << n; mask++){
			int last = 31 - __builtin_clz(mask & (-mask));
			sum[i][mask] = sum[i][mask & (mask - 1)] + c[i][last];
		}
	}
}

int solve(){
	for(int mask = 0; mask < (1 << n); mask++){
		
	}
	return memo[n - 1][total];
}

int main(){
	scanf("%d %d", &n, &m);
	total = (1 << n) - 1;
	for(int i = 1; i <= m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);}
		u--; v--;
		c[u][v] = c[v][u] = w;
	}
	preprocess();
	printf("%d\n", solve());
	return 0;
}
