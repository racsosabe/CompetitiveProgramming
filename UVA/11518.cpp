#include<bits/stdc++.h>
using namespace::std;

const int N = 10000 + 5;

int n;
int m;
int l;
bool vis[N];
vector<int> G[N];

void DFS(int u){
	vis[u] = true;
	for(int v : G[u]){
		if(vis[v]) continue;
		DFS(v);
	}
}

void clear(){
	for(int i = 1; i <= n; i++){
		G[i].clear();
		vis[i] = false;
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d", &n, &m, &l);
		for(int i = 1; i <= m; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			G[u].emplace_back(v);
		}
		for(int i = 1; i <= l; i++){
			int x;
			scanf("%d", &x);
			if(vis[x]) continue;
			DFS(x);
		}
		int ans = 0;
		for(int i = 1; i <= n; i++){
			ans += vis[i];
		}
		printf("%d\n", ans);
		clear();
	}
	return 0;
}
