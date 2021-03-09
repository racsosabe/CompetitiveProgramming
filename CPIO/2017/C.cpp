#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
bool vis[2][N];
int memo[2][N];
vector<int> G[N];

int DP(int u, int take){
	if(vis[take][u]) return memo[take][u];
	int res = take;
	for(int v : G[u]){
		if(take) res += min(DP(v, 0), DP(v, 1));
		else res += DP(v, 1);
	}
	vis[take][u] = true;
	return memo[take][u] = res;
}

int main(){
	scanf("%d", &n);
	for(int i = 2; i <= n; i++){
		int p;
		scanf("%d", &p);
		G[p].emplace_back(i);
	}
	printf("%d\n", min(DP(1, 0), DP(1, 1)));
	return 0;
}
