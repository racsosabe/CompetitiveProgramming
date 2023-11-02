#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
int suma[N];
bool vis[N];
vector<int> G[N];

void DFS(int u){
	vis[u] = true;
	for(int v : G[u]){
		if(vis[v]) continue;
		DFS(v);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		suma[i] = suma[i / 10] + i % 10;
		if(i + suma[i] <= n) G[i + suma[i]].emplace_back(i);
	}
	DFS(n);
	int ans = 0;
	for(int i = 1; i <= n; i++){
		if(vis[i]) ans += 1;
	}
	printf("%d\n", ans);
	return 0;
}
