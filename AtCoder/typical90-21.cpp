#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
int cnt;
bool vis[N];
stack<int> S;
long long ans;
vector<int> G[2][N];

void DFS(int u, int id, int p = -1){
	vis[u] = true;
	for(int v : G[id][u]){
		if(vis[v]) continue;
		DFS(v, id, u);
	}
	if(id == 0) S.emplace(u);
	else cnt += 1;
}

void getComponents(){
	for(int i = 1; i <= n; i++){
		if(vis[i]) continue;
		DFS(i, 0);
	}
	for(int i = 1; i <= n; i++) vis[i] = false;
	while(!S.empty()){
		int u = S.top();
		S.pop();
		if(vis[u]) continue;
		cnt = 0;
		DFS(u, 1);
		ans += 1ll * cnt * (cnt - 1) / 2;
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[0][u].emplace_back(v);
		G[1][v].emplace_back(u);
	}
	getComponents();
	printf("%lld\n", ans);
	return 0;
}
