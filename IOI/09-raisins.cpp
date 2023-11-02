#include<bits/stdc++.h>
using namespace::std;

const int N = 50 + 5;
const long long inf = 1e18;

int n;
int m;
int a[N][N];
bool vis[N][N][N][N];
long long memo[N][N][N][N];

long long sum(int r1, int c1, int r2, int c2){
	return a[r1 - 1][c1 - 1] + a[r2][c2] - a[r2][c1 - 1] - a[r1 - 1][c2];
}

long long DP(int lx, int ly, int rx, int ry){
	if(lx == rx and ly == ry) return 0;
	if(vis[lx][ly][rx][ry]) return memo[lx][ly][rx][ry];
	long long ans = inf;
	for(int i = lx; i < rx; i++){
		ans = min(ans, sum(lx, ly, rx, ry) + DP(lx, ly, i, ry) + DP(i + 1, ly, rx, ry));
	}
	for(int i = ly; i < ry; i++){
		ans = min(ans, sum(lx, ly, rx, ry) + DP(lx, ly, rx, i) + DP(lx, i + 1, rx, ry));
	}
	vis[lx][ly][rx][ry] = true;
	return memo[lx][ly][rx][ry] = ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			scanf("%d", &a[i][j]);
			a[i][j] += a[i - 1][j];
			a[i][j] += a[i][j - 1];
			a[i][j] -= a[i - 1][j - 1];
		}
	}
	printf("%lld\n", DP(1, 1, n, m));
	return 0;
}

