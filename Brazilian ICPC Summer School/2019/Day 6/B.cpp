#include<bits/stdc++.h>
using namespace::std;

const int N = 50 + 5;

int n;
int siz;
int a[N];
int deg[N];
bool vis[N];
stack<int> S;
vector<int> G[2][N];

void DFS(int u, int id){
	vis[u] = true;
	for(int v : G[id][u]){
		if(vis[v]) continue;
		DFS(v, id);
	}
	if(id == 0) S.emplace(u);
	else siz++;
}

int getSCC(){
	for(int i = 0; i < n; i++){
		if(vis[i]) continue;
		DFS(i, 0);
	}
	for(int i = 0; i < n; i++) vis[i] = false;
	int ans = 0;
	while(!S.empty()){
		int u = S.top(); S.pop();
		if(vis[u]) continue;
		siz = 0;
		DFS(u, 1);
		ans += max(1, siz - 1);
	}
	return ans;
}

int solve(){
	for(int i = 0; i < n; i++){
		if(a[i] == i) continue;
		G[0][i].emplace_back(a[i]);
		G[1][a[i]].emplace_back(i);
	}
	return getSCC();
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	printf("%d\n", solve());
	return 0;
}
