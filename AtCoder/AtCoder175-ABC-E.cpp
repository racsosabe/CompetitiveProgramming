#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Apply DP simulating the path chosen but taking an extra argument for the number

	  of items left to take in the same row. Restart this count each time you go

	  down one row.

	- Complexity: O(nm)
*/

const int N = 3000 + 5;
const long long inf = 1e18;

int n;
int m;
int k;
int a[N][N];
bool vis[N][N][4];
long long memo[N][N][4];

long long DP(int x, int y, int left) {
	if(x == n and y == m) return left ? a[x][y] : 0;
	if(vis[x][y][left]) return memo[x][y][left];
	long long res = -inf;
	if(x + 1 <= n) res = max(res, (left ? a[x][y] : 0) + DP(x + 1, y, 3));
	if(y + 1 <= m) {
		if(left) res = max(res, a[x][y] + DP(x, y + 1, left - 1));
		res = max(res, DP(x, y + 1, left));
	}
	vis[x][y][left] = true;
	return memo[x][y][left] = res;
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= k; i++) {
		int r, c, v;
		scanf("%d %d %d", &r, &c, &v);
		a[r][c] = v;
	}
	printf("%lld\n", DP(1, 1, 3));
	return 0;
}
