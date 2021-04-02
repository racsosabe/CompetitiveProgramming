#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Notice that we can just simulate where do we put the last position of each color

	  and then check if the current distribution is valid.

	- If we use a O(n^3) DP, we only need to know if the interval checking is

	  fast enough.

	- Actually, for a fixed r, since the three positions in our DP must be different (unless they take 0 as value)

	  then we have only O(n^2) different states that will check its intervals.

	  Thus, the interval checking part has a complexity of O(n^2 * m)

	- Complexity: O(n^2 (n + m))

*/

const int N = 300 + 5;
const int MOD = 1000000000 + 7;

int n;
int m;
int x[N];
int L[N];
vector<int> Q[N];
bool vis[N][N][N];
int memo[N][N][N];

bool check(int r, int g, int b){
	int pos = max({r, g, b});
	for(auto e : Q[pos]){
		int cnt = (r >= L[e]) + (g >= L[e]) + (b >= L[e]);
		if(cnt != x[e]) return false;
	}
	return true;
}

int DP(int r, int g, int b){
	int pos = max({r, g, b});
	if(vis[r][g][b]) return memo[r][g][b];
	vis[r][g][b] = true;
	if(pos == n) return memo[r][g][b] = check(r, g, b);
	if(!check(r, g, b)) return memo[r][g][b] = 0;
	int ans = 0;
	ans += DP(pos + 1, g, b);
	if(ans >= MOD) ans -= MOD;
	ans += DP(r, pos + 1, b);
	if(ans >= MOD) ans -= MOD;
	ans += DP(r, g, pos + 1);
	if(ans >= MOD) ans -= MOD;
	return memo[r][g][b] = ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		int r;
		scanf("%d %d %d", L + i, &r, x + i);
		Q[r].emplace_back(i);
	}
	printf("%d\n", DP(0, 0, 0));
	return 0;
}
